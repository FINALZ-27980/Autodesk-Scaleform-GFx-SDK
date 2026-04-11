float4 mvp[2] : register(c0);
void main( float4 pos : POSITION0,
           out float4 vpos : POSITION0)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, mvp[0]);
    vpos.y = dot(pos, mvp[1]);
    
}
