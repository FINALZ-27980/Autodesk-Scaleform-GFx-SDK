cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 offset : packoffset(c1);
float4 scolor : packoffset(c2);
float4 srctexscale : packoffset(c3);
float4 texscale : packoffset(c4);
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
    

    color += tex.SampleLevel(sampler_tex, tc + (offset.xy + i) * texscale.xy, 0.0f);
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    float4 base = srctex.SampleLevel(sampler_srctex, tc * srctexscale.xy, 0.0f);
    float lerpval = clamp((base.a - fcolor.a) * fsize.z, 0.0f, 1.0f);
    fcolor = lerp(base, scolor, lerpval) * base.a;
    float4 knockout = base * (1.0-lerpval) * base.a;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
