#version 150
uniform sampler2D tex[2];
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 fcolor_org = texture(tex[int(0.0)], tc0);
    vec4 fcolor_src = texture(tex[int(1.0)], tc1);
    float inAlpha = fcolor_src.a;
    

    fcolor.a = mix(inAlpha, 1.0, fcolor_org.a);
    

    fcolor.rgb = mix(fcolor_org.rgb, fcolor_src.rgb, inAlpha / fcolor.a);
    
}
