#version 120
uniform sampler2D tex[2];
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 fcolor0 = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture2D(tex[int(1.0)], tc1);
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
