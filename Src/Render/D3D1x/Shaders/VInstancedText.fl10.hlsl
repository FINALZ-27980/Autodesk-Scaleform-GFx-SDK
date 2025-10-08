cbuffer Constants { 
float4 vfuniforms[96] : packoffset(c0);
};

void main( float4 acolor : COLOR0,
           half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           uint vbatch : SV_InstanceID,
           out half2 tc0 : TEXCOORD0,
           out float4 vcolor : COLOR0,
           out float4 vpos : SV_Position)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 4 + 2+ 0.1f + 1]);
    

    vcolor = acolor * vfuniforms[vbatch * 4 + 1+ 0.1f] + vfuniforms[vbatch * 4 + 0+ 0.1f];
    tc0 = atc;
    
}
