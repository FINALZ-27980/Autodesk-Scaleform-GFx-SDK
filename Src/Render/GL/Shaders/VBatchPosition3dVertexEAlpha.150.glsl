#version 150
uniform mat4 vfmuniforms[24];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(afactor.b*255.01 * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    

      factor = afactor;
    
}
