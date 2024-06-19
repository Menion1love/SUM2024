export function letShader(...args) {
    return new shaders(...args)
}


class shaders {
    constructor (name) {
        if (name == "background") {
            this.vs_txt = this.backVS()
            this.fs_txt = this.backFS()
        }
        if (name == "man") {
            this.vs_txt = this.manVS()
            this.fs_txt = this.manFS()
        }

    }
    backVS() {
        return `#version 300 es
        precision highp float;
        in vec3 InPosition;
                
        out vec2 DrawPos;
        uniform sampler2D tex;
        
        uniform data
        {
          vec4 Data; 
        };  
        
        void main( void )
        {
          gl_Position = vec4(InPosition, 1);
          DrawPos = InPosition.xy;
        }`
    }
    backFS() {
        return `#version 300 es
        precision highp float;
        out vec4 OutColor;
        in vec2 DrawPos;
        
        uniform sampler2D tex;
        
        uniform data
        {
            vec4 Data; 
        };  

        void main( void )
        {
            float zoom = 0.015;
            vec4 c = texelFetch(tex, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
            OutColor = vec4(c);
        }`
    }
    manVS() {
        return `#version 300 es
        precision highp float;
        in vec3 InPosition;
                
        out vec2 DrawPos;

        void main( void )
        {
          gl_Position = vec4(InPosition, 1);
          DrawPos = InPosition.xy;
        }`
    }
    manFS() {
        return `#version 300 es
        precision highp float;
        out vec4 OutColor;
        in vec2 DrawPos;
          
        uniform sampler2D tex;

        uniform data
        {
            vec4 Data; 
        };  

        void main( void )
        {
            float zoom = 0.1;
            vec4 c = texelFetch(tex, ivec2((DrawPos.xy + 1.0) * vec2(16, 16)), 0);
            if (c.x == 1.0 && c.y == 1.0 && c.z == 1.0)
                OutColor = vec4(0.15, 0.15, 0.15, 0);
            else
                OutColor = vec4(c.xyz, 1);
        }`
    }
}