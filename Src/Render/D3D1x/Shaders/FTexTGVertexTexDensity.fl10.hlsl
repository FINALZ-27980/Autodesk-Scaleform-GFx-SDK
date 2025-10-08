cbuffer Constants { 
float mipLevels : packoffset(c0);
float2 textureDims : packoffset(c1);
};

SamplerState sampler_tex : register(s0);
Texture2D tex : register(t0);
void main( float4 color : COLOR0,
           float4 factor : COLOR1,
           half2 tc0 : TEXCOORD0,
           out float4 fcolor : SV_Target0)
{
    float4 fcolor0 = tex.Sample(sampler_tex,tc0);
    float4 fcolor1 = color;
    fcolor = lerp(fcolor1, fcolor0, factor.r);
    

      fcolor = fcolor;
    

    float2 dx = ddx(tc0 * textureDims.x);
    float2 dy = ddy(tc0 * textureDims.y);
    float d  = max(dot(dx, dx), dot(dy, dy));
    float mip = clamp(0.5f * log2(d) - 1, 0, mipLevels-1); // [0..mip-1]
    dx /= pow(2, mip);
    dy /= pow(2, mip);
    float H = clamp(1.0f - 0.5f * sqrt( max(dot(dx, dx), dot(dy, dy)) ), 0.0f, 1.0f) * (80.0f/255.0f);
    float R = abs(H * 6 - 3) - 1;
    float G = 2 - abs(H * 6 - 2);
    float B = 2 - abs(H * 6 - 4);
    // NOTE: must blend in a little bit of the original fcolor, otherwise the shader compiler might optimize the original block out,
    // because it would no longer contribute to the outputs of the shader.
    fcolor = fcolor*0.001f + clamp(float4(R,G,B, 1), 0.0f, 1.0f);
    
}
