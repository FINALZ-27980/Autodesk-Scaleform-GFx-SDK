#version 120
uniform sampler2D tex;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
void main() { 

    vec4 yuv = texture2D(tex, tc0);
    const vec4 g_YuvOffset = vec4( 0.501961, 0.0, 0.501961, 0.0);
    vec4 offset = yuv - g_YuvOffset;

    gl_FragColor.r = clamp( offset.g + 1.568648 * offset.b, 0.0, 1.0 );
    gl_FragColor.g = clamp( offset.g - 0.186593 * offset.r - 0.466296 * offset.b, 0.0, 1.0 );
    gl_FragColor.b = clamp( offset.g + 1.848352 * offset.r, 0.0, 1.0 );
    gl_FragColor.a = 1.0;
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    

      gl_FragColor = gl_FragColor;
    
}
