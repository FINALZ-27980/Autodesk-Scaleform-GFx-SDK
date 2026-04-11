#version 120
uniform sampler2D alphatex;
uniform sampler2D srctex;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    float alp = texture2D(alphatex, tc1).a;
    gl_FragColor    = texture2D(srctex, tc0);
    gl_FragColor    *= alp;
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    
}
