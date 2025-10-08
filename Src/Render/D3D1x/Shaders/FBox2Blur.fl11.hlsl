cbuffer Constants { 
float4 fsize : packoffset(c0);
float4 texscale : packoffset(c1);
};

SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           float2 tc0 : TEXCOORD2,
           out float4 fcolor : SV_Target0)
{
    fcolor       = float4(0, 0, 0, 0);
    float4 color = float4(0, 0, 0, 0);
    float2 i = float2(0, 0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color += tex.SampleLevel(sampler_tex, tc0 + i * texscale.xy, 0.0f);
    }} // EndBox1/2.
    fcolor = color * fsize.w;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

      fcolor = fcolor;
    
}
