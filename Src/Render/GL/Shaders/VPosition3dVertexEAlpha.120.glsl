#version 120
uniform mat4 mvp;
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    

      factor = afactor;
    
}
