#version 120
uniform sampler2D tex;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc;
void main() { 

    gl_FragColor = texture2D(tex,tc);
    

    gl_FragColor = gl_FragColor * fucxmul + fucxadd;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
