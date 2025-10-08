float4 vfuniforms[48] : register(c0);
void main( half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           float vbatch : COLOR1,
           out half2 tc : TEXCOORD0,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 2 + 0+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 2 + 0+ 0.1f + 1]);
    

      tc = atc;
    
}
