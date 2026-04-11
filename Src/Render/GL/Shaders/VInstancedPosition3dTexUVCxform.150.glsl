#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
in vec2 atc;
in vec4 pos;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc0;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    

      tc0 = atc;
    

    fucxadd = vfuniforms[int(gl_InstanceID * 2.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(gl_InstanceID * 2.0 + 1.0+ 0.1)];
    
}
