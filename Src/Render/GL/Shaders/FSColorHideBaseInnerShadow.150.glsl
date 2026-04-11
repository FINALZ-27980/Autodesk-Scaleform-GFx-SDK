#version 150
uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
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
    

    color += textureLod(tex, tc0 + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    vec4 shadowColor = scolor;
    vec4 shadowColor2 = vec4(0.0,0,0.0,0);
    fcolor.a = fcolor.a * fsize.z;
    fcolor.r = 0.0;
    

    vec4 base = textureLod(srctex, tc0 * srctexscale.xy, 0.0);
    vec4 baseValue = vec4(0.0,0,0.0,base.a*0.0001); // Blend a miniscule amount of base in, so it doesn't get compiled out.
    

    float lerpval = clamp((base.a*fsize.z - fcolor.a), 0.0, 1.0);
    lerpval *= shadowColor.a;
    fcolor = mix(baseValue, shadowColor, lerpval) * base.a;
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

      fcolor = fcolor;
    
}
