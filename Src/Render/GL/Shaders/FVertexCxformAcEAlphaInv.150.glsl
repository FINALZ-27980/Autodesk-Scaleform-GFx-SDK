#version 150
in vec4 color;
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
out vec4 fcolor;
void main() { 

  fcolor = color;
  

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
