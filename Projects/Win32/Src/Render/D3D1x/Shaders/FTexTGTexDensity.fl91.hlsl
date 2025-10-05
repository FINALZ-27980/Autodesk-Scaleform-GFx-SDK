float mipLevels : register(c0);
sampler2D tex : register(s0);
float2 textureDims : register(c1);

void main(float2 tc0 : TEXCOORD0, out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex, tc0);

    float2 dx = ddx(tc0 * textureDims.x);
    float2 dy = ddy(tc0 * textureDims.y);
    float d = max(dot(dx, dx), dot(dy, dy));
    float mip = clamp(0.5f * log2(d) - 1.0f, 0.0f, mipLevels - 1.0f); // [0..mip-1]
    dx /= pow(2.0f, mip);
    dy /= pow(2.0f, mip);
    float H = clamp(1.0f - 0.5f * sqrt(max(dot(dx, dx), dot(dy, dy))), 0.0f, 1.0f) * (80.0f / 255.0f);
    float R = abs(H * 6.0f - 3.0f) - 1.0f;
    float G = 2.0f - abs(H * 6.0f - 2.0f);
    float B = 2.0f - abs(H * 6.0f - 4.0f);
    fcolor = fcolor * 0.001f + clamp(float4(R, G, B, 1.0f), 0.0f, 1.0f);
}