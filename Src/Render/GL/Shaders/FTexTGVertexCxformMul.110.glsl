uniform sampler2D tex;
varying vec4 color;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc;
void main() { 

    vec4 fcolor0 = texture2D(tex,tc);
    vec4 fcolor1 = color;
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

    gl_FragColor = gl_FragColor * fucxmul + fucxadd;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
