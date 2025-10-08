float4 vfuniforms[96] : register(c0);
void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           float vbatch : COLOR2,
           out half2 tc : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 1]);
    

    vcolor = acolor * vfuniforms[vbatch * 4 + 1+ 0.1f] + vfuniforms[vbatch * 4 + 0+ 0.1f];
    tc = atc;
    
}
