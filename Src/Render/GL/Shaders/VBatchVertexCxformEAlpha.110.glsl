uniform vec4 vfuniforms[96];
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 2.0+ 0.1 + 0.0)]);
    gl_Position.y = dot(pos, vfuniforms[int(afactor.b*255.01 * 4.0 + 2.0+ 0.1 + 1.0)]);
    

    color = acolor;
    

    fucxadd = vfuniforms[int(afactor.b*255.01 * 4.0 + 0.0+ 0.1)];
    fucxmul = vfuniforms[int(afactor.b*255.01 * 4.0 + 1.0+ 0.1)];
    

      factor = afactor;
    
}
