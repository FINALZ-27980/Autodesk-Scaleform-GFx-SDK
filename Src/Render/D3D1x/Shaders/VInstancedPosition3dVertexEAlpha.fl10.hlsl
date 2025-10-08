cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
};

void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    color = acolor;
    

      factor = afactor;
    
}
