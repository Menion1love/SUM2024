import { vec3 } from "./mth.js";
import { mat4 } from "./mth.js";
import { Timer } from "./timer.js";

// Buffers
const pBuf = 1;
let primBuf;

// Some extern params
let canvas, gl, timeLoc, myTimer, time;

// Cube vertices
let cube = [
  // Font
  vec3(0, 0, 0),
  vec3(0.2, 0.0, 0.0),
  vec3(0.2, 0.2, 0.0),
  vec3(0.0, 0.2, 0.0),
  // Down
  vec3(0, 0, 0),
  vec3(0, 0.0, 0.2),
  vec3(0.2, 0.0, 0.2),
  vec3(0.2, 0.0, 0.0),
  // Font
  vec3(0, 0, 0),
  vec3(0.0, 0, 0.2),
  vec3(0.0, 0.2, 0.2),
  vec3(0.0, 0.2, 0.0),
  // Font
  vec3(0.2, 0.2, 0.2),
  vec3(0.2, 0.0, 0.2),
  vec3(0.2, 0, 0.0),
  vec3(0.2, 0.2, 0.0),
  // Font
  vec3(0.2, 0.2, 0.2),
  vec3(0, 0.2, 0.2),
  vec3(0, 0, 0.2),
  vec3(0.2, 0, 0.2),
  // Font
  vec3(0.2, 0.2, 0.2),
  vec3(0, 0.2, 0.2),
  vec3(0, 0.2, 0.0),
  vec3(0.2, 0.2, 0.0),
];
let cubeVerticesIndexBuffer;

export function initGL() {
  canvas = document.getElementById("myCan");
  gl = canvas.getContext("webgl2");
  gl.clearColor(0, 0, 0, 1);
  myTimer = new Timer();

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
    DrawPos = vec3(W * vec4(InPosition, 1)) * 2.0;
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
  for (let i = 0; i < 24; i++) {
    (vertexes[j] = cube[i].x),
      (vertexes[j + 1] = cube[i].y),
      (vertexes[j + 2] = cube[i].z);
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
  cubeVerticesIndexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  let cubeVertexIndices = [
    0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14,
    15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23,
  ];

  gl.bufferData(
    gl.ELEMENT_ARRAY_BUFFER,
    new Uint16Array(cubeVertexIndices),
    gl.STATIC_DRAW
  );

  // Uniform data
  timeLoc = gl.getUniformLocation(prg, "Time");

  // Primitive data buffer creation
  primBuf = gl.createBuffer();
  gl.bindBuffer(gl.UNIFORM_BUFFER, primBuf);
  gl.bufferData(gl.UNIFORM_BUFFER, 16 * 9, gl.STATIC_DRAW);

  gl.useProgram(prg);
  gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "bufW"), pBuf);
} // End of 'initGL' function

// Load and compile shader function
function loadShader(shaderType, shaderSource) {
  const shader = gl.createShader(shaderType);
  gl.shaderSource(shader, shaderSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    let buf = gl.getShaderInfoLog(shader);
    console.log("Shader compile fail: " + buf);
  }
  return shader;
} // End of 'loadShader' function

// Main render frame function
export function render() {
  // Set new params to timer
  myTimer.response();
  time = myTimer.localTime;

  // Set matrixes
  let w = mat4().mul(mat4()),
    winv = w.inverse().setTranspose(),
    wvp = mat4()
      .setRotateY(time * 45)
      .inverse();

  // Send info to shader
  let primdata = [].concat(w.toArray(), wvp.toArray(), winv.toArray());
  gl.bindBuffer(gl.UNIFORM_BUFFER, primBuf);
  gl.bufferData(gl.UNIFORM_BUFFER, new Float32Array(primdata), gl.STATIC_DRAW);
  gl.bindBufferBase(gl.UNIFORM_BUFFER, pBuf, primBuf);
  gl.uniform1f(timeLoc, time);

  // Clear depth and color
  gl.clear(gl.COLOR_BUFFER_BIT);
  gl.clear(gl.DEPTH_BUFFER_BIT);
  gl.enable(gl.DEPTH_TEST);
  gl.clearDepth(1.0);

  // Drawing
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_SHORT, 0);
} // End of 'render' function
