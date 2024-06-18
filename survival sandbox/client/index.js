import { rnd } from "./render/render.js";

function main() {
  window.addEventListener("load", () => {
    const render = rnd("mainCan");
    
    render.mainloop();
  });
}
main()