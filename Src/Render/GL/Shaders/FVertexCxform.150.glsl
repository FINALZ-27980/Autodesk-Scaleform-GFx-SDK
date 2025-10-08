#version 150
in vec4 color;
in vec4 fucxadd;
in vec4 fucxmul;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

    fcolor = fcolor * fucxmul + fucxadd;
    
}
