#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
in vec4 acolor;
in vec2 atc;
in vec4 pos;
out vec2 tc;
out vec4 vcolor;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    

    vcolor = acolor * vfuniforms[int(gl_InstanceID * 2.0 + 1.0+ 0.1)] + vfuniforms[int(gl_InstanceID * 2.0 + 0.0+ 0.1)];
    tc = atc;
    
}
