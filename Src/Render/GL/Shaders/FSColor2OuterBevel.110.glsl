uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
uniform vec4 scolor2;
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
    

    color.a += texture2DLod(tex, tc0 + (offset.xy + i) * texscale.xy, 0.0).a;
    color.r += texture2DLod(tex, tc0 - (offset.xy + i) * texscale.xy, 0.0).a;
    }
    } // EndBox2.
    gl_FragColor = color * fsize.w;
    

    vec4 shadowColor = scolor;
    vec4 shadowColor2 = scolor2;
    gl_FragColor.ar = (1.0 - gl_FragColor.ar * fsize.z) - (1.0 - gl_FragColor.ra * fsize.z);
    

    vec4 base = texture2DLod(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = base;
    

    vec2 alphas = vec2(shadowColor.a, shadowColor2.a);
    gl_FragColor.ar = clamp(gl_FragColor.ar, 0.0, 1.0) * alphas;
    gl_FragColor = (shadowColor * gl_FragColor.a + shadowColor2 * gl_FragColor.r)*(1.0-base.a) + baseValue;
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

      gl_FragColor = gl_FragColor;
    
}
