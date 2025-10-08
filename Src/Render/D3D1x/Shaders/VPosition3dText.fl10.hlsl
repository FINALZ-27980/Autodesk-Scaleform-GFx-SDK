cbuffer Constants { 
float4 cxadd : packoffset(c0);
float4 cxmul : packoffset(c1);
float4x4 mvp : packoffset(c2);
};

void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           out half2 tc0 : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    vcolor = acolor * cxmul + cxadd;
    tc0 = atc;
    
}
