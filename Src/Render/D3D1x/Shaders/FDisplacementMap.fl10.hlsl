cbuffer Constants { 
float4 compx : packoffset(c0);
float4 compy : packoffset(c1);
float4 mapScale : packoffset(c2);
float2 scale : packoffset(c3);
};

SamplerState sampler_maptex : register(s0);
Texture2D maptex : register(t0);
SamplerState sampler_tex : register(s1);
Texture2D tex : register(t1);
void main( half2 tc0 : TEXCOORD0,
           out float4 fcolor : SV_Target0)
{
    float2 mapTC = tc0*mapScale.xy - mapScale.zw;
    float mapInBoundsLow  = dot(step(mapTC, float2(0,0)), float2(1,1));
    float mapInBoundsHigh = dot(step(float2(1,1), mapTC), float2(1,1));
    float mapInBounds = 1 - clamp(mapInBoundsLow + mapInBoundsHigh, 0.0, 1.0f);
    fcolor = maptex.Sample(sampler_maptex,mapTC) * mapInBounds + float4(0.5,0.5,0.5,0.5) * (1-mapInBounds);

    float2 tc1;
    float2 componentChannel;
    componentChannel.x = dot(float4(1,1,1,1), compx * fcolor);
    componentChannel.y = dot(float4(1,1,1,1), compy * fcolor);
    tc1 = tc0 + (componentChannel - 0.5f) * scale;
    fcolor = tex.Sample(sampler_tex, tc1);
    

      fcolor = fcolor;
    
}
