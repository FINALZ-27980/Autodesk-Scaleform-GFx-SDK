#version 150
uniform mat4 vfmuniforms[24];
in vec4 pos;
in float vbatch;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    
}
