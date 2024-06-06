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
  len() {
    let len = this.dot(this);

    if (len == 1 || len == 0) return len;
    return Math.sqrt(len);
  }
}
