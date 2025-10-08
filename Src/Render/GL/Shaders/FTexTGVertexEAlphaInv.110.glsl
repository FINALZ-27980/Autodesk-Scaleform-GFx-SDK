uniform sampler2D tex;
varying vec4 color;
varying vec4 factor;
varying vec2 tc;
void main() { 

    vec4 fcolor0 = texture2D(tex,tc);
    vec4 fcolor1 = color;
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
