cbuffer Constants { 
float4 vfuniforms[192] : packoffset(c0);
};

void main( float4 pos : SV_Position,
           uint vbatch : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out half2 tc1 : TEXCOORD3,
           out float4 vpos : SV_Position)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 8 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 8 + 2+ 0.1f + 1]);
    

    tc0.x = dot(pos, vfuniforms[vbatch * 8 + 4+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[vbatch * 8 + 4+ 0.1f + 1]);
    tc1.x = dot(pos, vfuniforms[vbatch * 8 + 4+ 0.1f + 2]);
    tc1.y = dot(pos, vfuniforms[vbatch * 8 + 4+ 0.1f + 3]);
    

    fucxadd = vfuniforms[vbatch * 8 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 8 + 1+ 0.1f];
    
}
