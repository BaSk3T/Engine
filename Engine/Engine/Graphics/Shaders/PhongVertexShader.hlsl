
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx

struct VS_INPUT
{
	float4 position : POSITION;
	float4 normal   : NORMAL;
};

struct PS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 normal	: TEXCOORD0;
	float4 viewDir	: TEXCOORD1;
};

cbuffer MatrixConstantBuffer : register(b0)
{
	float4x4 worldViewProjection;
	float4x4 world;
};

cbuffer SceneConstantBuffer : register(b1)
{
	float4 lightDirection;
	float4 cameraPosition;
};

PS_OUTPUT main(VS_INPUT input)
{
	PS_OUTPUT output;

	float4 pos = input.position;
	float4 normal = input.normal;

	pos = mul(worldViewProjection, pos);
	normal = mul(world, normal);

	float4 positionInWorld = mul(world, input.position);

	output.position = pos;
	output.normal = normal;
	output.viewDir = cameraPosition - positionInWorld;

	return output;
}