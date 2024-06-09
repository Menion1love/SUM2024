import { mat4 } from "./mth.js";
import { Timer } from "./timer.js";
let MatrWorld;

export function rnd(...args) {
  return new Render(...args);
}

function setArr(arr, l) {
  let j = 0,
    m = [];

  for (let i = 0; i < l; i++) {
    (m[j] = arr[i].x), (m[j + 1] = arr[i].y), (m[j + 2] = arr[i].z);
    j += 3;
  }

  return m;
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
    gl.clearColor(0.5, 0.1, 0.9, 1);
    this.scale = 0.3;

    this.canvas.addEventListener("wheel", (e) => {
      e.preventDefault();
      this.scale += e.deltaY * 0.0001;
      if (this.scale < 0.0) this.scale = 0.0;
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
    in vec3 InNormal;
      
    out vec3 DrawNormal;
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
      DrawPos = vec3(W * vec4(InPosition, 1));
      DrawNormal =  mat3(transpose(inverse(W))) * InNormal;
    }
    `;
    let fs_txt = `#version 300 es
    precision highp float;
    out vec4 OutColor;

    in vec3 DrawPos;
    in vec3 DrawNormal;
    uniform float Time;

    void main( void )
    {
      vec3 V = normalize(DrawPos);
      vec3 N = normalize(DrawNormal);
      vec3 L = normalize(vec3(1, 0, -1));
      vec3 color = vec3(0.8, 0.2, 0.5);
      N = faceforward(N, V, N);
      float d = length(vec3(1, 1, 1));
      float cc = 1.0, cl = 0.01, cq = 0.001; 
      float att = min(1.0, 1.0 / (cc + cl * d + cq * d * d));        
      
      color += 0.15 * max(0.0, dot(V, L));
      color += 0.01 * max(0.0, pow(dot((reflect(V, N)), L), 1.0));
      color *= att;
      
      OutColor = vec4(N, 1);
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
    const vertexes = setArr(prim.vert, prim.vert.length);

    // Normals buffer creation
    const normalsdata = setArr(prim.norm, prim.norm.length);

    const posLoc = gl.getAttribLocation(prg, "InPosition");
    let vertexArray = gl.createVertexArray();
    gl.bindVertexArray(vertexArray);
    let vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexes), gl.STATIC_DRAW);
    const normLoc = gl.getAttribLocation(prg, "InNormal");
    gl.vertexAttribPointer(normLoc, 3, gl.FLOAT, false, 0, vertexes.length);
    if (posLoc != -1) {
      gl.vertexAttribPointer(posLoc, 3, gl.FLOAT, false, 0, 0);
      gl.enableVertexAttribArray(posLoc);
      gl.enableVertexAttribArray(normLoc);
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
      winv = w.inverse().transpose(),
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
      MatrWorld = mat4().mul(
        mat4()
          .rotateX(0)
          .mul(mat4().scale(this.scale))
          .mul(
            mat4()
              .translate(0, Math.sin(this.time) / 5, 0)
              .mul(mat4().rotateZ(0))
          )
      );
      // drawing
      this.render(MatrWorld);
      // animation register
      window.requestAnimationFrame(draw);
    };
    draw();
  }
}
