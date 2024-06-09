import { rnd } from "./render.js";
import { primCreate } from "./prims.js";
import { createCube, createTrg, createCrystal } from "./figures.js";

export function main() {
  window.addEventListener("load", () => {
    const primc = primCreate(createCube());
    const primt = primCreate(createTrg());
    const primcr = primCreate(createCrystal());
    const r1 = rnd("CanCube", primc);
    const r2 = rnd("CanTriangle", primt);
    const r3 = rnd("CanCryst", primcr);
    r1.mainloop();
    r2.mainloop();
    r3.mainloop();
  });
}
