SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( float4 color : COLOR0,
           float4 factor : COLOR1,
           float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor0 = tex.Sample(sampler_tex,tc0);
    float4 fcolor1 = color;
    fcolor = lerp(fcolor1, fcolor0, factor.r);
    

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
