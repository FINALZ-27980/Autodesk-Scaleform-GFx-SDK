#version 120
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(afactor.b*255.01 * 1.0 + 0.0+ 0.1)]);
    

    color = acolor;
    

    fucxadd = vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(afactor.b*255.01 * 2.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
