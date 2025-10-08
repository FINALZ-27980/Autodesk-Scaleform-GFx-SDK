uniform mat4 vfmuniforms[24];
attribute vec2 atc;
attribute vec4 pos;
attribute float vbatch;
varying vec2 tc;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    

      tc = atc;
    
}
