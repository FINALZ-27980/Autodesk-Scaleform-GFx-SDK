float4 vfuniforms[96] : register(c0);
void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : POSITION0,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out half2 tc : TEXCOORD0,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 1]);
    

    color = acolor;
    tc.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 0]);
    tc.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 1]);
    

      factor = afactor;
    
}
