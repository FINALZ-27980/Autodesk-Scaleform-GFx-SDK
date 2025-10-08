float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4x4 mvp : register(c2);
void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           out half2 tc0 : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

    vcolor = acolor * cxmul + cxadd;
    tc0 = atc;
    
}
