uniform mat4 vfmuniforms[24];
attribute vec4 pos;
attribute float vbatch;
void main() { 

    gl_Position = (pos) * ( vfmuniforms[int(vbatch * 1.0 + 0.0+ 0.1)]);
    
}
