void main( float4 color : COLOR0,
           out float4 fcolor : COLOR0)
{
  fcolor = color;
  

    fcolor.rgb = float3(fcolor.a, fcolor.a, fcolor.a);
    

      fcolor = fcolor;
    
}
