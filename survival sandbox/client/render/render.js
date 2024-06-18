import { Timer } from "./timer.js";
import { texture } from "./resourses/tex.js"

let bufID = 1;
let framebuffer
let form = [0.5, 0.5, 0.0, 0.0];
let myTimer;

export function rnd(...args) {
  return new Render(...args);
}

class Render {
  framedata = [0, 0, 0, 0];
  constructor(canvasId) {
    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2");
    this.gl = gl;
    
    this.tex = new Image()
    this.tex.src = "../res/map.png"
    this.tex = texture(this.tex, gl)

    myTimer = new Timer();
    window.addEventListener("keydown", (e) => {
      switch(e.which){
        case 87: // W
          form[1] += 0.05 * myTimer.globalDeltaTime;
          break;
        case 83: // S
          form[1] -= 0.05 * myTimer.globalDeltaTime;
          break;
        case 65: // A
          form[0] -= 0.05 * myTimer.globalDeltaTime;
          break;
        case 68: // D
          form[0] += 0.05 * myTimer.globalDeltaTime;
          break;
    }
    console.log(myTimer.globalDeltaTime)
    });
  
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

    // Shader creation
    let vs_txt = `#version 300 es
    precision highp float;
    in vec3 InPosition;
        
    out vec2 DrawPos;
    uniform float Time;
    uniform sampler2D tex1;

    uniform buf
    {
      vec4 Data; 
    };  
    
    void main( void )
    {
      gl_Position = vec4(InPosition, 1);
      DrawPos = InPosition.xy;
    }
    `;
    let fs_txt = `#version 300 es
    precision highp float;
    out vec4 OutColor;

    in vec2 DrawPos;
    uniform float Time;
    uniform sampler2D tex1;


    uniform buf
    {
      vec4 Data; 
    };  
    
    void main( void )
    {
      float zoom = 0.02;
      vec4 c = texelFetch(tex1, ivec2((DrawPos.xy * zoom + Data.xy) * vec2(3200, 1800)), 0);
      OutColor = vec4(c);
    }
    `;
    let vs = loadShader(gl.VERTEX_SHADER, vs_txt),
      fs = loadShader(gl.FRAGMENT_SHADER, fs_txt),
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
    
    this.texloc = gl.getUniformLocation(prg, "tex1")
    framebuffer = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);
  
    gl.useProgram(prg);
    gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "buf"), bufID);
    
    gl.uniform1i(this.texloc, 0);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, this.tex.id);
  }
  render() {
    const gl = this.gl;
    myTimer.response();
    this.time = myTimer.localTime;
    gl.uniform1f(this.timeLoc, this.time);
    gl.clearColor(0.5, 0.1, 0.9, 1);
    
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.bindBuffer(gl.UNIFORM_BUFFER, framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, new Float32Array(form), gl.STATIC_DRAW);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, bufID, framebuffer);
    console.log(form[0])

    

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
}
