sampler2D tex[3] : register(s0);
void main( float2 tc0 : TEXCOORD0,
           float2 tc1 : TEXCOORD1,
           float2 tc2 : TEXCOORD2,
           out float4 fcolor : COLOR0)
{
    float4 fcolor_org = tex2D(tex[0], tc0);
    float4 fcolor_src = tex2D(tex[1], tc1);
    float4 fcolor_alp = tex2D(tex[2], tc2);
    float inAlpha = fcolor_src.a * fcolor_alp.a;
    

    fcolor.a = inAlpha;
    

    fcolor.rgb = lerp(fcolor_org.rgb, fcolor_src.rgb, inAlpha / fcolor.a);
    
}
