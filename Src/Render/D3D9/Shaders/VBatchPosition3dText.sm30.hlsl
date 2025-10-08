float4x4 vfmuniforms[24] : register(c0);
float4 vfuniforms[48] : register(c96);
void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           float vbatch : COLOR2,
           out half2 tc : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    vcolor = acolor * vfuniforms[vbatch * 2 + 1+ 0.1f] + vfuniforms[vbatch * 2 + 0+ 0.1f];
    tc = atc;
    
}
