
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx
// https://en.wikipedia.org/wiki/Phong_reflection_model

struct PS_INPUT
{
	float4 position : SV_POSITION;	// interpolated vertex position (system value)
	float4 normal	: TEXCOORD0;	    // interpolated normal
};

cbuffer MatrixConstantBuffer : register(b0)
{
	float4x4 worldViewProjection;
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float4 lightDirection;
	float4 viewDirection;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 normal = normalize(input.normal);
	float4 lightDir = normalize(lightDirection);
	float4 viewDir = normalize(viewDirection);

	float4 lightAmbient = float4(0.2, 0.2, 0.2, 1);
	float4 lightDiffuse = float4(1, 1, 1, 1);
	float4 lightSpecular = float4(1, 1, 1, 1);

	float4 reflection = normalize(2 * dot(lightDir, normal) * normal - lightDir);

	float4 ambient = materialAmbient * lightAmbient;
	float4 diffuse = materialDiffuse * max(dot(normal, lightDirection), 0) * lightDiffuse;
	float4 specular = materialSpecular * pow(dot(reflection, viewDir), 2) * lightSpecular;

	return ambient + diffuse + specular;
}