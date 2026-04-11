uniform mat4 cxmul;
uniform mat4 cxmul1;
uniform sampler2D tex[2];
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 fcolor_original = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor_source   = texture2D(tex[int(1.0)], tc1);
    gl_FragColor = (fcolor_original) * ( cxmul) + (fcolor_source) * ( cxmul1);
    
}
