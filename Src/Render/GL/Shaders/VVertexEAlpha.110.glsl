uniform vec4 mvp[2];
attribute vec4 acolor;
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 color;
varying vec4 factor;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    color = acolor;
    

      factor = afactor;
    
}
