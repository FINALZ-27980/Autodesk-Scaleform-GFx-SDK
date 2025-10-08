#version 150
uniform sampler2D tex;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc);
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
