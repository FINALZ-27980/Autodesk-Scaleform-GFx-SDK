#version 150
uniform mat4 cxmul;
uniform mat4 cxmul1;
uniform sampler2D tex[2];
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 fcolor_original = texture(tex[int(0.0)], tc0);
    vec4 fcolor_source   = texture(tex[int(1.0)], tc1);
    fcolor = (fcolor_original) * ( cxmul) + (fcolor_source) * ( cxmul1);
    
}
