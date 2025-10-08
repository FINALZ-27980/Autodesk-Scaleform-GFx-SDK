#version 150
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
in vec4 acolor;
in vec4 afactor;
in vec4 pos;
out vec4 color;
out vec4 factor;
out vec4 fucxadd;
out vec4 fucxmul;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(afactor.b*255.01 * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    

    fucxadd = vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(afactor.b*255.01 * 2.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
