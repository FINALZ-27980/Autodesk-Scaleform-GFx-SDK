cbuffer Constants { 
float4x4 cxmul : packoffset(c0);
float4x4 cxmul1 : packoffset(c4);
};

SamplerState sampler_tex[2] : register(s0);
Texture2D tex[2] : register(t0);
void main( float2 tc0 : TEXCOORD0,
           float2 tc1 : TEXCOORD1,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor_original = tex[0].Sample(sampler_tex[0], tc0);
    float4 fcolor_source   = tex[1].Sample(sampler_tex[1], tc1);
    fcolor = mul(fcolor_original, cxmul) + mul(fcolor_source, cxmul1);
    
}
