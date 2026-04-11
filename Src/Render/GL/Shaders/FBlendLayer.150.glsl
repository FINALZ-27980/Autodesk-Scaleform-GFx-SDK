#version 150
uniform sampler2D alphatex;
uniform sampler2D srctex;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    float alp = texture(alphatex, tc1).a;
    fcolor    = texture(srctex, tc0);
    fcolor    *= alp;
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
