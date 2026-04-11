#version 120
uniform vec4 vfuniforms[192];
attribute vec4 pos;
attribute float vbatch;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(vbatch * 8.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(vbatch * 8.0 + 2.0+ 0.1 + 1.0)]);
    

    tc0.x = dot(pos, vfuniforms[int(vbatch * 8.0 + 4.0+ 0.1 + 0.0)]);
    tc0.y = dot(pos, vfuniforms[int(vbatch * 8.0 + 4.0+ 0.1 + 1.0)]);
    tc1.x = dot(pos, vfuniforms[int(vbatch * 8.0 + 4.0+ 0.1 + 2.0)]);
    tc1.y = dot(pos, vfuniforms[int(vbatch * 8.0 + 4.0+ 0.1 + 3.0)]);
    

    fucxadd = vfuniforms[int(vbatch * 8.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(vbatch * 8.0 + 1.0+ 0.1)];
    
}
