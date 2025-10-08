#version 150
#extension GL_ARB_draw_instanced : enable
uniform vec4 vfuniforms[48];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(gl_InstanceID * 2.0 + 0.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(gl_InstanceID * 2.0 + 0.0+ 0.1 + 1.0)]);
    

    color = acolor;
    

      factor = afactor;
    
}
