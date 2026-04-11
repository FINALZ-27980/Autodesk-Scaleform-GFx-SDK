float4x4 cxmul : register(c0);
float4x4 cxmul1 : register(c4);
sampler2D tex[2] : register(s0);
void main( float2 tc0 : TEXCOORD0,
           float2 tc1 : TEXCOORD1,
           out float4 fcolor : COLOR0)
{
    float4 fcolor_original = tex2D(tex[0], tc0);
    float4 fcolor_source   = tex2D(tex[1], tc1);
    fcolor = mul(fcolor_original, cxmul) + mul(fcolor_source, cxmul1);
    
}
