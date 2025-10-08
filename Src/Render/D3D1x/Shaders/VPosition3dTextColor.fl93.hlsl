float4x4 mvp : register(c0);
void main( half2 atc : TEXCOORD0,
           float4 pos : POSITION0,
           out half2 tc : TEXCOORD0,
           out float4 vpos : POSITION0)
{
    vpos = mul(pos, mvp);
    

      tc = atc;
    
}
