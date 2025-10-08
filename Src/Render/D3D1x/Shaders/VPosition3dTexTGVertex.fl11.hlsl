cbuffer Constants { 
float4x4 mvp : packoffset(c0);
float4 texgen[2] : packoffset(c4);
};

void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : SV_Position,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out half2 tc0 : TEXCOORD0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    tc0.x = dot(pos, texgen[0]);
    tc0.y = dot(pos, texgen[1]);
    

      factor = afactor;
    
}
