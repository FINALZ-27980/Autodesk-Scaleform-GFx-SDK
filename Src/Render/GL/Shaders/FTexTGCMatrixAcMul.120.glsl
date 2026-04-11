#version 120
uniform vec4 cxadd;
uniform mat4 cxmul;
uniform sampler2D tex;
varying vec2 tc0;
void main() { 

    gl_FragColor = texture2D(tex,tc0);
    

    gl_FragColor = (gl_FragColor) * (cxmul) + cxadd * (gl_FragColor.a + cxadd.a);
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    

      gl_FragColor = gl_FragColor;
    
}
