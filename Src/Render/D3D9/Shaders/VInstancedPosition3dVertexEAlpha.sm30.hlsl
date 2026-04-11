float4x4 vfmuniforms[24] : register(c0);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           float vbatch : COLOR2,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    color = acolor;
    

      factor = afactor;
    
}
