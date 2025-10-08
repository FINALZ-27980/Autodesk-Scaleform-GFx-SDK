cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
float4 vfuniforms[48] : packoffset(c96);
};

void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out half2 tc0 : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    vcolor = acolor * vfuniforms[vbatch * 2 + 1+ 0.1f] + vfuniforms[vbatch * 2 + 0+ 0.1f];
    tc0 = atc;
    
}
