#version 120
uniform float mipLevels;
uniform sampler2D tex;
uniform vec2 textureDims;
varying vec2 tc0;
void main() { 

    vec4 yuv = texture2D(tex, tc0);
    const vec4 g_YuvOffset = vec4( 0.501961, 0.0, 0.501961, 0.0);
    vec4 offset = yuv - g_YuvOffset;

    gl_FragColor.r = clamp( offset.g + 1.568648 * offset.b, 0.0, 1.0 );
    gl_FragColor.g = clamp( offset.g - 0.186593 * offset.r - 0.466296 * offset.b, 0.0, 1.0 );
    gl_FragColor.b = clamp( offset.g + 1.848352 * offset.r, 0.0, 1.0 );
    gl_FragColor.a = 1.0;
    

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
