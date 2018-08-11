//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ModelCBuffer : register(b0)
{
	matrix model;
	matrix world;
	matrix projection;
	matrix view;
};

Texture2D txDiffuse : register(t0); // texture
SamplerState samWrap : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float3 Norm : NORMAL0;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Pixel Shader Entry Point
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float4 textureColor = txDiffuse.Sample(samWrap, input.Tex);

	return textureColor;
};	