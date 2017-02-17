
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal   : NORMAL;
};

struct PS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 normal	: TEXCOORD0;
};

cbuffer MatrixConstantBuffer : register(b0)
{
	float4x4 worldViewProjection;
};

PS_OUTPUT main(VS_INPUT input)
{
	PS_OUTPUT output;

	float4 pos = float4(input.position, 1);

	pos = mul(worldViewProjection, pos);

	output.position = pos;
	output.normal = float4(input.normal, 1);

	return output;
}