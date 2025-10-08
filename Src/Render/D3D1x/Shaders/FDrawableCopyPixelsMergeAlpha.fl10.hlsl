SamplerState sampler_tex[2] : register(s0);
Texture2D tex[2] : register(t0);
void main( float2 tc0 : TEXCOORD0,
           float2 tc1 : TEXCOORD1,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor_org = tex[0].Sample(sampler_tex[0], tc0);
    float4 fcolor_src = tex[1].Sample(sampler_tex[1], tc1);
    float inAlpha = fcolor_src.a;
    

    fcolor.a = lerp(inAlpha, 1.0f, fcolor_org.a);
    

    fcolor.rgb = lerp(fcolor_org.rgb, fcolor_src.rgb, inAlpha / fcolor.a);
    
}
