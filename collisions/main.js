console.log("done") 

let enddata = [];
const data = []
const sdf = []

function createPix(...args) {
    return new pixel(...args);
}

function conv() {
  for (let x = 0; x < data.length; x++)
    for (let y = 0; y < data[x].length; y++) {
      sdf.push(data[x][y].f)
      sdf.push(data[x][y].f)
      sdf.push(data[x][y].f)
      sdf.push(255)
    }
}

class pixel {
      constructor (r, g, b){
          if (r == 0 && g == 0 && b == 0)
            this.f = 0;
          else
            this.f = 255;
      }
    }

function draw() {
  let ctx = document.getElementById("canvas1").getContext("2d");
  let c = document.getElementById("canvas2").getContext("2d"); 
  let img  = new Image(); 
  img.onload = function () {
    ctx.drawImage(img, 0, 0, 3200, 1800);   
    let k = ctx.getImageData(0, 0, 3200, 1800)
    let con = k.data;
    let pos = 0;
    console.log(con)
    for (let y = 0; y < 1800; y++)
    {
      let s = [], g = []
      
      for (let x = 0; x < 3200; x++)
      {
        g.push(createPix(2, 0, 0))
        s.push(createPix(con[pos], con[pos + 1], con[pos + 2]))
        pos += 4;    
      }  
      data.push(s)    
      enddata.push(g)
    }                  
    conv();	      
    for (let i = 0; i < con.length; i++)
      con[i] = sdf[i];
    c.drawImage(img, 0, 0, 3200, 1800);
    c.putImageData(k, 0, 0);
}
  //img.src = "../res/my.jpg";
  img.src = "collisions.png";

}
draw();