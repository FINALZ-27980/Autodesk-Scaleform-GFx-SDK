float4x4 vfmuniforms[24] : register(c0);
void main( half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           float vbatch : COLOR1,
           out half2 tc : TEXCOORD0,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

      tc = atc;
    
}
