#version 120
uniform vec4 vfuniforms[192];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 2.0+ 0.1 + 1.0)]);
    

    tc0.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 4.0+ 0.1 + 0.0)]);
    tc0.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 4.0+ 0.1 + 1.0)]);
    tc1.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 4.0+ 0.1 + 2.0)]);
    tc1.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 8.0 + 4.0+ 0.1 + 3.0)]);
    

    fucxadd = vfuniforms[int(afactor.b*255.01 * 8.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(afactor.b*255.01 * 8.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
