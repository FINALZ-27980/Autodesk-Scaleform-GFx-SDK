#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[96];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    tc.x = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 0.0)]);
    tc.y = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    fucxadd = vfuniforms[int(gl_InstanceID * 4.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(gl_InstanceID * 4.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
