sampler2D tex : register(s0);
void main( float4 factor : COLOR0,
           half2 tc0 : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex,tc0);
    

    fcolor.a *= factor.a;
    

      fcolor = fcolor;
    
}
