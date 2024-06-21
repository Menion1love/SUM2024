let isFirst = true, load;
let colmap = []

function setcol () {
  let ctx = document.getElementById("colCan").getContext("2d");

  let img  = new Image();
    img.src = "../res/collisions.png"; 
    img.onload = function () {
      ctx.drawImage(img, 0, 0, 3200, 1800);   
      let k = ctx.getImageData(0, 0, 3200, 1800)
      let con = k.data;
      let pos = 0;
      for (let y = 0; y < 1800; y++)
      {
        let s = []
        for (let x = 0; x < 3200; x++) {
          if (con[pos] == 0 && con[pos + 1] == 0 && con[pos + 2] == 0)
            s.push(1)
          else 
            s.push(0) 
          pos += 4;
        }  
        colmap.push(s)
      }
      load = true
    }
  isFirst = false
}



export function inputResponse(rnd, IsMove) {
    if (isFirst)
      setcol()
    let up = true, down = true, left = true, right = true;  
    rnd.centerX = rnd.form[0] * 3200;
    rnd.centerY = rnd.form[1] * 1800;

    rnd.colmap = colmap

    if (load) {
      
    // Count land collisions 
      if (colmap[Math.round(rnd.centerY) + 3][Math.round(rnd.centerX)] == 1)
        up = false
      if (colmap[Math.round(rnd.centerY) - 3][Math.round(rnd.centerX)] == 1)
        down = false
      if (colmap[Math.round(rnd.centerY)][Math.round(rnd.centerX) - 3] == 1)
        left = false
      if (colmap[Math.round(rnd.centerY)][Math.round(rnd.centerX) + 3] == 1)
        right = false
      console.log(up, down, left, right)
    }
    //let col = Checkchests();
    // up = col[0]
    // down = col[1]
    // left = col[2]
    // right = col[3]
    
    // Key W response
    if (!IsMove){
        if (rnd.keys["KeyW"] && up)
        if (rnd.keys["KeyS"] || rnd.keys["KeyA"] || rnd.keys["KeyD"] && down && left && right)
            rnd.form[1] += 0.051 * rnd.timer.globalDeltaTime;
        else rnd.form[1] += 0.051 * rnd.timer.globalDeltaTime;
        
        // Key S response
        if (rnd.keys["KeyS"] && down)
        if (rnd.keys["KeyW"] || rnd.keys["KeyA"] || rnd.keys["KeyD"] && up && left && right)
            rnd.form[1] -= 0.051 * rnd.timer.globalDeltaTime;
        else rnd.form[1] -= 0.051 * rnd.timer.globalDeltaTime;
        
        // Key A response
        if (rnd.keys["KeyA"] && left)
        if (rnd.keys["KeyS"] || rnd.keys["KeyW"] || rnd.keys["KeyD"] && up && down && right)
            rnd.form[0] -= 0.051 * rnd.timer.globalDeltaTime;
        else rnd.form[0] -= 0.051 * rnd.timer.globalDeltaTime;
        // Key D response 
        if (rnd.keys["KeyD"] && right)
        if (rnd.keys["KeyS"] || rnd.keys["KeyW"] || rnd.keys["KeyA"] && up && left && down)
            rnd.form[0] += 0.051 * rnd.timer.globalDeltaTime;
        else rnd.form[0] += 0.051 * rnd.timer.globalDeltaTime;
    }
    // if (rnd.keys["KeyE"] && col[4] != -1){
    //   console.log(1)
    //   openChest(col[4]);
    // }
    // // Enter response (return zoom)
    
    rnd.map.response(rnd)
    if (rnd.keys["Enter"]) rnd.zoom = 0.05;
  }