uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
uniform sampler2D srctex;
uniform vec4 srctexscale;
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
    

    color += texture2DLod(tex, tc + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    gl_FragColor = color * fsize.w;
    

    vec4 base = texture2DLod(srctex, tc * srctexscale.xy, 0.0);
    float lerpval = clamp((base.a - gl_FragColor.a) * fsize.z, 0.0, 1.0);
    gl_FragColor = mix(base, scolor, lerpval) * base.a;
    vec4 knockout = base * (1.0-lerpval) * base.a;
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
