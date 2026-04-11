sampler2D srctex : register(s0);
sampler2D tex : register(s1);
void main( float2 tc0 : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    float4 fchannels = tex2D(tex, tc0);
    fcolor  = tex2D(srctex, float2(fchannels.r, 0.125f));
    fcolor += tex2D(srctex, float2(fchannels.g, 0.375f));
    fcolor += tex2D(srctex, float2(fchannels.b, 0.625f));
    fcolor += tex2D(srctex, float2(fchannels.a, 0.875f));
    
}
