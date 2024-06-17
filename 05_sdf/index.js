console.log("done") 

let enddata = [];
const data = []
const sdf = []

function createPix(...args) {
    return new pixel(...args);
}

class pixel {
      constructor (r, g, b){
          if (r > 0 || g > 0 || b > 0)
            this.f = false;
          else
            this.f = true;
      }
    }


// function SDF() {
//   let res = 60;

//   for (let x = 1; x < data.length; x++)
//     for (let y = 1; y < data[x].length; y++) {
//       if (data[x][y].f == 0)
//       {
//         enddata[x][y].f = 0;
  
//         for (let t = y; t < y + 3; t++)
//         {
//           if (data[x][t].f !== 0)
//             enddata[x][t].f = enddata[x][t - 1].f + res;
//         }
//         for (let t = y; t > y - 3; t--)
//         {
//             if (data[x][t].f !== 0)
//               enddata[x][t].f = enddata[x][t + 1].f + res;
//         }

//       }   
//     }
 
  // for (let x = 1; x < data.length; x++)
  //   for (let y = 1; y < data[x].length; y++) {
  //     if (data[x][y].f !== 255)
  //     {
  //       enddata[y][x].f = data[y][x].f;
  
  //       for (let t = y; t < y + 3; t++)
  //       {
  //         if (data[t][x].f !== 0)
  //         enddata[t][x].f = enddata[t - 1][x].f + res;
  //       }
  //       for (let t = y; t < y - 3; t--)
  //       {
  //         if (data[t][x].f !== 0)
  //         enddata[t][x].f = enddata[t + 1][x].f + res;
  //       }

  //     }   
  //   }  
// }
function conv() {
  for (let x = 0; x < data.length; x++)
    for (let y = 0; y < data[x].length; y++) {
      sdf.push(enddata[x][y].f)
      sdf.push(enddata[x][y].f)
      sdf.push(enddata[x][y].f)
      sdf.push(255)
    }
}
function draw() {
  let ctx = document.getElementById("canvas1").getContext("2d");
  let c = document.getElementById("canvas2").getContext("2d"); 
  let img  = new Image(); 
  img.onload = function () {
    ctx.drawImage(img, 0, 0, 256, 256);   
    let k = ctx.getImageData(0, 0, 256, 256)
    let con = k.data;
    let pos = 0;
    for (let y = 0; y < 256; y++)
    {
      let s = [], g = []
      
      for (let x = 0; x < 256; x++)
      {
        g.push(createPix(2, 0, 0))
        s.push(createPix(con[pos], con[pos + 1], con[pos + 2]))
        pos += 4;    
      }  
      data.push(s)    
      enddata.push(g)
    }
    SDF()
    conv()
    for (let i = 0; i < con.length; i++)
      con[i] = sdf[i];
    c.drawImage(img, 0, 0, 256, 256);
    c.putImageData(k, 0, 0);
    
        
  }
  //img.src = "../res/my.jpg";
  img.src = "../res/j.png";
}
draw()


























//let img = new Image(); 
    //console.log(document.getElementById("canvas").getContext("2d"))
    // img.onload = function () {
    //   c.drawImage(img, 0, 0, 237, 217); 
    //   let con = c.getImageData(0, 0, 237, 217).data;
    //   console.log(con)
    //   let pos = 0;

    //   for (let x = 0; x < 237; x++)
    //     for (let y = 0; y < 237; y++)
    //     {
    //       data.push(createPix(x, y, con[pos], con[pos + 1], con[pos + 2], con[pos + 3]))
    //       pos += 4;    
    //     }      
    //   console.log(data)
    // };
    //c.strokeRect(25, 25, 100, 100);
    