float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4 mvp[2] : register(c2);
void main( half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, mvp[0]);
    vpos.y = dot(pos, mvp[1]);
    

      tc0 = atc;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    
}
