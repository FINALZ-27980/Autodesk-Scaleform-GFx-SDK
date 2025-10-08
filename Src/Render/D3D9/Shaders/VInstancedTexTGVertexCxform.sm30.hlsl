float4 vfuniforms[144] : register(c0);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           float vbatch : COLOR2,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out half2 tc : TEXCOORD2,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[vbatch * 6 + 2+ 0.1f + 1]);
    

    color = acolor;
    tc.x = dot(pos, vfuniforms[vbatch * 6 + 4+ 0.1f + 0]);
    tc.y = dot(pos, vfuniforms[vbatch * 6 + 4+ 0.1f + 1]);
    

    fucxadd = vfuniforms[vbatch * 6 + 0+ 0.1f];
    fucxmul = vfuniforms[vbatch * 6 + 1+ 0.1f];
    

      factor = afactor;
    
}
