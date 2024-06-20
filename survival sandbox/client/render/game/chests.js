let chests = []

export function Checkchests() {
    let s = [true, true, true, true, -1]
    for (let i = 0; i < chestCoords.length; i += 3)
    {
      if (Math.abs(Math.round(centerY) - chestCoords[i + 1]) <= 20 && Math.abs(Math.round(centerX) - chestCoords[i]) <= 20 && Math.round(centerY) < chestCoords[i + 1])
        s[0] = false
      if (Math.abs(Math.round(centerY) - chestCoords[i + 1]) <= 30 && Math.abs(Math.round(centerX) - chestCoords[i]) <= 20 && Math.round(centerY) > chestCoords[i + 1])
        s[1] = false
      if (Math.abs(Math.round(centerX) - chestCoords[i]) <= 30 && Math.abs(Math.round(centerY) - chestCoords[i + 1]) <= 20 && Math.round(centerX) > chestCoords[i])
        s[2] = false
      if (Math.abs(Math.round(centerX) - chestCoords[i]) <= 30 && Math.abs(Math.round(centerY) - chestCoords[i + 1]) <= 20 && Math.round(centerX) < chestCoords[i])
        s[3] = false
      if (s[0] == false || s[1] == false || s[2] == false || s[3] == false && s[4] == -1)
        s[4] = chestCoords[i + 2]; 
    }
    return s
}
export function genChestCoords() {
    let id = 0;
    for (let i = 0; i < 60; i += 3, id++) {
        chests[i] = Math.round(Math.abs(Math.random() * 2000 + 300))
        chests[i + 1] = Math.round(Math.abs(Math.random() * 900 + 300))
        chests[i + 2] = id
    }
    return chests   
}