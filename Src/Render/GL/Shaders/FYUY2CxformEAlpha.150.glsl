#version 150
uniform sampler2D tex;
in vec4 factor;
in vec4 fucxadd;
in vec4 fucxmul;
in vec2 tc0;
out vec4 fcolor;
void main() { 

    vec4 yuv = texture(tex, tc0);
    const vec4 g_YuvOffset = vec4( 0.501961, 0.0, 0.501961, 0.0);
    vec4 offset = yuv - g_YuvOffset;

    fcolor.r = clamp( offset.g + 1.568648 * offset.b, 0.0, 1.0 );
    fcolor.g = clamp( offset.g - 0.186593 * offset.r - 0.466296 * offset.b, 0.0, 1.0 );
    fcolor.b = clamp( offset.g + 1.848352 * offset.r, 0.0, 1.0 );
    fcolor.a = 1.0;
    

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    
}
