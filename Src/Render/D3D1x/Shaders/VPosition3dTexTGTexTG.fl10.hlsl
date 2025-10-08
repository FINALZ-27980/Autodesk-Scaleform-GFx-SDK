cbuffer Constants { 
float4x4 mvp : packoffset(c0);
float4 texgen[4] : packoffset(c4);
};

void main( half4 afactor : COLOR0,
           float4 pos : SV_Position,
           out half4 factor : COLOR0,
           out half2 tc0 : TEXCOORD0,
           out half2 tc1 : TEXCOORD1,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    tc0.x = dot(pos, texgen[0]);
    tc0.y = dot(pos, texgen[1]);
    tc1.x = dot(pos, texgen[2]);
    tc1.y = dot(pos, texgen[3]);
    

      factor = afactor;
    
}
