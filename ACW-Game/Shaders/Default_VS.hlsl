//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ModelCBuffer : register( b0 )
{
	matrix model;
	matrix world;
	matrix projection;
	matrix view;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float3 Norm : NORMAL0;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul(input.Pos, model);
	output.Pos = mul(output.Pos, world);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);
	output.Tex = input.Tex;
	output.Norm = input.Norm;

    return output;
}