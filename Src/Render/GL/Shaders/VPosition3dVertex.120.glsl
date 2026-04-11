#version 120
uniform mat4 mvp;
attribute vec4 acolor;
attribute vec4 pos;
varying vec4 color;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    
}
