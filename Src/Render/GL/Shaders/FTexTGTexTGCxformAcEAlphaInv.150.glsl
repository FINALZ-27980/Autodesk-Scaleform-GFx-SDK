#version 150
uniform sampler2D tex[2];
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
in vec2 tc1;
out vec4 fcolor;
void main() { 

    vec4 fcolor0 = texture(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture(tex[int(1.0)], tc1);
    fcolor = mix(fcolor1, fcolor0, factor.r);
    

      fcolor = (fcolor * vec4(fucxmul.rgb,1.0)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = vec3(fcolor.a, fcolor.a, fcolor.a);
    
}
