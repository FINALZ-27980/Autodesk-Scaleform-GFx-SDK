SamplerState sampler_dsttex : register(s0);
Texture2D dsttex : register(t0);
SamplerState sampler_srctex : register(s1);
Texture2D srctex : register(t1);
void main( half2 tc0 : TEXCOORD0,
           half2 tc1 : TEXCOORD1,
           out float4 fcolor : SV_Target0)
{
        float4 src = srctex.Sample(sampler_srctex, tc0);
        float4 dst = dsttex.Sample(sampler_dsttex, tc1);
        fcolor     = max(src,dst) * src.a + (1-src.a)*dst;
        fcolor.a   = src.a + (1.0-src.a)*dst.a;
    
}
