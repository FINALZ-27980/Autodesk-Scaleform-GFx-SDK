#version 120
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform vec4 mvp[2];
uniform vec4 texgen[4];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    tc0.x = dot(pos, texgen[int(0.0)]);
    tc0.y = dot(pos, texgen[int(1.0)]);
    tc1.x = dot(pos, texgen[int(2.0)]);
    tc1.y = dot(pos, texgen[int(3.0)]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
