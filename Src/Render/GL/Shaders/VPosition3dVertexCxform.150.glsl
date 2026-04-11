#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
in vec4 acolor;
in vec4 pos;
out vec4 color;
out vec4 fucxadd;
out vec4 fucxmul;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
