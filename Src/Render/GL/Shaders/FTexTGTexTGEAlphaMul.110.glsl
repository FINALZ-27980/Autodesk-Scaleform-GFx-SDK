uniform sampler2D tex[2];
varying vec4 factor;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 fcolor0 = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture2D(tex[int(1.0)], tc1);
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
