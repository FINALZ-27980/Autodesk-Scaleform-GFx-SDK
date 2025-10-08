#version 120
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec4 pos;
attribute float vbatch;
varying vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    tc.x = dot(pos, vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1 + 0.0)]);
    tc.y = dot(pos, vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1 + 1.0)]);
    
}
