#version 120
varying vec4 color;
varying vec4 fucxadd;
varying vec4 fucxmul;
void main() { 

  gl_FragColor = color;
  

    gl_FragColor = gl_FragColor * fucxmul + fucxadd;
    
}
