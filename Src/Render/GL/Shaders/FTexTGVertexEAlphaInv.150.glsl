#version 150
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
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
