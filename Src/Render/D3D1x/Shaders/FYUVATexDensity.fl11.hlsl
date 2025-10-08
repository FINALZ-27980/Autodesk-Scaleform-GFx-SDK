cbuffer Constants { 
float mipLevels : packoffset(c0);
float2 textureDims : packoffset(c1);
};

SamplerState sampler_tex[4] : register(s0);
Texture2D tex[4] : register(t0);
void main( float2 tc0 : TEXCOORD0,
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
