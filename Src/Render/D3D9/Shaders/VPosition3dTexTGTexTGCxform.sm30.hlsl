float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4x4 mvp : register(c2);
float4 texgen[4] : register(c6);
void main( half4 afactor : COLOR0,
           float4 pos : POSITION0,
           out half4 factor : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out half2 tc1 : TEXCOORD3,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

    tc0.x = dot(pos, texgen[0]);
    tc0.y = dot(pos, texgen[1]);
    tc1.x = dot(pos, texgen[2]);
    tc1.y = dot(pos, texgen[3]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
