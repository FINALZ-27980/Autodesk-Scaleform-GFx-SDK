void main( float4 color : COLOR0,
           out float4 fcolor : SV_Target0)
{
  fcolor = color;
  

    fcolor.rgb = fcolor.rgb * fcolor.a;
    

      fcolor = fcolor;
    
}
