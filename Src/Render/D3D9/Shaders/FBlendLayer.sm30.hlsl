sampler2D alphatex : register(s0);
sampler2D srctex : register(s1);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           half2 tc1 : TEXCOORD3,
           out float4 fcolor : COLOR0)
{
    float alp = tex2D(alphatex, tc1).a;
    fcolor    = tex2D(srctex, tc0);
    fcolor    *= alp;
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    
}
