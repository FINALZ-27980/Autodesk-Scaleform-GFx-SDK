#version 150
uniform mat4 mvp;
in vec2 atc;
in vec4 pos;
out vec2 tc0;
void main() { 

    gl_Position = (pos) * ( mvp);
    

      tc0 = atc;
    
}
