#version 120
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
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    
}
