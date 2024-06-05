let
  canvas,
  gl,
  timeLoc;    
 
// OpenGL initialization function  
export function initGL() {
  canvas = document.getElementById("myCan");
  gl = canvas.getContext("webgl2");
  gl.clearColor(0, 0, 0, 1);
  
  // Shader creation
  let vs_txt =
  `#version 300 es
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
  let fs_txt =
  `#version 300 es
  precision highp float;
  out vec4 OutColor;
  
  in vec2 DrawPos;
  uniform float Time;

  #define W 1800.0
  #define H 1500.0
  #define X0 -1.0
  #define Y0 -1.0
  #define X1 1.0
  #define Y1 1.0

  float Julia( vec2 Z, vec2 C )
  {
    float n = 0.0;
    vec2 zn = Z;
    while ((n < 256.0) && (sqrt(zn.x * zn.x + zn.y * zn.y) < 2.0))
    {
      n++;
      zn = (zn * zn + C);
    }
    return n;
  }
  
  float Mandle( vec2 Z )
  {
    float n = 0.0;
    vec2 zn = Z;
    while ((n < 256.0) && (sqrt(zn.x * zn.x + zn.y * zn.y) < 2.0))
    {
      n++;
      zn = (zn * zn + Z);
    }
    return n;
  }

  void main( void )
  {
    vec2 z;
    float n;
    vec2 C = vec2(0.35, 0.39); 
    z.x = (DrawPos.x * (X1 - X0)) * 1.0 + X0;
    z.y = (DrawPos.y * (Y1 - Y0)) * 1.0 + Y0;
    n = Julia(z, C);
    OutColor = vec4(n, n / 8.0, n * 8.0, 1.0);
  }
  `;
  let
    vs = loadShader(gl.VERTEX_SHADER, vs_txt),
    fs = loadShader(gl.FRAGMENT_SHADER, fs_txt),
    prg = gl.createProgram();
  gl.attachShader(prg, vs);
  gl.attachShader(prg, fs);
  gl.linkProgram(prg);
  if (!gl.getProgramParameter(prg, gl.LINK_STATUS)) {
    let buf = gl.getProgramInfoLog(prg);
    console.log('Shader program link fail: ' + buf);
  }                                            
 
  // Vertex buffer creation
  const size = 0.8;
  const vertexes = [-size, size, 0, -size, -size, 0, size, size, 0, size, -size, 0];
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
 
  // Uniform data
  timeLoc = gl.getUniformLocation(prg, "Time");
 
  gl.useProgram(prg);
}  // End of 'initGL' function               
 
// Load and compile shader function
function loadShader(shaderType, shaderSource) {
  const shader = gl.createShader(shaderType);
  gl.shaderSource(shader, shaderSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    let buf = gl.getShaderInfoLog(shader);
    console.log('Shader compile fail: ' + buf);
  }                                            
  return shader;
} // End of 'loadShader' function
  
let x = 1;                    
 
// Main render frame function
export function render() {
  // console.log(`Frame ${x++}`);
  gl.clear(gl.COLOR_BUFFER_BIT);
                                               
  if (timeLoc != -1) {
    const date = new Date();
    let t = date.getMinutes() * 60 +
            date.getSeconds() +
            date.getMilliseconds() / 1000;
 
    gl.uniform1f(timeLoc, t);
  }
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
} // End of 'render' function
 
console.log("CGSG forever!!! mylib.js imported");