sampler2D tex : register(s0);
void main( float4 factor : COLOR0,
           half2 tc : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex,tc);
    

    fcolor.a *= factor.a;
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    
}
