uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
