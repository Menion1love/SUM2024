let isFirst = true,
  load,
  loadc = false;
let colmap = [];
let chestmap = [],
  move;

function getLoot(rnd) {
  rnd.moneys += Math.round(Math.random() * 100 + 1);
  for (let y = 0; y < 120; y++)
    for (let x = 0; x < 108; x++)
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
        if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 0) s.push(1);
        else s.push(0);
        pos += 4;
      }
      chestmap.push(s);
    }
    loadc = true;
    return chestmap;
  };
}

function setcol() {
  let ctx = document.getElementById("colCan").getContext("2d");

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
      colmap.push(s);
    }
    img1.src = "../res/water.png";
    img1.onload = function () {
      ctx.drawImage(img1, 0, 0, 3200, 1800);
    };
    load = true;
  };
  isFirst = false;
}

export function inputResponse(rnd, IsMove) {
  if (isFirst) setcol();
  move = false;
  let up = true,
    down = true,
    left = true,
    right = true;
  rnd.centerX = rnd.form[0] * 3200;
  rnd.centerY = rnd.form[1] * 1800;

  rnd.colmap = colmap;

  if (load) {
    // Count land collisions
    for (let i = 0; i < 12; i++) {
      if (
        colmap[1800 - Math.round(rnd.centerY) - i][Math.round(rnd.centerX)] == 1
      )
        up = false;
      if (
        colmap[1800 - Math.round(rnd.centerY) + i][Math.round(rnd.centerX)] == 1
      )
        down = false;
      if (
        colmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) - i] == 1
      )
        left = false;
      if (
        colmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX) + i] == 1
      )
        right = false;
      if (!up && !down && !left && !right) up = down = left = right = true;
    }
    console.log(up, down, left, right);
  }

  // Key W response
  if (!IsMove) {
    if (rnd.keys["KeyW"] && up) {
      move = true;
      if (
        rnd.keys["KeyS"] ||
        rnd.keys["KeyA"] ||
        (rnd.keys["KeyD"] && down && left && right)
      )
        rnd.form[1] += 0.041 * rnd.timer.globalDeltaTime;
      else rnd.form[1] += 0.041 * rnd.timer.globalDeltaTime;
    }
    // Key S response
    if (rnd.keys["KeyS"] && down) {
      move = true;
      if (
        rnd.keys["KeyW"] ||
        rnd.keys["KeyA"] ||
        (rnd.keys["KeyD"] && up && left && right)
      )
        rnd.form[1] -= 0.041 * rnd.timer.globalDeltaTime;
      else rnd.form[1] -= 0.041 * rnd.timer.globalDeltaTime;
    }

    // Key A response
    if (rnd.keys["KeyA"] && left) {
      move = true;
      if (
        rnd.keys["KeyS"] ||
        rnd.keys["KeyW"] ||
        (rnd.keys["KeyD"] && up && down && right)
      )
        rnd.form[0] -= 0.041 * rnd.timer.globalDeltaTime;
      else rnd.form[0] -= 0.041 * rnd.timer.globalDeltaTime;
    }
    // Key D response
    if (rnd.keys["KeyD"] && right) {
      move = true;
      if (
        rnd.keys["KeyS"] ||
        rnd.keys["KeyW"] ||
        (rnd.keys["KeyA"] && up && left && down)
      )
        rnd.form[0] += 0.041 * rnd.timer.globalDeltaTime;
      else rnd.form[0] += 0.041 * rnd.timer.globalDeltaTime;
    }
  }
  // Enter response (return zoom)
  if (rnd.map != undefined) rnd.map.response(rnd);

  if (move) rnd.pos += 0.035;
  else rnd.pos = 1;

  if (loadc)
    if (chestmap[1800 - Math.round(rnd.centerY)][Math.round(rnd.centerX)] == 1)
      if (rnd.keysClick["KeyE"]) {
        getLoot(rnd);
        console.log(rnd.moneys);
      }

  if (rnd.keys["Enter"]) rnd.zoom = 0.05;
}
