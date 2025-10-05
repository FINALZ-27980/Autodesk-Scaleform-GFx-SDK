struct PixelShaderInput
{
	float4 pos      : SV_POSITION;
	float2 texcoord : TEXCOORD;
};
 
Texture2D		g_texture_0 : register(t0);
Texture2D		g_texture_1 : register(t1);
Texture2D		g_texture_2 : register(t2);
Texture2D		g_texture_3 : register(t3);
SamplerState	g_sampler   : register(s0);

float4 main(PixelShaderInput input) : SV_TARGET
{
     float4 TexY = g_texture_0.Sample( g_sampler, input.texcoord );
     float4 TexU = g_texture_1.Sample( g_sampler, input.texcoord ) - float4( 0.5f, 0.5f, 0.5f, 0.5f );
     float4 TexV = g_texture_2.Sample( g_sampler, input.texcoord ) - float4( 0.5f, 0.5f, 0.5f, 0.5f );
     float4 Color = ( TexY.a - float4( 0.0625f, 0.0625f, 0.0625f, 0.0625f ) ) * 1.164f;
     Color.a = 1.0f;
     Color.r +=                   TexV.a * 1.596f;
     Color.g += -TexU.a * 0.392f -TexV.a * 0.813f;
     Color.b +=  TexU.a * 2.017f;
     return Color;
}