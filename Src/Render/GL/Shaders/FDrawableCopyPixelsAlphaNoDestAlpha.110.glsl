uniform sampler2D tex[3];
varying vec2 tc0;
varying vec2 tc1;
varying vec2 tc2;
void main() { 

    vec4 fcolor_org = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor_src = texture2D(tex[int(1.0)], tc1);
    vec4 fcolor_alp = texture2D(tex[int(2.0)], tc2);
    float inAlpha = fcolor_src.a * fcolor_alp.a;
    

    gl_FragColor.a = 1.0;
    

    gl_FragColor.rgb = mix(fcolor_org.rgb, fcolor_src.rgb, inAlpha / gl_FragColor.a);
    
}
