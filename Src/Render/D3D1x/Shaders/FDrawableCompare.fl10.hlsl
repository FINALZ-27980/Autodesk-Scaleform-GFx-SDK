SamplerState sampler_tex[2] : register(s0);
Texture2D tex[2] : register(t0);
void main( float2 tc0 : TEXCOORD0,
           float2 tc1 : TEXCOORD1,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor0 = tex[0].Sample(sampler_tex[0], tc0);
    float4 fcolor1 = tex[1].Sample(sampler_tex[1], tc1);

    float4 diff = fcolor0 - fcolor1;
    float4 oneValue = float4(1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f );
    float4 ltZero = (sign(diff)+float4(1,1,1,1))*-0.25f;
    float4 partDiff = oneValue * (sign(ltZero)+float4(1,1,1,1));
    float4 wrapDiff = frac(diff + float4(1,1,1,1)) + partDiff;
    float rgbdiff = sign(dot(wrapDiff.rgb, float3(1,1,1)));
    fcolor = lerp( float4(1,1,1, wrapDiff.a), float4(wrapDiff.rgb, 1), rgbdiff );
    
}
