#version 150
uniform vec4 fsize;
uniform sampler2D gradtex;
uniform vec4 offset;
uniform sampler2D srctex;
uniform vec4 srctexscale;
uniform sampler2D tex;
uniform vec4 texscale;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor       = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec2 i = vec2(0.0, 0.0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color.a += textureLod(tex, tc0 + (offset.xy + i) * texscale.xy, 0.0).a;
    color.r += textureLod(tex, tc0 - (offset.xy + i) * texscale.xy, 0.0).a;
    }
    } // EndBox2.
    fcolor = color * fsize.w;
    

    fcolor.ar = (1.0 - fcolor.ar) - (1.0 - fcolor.ra);
    vec4 shadowColor = texture(gradtex,  vec2(clamp(0.0 + 0.5 * (1.0-fcolor.r * fsize.z) , 0.0, 0.5), 0.0));
    vec4 shadowColor2 = texture(gradtex, vec2(clamp(0.5 + 0.5 * fcolor.a * fsize.z, 0.5, 1.0), 0.0));
    fcolor.a = shadowColor.a;
    fcolor.r = shadowColor2.a;
    shadowColor.a = 1.0;
    shadowColor2.a = 1.0;
    

    vec4 base = textureLod(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = base;
    

    vec2 alphas = vec2(shadowColor.a, shadowColor2.a);
    fcolor.ar = clamp(fcolor.ar, 0.0, 1.0) * alphas;
    fcolor = (shadowColor * fcolor.a + shadowColor2 * fcolor.r)*(1.0-base.a) + baseValue;
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
