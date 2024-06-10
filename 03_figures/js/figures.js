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
    // Top
    [vec3(1, h / 2, 0), v1, vec3(cos72, h / 2, sin72)],
    [vec3(-cos36, h / 2, sin36), v1, vec3(cos72, h / 2, sin72)],
    [vec3(-cos36, h / 2, sin36), v1, vec3(-cos36, h / 2, -sin36)],
    [vec3(cos72, h / 2, -sin72), v1, vec3(-cos36, h / 2, -sin36)],
    [vec3(cos72, h / 2, -sin72), v1, vec3(1, h / 2, 0)],

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

    // Bottomn
    [vec3(-1, -h / 2, 0), v2, vec3(-cos72, -h / 2, sin72)],
    [vec3(cos36, -h / 2, sin36), v2, vec3(-cos72, -h / 2, sin72)],
    [vec3(cos36, -h / 2, sin36), v2, vec3(cos36, -h / 2, -sin36)],
    [vec3(-cos72, -h / 2, -sin72), v2, vec3(cos36, -h / 2, -sin36)],
    [vec3(-cos72, -h / 2, -sin72), v2, vec3(-1, -h / 2, 0)],
  ];
  return Ikosaider;
}

export function createDodekaedr() {
  let verts = createIkosaider(),
    vert = [];

  for (let v in verts) {
    let l = vec3(0);
    for (let i = 0; i < 3; i++) {
      l = l.add(verts[v][i]);
    }
    vert.push(l.div(3));
  }
  console.log(vert);
  let dodekaidr = [
    // Top
    [
      vert[0],
      vert[1],
      vert[2],
      vert[0],
      vert[2],
      vert[3],
      vert[0],
      vert[3],
      vert[4],
    ],
    // Up sight
    [
      vert[0],
      vert[5],
      vert[6],
      vert[0],
      vert[1],
      vert[6],
      vert[1],
      vert[7],
      vert[6],
    ],
    [
      vert[1],
      vert[7],
      vert[8],
      vert[1],
      vert[2],
      vert[8],
      vert[8],
      vert[9],
      vert[2],
    ],
    [
      vert[2],
      vert[9],
      vert[10],
      vert[2],
      vert[3],
      vert[10],
      vert[10],
      vert[11],
      vert[3],
    ],
    [
      vert[3],
      vert[11],
      vert[12],
      vert[3],
      vert[4],
      vert[12],
      vert[12],
      vert[13],
      vert[4],
    ],
    [
      vert[4],
      vert[13],
      vert[14],
      vert[4],
      vert[0],
      vert[14],
      vert[14],
      vert[5],
      vert[0],
    ],
    // Bottom
    [
      vert[15],
      vert[16],
      vert[17],
      vert[15],
      vert[17],
      vert[18],
      vert[15],
      vert[18],
      vert[19],
    ],
    // Down sight
    [
      vert[15],
      vert[8],
      vert[9],
      vert[15],
      vert[19],
      vert[9],
      vert[9],
      vert[10],
      vert[19],
    ],
    [
      vert[19],
      vert[10],
      vert[11],
      vert[19],
      vert[18],
      vert[11],
      vert[11],
      vert[12],
      vert[18],
    ],
    [
      vert[18],
      vert[12],
      vert[13],
      vert[18],
      vert[17],
      vert[13],
      vert[13],
      vert[14],
      vert[17],
    ],
    [
      vert[17],
      vert[14],
      vert[5],
      vert[17],
      vert[16],
      vert[5],
      vert[5],
      vert[6],
      vert[16],
    ],
    [
      vert[16],
      vert[6],
      vert[7],
      vert[16],
      vert[15],
      vert[7],
      vert[7],
      vert[8],
      vert[15],
    ],
  ];

  return dodekaidr;
}
