let form = [0.2, 0.02, 0.3, 1];

let canvas, gl, timeLoc;

let centerX, centerY, centerXLoc, centerYLoc, zoom, zoomLoc;
const bufID = 5;
let framebuffer;

// OpenGL initialization function
export function initGL(event) {
  canvas = document.getElementById("myCan");

  canvas.addEventListener("wheel", (e) => {
    e.preventDefault();
    zoommouse(e.deltaY * 0.0007);
  });

  canvas.addEventListener("mousemove", (e) => {
    setcenter(e.clientX, e.clientY);
  });

  gl = canvas.getContext("webgl2");
  gl.clearColor(1, 1, 1, 1);
  zoom = 4.0;
  centerX = 0.0;
  centerY = 0.0;
  // Shader creation
  let vs_txt = `#version 300 es
  precision highp float;
  in vec3 InPosition;
    
  out vec2 DrawPos;
  uniform float Time;
  uniform float zoom;

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
  uniform float zoom;
  uniform float centerX;
  uniform float centerY;

  uniform buf
  {
    vec4 Data; 
  };


  float norm( vec2 Z )
  {
    return sqrt(Z.x * Z.x + Z.y * Z.y);
  } 
  
  vec2 Mull( vec2 A, vec2 B )
  {
    vec2 r;
    r.x = A.x * B.x - A.y * A.y;
    r.y = A.x * B.y + B.x * A.y;
    
    return r;
  }
  
  vec2 Add( vec2 A, vec2 B )
  {
    vec2 r;
    r.x = A.x + B.x;
    r.y = A.y + B.y;
    
    return r;
  }

  float Julia( vec2 Z, vec2 C )
  {
    float n = 0.0;
    vec2 zn = Z;
    while ((n < 256.0) && (norm(zn) < 2.0))
    {
      n++;
      zn = Add(Mull(zn, zn), C);
    }
    return n;
  }
  
  void main( void )
  {
    vec2 z = vec2(DrawPos.x * zoom + centerX, DrawPos.y * zoom + centerY);
    vec2 C = vec2(0.35 + (Data.w / 10.0) * sin(Time * Data.w), 0.38 + 0.1 * sin(Time * Data.w));
    float n = Julia(z, C);
    OutColor = vec4(n * Data.x / 5.0, n * Data.y / 5.0, n * Data.z / 5.0, 1);
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
  const size = 0.8;
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

  // Uniform data
  timeLoc = gl.getUniformLocation(prg, "Time");
  zoomLoc = gl.getUniformLocation(prg, "zoom");
  centerXLoc = gl.getUniformLocation(prg, "centerX");
  centerYLoc = gl.getUniformLocation(prg, "centerY");

  framebuffer = gl.createBuffer();
  gl.bindBuffer(gl.UNIFORM_BUFFER, framebuffer);
  gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);
  gl.useProgram(prg);
  gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "buf"), bufID);
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

  gl.bindBuffer(gl.UNIFORM_BUFFER, framebuffer);
  gl.bufferData(gl.UNIFORM_BUFFER, new Float32Array(form), gl.STATIC_DRAW);
  gl.bindBufferBase(gl.UNIFORM_BUFFER, bufID, framebuffer);

  if (timeLoc != -1) {
    const date = new Date();
    let t =
      date.getMinutes() * 60 +
      date.getSeconds() +
      date.getMilliseconds() / 1000;

    gl.uniform1f(timeLoc, t);
  }
  gl.uniform1f(centerXLoc, centerX);
  gl.uniform1f(centerYLoc, centerY);
  gl.uniform1f(zoomLoc, zoom);
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
} // End of 'render' function

// // Zomming near function
// export function zoomsub() {
//   if (zoom > 0.1) zoom -= 0.05;
//   //console.log(zoom);
// } // End of 'zoomsub' function

// // Zomming far function
// export function zoomplus() {
//   if (zoom < 10.0) zoom += 0.05;
// } // End of 'zoomsub' function

// Zomming far function
export function zoommouse(scale) {
  zoom += scale;
  if (zoom <= 0.0) zoom = 0.0;
} // End of 'zoomsub' function

// Set new center
export function setcenter(x, y) {
  centerX = x / 300.0 - 2;
  centerY = -y / 300.0 + 2;
} // End of 'setcenter' function

// // Move right function
// export function right() {
//   centerX += 0.02;
// } // End of 'right' function

// // Move left function
// export function left() {
//   centerX -= 0.02;
// } // End of 'left' function

// // Move up function
// export function up() {
//   centerY += 0.02;
// } // End of 'up' function

// // Move down function
// export function down() {
//   centerY -= 0.02;
// } // End of 'down' function

// Set color function
export function setColor(x, y, z) {
  form[0] = x;
  form[1] = y;
  form[2] = z;
} // End of 'setColor' function

// Set speed function
export function setSpeed(x) {
  form[3] = x;
} // End of 'setSpeed' function

console.log("CGSG forever!!! mylib.js imported");
