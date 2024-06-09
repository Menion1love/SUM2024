import { vec3 } from "./mth.js";

export function createCube() {
  let cube = [
    // Font
    [vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, -1), vec3(1, -1, -1)],
    // Back
    [vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, 1), vec3(1, -1, 1)],
    // Left
    [vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(-1, 1, 1), vec3(-1, -1, 1)],
    // Right
    [vec3(1, -1, -1), vec3(1, 1, -1), vec3(1, 1, 1), vec3(1, -1, 1)],
    // Bottom
    [vec3(-1, -1, -1), vec3(-1, -1, 1), vec3(1, -1, 1), vec3(1, -1, -1)],
    // Top
    [vec3(-1, 1, -1), vec3(-1, 1, 1), vec3(1, 1, 1), vec3(1, 1, -1)],
  ];
  return cube;
}

export function createTrg() {
  let p0 = vec3(-1, -1, -1),
    p1 = vec3(0, 1, 0),
    p2 = vec3(0, -1, 1),
    p3 = vec3(1, -1, -1);
  let trg = [
    [p0, p1, p2],
    [p0, p2, p3],
    [p1, p2, p3],
    [p2, p0, p3],
  ];
  return trg;
}

export function createCrystal() {
  let x = 2 / Math.sqrt(2);
  let crystal = [
    [vec3(-1, 0, -1), vec3(0, x, 0), vec3(1, 0, -1)],
    [vec3(1, 0, -1), vec3(0, x, 0), vec3(1, 0, 1)],
    [vec3(1, 0, 1), vec3(0, x, 0), vec3(-1, 0, 1)],
    [vec3(-1, 0, 1), vec3(0, x, 0), vec3(-1, 0, -1)],
    [vec3(-1, 0, -1), vec3(0, -x, 0), vec3(1, 0, -1)],
    [vec3(1, 0, -1), vec3(0, -x, 0), vec3(1, 0, 1)],
    [vec3(1, 0, 1), vec3(0, -x, 0), vec3(-1, 0, 1)],
    [vec3(-1, 0, 1), vec3(0, -x, 0), vec3(-1, 0, -1)],
  ];
  return crystal;
}
