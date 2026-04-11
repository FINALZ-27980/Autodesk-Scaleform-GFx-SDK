#version 120
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
    

    color += texture2D(tex, tc0 + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    gl_FragColor = color * fsize.w;
    

    vec4 shadowColor = scolor;
    vec4 shadowColor2 = vec4(0.0,0,0.0,0);
    gl_FragColor.a = gl_FragColor.a * fsize.z;
    gl_FragColor.r = 0.0;
    

    vec4 base = texture2D(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = vec4(0.0,0,0.0,base.a*0.0001); // Blend a miniscule amount of base in, so it doesn't get compiled out.
    

    vec2 alphas = vec2(shadowColor.a, shadowColor2.a);
    gl_FragColor.ar = clamp(gl_FragColor.ar, 0.0, 1.0) * alphas;
    gl_FragColor = (shadowColor * gl_FragColor.a + shadowColor2 * gl_FragColor.r + baseValue * (1.0 - gl_FragColor.a - gl_FragColor.r));
    

      gl_FragColor = (gl_FragColor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      gl_FragColor += fucxadd * gl_FragColor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    

      gl_FragColor = gl_FragColor;
    
}
