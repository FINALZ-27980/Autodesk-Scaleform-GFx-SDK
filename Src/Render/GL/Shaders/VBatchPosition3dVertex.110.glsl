uniform mat4 vfmuniforms[24];
attribute vec4 acolor;
attribute vec4 pos;
attribute float vbatch;
varying vec4 color;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    
}
