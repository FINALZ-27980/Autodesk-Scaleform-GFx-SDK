#version 150
uniform sampler2D tex;
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc0);
    

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
