#version 150
uniform mat4 mvp;
in vec4 pos;
void main() { 

    gl_Position = (pos) * ( mvp);
    
}
