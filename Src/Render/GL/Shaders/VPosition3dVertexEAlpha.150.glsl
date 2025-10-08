#version 150
uniform mat4 mvp;
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    

      factor = afactor;
    
}
