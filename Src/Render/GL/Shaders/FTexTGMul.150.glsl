#version 150
uniform sampler2D tex;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc0);
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
