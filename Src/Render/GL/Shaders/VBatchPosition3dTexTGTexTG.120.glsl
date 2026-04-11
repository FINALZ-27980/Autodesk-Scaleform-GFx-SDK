#version 120
uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[96];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(afactor.b*255.01 * 1.0 + 0.0+ 0.1)]);
    

    tc0.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 0.0)]);
    tc0.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 1.0)]);
    tc1.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 2.0)]);
    tc1.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1 + 3.0)]);
    

      factor = afactor;
    
}
