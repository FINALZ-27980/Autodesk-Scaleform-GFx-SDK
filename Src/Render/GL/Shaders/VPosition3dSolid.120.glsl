#version 120
uniform mat4 mvp;
attribute vec4 pos;
void main() { 

    gl_Position = (pos) * ( mvp);
    
}
