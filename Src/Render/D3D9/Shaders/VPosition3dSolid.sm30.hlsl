float4x4 mvp : register(c0);
void main( float4 pos : POSITION0,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    
}
