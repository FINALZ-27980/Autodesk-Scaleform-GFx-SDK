uniform sampler2D tex;
varying vec2 tc;
varying vec4 vcolor;
void main() { 

    vec4 c = vcolor;
    c.a = c.a * texture2D(tex, tc).a;
    gl_FragColor = c;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
