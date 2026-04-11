uniform sampler2D tex;
varying vec4 factor;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
void main() { 

    gl_FragColor = texture2D(tex,tc0);
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = vec3(gl_FragColor.a, gl_FragColor.a, gl_FragColor.a);
    

      gl_FragColor = gl_FragColor;
    
}
