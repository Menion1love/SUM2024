import { mat4 } from "./mth.js";
import { Timer } from "./timer.js";

// Prim create function
export function primCreate(...args) {
  return new prim(...args);
}

// Prim class definition
class prim {
  constructor(verts, inds) {
    this.vert = verts;
    this.ind = inds;
  }
}

export function rnd(...args) {
  return new Render(...args);
}

class Render {
  framedata = [0, 0, 0, 0];
  constructor(canvasId, prim) {
    this.BufNum = 1;

    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2");
    this.gl = gl;
    this.myTimer = new Timer();
    this.Trans = mat4();
    this.Inds = prim.ind;
    gl.clearColor(0, 0, 0, 1);

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
      
    out vec3 DrawPos;
    uniform float Time;

    uniform bufW
    {
      mat4 W;
      mat4 WVP;
      mat4 WInv;
    };

    void main( void )
    {
      gl_Position = WVP * vec4(InPosition, 1);
      DrawPos = vec3(W * vec4(InPosition, 1)) * 10.0;
    }
    `;
    let fs_txt = `#version 300 es
    precision highp float;
    out vec4 OutColor;

    in vec3 DrawPos;
    uniform float Time;
    

    void main( void )
    {
      OutColor = vec4(DrawPos.x, DrawPos.y, DrawPos.z, 1);
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
    const vertexes = [];
    let j = 0;
    for (let i = 0; i < prim.vert.length; i++) {
      (vertexes[j] = prim.vert[i].x),
        (vertexes[j + 1] = prim.vert[i].y),
        (vertexes[j + 2] = prim.vert[i].z);
      j += 3;
    }

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

    this.cubeVerticesIndexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.cubeVerticesIndexBuffer);
    let cubeVertexIndices = prim.ind;

    gl.bufferData(
      gl.ELEMENT_ARRAY_BUFFER,
      new Uint16Array(cubeVertexIndices),
      gl.STATIC_DRAW
    );

    // Primitive data buffer creation
    this.primBuf = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.primBuf);
    gl.bufferData(gl.UNIFORM_BUFFER, 16 * 9, gl.STATIC_DRAW);

    gl.useProgram(prg);
    gl.uniformBlockBinding(
      prg,
      gl.getUniformBlockIndex(prg, "bufW"),
      this.BufNum
    );
  }
  render(MatrWorld) {
    const gl = this.gl;
    this.myTimer.response();
    this.time = this.myTimer.localTime;

    let w = mat4().mul(MatrWorld),
      winv = w.inverse().setTranspose(),
      wvp = w.mul(mat4());
    let primdata = [].concat(w.toArray(), wvp.toArray(), winv.toArray());

    gl.bindBuffer(gl.UNIFORM_BUFFER, this.primBuf);
    gl.bufferData(
      gl.UNIFORM_BUFFER,
      new Float32Array(primdata),
      gl.STATIC_DRAW
    );
    gl.bindBufferBase(gl.UNIFORM_BUFFER, this.BufNum, this.primBuf);
    gl.uniform1f(this.timeLoc, this.time);

    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.clear(gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);
    gl.clearDepth(1.0);

    // Drawing
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.cubeVerticesIndexBuffer);
    gl.drawElements(gl.TRIANGLES, this.Inds.length, gl.UNSIGNED_SHORT, 0);
  }
  mainloop() {
    const draw = () => {
      let MatrWorld = mat4().mul(
        mat4()
          .setRotateX(60 * this.time)
          .mul(mat4().setRotateZ(60 * this.time))
      );
      // drawing
      this.render(MatrWorld);
      // animation register
      window.requestAnimationFrame(draw);
    };
    draw();
  }
}
