uniform mat4 vfmuniforms[24];
uniform vec4 vfuniforms[48];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(afactor.b*255.01 * 1.0 + 0.0+ 0.1)]);
    

    tc.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1 + 0.0)]);
    tc.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1 + 1.0)]);
    

      factor = afactor;
    
}
