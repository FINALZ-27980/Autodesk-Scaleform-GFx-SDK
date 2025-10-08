#version 150
in vec4 color;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
