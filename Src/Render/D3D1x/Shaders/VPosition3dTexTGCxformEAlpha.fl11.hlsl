cbuffer Constants { 
float4 cxadd : packoffset(c0);
float4 cxmul : packoffset(c1);
float4x4 mvp : packoffset(c2);
float4 texgen[2] : packoffset(c6);
};

void main( half4 afactor : COLOR0,
           float4 pos : SV_Position,
           out half4 factor : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    tc0.x = dot(pos, texgen[0]);
    tc0.y = dot(pos, texgen[1]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
