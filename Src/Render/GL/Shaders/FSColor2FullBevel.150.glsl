#version 150
uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
uniform vec4 scolor2;
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
    

    vec4 shadowColor = scolor;
    vec4 shadowColor2 = scolor2;
    fcolor.ar = (1.0 - fcolor.ar * fsize.z) - (1.0 - fcolor.ra * fsize.z);
    

    vec4 base = textureLod(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = base;
    

    vec2 alphas = vec2(shadowColor.a, shadowColor2.a);
    fcolor.ar = clamp(fcolor.ar, 0.0, 1.0) * alphas;
    fcolor = (shadowColor * fcolor.a + shadowColor2 * fcolor.r + baseValue * (1.0 - fcolor.a - fcolor.r));
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

      fcolor = fcolor;
    
}
