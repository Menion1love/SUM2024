import { Timer } from "./timer.js";
import { texture } from "./resourses/tex.js";
import { letShader } from "./resourses/shd.js";
import { inputResponse, loadChests } from "./input.js";

let mLx,
  mLy,
  shop, 
  block = true, 
  centerX,
  centerY,
  interf,
  move = true,
  hp = 100,
  satiety = 100,
  moneys, chests,
  pos,
  form = [0.5, 0.5, 0.5, 0.5], time = 0, bat = false, ver = false, lcoin = false;

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
    this.coin = new Image();
    this.apple = new Image();
    this.buter = new Image();
    this.lcoin = new Image();
    this.gapple = new Image();
    this.rope = new Image();
    this.img.src = "../res/minimap.png";
    this.coin.src = "../res/money.png";
    this.img1.src = "../res/ak.png";
    this.apple.src = "../res/apple.png";
    this.buter.src = "../res/buter.png";
    this.lcoin.src = "../res/lcoin.png";
    this.gapple.src = "../res/gapple.png";
    this.rope.src = "../res/rope.png";
    
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
      this.ctx.drawImage(this.coin, 1050, 0, 150, 100);
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
      this.ctx.drawImage(this.img1, 601, 721, 400, 198);

      this.ctx.fill();
    }
    else if (shop) {
      this.ctx.font = "30px Pixelify Sans";
      document
        .querySelector("#interfaceCan")
        .style.setProperty("background", `rgba(212, 212, 212, 0.5)`);
      document
        .querySelector("#interfaceCan")
        .style.setProperty("border", `1px solid black`);
      this.ctx.fillText(`Hello my friend! If you want to get batteries,`, 500, 70)
      this.ctx.fillText(`you need to bring me the legendary coin, which `, 500, 150)
      this.ctx.fillText(`is in the dungeon!`, 500, 230);
      this.ctx.font = "50px Pixelify Sans";
      this.ctx.drawImage(this.apple, 0, 0, 200, 250);
      this.ctx.drawImage(this.coin, 250, 90, 100, 80);
      this.ctx.fillText(`30`, 200, 150);
      this.ctx.strokeRect(350, 100, 120, 70)
      this.ctx.fillText(`Buy`, 360, 150);
      this.ctx.drawImage(this.buter, 30, 220, 130, 160);
      this.ctx.drawImage(this.coin, 250, 290, 100, 80);
      this.ctx.strokeRect(350, 300, 120, 70)
      this.ctx.fillText(`60`, 200, 350);
      this.ctx.fillText(`Buy`, 360, 350);
      this.ctx.drawImage(this.gapple, 30, 420, 120, 150);
      this.ctx.drawImage(this.coin, 250, 490, 100, 80);
      this.ctx.strokeRect(350, 500, 120, 70)
      
      this.ctx.fillText(`100`, 180, 550);
      this.ctx.fillText(`Buy`, 360, 550);
      this.ctx.drawImage(this.rope, 20, 620, 150, 180);
      this.ctx.drawImage(this.coin, 250, 690, 100, 80);
      this.ctx.strokeRect(350, 700, 120, 70)
      
      this.ctx.fillText(`400`, 180, 750);
      this.ctx.fillText(`Buy`, 360, 750);
      
      this.ctx.font = "50px Pixelify Sans";
      //console.log(mLx, mLy)
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
    this.ctx.clearRect(0, 0, 1920, 1080);
    this.ctx.beginPath();
    this.ctx.moveTo(0.5 * 1920, 0.5 * 1080);
    let cr = [];
    if (mLy <= 540) {
      cr[0] = 960 - 540 * (960 - mLx) / (540 - mLy);
      cr[1] = 0
      if (p[0] != cr[0] && p[1] >= 0)
        p[0] -= (960 - cr[0]) / 540 * 30, p[1] -= 30
    }
    else {
      cr[0] = 960 - 540 * (960 - mLx) / (mLy - 540);
      cr[1] = 1080;
      if (p[0] != cr[0] && p[1] <= 1090)
        p[0] -= (960 - cr[0]) / 540 * 10, p[1] += 10
    }
   
    this.ctx.fillRect(p[0], p[1], 20, 20)
    this.ctx.stroke();
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
    window.addEventListener("mousedown", (e) => {
      if (e.which == 1 && shop) {
        if (mLx >= 720 && mLy >= 190 && mLx <= 840 && mLy <= 270)
          if (this.moneys >= 30)
          {
            this.moneys -= 30;
            satiety += 20;       
            if (satiety > 100)
              satiety = 100     
          }
        if (mLx >= 720 && mLy >= 390 && mLx <= 840 && mLy <= 470)
          if (this.moneys >= 60)
          {
            this.moneys -= 60;
            satiety += 50;       
            if (satiety > 100)
              satiety = 100           
          }
        if (mLx >= 720 && mLy >= 590 && mLx <= 840 && mLy <= 670)
          if (this.moneys >= 100)
          {
            this.moneys -= 100;
            satiety += 100;      
            if (satiety > 100)
              satiety = 100
            hp += 10;            
            if (hp > 100)
              hp = 100      
          }
        if (mLx >= 720 && mLy >= 790 && mLx <= 840 && mLy <= 870)
          if (this.moneys >= 400 && !ver)
          {
            this.moneys -= 400;
            ver = true;
          }
            
      }
    });

    // Set parameters
    this.moneys = 1000;
    this.timer = new Timer();
    this.alpha = 0;
    this.form = [0.8, 0.3, 0.5, 0.5];
    (this.centerX = 0.5 * 3200), (this.centerY = 0.5 * 1800);
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;
    this.zoom = 0.05;
    this.mZ = data.mZ;
    this.pos = 0;
    
    this.shop = shop = false

    this.map = interRnd("interfaceCan", this.tex.src);
    this.shot = shotRnd("shotCan");
    this.chestmap = loadChests(chests);
    this.eventctx = document.getElementById("textCan").getContext("2d");;
    
    this.eventctx.font = "80px Pixelify Sans";
    window.addEventListener("keydown", (e) => {
      if (e.which == 32) {
        if (!shop)
          interf = !interf;
      }
      if (e.which == 69)
        if (this.chestmap[1800 - Math.round(centerY)][Math.round(centerX)] == 2 && !interf)
          shop = !shop, this.shop = !this.shop
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
    this.timer.response();
    if (Math.round(this.timer.localTime) % 5 == 0 && block){
      if (satiety == 0 && hp > 0)
        hp -= 4
      if (satiety >= 2)
        satiety -= 2
      block = false
    }
    if (Math.round(this.timer.localTime) % 5 != 0)
      block = true

    
    inputResponse(this, interf, move, bat, ver, shop);
    centerX = this.centerX;
    centerY = this.centerY;
    this.form[3] = this.zoom;
    // /this.form[3] = Math.max(Math.sin(this.timer.localTime) / 17, 0.05)
    //this.form[1] += Math.sin(this.timer.localTime) / 1000
    form[0] = this.form[0];
    form[1] = this.form[1];
    form[3] = this.form[3];
    moneys = this.moneys;
    pos = this.pos;
    time = this.timer.localTime;
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
    this.die = new Image();
    this.col = new Image();
    this.img.src = "../res/pos2.png";
    this.img1.src = "../res/pos3.png";
    this.img2.src = "../res/pos1.png";
    this.die.src = "../res/die.png";
    this.col.src = "../res/coleni.png";
    this.startTime = 0;
  }

  render() {
    // Count and set angel
    if(move) {
      if (!shop) {
        let dx = mLx - 1920 / 2,
          dy = mLy - 1080 / 2,
          d = Math.sqrt(dx * dx + dy * dy),
          sine = dy / d,
          cosine = dx / d,
          a = Math.atan2(sine, cosine);
        document
          .querySelector("#manCan")
          .style.setProperty("transform", `rotate(${(a * 180) / Math.PI}deg)`);
      }
    }
    this.ctx.clearRect(0, 0, 64, 64);
    if (Math.floor(pos) % 4 == 0 && hp > 0) this.ctx.drawImage(this.img, 16, 16, 32, 32);
    if (Math.floor(pos) % 4 == 2 && hp > 0) this.ctx.drawImage(this.img1, 16, 16, 32, 32);
    if ((Math.floor(pos) % 4 == 1 || Math.floor(pos) % 4 == 3) && hp > 0)
      this.ctx.drawImage(this.img2, 16, 16, 32, 32);
    if (hp == 0) {
      if (move)
        this.startTime = time
      move = false
      if (time - this.startTime >= 1)
        this.ctx.drawImage(this.die, 16, 16, 32, 32), shop = false, interf = false;
      else
        this.ctx.drawImage(this.col, 16, 16, 32, 32), shop = false, interf = false;
    }
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
