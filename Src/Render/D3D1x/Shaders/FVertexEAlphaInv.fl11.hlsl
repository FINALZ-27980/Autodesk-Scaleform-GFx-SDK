void main( float4 color : COLOR0,
           float4 factor : COLOR1,
           out float4 fcolor : SV_Target0)
{
  fcolor = color;
  

    fcolor.a *= factor.a;
    

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
