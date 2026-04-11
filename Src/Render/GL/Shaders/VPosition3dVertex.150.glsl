#version 150
uniform mat4 mvp;
in vec4 acolor;
in vec4 pos;
out vec4 color;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    
}
