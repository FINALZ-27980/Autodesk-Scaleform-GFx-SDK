uniform vec4 mvp[2];
uniform vec4 texgen[2];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec2 tc;
void main() { 

    gl_Position = vec4(0.0,0,0.0,1);
    gl_Position.x = dot(pos, mvp[int(0.0)]);
    gl_Position.y = dot(pos, mvp[int(1.0)]);
    

    tc.x = dot(pos, texgen[int(0.0)]);
    tc.y = dot(pos, texgen[int(1.0)]);
    

      factor = afactor;
    
}
