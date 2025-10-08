#version 150
uniform vec4 cxadd;
uniform mat4 cxmul;
uniform sampler2D tex;
in vec4 factor;
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc);
    

    fcolor = (fcolor) * (cxmul) + cxadd * (fcolor.a + cxadd.a);
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
