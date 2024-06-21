import { rnd, manRnd } from "./render/render.js"; 

function createMan(...args) {
  return new man(...args)
}

function createBack(...args) {
  return new background(...args)
}

class background {
  constructor () {
    this.type = "background"
    this.keys = [];
    this.keysOld = [];
    this.keysClick = [];
    
    this.mX = 0;
    this.mY = 0;
    this.mZ = 0;
    this.mDx = 0;
    this.mDy = 0;
    this.mDz = 0;
    this.mLx = 0;
    this.mLy = 0;
    this.texPath = "../res/fin map.png"
    window.addEventListener("keydown", (e) => this.onKeyDown(e))
    window.addEventListener("keyup",  (e) => this.onKeyUp(e));
  }
  
  onKeyDown(e) {
    this.keysOld[e.code] = this.keys[e.code];
    this.keys[e.code] = 1;
    this.keysClick[e.code] = !this.keysOld[e.code] && this.keys[e.code];
    
    this.shiftKey = e.shiftKey;
    this.altKey = e.altKey;
    this.ctrlKey = e.ctrlKey;
  } // End of 'onKeyDown' function
  
  onKeyUp(e) {
    this.keysOld[e.code] = this.keys[e.code];
    this.keys[e.code] = 0;
    this.keysClick[e.code] = 0;
 
    this.shiftKey = e.shiftKey;
    this.altKey = e.altKey;
    this.ctrlKey = e.ctrlKey;
  } // End of 'onKeyUp' function
  
}

class man {
  constructor() {
    this.texPath = "../res/man.png"
  }
  }

function main() {
  window.addEventListener("load", () => {
    const back = rnd("mainCan", createBack());
    const tip = manRnd("manCan", createMan());
    tip.mainloop(); 
    back.mainloop();
  });
}
main()    