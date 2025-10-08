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
in vec2 tc;
out vec4 fcolor;
void main() { 

    fcolor       = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec2 i = vec2(0.0, 0.0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color.a += textureLod(tex, tc + (offset.xy + i) * texscale.xy, 0.0).a;
    color.r += textureLod(tex, tc - (offset.xy + i) * texscale.xy, 0.0).a;
    }
    } // EndBox2.
    fcolor = color * fsize.w;
    

    vec4 base = textureLod(srctex, tc * srctexscale.xy, 0.0);
    fcolor.ar = clamp((1.0 - fcolor.ar * fsize.z) - (1.0 - fcolor.ra * fsize.z), 0.0, 1.0);
    vec4 knockout = base;
    fcolor = ((scolor * fcolor.a + scolor2 * fcolor.r)*(1.0-base.a) + base);
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
