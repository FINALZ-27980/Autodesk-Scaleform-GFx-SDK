void main( float4 color : COLOR0,
           float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           out float4 fcolor : COLOR0)
{
  fcolor = color;
  

    fcolor = fcolor * fucxmul + fucxadd;
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    
}
