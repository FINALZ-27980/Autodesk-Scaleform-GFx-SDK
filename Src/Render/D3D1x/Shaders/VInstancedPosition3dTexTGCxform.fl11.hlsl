cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
float4 vfuniforms[96] : packoffset(c96);
};

void main( float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    tc0.x = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 1]);
    

    fucxadd = vfuniforms[vbatch * 4 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 4 + 1+ 0.1f];
    
}
