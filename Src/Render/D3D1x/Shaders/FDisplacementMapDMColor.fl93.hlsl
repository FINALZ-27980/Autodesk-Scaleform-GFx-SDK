float4 boundColor : register(c0);
float4 compx : register(c1);
float4 compy : register(c2);
float4 mapScale : register(c3);
sampler2D maptex : register(s0);
float2 scale : register(c4);
sampler2D tex : register(s1);
void main( half2 tc0 : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    float2 mapTC = tc0*mapScale.xy - mapScale.zw;
    float mapInBoundsLow  = dot(step(mapTC, float2(0,0)), float2(1,1));
    float mapInBoundsHigh = dot(step(float2(1,1), mapTC), float2(1,1));
    float mapInBounds = 1 - clamp(mapInBoundsLow + mapInBoundsHigh, 0.0, 1.0f);
    fcolor = tex2D(maptex,mapTC) * mapInBounds + float4(0.5,0.5,0.5,0.5) * (1-mapInBounds);

    float2 tc1;
    float2 componentChannel;
    componentChannel.x = dot(float4(1,1,1,1), compx * fcolor);
    componentChannel.y = dot(float4(1,1,1,1), compy * fcolor);
    tc1 = tc0 + (componentChannel - 0.5f) * scale;
    fcolor = tex2D(tex, tc1);
    

    float srcInBoundsLow  = dot(step(tc1, float2(0,0)), float2(1,1));
    float srcInBoundsHigh = dot(step(float2(1,1), tc1), float2(1,1));
    float srcInBounds     = 1 - clamp(srcInBoundsLow + srcInBoundsHigh, 0.0, 1.0f);
    fcolor = (fcolor * srcInBounds) + boundColor * (1-srcInBounds);
    

      fcolor = fcolor;
    
}
