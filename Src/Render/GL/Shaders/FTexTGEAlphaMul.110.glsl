uniform sampler2D tex;
varying vec4 factor;
varying vec2 tc;
void main() { 

    gl_FragColor = texture2D(tex,tc);
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
