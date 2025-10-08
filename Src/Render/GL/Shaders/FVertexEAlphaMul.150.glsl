#version 150
in vec4 color;
in vec4 factor;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
