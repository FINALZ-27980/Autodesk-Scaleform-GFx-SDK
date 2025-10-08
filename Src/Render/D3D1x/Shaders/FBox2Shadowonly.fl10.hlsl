cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 offset : packoffset(c1);
float4 scolor : packoffset(c2);
float4 texscale : packoffset(c3);
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
    

    color += tex.SampleLevel(sampler_tex, tc + (offset.xy + i) * texscale.xy, 0.0f);
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    fcolor = scolor * clamp(fcolor.a * fsize.z, 0.0f, 1.0f);
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
