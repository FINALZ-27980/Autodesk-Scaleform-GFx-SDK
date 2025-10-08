float4 fsize : register(c0);
float4 offset : register(c1);
float4 scolor : register(c2);
sampler2D tex : register(s0);
float4 texscale : register(c3);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           float2 tc : TEXCOORD2,
           out float4 fcolor : COLOR0)
{
    fcolor       = float4(0, 0, 0, 0);
    float4 color = float4(0, 0, 0, 0);
    float2 i = float2(0, 0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color += tex2Dlod( tex, float4( ( tc + (offset.xy + i) * texscale.xy), 0.0,  0.0f ) );
    }
    } // EndBox2.

    fcolor = color * fsize.w;
    

    fcolor = scolor * clamp(fcolor.a * fsize.z, 0.0f, 1.0f);
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
