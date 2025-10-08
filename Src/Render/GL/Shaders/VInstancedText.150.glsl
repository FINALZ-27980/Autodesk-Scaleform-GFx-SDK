#version 150
#extension GL_ARB_draw_instanced : enable
uniform vec4 vfuniforms[96];
in vec4 acolor;
in vec2 atc;
in vec4 pos;
out vec2 tc;
out vec4 vcolor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(gl_InstanceID * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    vcolor = acolor * vfuniforms[int(gl_InstanceID * 4.0 + 1.0+ 0.1)] + vfuniforms[int(gl_InstanceID * 4.0 + 0.0+ 0.1)];
    tc = atc;
    
}
