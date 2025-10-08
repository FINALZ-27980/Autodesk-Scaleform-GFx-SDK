float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4x4 mvp : register(c2);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
