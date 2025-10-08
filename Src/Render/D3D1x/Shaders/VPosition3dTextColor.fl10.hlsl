cbuffer Constants { 
float4x4 mvp : packoffset(c0);
};

void main( half2 atc : TEXCOORD0,
           float4 pos : SV_Position,
           out half2 tc : TEXCOORD0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

      tc = atc;
    
}
