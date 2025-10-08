#version 150
uniform vec4 mvp[2];
uniform vec4 texgen[6];
in vec4 pos;
out vec2 tc0;
out vec2 tc1;
out vec2 tc2;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    tc0.x = dot(pos, texgen[int(0.0)]);
    tc0.y = dot(pos, texgen[int(1.0)]);
    tc1.x = dot(pos, texgen[int(2.0)]);
    tc1.y = dot(pos, texgen[int(3.0)]);
    tc2.x = dot(pos, texgen[int(4.0)]);
    tc2.y = dot(pos, texgen[int(5.0)]);
    
}
