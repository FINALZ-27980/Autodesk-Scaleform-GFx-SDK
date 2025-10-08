float4 cxadd : register(c0);
float4 cxmul : register(c1);
float4 mvp[2] : register(c2);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, mvp[0]);
    vpos.y = dot(pos, mvp[1]);
    

    color = acolor;
    

    fucxadd = cxadd;
    fucxmul = cxmul;
    

      factor = afactor;
    
}
