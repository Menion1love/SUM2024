export class Prim {
    constructor (shd) {
        const size = 1;
        this.vertexes = [
          -size,
          size,
          0,
          -size,
          -size,
          0,
          size,
          size,
          0,
          size,
          -size,
          0,
        ];
        
        this.shd = shd;
        this.loaded = false;
        if (this.shd.prg != null)
            this.loaded = true;

        
        this.vertexArrayId = shd.rnd.gl.createVertexArray();
        shd.rnd.gl.bindVertexArray(this.vertexArrayId);
        this.vertexBufferId = shd.rnd.gl.createBuffer();

        shd.rnd.gl.bindBuffer(shd.rnd.gl.ARRAY_BUFFER, this.vertexBufferId);
        shd.rnd.gl.bufferData(shd.rnd.gl.ARRAY_BUFFER, new Float32Array(this.vertexes), shd.rnd.gl.STATIC_DRAW);

        if (this.posLoc != -1 && this.normLoc != -1) {
            shd.rnd.gl.vertexAttribPointer(shd.posLoc, 3, shd.rnd.gl.FLOAT, false, 0, 0);
            shd.rnd.gl.enableVertexAttribArray(shd.posLoc);
        }
    }

    render() {
        // Recreating primitive if it wasn't created
        // (because of shader async initialization)
        if (this.shd.prg != null && this.loaded == false) {
            this.create(this.shd);
            this.loaded = true;
        }

        // Drawing primitive if shader is loaded
        this.shd.rnd.gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    }
}