SamplerState sampler_tex[4] : register(s0);
Texture2D tex[4] : register(t0);
void main( float4 fucxadd : TEXCOORD0,
           float4 fucxmul : TEXCOORD1,
           float2 tc0 : TEXCOORD2,
           out float4 fcolor : SV_Target0)
{
    float c0 = float((tex[0].Sample(sampler_tex[0], tc0).r - 16./255.) * 1.164);
    float U0 = float(tex[1].Sample(sampler_tex[1], tc0).r - 128./255.);
    float V0 = float(tex[2].Sample(sampler_tex[2], tc0).r - 128./255.);
    float4 c = float4(c0,c0,c0,c0);
    float4 U = float4(U0,U0,U0,U0);
    float4 V = float4(V0,V0,V0,V0);
    c += V * float4(1.596, -0.813, 0, 0);
    c += U * float4(0, -0.392, 2.017, 0);
    c.a = tex[3].Sample(sampler_tex[3], tc0).r;
    fcolor = c;
    

    fcolor = fcolor * fucxmul + fucxadd;
    

      fcolor = fcolor;
    
}
