#version 150
#extension GL_ARB_draw_instanced : enable
uniform sampler2D tex;
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc);
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
