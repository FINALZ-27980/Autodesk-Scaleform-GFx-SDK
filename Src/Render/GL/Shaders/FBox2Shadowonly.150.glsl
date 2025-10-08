#version 150
uniform vec4 fsize;
uniform vec4 offset;
uniform vec4 scolor;
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
    

    color += textureLod(tex, tc + (offset.xy + i) * texscale.xy, 0.0);
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    fcolor = scolor * clamp(fcolor.a * fsize.z, 0.0, 1.0);
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
