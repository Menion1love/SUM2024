let chestmap = [];

export function loadChests() {
  let ctx = document.getElementById("colCan").getContext("2d");
  let img = new Image();

  img.src = "./client/res/chestmap.png";
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
    return chestmap;
  };
}
