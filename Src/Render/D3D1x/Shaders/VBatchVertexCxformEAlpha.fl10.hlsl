cbuffer Constants { 
float4 vfuniforms[96] : packoffset(c0);
};

void main( float4 acolor : COLOR0,
           half4 afactor : COLOR1,
           float4 pos : SV_Position,
           out float4 color : COLOR0,
           out half4 factor : COLOR1,
           out float4 fucxadd : TEXCOORD0,
           out float4 fucxmul : TEXCOORD1,
           out float4 vpos : SV_Position)
{
    vpos = float4(0,0,0,1);
    vpos.x = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 0]);
    vpos.y = dot(pos, vfuniforms[afactor.b*255.01f * 4 + 2+ 0.1f + 1]);
    

    color = acolor;
    

    fucxadd = vfuniforms[afactor.b*255.01f * 4 + 0+ 0.1f];
    fucxmul = vfuniforms[afactor.b*255.01f * 4 + 1+ 0.1f];
    

      factor = afactor;
    
}
