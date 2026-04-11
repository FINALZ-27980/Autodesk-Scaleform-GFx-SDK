uniform sampler2D dsttex;
uniform sampler2D srctex;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

        vec4 src = texture2D(srctex, tc0);
        vec4 dst = texture2D(dsttex, tc1);
        vec3 clr = min(src.rgb, dst.rgb);
        gl_FragColor.rgb = clr * (dst.a) + (1.0-dst.a)*src.rgb + dst.rgb*(1.0-src.a);        
        gl_FragColor.a   = src.a + (1.0-src.a)*dst.a;
    
}
