#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform vec4 mvp[2];
in vec4 acolor;
in vec4 pos;
out vec4 color;
out vec4 fucxadd;
out vec4 fucxmul;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
