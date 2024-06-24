import { Timer } from "./timer.js";
import { texture } from "./resourses/tex.js";
import { letShader } from "./resourses/shd.js";
import { inputResponse, loadChests } from "./input.js";

let mLx,
  mLy,
  centerX,
  centerY,
  interf,
  hp = 100,
  satiety = 100,
  moneys,
  pos,
  form = [0.5, 0.5, 0.5, 0.5];

let bullets = [];

let bufID = 0;

export function interRnd(...args) {
  return new InterRender(...args);
}

class InterRender {
  constructor(canvasId) {
    this.can = document.getElementById(canvasId);
    this.ctx = this.can.getContext("2d");
    this.img = new Image();
    this.img1 = new Image();
    this.mimg = new Image();
    this.img.src = "../res/minimap.png";
    this.mimg.src = "../res/money.png";
    this.img1.src = "../res/katana.png";
    this.ctx.font = "50px Pixelify Sans";
    interf = false;
  }
  response() {
    this.ctx.clearRect(0, 0, 1600, 900);
    if (interf) {
      // Create canvas visible
      document
        .querySelector("#interfaceCan")
        .style.setProperty("background", `rgba(212, 212, 212, 0.5)`);
      document
        .querySelector("#interfaceCan")
        .style.setProperty("border", `1px solid black`);

      // Draw minimap
      this.ctx.drawImage(this.img, 5, 0, 740, 580);
      this.ctx.drawImage(this.mimg, 1050, 0, 150, 100);
      this.ctx.beginPath();
      this.ctx.strokeStyle = "#000";
      this.ctx.fillStyle = "#FFF";

      // Create mark
      this.ctx.fillRect(
        (centerX / 3200) * 740,
        ((1800 - centerY) / 1800) * 580,
        10,
        10
      );

      // Weapon rect
      this.ctx.strokeRect(400, 750, 780, 140);

      // Hp rect
      this.ctx.strokeRect(50, 670, 1100, 60);
      this.ctx.strokeRect(50, 600, 1100, 60);

      // Hp graf
      this.ctx.fillStyle = "#F01";
      this.ctx.fillRect(50 + 1, 600 + 1, 11 * hp - 1, 58);
      this.ctx.fillStyle = "#07F";
      this.ctx.fillRect(50 + 1, 670 + 1, 11 * satiety - 1, 58);

      // Hp text
      this.ctx.fillStyle = "#000";

      this.ctx.fillText(`Coins: ${moneys}`, 800, 70);
      this.ctx.fillText(`Hp: ${hp}%`, 100, 650);
      this.ctx.fillText(`Satiety ${satiety}%`, 100, 720);

      // Weapon text and picture
      this.ctx.fillText(`Weapon: `, 100, 850);
      this.ctx.drawImage(this.img1, 401, 771, 779, 98);

      this.ctx.fill();
    } else {
      document
        .querySelector("#interfaceCan")
        .style.setProperty("border", `0px`);
      document
        .querySelector("#interfaceCan")
        .style.setProperty("background", `rgba(212, 212, 212, 0.0)`);
    }
  }
}

// function createBullet(x, y) {
//   bullets.push([x, y])
// }

export function shotRnd(...args) {
  return new shotRender(...args);
}

class shotRender {
  constructor(canvasId) {
    this.can = document.getElementById(canvasId);
    this.ctx = this.can.getContext("2d");
  }
  response() {
    //let tga = (mLy - 1080 / 2) / Math.max(1920 / 2 - mLx, 1);
    this.ctx.clearRect(0, 0, 1920, 1080);
    this.ctx.beginPath();
    this.ctx.moveTo(0.5 * 1920, 0.5 * 1080);
    this.ctx.lineTo(mLx, mLy);
    // /this.ctx.lineTo(960, 540);

    this.ctx.stroke();
    // // this.ctx.clearRect(0, 0, 1600, 900);
    // if (bullets.length != 0) {
    //   // Draw minimap
    //   this.ctx.drawImage(this.img, 5, 0, 740, 580);
    //   this.ctx.beginPath();
    //   this.ctx.strokeStyle = '#000';
    //   this.ctx.fillStyle = '#FFF';

    //   // Create mark
    //   this.ctx.fillRect(centerX / 3200 * 740, (1800 - centerY) / 1800 * 580, 10, 10)

    //   // Weapon rect
    //   this.ctx.strokeRect(400, 750, 780, 140)

    //   // Hp rect
    //   this.ctx.strokeRect(50, 670, 1100, 60)
    //   this.ctx.strokeRect(50, 600, 1100, 60)

    //   // Hp graf
    //   this.ctx.fillStyle = '#F01';
    //   this.ctx.fillRect(50 + 1, 600 + 1, 11 * hp - 1, 58)
    //   this.ctx.fillStyle = '#07F';
    //   this.ctx.fillRect(50 + 1, 670 + 1, 11 * satiety - 1, 58)

    //   // Hp text
    //   this.ctx.fillStyle = '#000';
    //   this.ctx.fillText(`Hp: ${hp}%`, 100, 650);
    //   this.ctx.fillText(`Satiety ${satiety}%`, 100, 720);

    //   // Weapon text and picture
    //   this.ctx.fillText(`Weapon: `, 100, 850);
    //   this.ctx.drawImage(this.img1, 401, 771, 779, 98);

    //   this.ctx.fill();

    // }
    // else {
    //   document
    //   .querySelector("#interfaceCan")
    //   .style.setProperty("border", `0px`);
    //   document
    //   .querySelector("#interfaceCan")
    //   .style.setProperty("background", `rgba(212, 212, 212, 0.0)`);

    // }
  }
}

// Load shaders function
function loadShader(shaderType, shaderSource, gl) {
  const shader = gl.createShader(shaderType);
  gl.shaderSource(shader, shaderSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    let buf = gl.getShaderInfoLog(shader);
    console.log("Shader compile fail: " + buf);
  }
  return shader;
}

export function rnd(...args) {
  return new backRender(...args);
}

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
    this.moneys = 0;
    this.timer = new Timer();
    this.alpha = 0;
    this.form = [0.5, 0.5, 0.5, 0.5];
    (this.centerX = 0.5 * 3200), (this.centerY = 0.5 * 1800);
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;
    this.zoom = 0.05;
    this.mZ = data.mZ;
    this.pos = 0;

    this.map = interRnd("interfaceCan", this.tex.src);
    this.shot = shotRnd("shotCan");
    this.chestmap = loadChests();

    window.addEventListener("keydown", (e) => {
      if (e.which == 32) {
        interf = !interf;
      }
    });
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
    this.shot.response();
    this.timer.response();
    //if (interf == false)
    inputResponse(this, interf);
    centerX = this.centerX;
    centerY = this.centerY;
    this.form[3] = this.zoom;
    form[0] = this.form[0];
    form[1] = this.form[1];
    form[3] = this.form[3];
    moneys = this.moneys;
    pos = this.pos;
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
  constructor(canvasId) {
    this.can = document.getElementById(canvasId);
    this.ctx = this.can.getContext("2d");
    this.img = new Image();
    this.img1 = new Image();
    this.img2 = new Image();
    this.img.src = "../res/pos2.png";
    this.img1.src = "../res/pos3.png";
    this.img2.src = "../res/pos1.png";
  }

  render() {
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
    this.ctx.clearRect(0, 0, 32, 32);
    if (Math.floor(pos) % 4 == 0) this.ctx.drawImage(this.img, 0, 0, 32, 32);
    if (Math.floor(pos) % 4 == 2) this.ctx.drawImage(this.img1, 0, 0, 32, 32);
    if (Math.floor(pos) % 4 == 1 || Math.floor(pos) % 4 == 3)
      this.ctx.drawImage(this.img2, 0, 0, 32, 32);
    // Drawing
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

export function enviRnd(...args) {
  return new enviRender(...args);
}

class enviRender {
  constructor(canvasId, data) {
    // Create canvas and gl
    this.canvas = document.getElementById(canvasId);
    let gl = this.canvas.getContext("webgl2", { alpha: true });
    this.gl = gl;
    gl.clearColor(0.5, 0.1, 0.9, 1);

    this.tex = new Image();
    this.tex.src = data.texPath;
    this.tex = texture(this.tex, gl);

    // Set parameters
    this.timer = new Timer();

    this.form = [0.5, 0.5, 0.5, 0.5];

    (this.centerX = 0.5 * 3200), (this.centerY = 0.5 * 1800);
    this.zoom = 0.05;
    this.mZ = data.mZ;
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;

    // Create shaders
    let shd = letShader("enviroment");
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
    //inputResponse(this, interf);
    this.form[0] = form[0];
    this.form[1] = form[1];
    this.form[3] = form[3];
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(
      gl.UNIFORM_BUFFER,
      new Float32Array(this.form),
      gl.STATIC_DRAW
    );
    gl.bindBufferBase(gl.UNIFORM_BUFFER, bufID, this.framebuffer);

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
