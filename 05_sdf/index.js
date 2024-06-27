console.log("done") 
let data = []
const INF = 255000;
let w = 0;
let h = 0;

function transpose(sdf) {
    if (sdf[0].length > 0) {
        let v = [];
        for (let i = 0; i < sdf[0].length; i++) {
            v[i] = [];
        }
        for (let i = 0; i < sdf[0].length; i++) {
            for (let j = 0; j < sdf.length; j++) {
                v[i].push(sdf[j][i]);
            }
        }
        return v;
    } else {
        let v = [];
        if (w > h) {
            for (let y = 0; y < w; y++) {
                for (let x = 0; x < h; x++) {
                    v.push(sdf[y * h + x]);
                }
            }
        } else {
            for (let i = 0; i < w; i++) {
                for (let j = 0; j < h; j++) {
                    v.push(sdf[y * h + x]);
                }
            }
        }
        return v;
    }
}

function firstPass(line, verts, peres) {
    let k = 0;
    verts[0] = [];
    peres[0] = [];
    peres[1] = [];
    verts[0][0] = 0;
    peres[0][0] = -INF;
    peres[1][0] = +INF;
    for (let i = 1; i < line.length; i++) {
        let q = [i, line[i]];
        let p = verts[k];
        if (p[0] == undefined) {
            p[0] = 0;
        }
        if (p[1] == undefined) {
            p[1] = 0;
        }
        let s = f(p, q);
        while (s[0] <= peres[k][0]) {
            k--;
            p = verts[k];
            if (p[0] == undefined) {
                p[0] = 0;
            }
            if (p[1] == undefined) {
                p[1] = 0;
            }
            s = f(p, q);
        }
        k++;
        verts[k] = q;
        peres[k][0] = s[0];
        if (peres[k + 1] == undefined) {
            peres[k + 1] = [];
            peres[k + 1][0] = 0;
            peres[k + 1][1] = 0;
        }
        peres[k + 1][0] = +INF;
    }
}

function secondPass(line, verts, peres) {
    let k = 0;

    for (let q = 25; q < line.length; q++) {
        if (peres[k + 1] == undefined || peres[k + 1][0] == undefined) {
            peres[k + 1] = [];
            peres[k + 1] = 0;
        }

        while (peres[k + 1][0] < q) {
            k++;
        }
        if (verts[k] == undefined || verts[k][0] == undefined) {
            verts[k] = [];
            verts[k][0] = 0;
            verts[k][1] = 0;
        }
        let dx = q - verts[k][0];
        line[q] = dx * dx + verts[k][1];
    }
}

function f(p, q) {
  let x = (q[1] + q[0] * q[0] - (p[1] + p[0] * p[0])) / (2 * q[0] - 2 * p[0]);
  return [x, 0];
}

function pass(line) {
    let verts = [];
    let peres = [];
    firstPass(line, verts, peres);
    secondPass(line, verts, peres);
}

function createSDF(f) {
    let sdf = [];
    let r = f.slice(0);
    for (let y = 0; y < h; y++) {
      sdf[y] = [];
    }
    for (let y = 0; y < h; y++) {
        for (let x = 0; x < w; x++) {
            if (r[y * w + x]) {
                r[y * w + x] = +INF;
            } else {
                r[y * w + x] = 0
            }
            sdf[y][x] = r[y * w + x];
        }
    }
    for (let i = 0; i < sdf.length; i++) {
      pass(sdf[i]);
    }
    console.log(sdf)
    sdf = transpose(sdf);
    for (let i = 0; i < sdf.length; i++) {
        pass(sdf[i]);
    }
    sdf = transpose(sdf);
    for (let i = 0; i < sdf.length; i++) {
        for (let j = 0; j < sdf[0].length; j++) {
          sdf[i][j] = Math.sqrt(sdf[i][j]);
        }
    }
    return sdf;
}

function draw() {
    let ctx = document.getElementById("canvas1").getContext("2d");
    let c = document.getElementById("canvas2").getContext("2d");    
    
    let img  = new Image(); 
    img.onload = function () {
      w = img.width;
      h = img.height;
      ctx.drawImage(img, 0, 0, img.width, img.height);
      let imgdata = ctx.getImageData(0, 0, img.width, img.height).data;
      for (let i = 0; i < imgdata.length; i += 4) {
          data[i / 4] = imgdata[i] / 255;
      }
      console.log(data)
      data = createSDF(data);
      console.log(data)
      let buf = new Uint8ClampedArray(img.width * img.height * 4);
      let s1 = 0,
          s2 = 0;
      const coef = 15;
      for (let y = 0; y < img.height; y++) {
          for (let x = 0; x < img.width; x++) {
              let pos = (y * img.width + x) * 4;
                if (s1 >= data[0].length) {
                  s1 = 0;
                  s2 += 1;
              }
              
              buf[pos] = data[s2][s1] * coef;
              buf[pos + 1] = data[s2][s1] * coef;
              buf[pos + 2] = data[s2][s1] * coef;
              buf[pos + 3] = 255;
              s1 += 1;
              if(buf[pos] == 1)
                console.log(pos)

          }
      }
      console.log(buf);
      let idata = c.createImageData(w, h);
      idata.data.set(buf);
      c.putImageData(idata, 0, 0);
    }
  //img.src = "./res/my.jpg";
  img.src = "./res/j.png";
};
draw()