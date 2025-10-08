#version 150
#extension GL_ARB_draw_instanced : enable
in vec4 color;
in vec4 fucxadd;
in vec4 fucxmul;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
