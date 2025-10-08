cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
};

void main( half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           uint vbatch : COLOR1,
           out half2 tc : TEXCOORD0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

      tc = atc;
    
}
