float4x4 vfmuniforms[24] : register(c0);
float4 vfuniforms[144] : register(c96);
void main( half4 afactor : COLOR0,
           float4 pos : POSITION0,
           float vbatch : COLOR1,
           out half4 factor : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out half2 tc1 : TEXCOORD3,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, vfmuniforms[vbatch * 1 + 0+ 0.1f]);
    

    tc0.x = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 1]);
    tc1.x = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 2]);
    tc1.y = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 3]);
    

    fucxadd = vfuniforms[vbatch * 6 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 6 + 1+ 0.1f];
    

      factor = afactor;
    
}
