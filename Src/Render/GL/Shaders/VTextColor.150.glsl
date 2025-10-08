#version 150
uniform vec4 mvp[2];
in vec2 atc;
in vec4 pos;
out vec2 tc;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

      tc = atc;
    
}
