#version 150
in vec4 color;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
