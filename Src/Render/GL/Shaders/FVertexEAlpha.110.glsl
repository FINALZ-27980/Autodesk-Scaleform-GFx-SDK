varying vec4 color;
varying vec4 factor;
void main() { 

  gl_FragColor = color;
  

    gl_FragColor.a *= factor.a;
    
}
