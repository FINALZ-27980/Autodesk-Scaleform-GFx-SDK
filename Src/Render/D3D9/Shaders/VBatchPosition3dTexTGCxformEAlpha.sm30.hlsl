float4x4 vfmuniforms[24] : register(c0);
float4 vfuniforms[96] : register(c96);
void main( half4 afactor : COLOR0,
           float4 pos : POSITION0,
           out half4 factor : COLOR0,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc : TEXCOORD2,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, vfmuniforms[afactor.b*255.01f * 1 + 0+ 0.1f]);
    

    tc.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 0]);
    tc.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 1]);
    

    fucxadd = vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f];
    fucxmul = vfuniforms[afactor.b*255.01f * 4 + 1+ 0.1f];
    

      factor = afactor;
    
}
