#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[144];
in vec4 afactor;
in vec4 pos;
out vec4 factor;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc0;
out vec2 tc1;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    

    tc0.x = dot(pos, vfuniforms[int(gl_InstanceID * 6.0 + 2.0+ 0.1 + 0.0)]);
    tc0.y = dot(pos, vfuniforms[int(gl_InstanceID * 6.0 + 2.0+ 0.1 + 1.0)]);
    tc1.x = dot(pos, vfuniforms[int(gl_InstanceID * 6.0 + 2.0+ 0.1 + 2.0)]);
    tc1.y = dot(pos, vfuniforms[int(gl_InstanceID * 6.0 + 2.0+ 0.1 + 3.0)]);
    

    fucxadd = vfuniforms[int(gl_InstanceID * 6.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(gl_InstanceID * 6.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
