#version 150
uniform float mipLevels;
uniform sampler2D tex;
uniform vec2 textureDims;
in vec4 factor;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    fcolor = texture(tex,tc0);
    

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
