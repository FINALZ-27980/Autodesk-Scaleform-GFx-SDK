float4 cxadd : register(c0);
float4x4 cxmul : register(c1);
sampler2D tex : register(s0);
void main( float4 factor : COLOR0,
           half2 tc : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex,tc);
    

    fcolor = mul(fcolor,cxmul) + cxadd * (fcolor.a + cxadd.a);
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
