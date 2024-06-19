import { Timer } from "./timer.js";
import { texture } from "./resourses/tex.js"
import { letShader } from "./resourses/shd.js"

let mLx, mLy; 

let bufID = 0;

export function rnd(...args) {
  return new Render(...args);
}

class Render {
  constructor(canvasId, data) {
    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2", { alpha: true });
    this.gl = gl;
    window.addEventListener('mousewheel', (e) => {
      this.zoom += this.zoom * e.deltaY * 0.001});
    if (data.texPath) {
      this.tex = new Image()
      this.tex.src = data.texPath
      this.tex = texture(this.tex, gl)
    }
    this.timer = new Timer();
    this.type = data.type;
    this.alpha = 0;
    /// Keyboard handle
    // Load shaders
    const loadShader = (shaderType, shaderSource) => {
      const shader = gl.createShader(shaderType);
      gl.shaderSource(shader, shaderSource);
      gl.compileShader(shader);
      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        let buf = gl.getShaderInfoLog(shader);
        console.log("Shader compile fail: " + buf);
      }
      return shader;
    };
    
    window.addEventListener('mousemove', (e) => this.onMouseMove(e))
    
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;
    this.form = [0.5, 0.5, 0.5, 0.5]
    this.mZ = data.mZ
    this.mDz = data.mDz
    this.zoom = 0.015    
    gl.clearColor(0.5, 0.1, 0.9, 1);
    let shd = letShader(this.type)
    let vs = loadShader(gl.VERTEX_SHADER, shd.vs_txt),
      fs = loadShader(gl.FRAGMENT_SHADER, shd.fs_txt),
      prg = gl.createProgram();
    gl.attachShader(prg, vs);
    gl.attachShader(prg, fs);
    gl.linkProgram(prg);
    if (!gl.getProgramParameter(prg, gl.LINK_STATUS)) {
      let buf = gl.getProgramInfoLog(prg);
      console.log("Shader program link fail: " + buf);
    }

    // Vertex buffer creation
    const size = 1;
    const vertexes = [
      -size,
      size,
      0,
      -size,
      -size,
      0,
      size,
      size,
      0,
      size,
      -size,
      0,
    ];
    const posLoc = gl.getAttribLocation(prg, "InPosition");
    
    let vertexArray = gl.createVertexArray();
    gl.bindVertexArray(vertexArray);
    let vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexes), gl.STATIC_DRAW);
    if (posLoc != -1) {
      gl.vertexAttribPointer(posLoc, 3, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(posLoc);
    }
    
    this.timeLoc = gl.getUniformLocation(prg, "Time");
    
    this.texloc = gl.getUniformLocation(prg, "tex")
    
    this.framebuffer = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);
  
    gl.useProgram(prg);
    gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "data"), 0);
    if (this.texloc != -1 && (data.texPath != 0)) {
      gl.uniform1i(this.texloc, 0);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, this.tex.id);
    }
  }
  render() {
    const gl = this.gl;
    
    let dx = mLx - 60 - 1920 / 4, dy = mLy - 30 - 1080 / 4, d = Math.sqrt(dx * dx + dy * dy), sine = dy / d, cosine = dx / d, a = Math.atan2(sine, cosine)
    this.form[3] = this.zoom + this.mZ
    this.timer.response();
    this.inputResponse()
    this.time = this.timer.localTime;
    gl.uniform1f(this.timeLoc, this.time);
    document.querySelector('#manCan').style.setProperty('transform', `rotate(${a * 180 / Math.PI}deg)`)
    let w = (dx * Math.sin(a) - dx * Math.cos(a)) / 10
    console.log(mLy)
    if (mLx < 450)
      document.querySelector('#manCan').style.setProperty('left', `${w}px`)
    else 
      document.querySelector('#manCan').style.setProperty('right', `${w}px`)
    if (mLy > 250)
      document.querySelector('#manCan').style.setProperty('top', `${(dy * Math.cos(a) + dy * Math.sin(a)) / 5}px`)
    else
      document.querySelector('#manCan').style.setProperty('bottom', `${(dy * Math.cos(a) + dy * Math.sin(a)) / 5}px`)
    
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, new Float32Array(this.form), gl.STATIC_DRAW);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, bufID, this.framebuffer);
    
    // Drawing
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
  }
  mainloop() {
    const draw = () => {
      // drawing
      this.render();
      // animation register
      window.requestAnimationFrame(draw);
    };
    draw();
  }
      
  inputResponse() {
    if (this.type == "background") {
      if (this.keys["KeyW"]) 
        if (this.keys["KeyS"] || this.keys["KeyA"] || this.keys["KeyD"])
          this.form[1] += 0.007 * this.timer.globalDeltaTime
        else
          this.form[1] += 0.01 * this.timer.globalDeltaTime
      if (this.keys["KeyS"])
        if (this.keys["KeyW"] || this.keys["KeyA"] || this.keys["KeyD"])
          this.form[1] -= 0.007 * this.timer.globalDeltaTime
        else
          this.form[1] -= 0.01 * this.timer.globalDeltaTime 
      if (this.keys["KeyA"])
        if (this.keys["KeyS"] || this.keys["KeyW"] || this.keys["KeyD"])
          this.form[0] -= 0.007 * this.timer.globalDeltaTime
        else 
          this.form[0] -= 0.008 * this.timer.globalDeltaTime
      if (this.keys["KeyD"])
        if (this.keys["KeyS"] || this.keys["KeyW"] || this.keys["KeyA"])
          this.form[0] += 0.007 * this.timer.globalDeltaTime
        else 
          this.form[0] += 0.008 * this.timer.globalDeltaTime
      if (this.keys["Enter"])
        this.zoom = 0.015         
  }
}
  onMouseMove(e) {
    mLx = e.clientX
    mLy = e.clientY
  } // End of 'onMouseMove' function

}
