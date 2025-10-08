float4 cxmul : register(c0);
void main( out float4 fcolor : COLOR0)
{
    fcolor = cxmul;
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    
}
