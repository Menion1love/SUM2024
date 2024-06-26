export function letShader(...args) {
  return new shaders(...args);
}

class shaders {
  constructor(name) {
    if (name == "background") {
      this.vs_txt = this.backVS();
      this.fs_txt = this.backFS();
    }
    if (name == "man") {
      this.vs_txt = this.manVS();
      this.fs_txt = this.manFS();
    }
    if (name == "enviroment") {
      this.vs_txt = this.enviVS();
      this.fs_txt = this.enviFS();
    }
  }
  backVS() {
    return `#version 300 es
        precision highp float;
        in vec3 InPosition;
                
        out vec2 DrawPos;
        
        uniform data
        {
          vec4 Data; 
        };  
        
        void main( void )
        {
          gl_Position = vec4(InPosition, 1);
          DrawPos = InPosition.xy;
        }`;
  }
  backFS() {
    return `#version 300 es
        precision highp float;
        out vec4 OutColor;
        in vec2 DrawPos;
        
        uniform sampler2D tex1;
        uniform sampler2D tex2;
        uniform sampler2D tex3;


        uniform data
        {
            vec4 Data; 
        };  

        void main( void )
        {
            if (Data[2] == 1.0) {
              vec4 c = texelFetch(tex1, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
              OutColor = vec4(c);
            }
            if (Data[2] == 2.0) {
              vec4 c = texelFetch(tex2, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
              OutColor = vec4(c);
            }
           
            if (Data[2] == 3.0) {
              vec4 c = texelFetch(tex3, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
              OutColor = vec4(c);
            }
        }`;
  }
  enviVS() {
    return `#version 300 es
        precision highp float;
        in vec3 InPosition;
                
        out vec2 DrawPos;
        
        uniform data
        {
          vec4 Data; 
        };  
        
        void main( void )
        {
          gl_Position = vec4(InPosition, 1);
          DrawPos = InPosition.xy;
        }`;
  }
  enviFS() {
    return `#version 300 es
        precision highp float;
        out vec4 OutColor;
        in vec2 DrawPos;
        
        uniform sampler2D tex1;
        uniform sampler2D tex2;
        uniform sampler2D tex3;
        
        uniform data
        {
            vec4 Data; 
        };  

        void main( void )
        {
            if (Data[2] == 1.0) {
              vec4 c = texelFetch(tex1, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
              OutColor = vec4(c);
            }
            if (Data[2] == 3.0) {
              vec4 c = texelFetch(tex3, ivec2((DrawPos.xy * Data[3] + Data.xy) * vec2(3200, 1800)), 0);
              OutColor = vec4(c);
            }

        }`;
  }
}
