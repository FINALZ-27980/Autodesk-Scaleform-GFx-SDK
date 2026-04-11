#version 150
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
uniform vec4 texgen[4];
in vec4 afactor;
in vec4 pos;
out vec4 factor;
out vec4 fucxadd;
out vec4 fucxmul;
out vec2 tc0;
out vec2 tc1;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    tc0.x = dot(pos, texgen[int(0.0)]);
    tc0.y = dot(pos, texgen[int(1.0)]);
    tc1.x = dot(pos, texgen[int(2.0)]);
    tc1.y = dot(pos, texgen[int(3.0)]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
