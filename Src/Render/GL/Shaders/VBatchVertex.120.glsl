#version 120
uniform vec4 vfuniforms[48];
attribute vec4 acolor;
attribute vec4 pos;
attribute float vbatch;
varying vec4 color;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1 + 1.0)]);
    

    color = acolor;
    
}
