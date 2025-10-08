#version 120
uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
uniform vec4 scolor2;
uniform sampler2D tex;
uniform vec4 texscale;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc;
void main() { 

    gl_FragColor       = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec2 i = vec2(0.0, 0.0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color.a += texture2D(tex, tc + (offset.xy + i) * texscale.xy, 0.0).a;
    color.r += texture2D(tex, tc - (offset.xy + i) * texscale.xy, 0.0).a;
    }
    } // EndBox2.
    gl_FragColor = color * fsize.w;
    

    gl_FragColor.ar = clamp((1.0 - gl_FragColor.ar * fsize.z) - (1.0 - gl_FragColor.ra * fsize.z), 0.0, 1.0);
    gl_FragColor = (scolor * gl_FragColor.a + scolor2 * gl_FragColor.r);
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
