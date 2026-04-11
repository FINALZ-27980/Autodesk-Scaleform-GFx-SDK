#version 120
uniform mat4 mvp;
attribute vec2 atc;
attribute vec4 pos;
varying vec2 tc0;
void main() { 

    gl_Position = (pos) * ( mvp);
    

      tc0 = atc;
    
}
