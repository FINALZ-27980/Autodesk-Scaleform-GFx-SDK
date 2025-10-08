#version 120
uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
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
    

    color += texture2D(tex, tc + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    gl_FragColor = color * fsize.w;
    

    gl_FragColor = scolor * clamp(gl_FragColor.a * fsize.z, 0.0, 1.0);
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    
}
