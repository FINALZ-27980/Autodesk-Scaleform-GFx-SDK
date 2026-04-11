#version 150
uniform sampler2D dsttex;
uniform sampler2D srctex;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 src = texture(srctex, tc0);
    vec4 dst = texture(dsttex, tc1);
    fcolor     = max(src - dst, dst - src);
    fcolor.a   = src.a + (1.0-src.a)*dst.a;
    
}
