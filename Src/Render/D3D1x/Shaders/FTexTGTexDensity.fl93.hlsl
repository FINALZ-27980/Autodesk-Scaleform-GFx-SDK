float mipLevels : register(c0);
sampler2D tex : register(s0);
float2 textureDims : register(c1);
void main( float2 tc0 : TEXCOORD0,
           out float4 fcolor : COLOR0)
{
    fcolor = tex2D(tex,tc0);
    

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
