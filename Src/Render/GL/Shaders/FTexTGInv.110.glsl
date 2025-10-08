uniform sampler2D tex;
varying vec2 tc;
void main() { 

    gl_FragColor = texture2D(tex,tc);
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
