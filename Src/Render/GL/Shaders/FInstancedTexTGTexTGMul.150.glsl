#version 150
#extension GL_ARB_draw_instanced : enable
uniform sampler2D tex[2];
in vec4 factor;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 fcolor0 = texture(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture(tex[int(1.0)], tc1);
    fcolor = mix(fcolor1, fcolor0, factor.r);
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
