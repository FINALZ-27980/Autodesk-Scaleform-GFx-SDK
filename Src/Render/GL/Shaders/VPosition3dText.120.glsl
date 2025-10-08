#version 120
uniform vec4 cxadd;
uniform vec4 cxmul;
uniform mat4 mvp;
attribute vec4 acolor;
attribute vec2 atc;
attribute vec4 pos;
varying vec2 tc;
varying vec4 vcolor;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    vcolor = acolor * cxmul + cxadd;
    tc = atc;
    
}
