SamplerState sampler_srctex : register(s0);
Texture2D srctex : register(t0);
SamplerState sampler_tex : register(s1);
Texture2D tex : register(t1);
void main( float2 tc0 : TEXCOORD0,
           out float4 fcolor : SV_Target0)
{
    float4 fchannels = tex.Sample(sampler_tex, tc0);
    fcolor  = srctex.Sample(sampler_srctex, float2(fchannels.r, 0.125f));
    fcolor += srctex.Sample(sampler_srctex, float2(fchannels.g, 0.375f));
    fcolor += srctex.Sample(sampler_srctex, float2(fchannels.b, 0.625f));
    fcolor += srctex.Sample(sampler_srctex, float2(fchannels.a, 0.875f));
    
}
