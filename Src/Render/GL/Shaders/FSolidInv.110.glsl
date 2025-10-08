uniform vec4 cxmul;
void main() { 

    gl_FragColor = cxmul;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
