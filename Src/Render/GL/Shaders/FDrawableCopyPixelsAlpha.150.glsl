#version 150
uniform sampler2D tex[3];
in vec2 tc0;
in vec2 tc1;
in vec2 tc2;
out vec4 fcolor;
void main() { 

    vec4 fcolor_org = texture(tex[int(0.0)], tc0);
    vec4 fcolor_src = texture(tex[int(1.0)], tc1);
    vec4 fcolor_alp = texture(tex[int(2.0)], tc2);
    float inAlpha = fcolor_src.a * fcolor_alp.a;
    

    fcolor.a = inAlpha;
    

    fcolor.rgb = mix(fcolor_org.rgb, fcolor_src.rgb, inAlpha / fcolor.a);
    
}
