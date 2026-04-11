#version 120
uniform sampler2D tex;
varying vec4 color;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
void main() { 

    vec4 fcolor0 = texture2D(tex,tc0);
    vec4 fcolor1 = color;
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

    gl_FragColor = gl_FragColor * fucxmul + fucxadd;
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    

      gl_FragColor = gl_FragColor;
    
}
