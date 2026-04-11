#version 120
uniform sampler2D dsttex;
uniform sampler2D srctex;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 src = texture2D(srctex, tc0);
    vec4 dst = texture2D(dsttex, tc1);
    gl_FragColor     = max(src - dst, dst - src);
    gl_FragColor.a   = src.a + (1.0-src.a)*dst.a;
    
}
