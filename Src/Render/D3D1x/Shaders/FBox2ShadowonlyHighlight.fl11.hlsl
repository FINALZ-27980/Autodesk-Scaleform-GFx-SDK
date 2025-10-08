cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 offset : packoffset(c1);
float4 scolor : packoffset(c2);
float4 scolor2 : packoffset(c3);
float4 texscale : packoffset(c4);
};

SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           float2 tc : TEXCOORD2,
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
    

    fcolor.ar = clamp((1.0 - fcolor.ar * fsize.z) - (1.0 - fcolor.ra * fsize.z), 0.0f, 1.0f);
    fcolor = (scolor * fcolor.a + scolor2 * fcolor.r);
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
