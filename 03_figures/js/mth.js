export function D2R(ang) {
  return ang * (Math.PI / 180.0);
}
export function R2D(ang) {
  return (ang * 180.0) / Math.PI;
}

// Vector set function
export function vec3(...args) {
  return new _vec3(...args);
}

// Vec3 class
class _vec3 {
  // Set vector part
  constructor(x, y, z) {
    if (x == undefined) {
      this.x = 0;
      this.y = 0;
      this.z = 0;
    } else if (typeof x == "object")
      if (x.length == 3) {
        this.x = x[0];
        this.y = x[1];
        this.z = x[2];
      } else {
        this.x = x.x;
        this.y = x.y;
        this.z = x.z;
      }
    else if (y == undefined && z == undefined) {
      this.x = x;
      this.y = x;
      this.z = x;
    } else {
      this.x = x;
      this.y = y;
      this.z = z;
    }
  }
  // Vectors dot production
  dot(v) {
    return this.x * v.x + this.y * v.y + this.z * v.z;
  }
  // Division vector
  div(n) {
    if (typeof n == "number") return vec3(this.x / n, this.y / n, this.z / n);
    return vec3(this.x / n.x, this.y / n.y, this.z / n.z);
  }
  // Multiplication vector
  mul(n) {
    if (typeof n == "number") return vec3(this.x * n, this.y * n, this.z * n);
    return vec3(this.x * n.x, this.y * n.y, this.z * n.z);
  }
  // Add number
  add(n) {
    if (typeof n == "number") return vec3(this.x + n, this.y + n, this.z + n);
    return vec3(this.x + n.x, this.y + n.y, this.z + n.z);
  }
  // Subscrbtion vector
  sub(n) {
    if (typeof n == "number") return vec3(this.x - n, this.y - n, this.z - n);
    return vec3(this.x - n.x, this.y - n.y, this.z - n.z);
  }
  // Normalize vector
  normalize() {
    let len = this.dot(this);

    if (len == 1 || len == 0) return vec3(this);

    let n = Math.sqrt(len);
    return vec3(this.x / n, this.y / n, this.z / n);
  }
  neg() {
    return vec3(-this.x, -this.y, -this.z);
  }
  cross(v) {
    return vec3(
      this.y * v.z - this.z * v.y,
      this.z * v.x - this.x * v.z,
      this.x * v.y - this.y * v.x
    );
  }
  len() {
    let len = this.dot(this);

    if (len == 1 || len == 0) return len;
    return Math.sqrt(len);
  }
}

// Matrix set function
export function mat4(...args) {
  return new _mat4(...args);
}

// Matrix class
class _mat4 {
  addMethod(obj, name, func) {
    let old = obj[name];
    obj[name] = (...args) => {
      if (func.length == args.length) return func.apply(obj, args);
      else if (typeof old == "function") return old.apply(obj, args);
    };
  }
  constructor(m = null) {
    if (m == null)
      this.m = [
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],
      ];
    else if (typeof m == "object" && m.length == 4) this.m = m;
    else this.m = m.m;

    // Translate matrix
    this.addMethod(this, "translate", (dx, dy, dz) => {
      this.m = [
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, 0],
        [dx, dy, dz, 1],
      ];
      return this;
    });
    this.addMethod(this, "translate", (v) => {
      return this.translate(v.x, v.y, x.z);
    });

    // Transpose matrix
    this.addMethod(this, "transpose", () => {
      let r = mat4();
      for (let i = 0; i < 4; i++)
        for (let j = 0; j < 4; j++) r.m[i][j] = this.m[j][i];
      return r;
    });

    // Scale matrix
    this.addMethod(this, "scale", (dx, dy, dz) => {
      this.m = [
        [dx, 0, 0, 0],
        [0, dy, 0, 0],
        [0, 0, dz, 0],
        [0, 0, 0, 1],
      ];
      return this;
    });
    this.addMethod(this, "scale", (v) => {
      if (typeof v == "number") return this.scale(v, v, v);
      else return this.scale(v.x, v.y, v.z);
    });
    // Rotate matrix on x
    this.addMethod(this, "rotateX", (ang) => {
      let co = Math.cos(D2R(ang)),
        si = Math.sin(D2R(ang));
      this.m = [
        [1, 0, 0, 0],
        [0, co, si, 0],
        [0, -si, co, 0],
        [0, 0, 0, 1],
      ];
      return this;
    });
    // Rotate matrix on y
    this.addMethod(this, "rotateY", (ang) => {
      let co = Math.cos(D2R(ang)),
        si = Math.sin(D2R(ang));
      this.m = [
        [co, 0, -si, 0],
        [0, 1, 0, 0],
        [si, 0, co, 0],
        [0, 0, 0, 1],
      ];
      return this;
    });
    // Rotate matrix on z
    this.addMethod(this, "rotateZ", (ang) => {
      let co = Math.cos(D2R(ang)),
        si = Math.sin(D2R(ang));
      this.m = [
        [co, si, 0, 0],
        [-si, co, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],
      ];
      return this;
    });
    this.addMethod(this, "rotate", (angel, v) => {
      let L = D2R(angel),
        co = Math.cos(L),
        si = Math.sin(L);
      let C = v.normalize();
      let m = mat4([
        [
          co + C.x * C.x * (1 - co),
          C.x * C.y * (1 - co) + C.z * si,
          C.x * C.z * (1 - co) - C.y * si,
          0,
        ],
        [
          C.y * C.x * (1 - co) - C.z * si,
          co + C.y * C.y * (1 - co),
          C.y * C.z * (1 - co) + C.x * si,
          0,
        ],
        [
          C.z * C.x * (1 - co) + C.y * si,
          0,
          C.z * C.y * (1 - co) + C.x * si,
          co + C.z * C.z * (1 - co),
        ],
        [0, 0, 0, 1],
      ]);

      return m;
    });
    this.addMethod(this, "ortho", (l, r, b, t, n, f) => {
      this.m = [
        [2 / (r - l), 0, 0, 0],
        [0, 2 / (t - b), 0, 0],
        [0, 0, 2 / (f - n), 0],
        [-((r + l) / (r - l)), -((t + b) / (t - b)), -((f + n) / (f - n)), 1],
      ];
      return this;
    });
    this.addMethod(
      this,
      "Determ3x3",
      (m11, m12, m13, m21, m22, m23, m31, m32, m33) => {
        return (
          m11 * m22 * m33 +
          m12 * m23 * m31 +
          m13 * m21 * m32 -
          m11 * m23 * m32 -
          m12 * m21 * m33 -
          m13 * m22 * m31
        );
      }
    );
    this.addMethod(this, "determ", () => {
      return (
        this.m[0][0] *
          this.Determ3x3(
            this.m[1][1],
            this.m[1][2],
            this.m[1][3],
            this.m[2][1],
            this.m[2][2],
            this.m[2][3],
            this.m[3][1],
            this.m[3][2],
            this.m[3][3]
          ) +
        -this.m[0][1] *
          this.Determ3x3(
            this.m[1][0],
            this.m[1][2],
            this.m[1][3],
            this.m[2][0],
            this.m[2][2],
            this.m[2][3],
            this.m[3][0],
            this.m[3][2],
            this.m[3][3]
          ) +
        +this.m[0][2] *
          this.Determ3x3(
            this.m[1][0],
            this.m[1][1],
            this.m[1][3],
            this.m[2][0],
            this.m[2][1],
            this.m[2][3],
            this.m[3][0],
            this.m[3][1],
            this.m[3][3]
          ) +
        -this.m[0][3] *
          this.Determ3x3(
            this.m[1][0],
            this.m[1][1],
            this.m[1][2],
            this.m[2][0],
            this.m[2][1],
            this.m[2][2],
            this.m[3][0],
            this.m[3][1],
            this.m[3][2]
          )
      );
    });
    this.addMethod(this, "inverse", () => {
      let det = this.determ(),
        r = mat4(),
        i,
        j,
        s = [1, -1],
        p = [
          [1, 2, 3],
          [0, 2, 3],
          [0, 1, 3],
          [0, 1, 2],
        ];
      if (det == 0) return r;
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          r.m[j][i] =
            (s[(i + j) % 2] *
              this.Determ3x3(
                this.m[p[i][0]][p[j][0]],
                this.m[p[i][0]][p[j][1]],
                this.m[p[i][0]][p[j][2]],
                this.m[p[i][1]][p[j][0]],
                this.m[p[i][1]][p[j][1]],
                this.m[p[i][1]][p[j][2]],
                this.m[p[i][2]][p[j][0]],
                this.m[p[i][2]][p[j][1]],
                this.m[p[i][2]][p[j][2]]
              )) /
            det;
      return r;
    });
    this.addMethod(this, "view", (loc, at, up1) => {
      if (loc == undefined) return mat4();
      else {
        let d = vec3.normalize.sub(at, loc),
          r = vec3.normalize.cross(dir, up1),
          u = vec3.normalize.cross(right, dir);
        this.m = [
          [r.x, u.x, -d.x, 0],
          [r.y, u.y, -d.y, 0],
          [r.z, u.z, -d.z, 0],
          [-vec3.dot(loc, r), -vec3.dot(loc, u), vec3.dot(loc, d), 1],
        ];
        return this;
      }
    });
    this.addMethod(this, "frustum", (l, r, b, t, n, f) => {
      this.m = [
        [(2 * n) / (r - l), 0, 0, 0],
        [0, (2 * n) / (t - b), 0, 0],
        [(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1],
        [0, 0, -((2 * n * f) / (f - n)), 0],
      ];
      return this;
    });
  }
  mul(n) {
    if (typeof n == "number") {
      for (let i = 0; i < 4; i++) for (let j = 0; j < 4; j++) this.m[i][j] *= n;
      return this;
    } else if (typeof n == "object" && n.m.length == 4) {
      let r = mat4([
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
      ]);
      for (let i = 0; i < 4; i++)
        for (let j = 0; j < 4; j++)
          for (let k = 0; k < 4; k++) r.m[i][j] += this.m[i][k] * n.m[k][j];
      this.m = r.m;
      return this;
    }
  }
  toArray() {
    return [].concat(...this.m);
  }
}
