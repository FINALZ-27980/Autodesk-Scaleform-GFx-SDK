#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
in vec4 pos;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    
}
