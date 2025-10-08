varying vec4 color;
void main() { 

  gl_FragColor = color;
  

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    
}
