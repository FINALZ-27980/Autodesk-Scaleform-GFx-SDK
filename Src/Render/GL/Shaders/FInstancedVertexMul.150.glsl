#version 150
#extension GL_ARB_draw_instanced : enable
in vec4 color;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
