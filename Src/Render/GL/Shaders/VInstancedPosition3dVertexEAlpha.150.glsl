#version 150
#extension GL_ARB_draw_instanced : enable
uniform mat4 vfmuniforms[24];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(gl_InstanceID * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    

      factor = afactor;
    
}
