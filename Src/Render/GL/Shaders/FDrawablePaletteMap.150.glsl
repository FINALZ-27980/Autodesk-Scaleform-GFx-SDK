#version 150
uniform sampler2D srctex;
uniform sampler2D tex;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    vec4 fchannels = texture(tex, tc0);
    fcolor  = texture(srctex, vec2(fchannels.r, 0.125));
    fcolor += texture(srctex, vec2(fchannels.g, 0.375));
    fcolor += texture(srctex, vec2(fchannels.b, 0.625));
    fcolor += texture(srctex, vec2(fchannels.a, 0.875));
    
}
