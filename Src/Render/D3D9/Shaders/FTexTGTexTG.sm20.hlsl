sampler2D tex[2] : register(s0);
void main( float4 factor : COLOR0,
           half2 tc0 : TEXCOORD0,
           half2 tc1 : TEXCOORD1,
           out float4 fcolor : COLOR0)
{
    float4 fcolor0 = tex2D(tex[0], tc0);
    float4 fcolor1 = tex2D(tex[1], tc1);
    fcolor = lerp(fcolor1, fcolor0, factor.r);
    

      fcolor = fcolor;
    
}
