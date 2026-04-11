uniform sampler2D dsttex;
uniform sampler2D srctex;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

        vec4 src = texture2D(srctex, tc0);
        vec4 dst = texture2D(dsttex, tc1);
        vec3 screen = 1.0 - 2.0*(1.0 - src.rgb)*(1.0 - dst.rgb);
        vec3 mult = 2.0 * src.rgb * dst.rgb;
        vec3 select = step(vec3(0.5, 0.5, 0.5), dst.rgb);
        gl_FragColor.rgb = (screen * select + mult * (vec3(1.0,1,1.0) - select)) * src.a + src.rgb * (1.0 - dst.a) + dst.rgb * (1.0 - src.a);
        gl_FragColor.a   = src.a + (1.0-src.a)*dst.a;
    
}
