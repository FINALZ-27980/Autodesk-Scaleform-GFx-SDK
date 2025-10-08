#version 150
#extension GL_ARB_draw_instanced : enable
uniform sampler2D tex;
in vec2 tc;
in vec4 vcolor;
out vec4 fcolor;
void main() { 

    vec4 c = vcolor;
    c.a = c.a * texture(tex, tc).r;
    fcolor = c;
    
}
