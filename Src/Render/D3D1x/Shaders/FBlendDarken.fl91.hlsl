sampler2D dsttex : register(s0);
sampler2D srctex : register(s1);
void main( half2 tc0 : TEXCOORD0,
           half2 tc1 : TEXCOORD1,
           out float4 fcolor : COLOR0)
{
        float4 src = tex2D(srctex, tc0);
        float4 dst = tex2D(dsttex, tc1);
        float3 clr = min(src.rgb, dst.rgb);
        fcolor.rgb = clr * (dst.a) + (1-dst.a)*src.rgb + dst.rgb*(1-src.a);        
        fcolor.a   = src.a + (1.0-src.a)*dst.a;
    
}
