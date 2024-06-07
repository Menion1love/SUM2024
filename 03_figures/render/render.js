import { vec3 } from "./mth.js";
let canvas, gl, timeLoc;
let cube = [
  vec3(0, 0, 0),
  vec3(0.2, 0.0, 0.0),
  vec3(0.2, 0.2, 0.0),
  vec3(0.0, 0.2, 0.0),
];
let cubeVerticesIndexBuffer;

export function initGL() {
  canvas = document.getElementById("myCan");
  gl = canvas.getContext("webgl2");
  gl.clearColor(0, 0, 0, 1);

  // Shader creation
  let vs_txt = `#version 300 es
  precision highp float;
  in vec3 InPosition;
    
  out vec2 DrawPos;
  uniform float Time;
  
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
  
  void main( void )
  {
    OutColor = vec4(DrawPos.x, DrawPos.y, 1, 1);
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
  const vertexes = [
    cube[0].x,
    cube[0].y,
    cube[0].z,
    cube[1].x,
    cube[1].y,
    cube[1].z,
    cube[2].x,
    cube[2].y,
    cube[2].z,
    cube[3].x,
    cube[3].y,
    cube[3].z,
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
  cubeVerticesIndexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  let cubeVertexIndices = [0, 1, 2, 0, 2, 3];

  gl.bufferData(
    gl.ELEMENT_ARRAY_BUFFER,
    new Uint16Array(cubeVertexIndices),
    gl.STATIC_DRAW
  );

  // Uniform data
  timeLoc = gl.getUniformLocation(prg, "Time");
  gl.useProgram(prg);
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
  gl.clear(gl.COLOR_BUFFER_BIT);
  //gl.clear(gl.DEPTH_BUFFER_BIT);
  //gl.enable(gl.DEPTH_TEST);
  if (timeLoc != -1) {
    const date = new Date();
    let t =
      date.getMinutes() * 60 +
      date.getSeconds() +
      date.getMilliseconds() / 1000;

    gl.uniform1f(timeLoc, t);
  }
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);
} // End of 'render' function
