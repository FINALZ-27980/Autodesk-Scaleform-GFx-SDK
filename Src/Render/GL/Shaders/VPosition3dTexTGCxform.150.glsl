#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
uniform vec4 texgen[2];
in vec4 pos;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    tc.x = dot(pos, texgen[int(0.0)]);
    tc.y = dot(pos, texgen[int(1.0)]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
