import { rnd } from "./render.js";
import { primCreate } from "./prims.js";
import {
  createCube,
  createTrg,
  createCrystal,
  createIkosaider,
} from "./figures.js";

export function main() {
  window.addEventListener("load", () => {
    const primc = primCreate(createCube());
    const primt = primCreate(createTrg());
    const primcr = primCreate(createCrystal());
    const primiko = primCreate(createIkosaider());

    const r1 = rnd("CanCube", primc);
    const r2 = rnd("CanTriangle", primt);
    const r3 = rnd("CanCryst", primcr);
    const r4 = rnd("CanIko", primiko);

    r1.mainloop();
    r2.mainloop();
    r3.mainloop();
    r4.mainloop();
  });
}
