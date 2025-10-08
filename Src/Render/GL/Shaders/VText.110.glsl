uniform vec4 cxadd;
uniform vec4 cxmul;
uniform vec4 mvp[2];
attribute vec4 acolor;
attribute vec2 atc;
attribute vec4 pos;
varying vec2 tc;
varying vec4 vcolor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    vcolor = acolor * cxmul + cxadd;
    tc = atc;
    
}
