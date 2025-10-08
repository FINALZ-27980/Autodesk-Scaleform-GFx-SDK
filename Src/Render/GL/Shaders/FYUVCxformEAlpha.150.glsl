#version 150
uniform sampler2D tex[3];
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc;
out vec4 fcolor;
void main() { 

    float c0 = float((texture(tex[int(0.0)], tc).r - 16./255.) * 1.164);
    float U0 = float(texture(tex[int(1.0)], tc).r - 128./255.);
    float V0 = float(texture(tex[int(2.0)], tc).r - 128./255.);
    vec4 c = vec4(c0,c0,c0,c0);
    vec4 U = vec4(U0,U0,U0,U0);
    vec4 V = vec4(V0,V0,V0,V0);
    c += V * vec4(1.596, -0.813, 0.0, 0.0);
    c += U * vec4(0.0, -0.392, 2.017, 0.0);
    c.a = 1.0;
    fcolor = c;
    

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.a *= factor.a;
    
}
