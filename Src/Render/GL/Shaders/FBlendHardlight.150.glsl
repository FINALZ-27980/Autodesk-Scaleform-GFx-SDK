#version 150
uniform sampler2D dsttex;
uniform sampler2D srctex;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

        vec4 src = texture(srctex, tc0);
        vec4 dst = texture(dsttex, tc1);
        vec3 screen = 1.0 - 2.0*(1.0 - src.rgb)*(1.0 - dst.rgb);
        vec3 mult = 2.0 * src.rgb * dst.rgb;
        vec3 select = step(vec3(0.5, 0.5, 0.5), dst.rgb);
        fcolor.rgb = (mult * select + screen * (vec3(1.0,1,1.0) - select)) * src.a + src.rgb * (1.0 - dst.a) + dst.rgb * (1.0 - src.a);
        fcolor.a   = src.a + (1.0-src.a)*dst.a;
    
}
