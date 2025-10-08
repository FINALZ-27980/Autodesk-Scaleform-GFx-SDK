#version 150
uniform vec4 fsize;
uniform sampler2D tex;
uniform vec4 texscale;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc;
out vec4 fcolor;
void main() { 

      fcolor       = vec4(0.0, 0.0, 0.0, 0.0);
      vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
      float  i = 0.0;
      for (i = -fsize.x; i <= fsize.x; i++)
      {{
    

    color += textureLod(tex, tc + i * texscale.xy, 0.0);
    }} // EndBox1/2.
    fcolor = color * fsize.w;
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
