cbuffer Constants { 
float4 cxadd : packoffset(c0);
float4 cxmul : packoffset(c1);
float4x4 mvp : packoffset(c2);
};

void main( float4 acolor : COLOR0,
           float4 pos : SV_Position,
           out float4 color : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
