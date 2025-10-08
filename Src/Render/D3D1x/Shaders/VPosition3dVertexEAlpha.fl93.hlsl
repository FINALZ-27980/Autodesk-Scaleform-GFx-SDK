float4x4 mvp : register(c0);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    

      factor = afactor;
    
}
