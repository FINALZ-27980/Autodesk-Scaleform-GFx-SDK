cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 offset : packoffset(c1);
float4 srctexscale : packoffset(c2);
float4 texscale : packoffset(c3);
};

SamplerState sampler_gradtex : register(s0);
Texture2D gradtex : register(t0);
SamplerState sampler_srctex : register(s1);
Texture2D srctex : register(t1);
SamplerState sampler_tex : register(s2);
Texture2D tex : register(t2);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           out float4 fcolor : SV_Target0)
{
    fcolor       = float4(0, 0, 0, 0);
    float4 color = float4(0, 0, 0, 0);
    float2 i = float2(0, 0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color += tex.SampleLevel(sampler_tex, tc0 + (offset.xy + i) * texscale.xy, 0.0f);
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    float4 shadowColor = gradtex.Sample(sampler_gradtex, float2(clamp(fcolor.a* fsize.z,0.0f,1.0f), 0.0f));
    float4 shadowColor2 = float4(0,0,0,0);
    fcolor.a = shadowColor.a;
    fcolor.r = 0.0f;
    shadowColor.a = 1.0f;
    

    float4 base = srctex.SampleLevel(sampler_srctex, tc0 * srctexscale.xy, 0.0f);
    float4 baseValue = base;
    

    float2 alphas = float2(shadowColor.a, shadowColor2.a);
    fcolor.ar = clamp(fcolor.ar, 0.0f, 1.0f) * alphas;
    fcolor = (shadowColor * fcolor.a + shadowColor2 * fcolor.r + baseValue * (1.0 - fcolor.a - fcolor.r));
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
