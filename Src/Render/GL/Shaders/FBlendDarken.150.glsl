#version 150
uniform sampler2D dsttex;
uniform sampler2D srctex;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

        vec4 src = texture(srctex, tc0);
        vec4 dst = texture(dsttex, tc1);
        vec3 clr = min(src.rgb, dst.rgb);
        fcolor.rgb = clr * (dst.a) + (1.0-dst.a)*src.rgb + dst.rgb*(1.0-src.a);        
        fcolor.a   = src.a + (1.0-src.a)*dst.a;
    
}
