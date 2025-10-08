cbuffer Constants { 
float4x4 vfmuniforms[24] : packoffset(c0);
float4 vfuniforms[96] : packoffset(c96);
};

void main( half4 afactor : COLOR0,
           float4 pos : SV_Position,
           out half4 factor : COLOR0,
           out half2 tc0 : TEXCOORD0,
           out half2 tc1 : TEXCOORD1,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, vfmuniforms[afactor.b*255.01f * 1 + 0+ 0.1f]);
    

    tc0.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 1]);
    tc1.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 2]);
    tc1.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 3]);
    

      factor = afactor;
    
}
