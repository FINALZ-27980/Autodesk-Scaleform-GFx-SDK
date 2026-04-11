#version 120
uniform float mipLevels;
uniform sampler2D tex[2];
uniform vec2 textureDims;
varying vec4 factor;
varying vec2 tc0;
varying vec2 tc1;
void main() { 

    vec4 fcolor0 = texture2D(tex[int(0.0)], tc0);
    vec4 fcolor1 = texture2D(tex[int(1.0)], tc1);
    gl_FragColor = mix(fcolor1, fcolor0, factor.r);
    

      gl_FragColor = gl_FragColor;
    

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
    // NOTE: must blend in a little bit of the original gl_FragColor, otherwise the shader compiler might optimize the original block out,
    // because it would no longer contribute to the outputs of the shader.
    gl_FragColor = gl_FragColor*0.001 + clamp(vec4(R,G,B, 1.0), 0.0, 1.0);
    
}
