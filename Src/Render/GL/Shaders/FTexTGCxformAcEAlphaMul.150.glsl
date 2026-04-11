#version 150
uniform sampler2D tex;
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc0);
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
