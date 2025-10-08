cbuffer Constants { 
float4 vfuniforms[96] : packoffset(c0);
};

void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out half2 tc0 : TEXCOORD0,
           out float4 vpos : SV_Position)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 4 + 0+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 4 + 0+ 0.1f + 1]);
    

    color = acolor;
    tc0.x = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 1]);
    

      factor = afactor;
    
}
