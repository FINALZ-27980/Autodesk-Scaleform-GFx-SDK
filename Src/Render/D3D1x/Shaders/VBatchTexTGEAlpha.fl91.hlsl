float4 vfuniforms[96] : register(c0);
void main( half4 afactor : COLOR0,
           float4 pos : POSITION0,
           out half4 factor : COLOR0,
           out half2 tc0 : TEXCOORD0,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f + 1]);
    

    tc0.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 0]);
    tc0.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 1]);
    

      factor = afactor;
    
}
