cbuffer Constants { 
float4x4 mvp : packoffset(c0);
};

void main( float4 acolor : COLOR0,
           float4 pos : SV_Position,
           out float4 color : COLOR0,
           out float4 vpos : SV_Position)
{
    vpos = mul(pos, mvp);
    

    color = acolor;
    
}
