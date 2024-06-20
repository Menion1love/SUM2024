import { Timer } from "./timer.js";
import { texture } from "./resourses/tex.js";
import { letShader } from "./resourses/shd.js";
import { genChestCoords, Checkchests } from "./game/chests.js";
import { inputResponse } from "./input.js";

let mLx, mLy, centerX, centerY, interf;
let chestCoords;

let bufID = 0;

export function rnd(...args) {
  return new backRender(...args);
}

export function interRnd(...args) {
  return new InterRender(...args) 
}

class InterRender {
  constructor (canvasId) {
    this.can = document.getElementById(canvasId)
    this.ctx = this.can.getContext('2d');
    this.img = new Image(); 
    this.img.src = "../res/new map.png";
    interf = false;
  }
  response() {
    this.ctx.clearRect(0, 0, 1600, 900);
    if (interf) {
      document
      .querySelector("#interfaceCan")
      .style.setProperty("background", `rgba(212, 212, 212, 0.5)`);
      document
      .querySelector("#interfaceCan")
      .style.setProperty("border", `1px solid black`);
      this.ctx.drawImage(this.img, 5, 0, 640, 480);
      this.ctx.fillStyle = 'rgba(1, 1, 0, 0.5)';
      this.ctx.strokeStyle = '#000';
      this.ctx.beginPath();
      this.ctx.fillRect(centerX / 3200 * 640, (1800 - centerY) / 1800 * 580, 3, 5)
      
      for (let j = 0; j < 10; j++)    {  
        this.ctx.strokeRect(100 * j, 790, 100 * j + 100, 100)
        this.ctx.fillRect(100 * j + 1, 790 + 1, 100 * j + 100, 100 - 1)
      }
      this.ctx.fill(); 
    }
    else {
      document
      .querySelector("#interfaceCan")
      .style.setProperty("border", `0px`);
      document
      .querySelector("#interfaceCan")
      .style.setProperty("background", `rgba(212, 212, 212, 0.0)`);
      
      
    }
  }
}

// Load shaders function
function loadShader (shaderType, shaderSource, gl) {
  const shader = gl.createShader(shaderType);
  gl.shaderSource(shader, shaderSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    let buf = gl.getShaderInfoLog(shader);
    console.log("Shader compile fail: " + buf);
  }
  return shader;
};

class backRender {
  constructor(canvasId, data) {
    // Create canvas and gl
    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2", { alpha: true });
    this.gl = gl;
    gl.clearColor(0.5, 0.1, 0.9, 1);

    this.tex = new Image();
    this.tex.src = data.texPath;
    this.tex = texture(this.tex, gl);
    

    // Add zoom (only for debug) and mouse move func
    window.addEventListener("mousewheel", (e) => {
      this.zoom += this.zoom * e.deltaY * 0.001;
    });
    window.addEventListener("mousemove", (e) => {
      mLx = e.pageX;
      mLy = e.pageY;
    });

    // Set parameters
    this.timer = new Timer();
    this.alpha = 0;
    this.form = [0.5, 0.5, 0.5, 0.5];
    this.centerX = 0.5 * 3200, this.centerY = 0.5 * 1800
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;
    this.zoom = 0.05
    this.mZ = data.mZ;
    
    
    this.map = interRnd("interfaceCan", this.tex.src)
    chestCoords = genChestCoords()
      
    window.addEventListener("keydown", (e) => {
      if (e.which == 32) {
        interf = !interf;
      }
    })
    
    // Create shaders
    let shd = letShader("background");
    let vs = loadShader(gl.VERTEX_SHADER, shd.vs_txt, gl),
      fs = loadShader(gl.FRAGMENT_SHADER, shd.fs_txt, gl),
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
    this.texloc = gl.getUniformLocation(prg, "tex");

    // Create uniform block
    this.framebuffer = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);

    gl.useProgram(prg);
    gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "data"), 0);
    
    // Create texture
    if (this.texloc != -1) {
      gl.uniform1i(this.texloc, 0);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, this.tex.id);
    }
  }
  render() {
    const gl = this.gl;
    // Responses and uniform updates
    
    this.timer.response();
    
    //if (interf == false)
    inputResponse(this, interf);
    centerX = this.centerX
    centerY = this.centerY
    this.form[3] = this.zoom
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(
      gl.UNIFORM_BUFFER,
      new Float32Array(this.form),
      gl.STATIC_DRAW
    );
    gl.bindBufferBase(gl.UNIFORM_BUFFER, bufID, this.framebuffer);
    
    this.time = this.timer.localTime;
    gl.uniform1f(this.timeLoc, this.time);

    // Drawing
    gl.clear(gl.COLOR_BUFFER_BIT);
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
}


export function manRnd(...args) {
  return new manRender(...args);
}

class manRender {
  constructor (canvasId, data) {
    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2", { alpha: true });
    this.gl = gl;
    gl.clearColor(0.5, 0.1, 0.9, 1);
    
    this.tex = new Image();
    
    this.tex.src = data.texPath;
    
    this.tex = texture(this.tex, gl);
    
    // Create shaders
    let shd = letShader("man");
    let vs = loadShader(gl.VERTEX_SHADER, shd.vs_txt, gl),
      fs = loadShader(gl.FRAGMENT_SHADER, shd.fs_txt, gl),
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

    this.texloc = gl.getUniformLocation(prg, "tex");
    gl.useProgram(prg);
    
    // Create texture
    if (this.texloc != -1) {
      gl.uniform1i(this.texloc, 0);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, this.tex.id);
    }
    
  }
  
  render() {
    const gl = this.gl;
    
    // Count and set angel
    let dx = mLx - 1920 / 2,
      dy = mLy - 1080 / 2,
      d = Math.sqrt(dx * dx + dy * dy),
      sine = dy / d,
      cosine = dx / d,
      a = Math.atan2(sine, cosine);
     document
      .querySelector("#manCan")
      .style.setProperty("transform", `rotate(${(a * 180) / Math.PI}deg)`);
    // Drawing
    gl.clear(gl.COLOR_BUFFER_BIT);
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
}
