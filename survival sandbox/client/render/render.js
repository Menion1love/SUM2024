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
  moneys,
  pos, end = false,
  scene,
  step = 0,
  fin = false,
  intro = 0,
  introend = 0,
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
    this.bat = new Image();
    this.img.src = "../res/minimap.png";
    this.coin.src = "../res/money.png";
    this.img1.src = "../res/ak.png";
    this.apple.src = "../res/apple.png";
    this.buter.src = "../res/buter.png";
    this.lcoin.src = "../res/lcoin.png";
    this.gapple.src = "../res/gapple.png";
    this.rope.src = "../res/rope.png";
    this.bat.src = "../res/bat.png";
    
    this.ctx.font = "50px Pixelify Sans";
    interf = false;
  }
  response(rnd) {
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
      this.ctx.fillText(`Item: `, 100, 840);
      if (ver)
        this.ctx.drawImage(this.rope, 241, 721, 200, 200);
      if (lcoin)
        this.ctx.drawImage(this.lcoin, 251, 751, 130, 130);
      if (bat)
        this.ctx.drawImage(this.bat, 251, 751, 150, 150);

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
      if (!lcoin && !fin) {
        this.ctx.fillText(`Hello my friend! If you want to get batteries,`, 500, 70)
        this.ctx.fillText(`you need to bring me the legendary coin, which `, 500, 150)
        this.ctx.fillText(`is in the dungeon!`, 500, 230);
      }
      else {
        lcoin = false; 
        fin = true; 
        bat = true;
        rnd.lcoin = false;
        this.ctx.fillText(`Oh, thank you my friend! I think you,`, 500, 70)
        this.ctx.fillText(`deserve your batteries!`, 500, 150)  
      }
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
    this.ctx.fillStyle = "#FFF";
      
  }
  response() {
    this.ctx.clearRect(0, 0, 1920, 1080);  
    if (intro == 0) {
      this.ctx.font = "100px Pixelify Sans";
      this.ctx.fillText(`Once upon a time...`, 550, 550);

      this.ctx.font = "50px Pixelify Sans";
      this.ctx.fillText(`Press Enter...`, 800, 1050);
    }
    if (introend) {
      this.ctx.font = "100px Pixelify Sans";
      this.ctx.fillText(`The end?`, 750, 550);
    }
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

    this.tex1 = new Image();
    this.tex1.src = data.texPath;
    this.tex1 = texture(this.tex1, gl);
    this.tex2 = new Image();
    this.tex2.src = "../res/secmap.png";
    this.tex2 = texture(this.tex2, gl);
    this.tex3 = new Image();
    this.tex3.src = "../res/nightmap.png";
    this.tex3 = texture(this.tex3, gl);
    
    // Add zoom (only for debug) and mouse move func
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
          if (this.moneys >= 400 && !ver && !bat)
          {
            this.moneys -= 400;
            ver = true;
            this.ver = true
          }
            
      }
    });

    // Set parameters
    this.moneys = 0;
    this.timer = new Timer();
    this.alpha = 0;
    this.step = 1;
    this.form = [0.09, 0.08, 1, 0.5];
    (this.centerX = 0.5 * 3200), (this.centerY = 0.5 * 1800);
    this.keys = data.keys;
    this.keysOld = data.keysOld;
    this.keysClick = data.keysClick;
    this.zoom = 0.05;
    this.mZ = data.mZ;
    this.pos = 0;
    this.ver = false;
    this.scene = false;
    this.lcoin = false
    this.filled = false
    this.shop = shop = false
    this.map = interRnd("interfaceCan", this.tex1.src);
    this.shot = shotRnd("introCan");
    this.chestmap = loadChests();
    this.eventctx = document.getElementById("textCan").getContext("2d");
    this.scenetime = 0;

    this.eventctx.font = "80px Pixelify Sans";
    window.addEventListener("keydown", (e) => { 
      if (e.which == 32) {
        if (!shop)
          interf = !interf;
      }
      if (e.which == 69 && (this.step == 1 || this.step == 3))
        if (this.chestmap[1800 - Math.round(centerY)][Math.round(centerX)] == 2 && !interf)
          shop = !shop, this.shop = !this.shop

      if (e.which == 13)
      {
        if (intro == 0)
          $(".introCan").animate({ opacity: "hide" }, "slow");
        intro = 1;
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
    this.texloc1 = gl.getUniformLocation(prg, "tex1");
    this.texloc2 = gl.getUniformLocation(prg, "tex2");
    this.texloc3 = gl.getUniformLocation(prg, "tex3");

    // Create uniform block
    this.framebuffer = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);

    gl.useProgram(prg);
    gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "data"), 0);

    // Create texture
    if (this.texloc1 != -1) {
      gl.uniform1i(this.texloc1, 0);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, this.tex1.id);
    }
    if (this.texloc2 != -1) {
      gl.uniform1i(this.texloc2, 1);
      gl.activeTexture(gl.TEXTURE0 + 1);
      gl.bindTexture(gl.TEXTURE_2D, this.tex2.id);
    }
    if (this.texloc3 != -1) {
      gl.uniform1i(this.texloc3, 2);
      gl.activeTexture(gl.TEXTURE0 + 2);
      gl.bindTexture(gl.TEXTURE_2D, this.tex3.id);
    }
  }
  render() {
    const gl = this.gl;
    this.timer.response();
    
    if (this.scene) {
      if (step == 0) {
        if (this.form[0] <= 0.15)
          this.form[0] += this.timer.localDeltaTime / 30, this.pos += 0.05
        else if (this.form[0] >= 0.16)
          this.form[0] -= this.timer.localDeltaTime / 30, this.pos += 0.05
        else step++
      }
      if (step == 1)
        if (this.form[1] >= 0.65)
          this.form[1] -= this.timer.localDeltaTime / 30, this.pos += 0.05
        else step++
      if (step == 2)
        if (this.form[0] >= 0.08)
          this.form[0] -= this.timer.localDeltaTime / 30, this.pos += 0.05
        else this.scenetime = this.timer.localTime, step++
      if (step == 3) {
        this.pos = 1; 
        if (this.timer.localTime - this.scenetime >= 2)
          end = true 
        if (this.timer.localTime - this.scenetime >= 4) {
          $(".introCan").animate({ opacity: "show" }, "slow");
          introend = true
        }
      }
    }
    else{   
      if (Math.round(this.timer.localTime) % 5 == 0 && block){
        if (satiety == 0 && hp > 0)
          hp -= 4
        if (satiety >= 4)
          satiety -= 4
        block = false
      }
      if (Math.round(this.timer.localTime) % 5 != 0)
        block = true
      if (intro != 0)
        inputResponse(this, interf, move, bat, ver, shop);
    }
      
    // Responses and uniform updates
    this.shot.response()   
    centerX = this.centerX;
    centerY = this.centerY;
    this.form[3] = this.zoom;
    // /this.form[3] = Math.max(Math.sin(this.timer.localTime) / 17, 0.05)
    //this.form[1] += Math.sin(this.timer.localTime) / 1000
    this.form[2] = this.step;
    form[0] = this.form[0];
    form[1] = this.form[1];
    form[2] = this.form[2];
    form[3] = this.form[3];
    moneys = this.moneys;
    pos = this.pos;
    scene = this.scene;
    lcoin = this.lcoin;
    time = this.timer.localTime;
    ver = this.ver
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
    this.end = new Image();
    this.img.src = "../res/pos2.png";
    this.img1.src = "../res/pos3.png";
    this.img2.src = "../res/pos1.png";
    this.die.src = "../res/die.png";
    this.col.src = "../res/coleni.png";
    this.end.src = "../res/end.png";
    this.startTime = 0;
  }

  render() {
    // Count and set angel
    if(move) {
      if (scene) {
        if (step == 0 || step == 1)
          {
            let dx = 960 - 1920 / 2,
            dy = 1080 - 1080 / 2,
            d = Math.sqrt(dx * dx + dy * dy),
            sine = dy / d,
            cosine = dx / d,
            a = Math.atan2(sine, cosine);
          document
            .querySelector("#manCan")
            .style.setProperty("transform", `rotate(${(a * 180) / Math.PI}deg)`);
          }
          else if (step == 2) {
            let dx = 0 - 1920 / 2,
            dy = 540 - 1080 / 2,
            d = Math.sqrt(dx * dx + dy * dy),
            sine = dy / d,
            cosine = dx / d,
            a = Math.atan2(sine, cosine);
          document
            .querySelector("#manCan")
            .style.setProperty("transform", `rotate(${(a * 180) / Math.PI}deg)`);
          }
      }
      else 
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
    if (end) {
      this.ctx.clearRect(0, 0, 64, 64);  
      this.ctx.drawImage(this.end, 16, 16, 32, 32)
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

    this.tex1 = new Image();
    this.tex1.src = data.texPath;
    this.tex1 = texture(this.tex1, gl);
    this.tex2 = new Image();
    this.tex2.src = data.texPath;
    this.tex2 = texture(this.tex2, gl);
    this.tex3 = new Image();
    this.tex3.src = "../res/nightenvi.png";
    this.tex3 = texture(this.tex3, gl);

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

    // Create uniform block
    this.framebuffer = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, this.framebuffer);
    gl.bufferData(gl.UNIFORM_BUFFER, 4 * 4, gl.STATIC_DRAW);

    gl.useProgram(prg);
    gl.uniformBlockBinding(prg, gl.getUniformBlockIndex(prg, "data"), 0);

    // Create texture
    this.texloc1 = gl.getUniformLocation(prg, "tex1");
    this.texloc2 = gl.getUniformLocation(prg, "tex2");
    this.texloc3 = gl.getUniformLocation(prg, "tex3");
    
    // Create texture
    if (this.texloc1 != -1) {
      gl.uniform1i(this.texloc1, 0);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, this.tex1.id);
    }
    if (this.texloc2 != -1) {
      gl.uniform1i(this.texloc2, 1);
      gl.activeTexture(gl.TEXTURE0 + 1);
      gl.bindTexture(gl.TEXTURE_2D, this.tex2.id);
    }
    if (this.texloc3 != -1) {
      gl.uniform1i(this.texloc3, 2);
      gl.activeTexture(gl.TEXTURE0 + 2);  
      gl.bindTexture(gl.TEXTURE_2D, this.tex3.id);
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
    this.form[2] = form[2];
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