#version 120
uniform vec4 cxmul;
void main() { 

    gl_FragColor = cxmul;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
