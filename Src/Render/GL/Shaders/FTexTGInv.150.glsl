#version 150
uniform sampler2D tex;
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc);
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
