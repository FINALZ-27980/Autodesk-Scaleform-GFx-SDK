cbuffer Constants { 
float4 cxadd : packoffset(c0);
float4x4 cxmul : packoffset(c1);
};

SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( float4 factor : COLOR0,
           half2 tc0 : TEXCOORD0,
           out float4 fcolor : SV_Target0)
{
    fcolor = tex.Sample(sampler_tex,tc0);
    

    fcolor = mul(fcolor,cxmul) + cxadd * (fcolor.a + cxadd.a);
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    
}
