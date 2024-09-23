let isFirst = true,
  load13, load2,
  loadc = false;
let colmap13 = [], colmap2 = [];
let chestmap = [],
  move;

function getLoot(rnd) {
  rnd.eventctx.fillStyle = "#FFF";    
  let r = Math.round(Math.random() * 100 + 1);
  rnd.moneys += r;
  if (rnd.filled)
    rnd.eventctx.clearRect(0, 0, 1920, 1080)
  rnd.filled = true;
  rnd.eventctx.fillText(`You reached ${r} coins`, 10, 100)
  for (let y = 0; y < 120; y++)
    for (let x = 0; x < 108; x++)
      if (chestmap[1800 - Math.round(rnd.centerY) + y - 60][
        Math.round(rnd.centerX) + x - 54
      ] == 1)
      chestmap[1800 - Math.round(rnd.centerY) + y - 60][
        Math.round(rnd.centerX) + x - 54
      ] = 0;
}

export function loadChests() {
  let ctx = document.getElementById("chestCan").getContext("2d");
  let img = new Image();

  img.src = "../res/chestmap.png";
  img.onload = function () {
    ctx.drawImage(img, 0, 0, 3200, 1800);
    let k = ctx.getImageData(0, 0, 3200, 1800);
    let con = k.data;
    let pos = 0;
    for (let y = 0; y < 1800; y++) {
      let s = [];
      for (let x = 0; x < 3200; x++) {
        if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(1)
        else if (con[pos] == 255 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(2)
        else if (con[pos] == 0 && con[pos + 1] == 255 && con[pos + 2] == 0) s.push(3)
        else if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 255) s.push(4)
        else s.push(0);
        pos += 4;
        }
      chestmap.push(s);
    }
    loadc = true;
  };
}

function setcol() {
  let ctx = document.getElementById("colCan").getContext("2d", { willReadFrequently: true });

  let img = new Image(),
    img1 = new Image();

  img.src = "../res/collisions.png";
  img.onload = function () {
    ctx.drawImage(img, 0, 0, 3200, 1800);
    let k = ctx.getImageData(0, 0, 3200, 1800);
    let con = k.data;
    let pos = 0;
    for (let y = 0; y < 1800; y++) {
      let s = [];
      for (let x = 0; x < 3200; x++) {
        if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(1);
        else s.push(0);
        pos += 4;
      }
      colmap13.push(s);
    }
    load13 = true;
    img1.src = "../res/col2.png";
    img1.onload = function () {
      ctx.drawImage(img1, 0, 0, 3200, 1800);
      let k = ctx.getImageData(0, 0, 3200, 1800);
      let con = k.data;
      let pos = 0;
      for (let y = 0; y < 1800; y++) {
        let s = [];
        for (let x = 0; x < 3200; x++) {
          if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(1);
          else if (con[pos] == 255 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(2)
            else if (con[pos] == 0 && con[pos + 1] == 255 && con[pos + 2] == 0) s.push(3)
          else s.push(0);
        pos += 4;
      }
      colmap2.push(s);
    }
    console.log(colmap2)
    load2 = true;
    };
  };
  isFirst = false;
}

export function inputResponse(rnd, IsMove, m, bat, ver, lcoin) {
  if (isFirst) setcol();
  move = false;
  let up = true,
    down = true,
    left = true,
    right = true;
  rnd.centerX = rnd.form[0] * 3200;
  rnd.centerY = rnd.form[1] * 1800;

  rnd.colmap13 = colmap13;

  if (load13 && (rnd.step == 1 || rnd.step == 3)) {
    // Count land collisions
    for (let i = 0; i < 12; i++) {
      if (
        colmap13[1800 - Math.round(rnd.centerY) - i][Math.round(rnd.centerX)] == 1
      )
        up = false;
      if (
        colmap13[1800 - Math.round(rnd.centerY) + i][Math.round(rnd.centerX)] == 1
      )
        down = false;
      if (
        colmap13[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) - i] == 1
      )
        left = false;
      if (
        colmap13[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) + i] == 1
      )
        right = false;
      if (!up && !down && !left && !right) up = down = left = right = true;
    }
  }
  if (load2 && rnd.step == 2) {
    // Count land collisions
    for (let i = 0; i < 12; i++) {
      if (
        colmap2[1800 - Math.round(rnd.centerY) - i][Math.round(rnd.centerX)] == 1
      )
        up = false;
      if (
        colmap2[1800 - Math.round(rnd.centerY) + i][Math.round(rnd.centerX)] == 1
      )
        down = false;
      if (
        colmap2[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) - i] == 1
      )
        left = false;
      if (
        colmap2[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) + i] == 1
      )
        right = false;
      if (!up && !down && !left && !right) up = down = left = right = true;
      if (colmap2[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 2)
        if (rnd.keysClick["KeyE"] && m) {
          rnd.eventctx.fillStyle = "#FFF";  
          rnd.startTime = Math.round(rnd.time)
        
          if (lcoin == false) {
            rnd.lcoin = true;
            rnd.eventctx.clearRect(0, 0, 1600, 900);
            rnd.eventctx.fillText(`You received legendary`, 10, 100)} 
            rnd.eventctx.fillText(`coin!`, 10, 200)
        }
      if (colmap2[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 3)
        if (rnd.keysClick["KeyE"] && m) {
          rnd.eventctx.fillStyle = "#FFF";  
          rnd.startTime = Math.round(rnd.time)
          
          if (rnd.lcoin == false) {
            rnd.eventctx.clearRect(0, 0, 1600, 900);
            rnd.eventctx.fillText(`I can't go whithout coin!`, 10, 100)} 
          else {
            console.log(rnd.form[0], rnd.form[1])
            rnd.form[0] = 0.7813879999999913, rnd.form[1] = 0.6966469999998476
            rnd.step = 3
        }  
      }
      
    }
  }

  // Key W response
  if (!IsMove && m && !rnd.shop) {
    if (rnd.keys["KeyW"] && up) {
      move = true;
      // if (
      //   rnd.keys["KeyS"] ||
      //   rnd.keys["KeyA"] ||
      //   (rnd.keys["KeyD"] && down && left && right)
      // )
      //   rnd.form[1] += 0.04 * rnd.timer.globalDeltaTime;
      rnd.form[1] += 0.040 * rnd.timer.globalDeltaTime;
    }
    // Key S response
    if (rnd.keys["KeyS"] && down) {
      move = true;
      // if (
      //   rnd.keys["KeyW"] ||
      //   rnd.keys["KeyA"] ||
      //   (rnd.keys["KeyD"] && up && left && right)
      // )
      //   rnd.form[1] -= 0.05 * rnd.timer.globalDeltaTime;
      rnd.form[1] -= 0.040 * rnd.timer.globalDeltaTime;
    }

    // Key A response
    if (rnd.keys["KeyA"] && left) {
      move = true;
      // if (
      //   rnd.keys["KeyS"] ||
      //   rnd.keys["KeyW"] ||
      //   (rnd.keys["KeyD"] && up && down && right)
      // )
      //   rnd.form[0] -= 0.05 * rnd.timer.globalDeltaTime;
      rnd.form[0] -= 0.040 * rnd.timer.globalDeltaTime;
    }
    // Key D response
    if (rnd.keys["KeyD"] && right) {
      move = true;
      // if (
      //   rnd.keys["KeyS"] ||
      //   rnd.keys["KeyW"] ||
      //   (rnd.keys["KeyA"] && up && left && down)
      // )
      //   rnd.form[0] += 0.05 * rnd.timer.globalDeltaTime;
      rnd.form[0] += 0.040 * rnd.timer.globalDeltaTime;
    }
  }
  // Enter response (return zoom)
  if (rnd.map != undefined) rnd.map.response(rnd);

  if (move) rnd.pos += 0.065;
  else rnd.pos = 1;

  if (loadc && (rnd.step == 1 || rnd.step == 3)) {
    rnd.chestmap = chestmap
    rnd.eventctx.fillStyle = "#FFF";    
    if (chestmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 1)
      if (rnd.keysClick["KeyE"] && m) {
        getLoot(rnd);  
        
        rnd.startTime = Math.round(rnd.time)
        console.log(rnd.moneys);
      }
    if (chestmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 4)
      if (rnd.keysClick["KeyE"] && m) {
        
        rnd.startTime = Math.round(rnd.time)
        if (ver == false) {
          rnd.eventctx.clearRect(0, 0, 1600, 900);
          rnd.eventctx.fillText(`I need a rope!`, 10, 100)}
        else {
          rnd.step = 2;
          rnd.form[0] = 0.849491000000208, rnd.form[1] = 0.7816699999997926
          rnd.ver = false
        }
      }
    if (chestmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 3)
      if (rnd.keysClick["KeyE"] && m) {
        
        rnd.startTime = Math.round(rnd.time)
        if (bat == false) {
          
          rnd.eventctx.clearRect(0, 0, 1600, 900);
          rnd.eventctx.fillText(`I need batteries!`, 10, 100)}
        else {
          rnd.scene = true
        }
      }
   
  }
  if (rnd.time - rnd.startTime >= 1.5) {
    rnd.eventctx.clearRect(0, 0, 1600, 900);
    rnd.startTime = 100000;
    rnd.filled = false
  }
  if (rnd.keys["Enter"]) rnd.zoom = 0.05;
}

