cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 offset : packoffset(c1);
float4 scolor : packoffset(c2);
float4 scolor2 : packoffset(c3);
float4 srctexscale : packoffset(c4);
float4 texscale : packoffset(c5);
};

SamplerState sampler_srctex : register(s0);
Texture2D srctex : register(t0);
SamplerState sampler_tex : register(s1);
Texture2D tex : register(t1);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc : TEXCOORD2,
           out float4 fcolor : SV_Target0)
{
    fcolor       = float4(0, 0, 0, 0);
    float4 color = float4(0, 0, 0, 0);
    float2 i = float2(0, 0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color.a += tex.SampleLevel(sampler_tex, tc + (offset.xy + i) * texscale.xy, 0.0f).a;
    color.r += tex.SampleLevel(sampler_tex, tc - (offset.xy + i) * texscale.xy, 0.0f).a;
    }
    } // EndBox2.
    fcolor = color * fsize.w;
    

    float4 base = srctex.SampleLevel(sampler_srctex, tc * srctexscale.xy, 0.0f);
    fcolor.ar = clamp((1.0 - fcolor.ar * fsize.z) - (1.0 - fcolor.ra * fsize.z), 0.0f, 1.0f);
    float4 knockout = base;
    fcolor = ((scolor * fcolor.a + scolor2 * fcolor.r)*(1.0-base.a) + base);
    

    fcolor -= knockout;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
