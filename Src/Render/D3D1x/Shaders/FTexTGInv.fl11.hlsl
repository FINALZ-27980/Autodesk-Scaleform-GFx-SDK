SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( half2 tc0 : TEXCOORD0,
           out float4 fcolor : SV_Target0)
{
    fcolor = tex.Sample(sampler_tex,tc0);
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
