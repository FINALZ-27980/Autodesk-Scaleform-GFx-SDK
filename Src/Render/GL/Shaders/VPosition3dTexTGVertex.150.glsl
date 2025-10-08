#version 150
uniform mat4 mvp;
uniform vec4 texgen[2];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
out vec2 tc;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    color = acolor;
    tc.x = dot(pos, texgen[int(0.0)]);
    tc.y = dot(pos, texgen[int(1.0)]);
    

      factor = afactor;
    
}
