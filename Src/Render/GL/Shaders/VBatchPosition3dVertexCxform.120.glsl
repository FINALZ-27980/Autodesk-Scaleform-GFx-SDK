#version 120
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec4 acolor;
attribute vec4 pos;
attribute float vbatch;
varying vec4 color;
varying vec4 fucxadd;
varying vec4 fucxmul;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    

    fucxadd = vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(vbatch * 2.0 + 1.0+ 0.1)];
    
}
