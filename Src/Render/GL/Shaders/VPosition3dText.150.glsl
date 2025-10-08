#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
in vec4 acolor;
in vec2 atc;
in vec4 pos;
out vec2 tc;
out vec4 vcolor;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    vcolor = acolor * cxmul + cxadd;
    tc = atc;
    
}
