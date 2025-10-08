sampler2D tex : register(s0);
void main( half2 tc0 : TEXCOORD0,
           float4 vcolor : COLOR0,
           out float4 fcolor : COLOR0)
{
    float4 c = vcolor;
    c.a = c.a * tex2D(tex, tc0).r;
    fcolor = c;
    

      fcolor = fcolor;
    
}
