float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4x4 mvp : register(c2);
void main( half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

      tc0 = atc;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
