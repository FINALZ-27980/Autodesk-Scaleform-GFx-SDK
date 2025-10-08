SamplerState sampler_alphatex : register(s0);
Texture2D alphatex : register(t0);
SamplerState sampler_srctex : register(s1);
Texture2D srctex : register(t1);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           half2 tc1 : TEXCOORD3,
           out float4 fcolor : SV_Target0)
{
    float alp = alphatex.Sample(sampler_alphatex, tc1).a;
    fcolor    = srctex.Sample(sampler_srctex, tc0);
    fcolor    *= alp;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
