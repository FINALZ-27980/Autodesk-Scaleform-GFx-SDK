sampler2D tex[2] : register(s0);
void main( float4 factor : COLOR0,
           float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           half2 tc0 : TEXCOORD2,
           half2 tc1 : TEXCOORD3,
           out float4 fcolor : COLOR0)
{
    float4 fcolor0 = tex2D(tex[0], tc0);
    float4 fcolor1 = tex2D(tex[1], tc1);
    fcolor = lerp(fcolor1, fcolor0, factor.r);
    

      fcolor = (fcolor * float4(fucxmul.rgb,1)) * fucxmul.a;
      fcolor += fucxadd * fcolor.a;
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    
}
