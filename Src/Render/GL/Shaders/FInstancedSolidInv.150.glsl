#version 150
#extension GL_ARB_draw_instanced : enable
uniform vec4 cxmul;
out vec4 fcolor;
void main() { 

    fcolor = cxmul;
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
