#version 150
#extension GL_ARB_draw_instanced : enable
uniform sampler2D tex;
in vec4 color;
in vec4 factor;
in vec2 tc;
out vec4 fcolor;
void main() { 

    vec4 fcolor0 = texture(tex,tc);
    vec4 fcolor1 = color;
    fcolor = mix(fcolor1, fcolor0, factor.r);
    

    fcolor.a *= factor.a;
    
}
