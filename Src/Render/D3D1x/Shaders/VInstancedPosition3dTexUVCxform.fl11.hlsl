cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
float4 vfuniforms[48] : packoffset(c96);
};

void main( half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

      tc0 = atc;
    

    fucxadd = vfuniforms[vbatch * 2 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 2 + 1+ 0.1f];
    
}
