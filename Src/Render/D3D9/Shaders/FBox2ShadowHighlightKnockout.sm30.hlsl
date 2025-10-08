float4 fsize : register(c0);
float4 offset : register(c1);
float4 scolor : register(c2);
float4 scolor2 : register(c3);
sampler2D srctex : register(s0);
float4 srctexscale : register(c4);
sampler2D tex : register(s1);
float4 texscale : register(c5);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc : TEXCOORD2,
           out float4 fcolor : COLOR0)
{
    fcolor       = float4(0, 0, 0, 0);
    float4 color = float4(0, 0, 0, 0);
    float2 i = float2(0, 0);
    for (i.x = -fsize.x; i.x <= fsize.x; i.x++)
    {
      for (i.y = -fsize.y; i.y <= fsize.y; i.y++)
      {
    

    color.a += tex2Dlod( tex, float4( ( tc + (offset.xy + i) * texscale.xy), 0.0,  0.0f ) ).a;
    color.r += tex2Dlod( tex, float4( ( tc - (offset.xy + i) * texscale.xy), 0.0,  0.0f ) ).a;
    }
    } // EndBox2.
    fcolor = color * fsize.w;
    

    float4 base = tex2Dlod( srctex, float4( ( tc * srctexscale.xy), 0.0,  0.0f ) );
    fcolor.ar = clamp((1.0 - fcolor.ar * fsize.z) - (1.0 - fcolor.ra * fsize.z), 0.0f, 1.0f);
    float4 knockout = base;
    fcolor = ((scolor * fcolor.a + scolor2 * fcolor.r)*(1.0-base.a) + base);
    

    fcolor -= knockout;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
