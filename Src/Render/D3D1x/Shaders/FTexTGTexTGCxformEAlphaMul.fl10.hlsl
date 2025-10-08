SamplerState sampler_tex[2] : register(s0);
Texture2D tex[2] : register(t0);
void main( float4 factor : COLOR0,
           float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           half2 tc1 : TEXCOORD3,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor0 = tex[0].Sample(sampler_tex[0], tc0);
    float4 fcolor1 = tex[1].Sample(sampler_tex[1], tc1);
    fcolor = lerp(fcolor1, fcolor0, factor.r);
    

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
