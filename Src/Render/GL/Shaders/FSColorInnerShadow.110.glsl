uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
uniform sampler2D srctex;
uniform vec4 srctexscale;
uniform sampler2D tex;
uniform vec4 texscale;
varying vec4 fucxadd;
varying vec4 fucxmul;
varying vec2 tc0;
void main() { 

    gl_FragColor       = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec2 i = vec2(0.0, 0.0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color += texture2DLod(tex, tc0 + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    gl_FragColor = color * fsize.w;
    

    vec4 shadowColor = scolor;
    vec4 shadowColor2 = vec4(0.0,0,0.0,0);
    gl_FragColor.a = gl_FragColor.a * fsize.z;
    gl_FragColor.r = 0.0;
    

    vec4 base = texture2DLod(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = base;
    

    float lerpval = clamp((base.a*fsize.z - gl_FragColor.a), 0.0, 1.0);
    lerpval *= shadowColor.a;
    gl_FragColor = mix(baseValue, shadowColor, lerpval) * base.a;
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

      gl_FragColor = gl_FragColor;
    
}
