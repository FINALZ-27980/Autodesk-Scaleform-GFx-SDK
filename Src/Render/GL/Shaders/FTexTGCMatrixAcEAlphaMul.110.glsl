uniform vec4 cxadd;
uniform mat4 cxmul;
uniform sampler2D tex;
varying vec4 factor;
varying vec2 tc;
void main() { 

    gl_FragColor = texture2D(tex,tc);
    

    gl_FragColor = (gl_FragColor) * (cxmul) + cxadd * (gl_FragColor.a + cxadd.a);
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
