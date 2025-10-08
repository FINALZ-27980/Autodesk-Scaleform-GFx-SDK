float4 vfuniforms[192] : register(c0);
void main( float4 pos : POSITION0,
           float vbatch : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc0 : TEXCOORD2,
           out half2 tc1 : TEXCOORD3,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 2+ 0.1f + 1]);
    

    tc0.x = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 4+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 4+ 0.1f + 1]);
    tc1.x = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 4+ 0.1f + 2]);
    tc1.y = dot(pos, vfuniforms[vbatch * 255.01f * 8 + 4+ 0.1f + 3]);
    

    fucxadd = vfuniforms[vbatch * 255.01f * 8 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 255.01f * 8 + 1+ 0.1f];
    
}
