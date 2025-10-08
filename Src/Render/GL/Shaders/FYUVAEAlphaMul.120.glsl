#version 120
uniform sampler2D tex[4];
varying vec4 factor;
varying vec2 tc;
void main() { 

    float c0 = float((texture2D(tex[int(0.0)], tc).a - 16./255.) * 1.164);
    float U0 = float(texture2D(tex[int(1.0)], tc).a - 128./255.);
    float V0 = float(texture2D(tex[int(2.0)], tc).a - 128./255.);
    vec4 c = vec4(c0,c0,c0,c0);
    vec4 U = vec4(U0,U0,U0,U0);
    vec4 V = vec4(V0,V0,V0,V0);
    c += V * vec4(1.596, -0.813, 0.0, 0.0);
    c += U * vec4(0.0, -0.392, 2.017, 0.0);
    c.a = texture2D(tex[int(3.0)], tc).a;
    gl_FragColor = c;
    

    gl_FragColor.a *= factor.a;
    

    gl_FragColor.rgb = gl_FragColor.rgb * gl_FragColor.a;
    
}
