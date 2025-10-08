#version 120
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec2 atc;
attribute vec4 pos;
attribute float vbatch;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

      tc = atc;
    

    fucxadd = vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(vbatch * 2.0 + 1.0+ 0.1)];
    
}
