cbuffer Constants { 
float4 cxadd : packoffset(c0);
float4 cxmul : packoffset(c1);
float4 mvp[2] : packoffset(c2);
};

void main( float4 acolor : COLOR0,
           float4 pos : SV_Position,
           out float4 color : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out float4 vpos : SV_Position)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, mvp[0]);
    vpos.y = dot(pos, mvp[1]);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
