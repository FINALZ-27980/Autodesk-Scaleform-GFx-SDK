#version 150
#extension GL_ARB_draw_instanced : enable
uniform sampler2D tex;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc0);
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
