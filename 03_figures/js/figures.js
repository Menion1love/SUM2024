import { vec3, D2R } from "./mth.js";

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
  let s3 = Math.sqrt(3);
  let p0 = vec3(0, -1, s3),
    p1 = vec3(-1, -1, 0),
    p2 = vec3(1, -1, 0),
    p3 = vec3(0, 0.6, s3 / 3);
  let trg = [
    [p0, p1, p2],
    [p0, p2, p3],
    [p0, p1, p3],
    [p1, p2, p3],
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

export function createIkosaider() {
  let cos72 = Math.cos(D2R(72)),
    sin72 = Math.sin(D2R(72)),
    cos36 = Math.cos(D2R(36)),
    sin36 = Math.sin(D2R(36)),
    a = Math.sqrt(1 + 1 - 2 * cos72),
    x = Math.sqrt(1 + 1 - 2 * cos36),
    h = Math.sqrt(a * a - x * x),
    bt = Math.sqrt((h * h) / 4 + 1),
    v1 = vec3(0, bt, 0),
    v2 = vec3(0, -bt, 0);

  let Ikosaider = [
    // Middle
    [vec3(1, h / 2, 0), vec3(cos36, -h / 2, sin36), vec3(cos72, h / 2, sin72)],
    [
      vec3(-cos72, -h / 2, sin72),
      vec3(cos36, -h / 2, sin36),
      vec3(cos72, h / 2, sin72),
    ],
    [
      vec3(-cos72, -h / 2, sin72),
      vec3(-cos36, h / 2, sin36),
      vec3(cos72, h / 2, sin72),
    ],
    [
      vec3(-cos72, -h / 2, sin72),
      vec3(-cos36, h / 2, sin36),
      vec3(-1, -h / 2, 0),
    ],
    [
      vec3(-cos36, h / 2, -sin36),
      vec3(-cos36, h / 2, sin36),
      vec3(-1, -h / 2, 0),
    ],
    [
      vec3(-cos36, h / 2, -sin36),
      vec3(-cos72, -h / 2, -sin72),
      vec3(-1, -h / 2, 0),
    ],
    [
      vec3(-cos36, h / 2, -sin36),
      vec3(-cos72, -h / 2, -sin72),
      vec3(cos72, h / 2, -sin72),
    ],
    [
      vec3(-cos72, -h / 2, -sin72),
      vec3(cos72, h / 2, -sin72),
      vec3(cos36, -h / 2, -sin36),
    ],
    [
      vec3(cos72, h / 2, -sin72),
      vec3(cos36, -h / 2, -sin36),
      vec3(1, h / 2, 0),
    ],
    [
      vec3(cos36, -h / 2, -sin36),
      vec3(cos36, -h / 2, sin36),
      vec3(1, h / 2, 0),
    ],

    // Top
    [vec3(1, h / 2, 0), v1, vec3(cos72, h / 2, sin72)],
    [vec3(-cos36, h / 2, sin36), v1, vec3(cos72, h / 2, sin72)],
    [vec3(-cos36, h / 2, sin36), v1, vec3(-cos36, h / 2, -sin36)],
    [vec3(cos72, h / 2, -sin72), v1, vec3(-cos36, h / 2, -sin36)],
    [vec3(cos72, h / 2, -sin72), v1, vec3(1, h / 2, 0)],

    // Bottomn
    [vec3(-1, -h / 2, 0), v2, vec3(-cos72, -h / 2, sin72)],
    [vec3(cos36, -h / 2, sin36), v2, vec3(-cos72, -h / 2, sin72)],
    [vec3(cos36, -h / 2, sin36), v2, vec3(cos36, -h / 2, -sin36)],
    [vec3(-cos72, -h / 2, -sin72), v2, vec3(cos36, -h / 2, -sin36)],
    [vec3(-cos72, -h / 2, -sin72), v2, vec3(-1, -h / 2, 0)],
  ];
  return Ikosaider;
}
