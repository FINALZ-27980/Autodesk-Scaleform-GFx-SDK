sampler2D tex : register(s0);
void main( float4 factor : COLOR0,
           half2 tc0 : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    float4 yuv = tex2D(tex, tc0);
    const float4 g_YuvOffset = float4( 0.501961, 0, 0.501961, 0);
    float4 offset = yuv - g_YuvOffset;

    fcolor.r = clamp( offset.g + 1.568648 * offset.b, 0.0, 1.0 );
    fcolor.g = clamp( offset.g - 0.186593 * offset.r - 0.466296 * offset.b, 0.0, 1.0 );
    fcolor.b = clamp( offset.g + 1.848352 * offset.r, 0.0, 1.0 );
    fcolor.a = 1.0;
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    
}
