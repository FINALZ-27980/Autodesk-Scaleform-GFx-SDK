sampler2D tex : register(s0);
void main( half2 tc : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex,tc);
    

    fcolor.rgb = fcolor.rgb * fcolor.a;
    
}
