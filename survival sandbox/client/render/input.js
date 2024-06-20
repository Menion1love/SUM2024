export function inputResponse(rnd, IsMove) {
    let up = true, down = true, left = true, right = true;  
    rnd.centerX = rnd.form[0] * 3200;
    rnd.centerY = rnd.form[1] * 1800;

    // Count land collisions 
    if (Math.round(rnd.centerY) + 16 >= 1630)
      up = false
    if (Math.round(rnd.centerY) - 16 <= 300)
      down = false
    if (Math.round(rnd.centerX) - 16 <= 200)
      left = false
    if (Math.round(rnd.centerX) + 16 >= 3050)
      right = false
    //let col = Checkchests();
    // up = col[0]
    // down = col[1]
    // left = col[2]
    // right = col[3]
    
    // Key W response
    if (!IsMove){
        if (rnd.keys["KeyW"] && up)
        if (rnd.keys["KeyS"] || rnd.keys["KeyA"] || rnd.keys["KeyD"] && down && left && right)
            rnd.form[1] += 0.11 * rnd.timer.globalDeltaTime;
        else rnd.form[1] += 0.12 * rnd.timer.globalDeltaTime;
        
        // Key S response
        if (rnd.keys["KeyS"] && down)
        if (rnd.keys["KeyW"] || rnd.keys["KeyA"] || rnd.keys["KeyD"] && up && left && right)
            rnd.form[1] -= 0.11 * rnd.timer.globalDeltaTime;
        else rnd.form[1] -= 0.12 * rnd.timer.globalDeltaTime;
        
        // Key A response
        if (rnd.keys["KeyA"] && left)
        if (rnd.keys["KeyS"] || rnd.keys["KeyW"] || rnd.keys["KeyD"] && up && down && right)
            rnd.form[0] -= 0.11 * rnd.timer.globalDeltaTime;
        else rnd.form[0] -= 0.12 * rnd.timer.globalDeltaTime;
        // Key D response 
        if (rnd.keys["KeyD"] && right)
        if (rnd.keys["KeyS"] || rnd.keys["KeyW"] || rnd.keys["KeyA"] && up && left && down)
            rnd.form[0] += 0.11 * rnd.timer.globalDeltaTime;
        else rnd.form[0] += 0.12 * rnd.timer.globalDeltaTime;
    }
    // if (rnd.keys["KeyE"] && col[4] != -1){
    //   console.log(1)
    //   openChest(col[4]);
    // }
    // // Enter response (return zoom)
    
    rnd.map.response()
    if (rnd.keys["Enter"]) rnd.zoom = 0.05;
  }