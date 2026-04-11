#version 120
uniform sampler2D tex[2];
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 fcolor_org = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor_src = texture2D(tex[int(1.0)], tc1);
    float inAlpha = fcolor_src.a;
    

    gl_FragColor.a = inAlpha;
    

    gl_FragColor.rgb = mix(fcolor_org.rgb, fcolor_src.rgb, inAlpha / gl_FragColor.a);
    
}
