float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4x4 mvp : register(c2);
float4 texgen[2] : register(c6);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc : TEXCOORD2,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    tc.x = dot(pos, texgen[0]);
    tc.y = dot(pos, texgen[1]);
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
