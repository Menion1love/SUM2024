import { rnd } from "./render.js";
import { primCreate } from "./prims.js";
import {
  createCube,
  createTrg,
  createCrystal,
  createIkosaider,
  createDodekaedr,
} from "./figures.js";

export function main() {
  window.addEventListener("load", () => {
    const primc = primCreate(createCube());
    const primt = primCreate(createTrg());
    const primcr = primCreate(createCrystal());
    const primiko = primCreate(createIkosaider());
    const primoct = primCreate(createDodekaedr());
    const r1 = rnd("CanCube", primc);
    const r2 = rnd("CanTriangle", primt);
    const r3 = rnd("CanCryst", primcr);
    const r4 = rnd("CanIko", primiko);
    const r5 = rnd("CanOct", primoct);

    r1.mainloop();
    r2.mainloop();
    r3.mainloop();
    r4.mainloop();
    r5.mainloop();
  });
}
