uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
attribute vec2 atc;
attribute vec4 pos;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc;
void main() { 

    gl_Position = (pos) * ( mvp);
    

      tc = atc;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
