#version 150
#extension GL_ARB_draw_instanced : enable
uniform float mipLevels;
uniform sampler2D tex[4];
uniform vec2 textureDims;
in vec4 factor;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    float c0 = float((texture(tex[int(0.0)], tc0).r - 16./255.) * 1.164);
    float U0 = float(texture(tex[int(1.0)], tc0).r - 128./255.);
    float V0 = float(texture(tex[int(2.0)], tc0).r - 128./255.);
    vec4 c = vec4(c0,c0,c0,c0);
    vec4 U = vec4(U0,U0,U0,U0);
    vec4 V = vec4(V0,V0,V0,V0);
    c += V * vec4(1.596, -0.813, 0.0, 0.0);
    c += U * vec4(0.0, -0.392, 2.017, 0.0);
    c.a = texture(tex[int(3.0)], tc0).r;
    fcolor = c;
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    

    vec2 dx = dFdx(tc0 * textureDims.x);
    vec2 dy = dFdy(tc0 * textureDims.y);
    float d  = max(dot(dx, dx), dot(dy, dy));
    float mip = clamp(0.5 * log2(d) - 1.0, 0.0, mipLevels-1.0); // [int(0..mip-1.0)]
    dx /= pow(2.0, mip);
    dy /= pow(2.0, mip);
    float H = clamp(1.0 - 0.5 * sqrt( max(dot(dx, dx), dot(dy, dy)) ), 0.0, 1.0) * (80.0/255.0);
    float R = abs(H * 6.0 - 3.0) - 1.0;
    float G = 2.0 - abs(H * 6.0 - 2.0);
    float B = 2.0 - abs(H * 6.0 - 4.0);
    // NOTE: must blend in a little bit of the original fcolor, otherwise the shader compiler might optimize the original block out,
    // because it would no longer contribute to the outputs of the shader.
    fcolor = fcolor*0.001 + clamp(vec4(R,G,B, 1.0), 0.0, 1.0);
    
}
