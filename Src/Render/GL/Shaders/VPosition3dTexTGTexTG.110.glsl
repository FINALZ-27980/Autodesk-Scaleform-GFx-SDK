uniform mat4 mvp;
uniform vec4 texgen[4];
attribute vec4 afactor;
attribute vec4 pos;
varying vec4 factor;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    gl_Position = (pos) * ( mvp);
    

    tc0.x = dot(pos, texgen[int(0.0)]);
    tc0.y = dot(pos, texgen[int(1.0)]);
    tc1.x = dot(pos, texgen[int(2.0)]);
    tc1.y = dot(pos, texgen[int(3.0)]);
    

      factor = afactor;
    
}
