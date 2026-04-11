#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
in vec2 atc;
in vec4 pos;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc0;
void main() { 

    gl_Position = (pos) * ( mvp);
    

      tc0 = atc;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
