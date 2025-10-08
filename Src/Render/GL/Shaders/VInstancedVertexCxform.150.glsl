#version 150
#extension GL_ARB_draw_instanced : enable
uniform vec4 vfuniforms[96];
in vec4 acolor;
in vec4 pos;
out vec4 color;
out vec4 fucxadd;
out vec4 fucxmul;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    color = acolor;
    

    fucxadd = vfuniforms[int(gl_InstanceID * 4.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(gl_InstanceID * 4.0 + 1.0+ 0.1)];
    
}
