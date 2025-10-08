#version 150
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
in vec4 acolor;
in vec2 atc;
in vec4 pos;
in float vbatch;
out vec2 tc;
out vec4 vcolor;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

    vcolor = acolor * vfuniforms[int(vbatch * 2.0 + 1.0+ 0.1)] + vfuniforms[int(vbatch * 2.0 + 0.0+ 0.1)];
    tc = atc;
    
}
