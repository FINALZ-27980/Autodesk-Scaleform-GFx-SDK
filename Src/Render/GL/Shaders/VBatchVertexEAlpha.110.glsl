uniform vec4 vfuniforms[48];
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 2.0 + 0.0+ 0.1 + 1.0)]);
    

    color = acolor;
    

      factor = afactor;
    
}
