#version 150
uniform sampler2D tex;
in vec4 factor;
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc);
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
