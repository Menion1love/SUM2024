import { vec3 } from "./mth.js";
// Prim create function
export function primCreate(...args) {
  return new prim(...args);
}

function Normals(vert, ind) {
  let N = [];

  for (let i = 0; i < vert.length; i++) {
    N[i] = vec3(0);
  }

  for (let i = 0; i < ind.length; i += 3) {
    let n0 = ind[i],
      n1 = ind[i + 1],
      n2 = ind[i + 2];
    let p0 = vert[n0],
      p1 = vert[n1],
      p2 = vert[n2];
    let n = p1.sub(p0).cross(p2.sub(p0)).normalize();
    N[n0] = N[n0].add(n);
    N[n1] = N[n1].add(n);
    N[n2] = N[n2].add(n);
  }

  for (let i = 0; i < N.length; i++) N[i] = N[i].normalize();
  return N;
}

// Prim class definition
class prim {
  constructor(verts) {
    this.vert = [];
    this.ind = [];
    let j = 0;
    // Create indexes
    for (let v of verts) {
      for (let t of v) this.vert.push(vec3(t));

      for (let i = 2; i < v.length; i++) {
        this.ind.push(0 + j);
        this.ind.push(i - 1 + j);
        this.ind.push(i + j);
      }
      j += v.length;
    }

    this.norm = Normals(this.vert, this.ind);
  }
}
