uniform vec4 vfuniforms[96];
attribute vec4 acolor;
attribute vec2 atc;
attribute vec4 pos;
attribute float vbatch;
varying vec2 tc;
varying vec4 vcolor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(vbatch * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    vcolor = acolor * vfuniforms[int(vbatch * 4.0 + 1.0+ 0.1)] + vfuniforms[int(vbatch * 4.0 + 0.0+ 0.1)];
    tc = atc;
    
}
