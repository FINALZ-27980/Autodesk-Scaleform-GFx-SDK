uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec4 acolor;
attribute vec2 atc;
attribute vec4 pos;
attribute float vbatch;
varying vec2 tc;
varying vec4 vcolor;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    vcolor = acolor * vfuniforms[int(vbatch * 2.0 + 1.0+ 0.1)] + vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1)];
    tc = atc;
    
}
