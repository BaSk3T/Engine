
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx
// https://en.wikipedia.org/wiki/Phong_reflection_model

struct PS_INPUT
{
	float4 position : SV_POSITION;	// interpolated vertex position (system value)
	float4 normal	: TEXCOORD0;	// interpolated normal
	float4 viewDir	: TEXCOORD1;
};

cbuffer MaterialsConstantBuffer : register(b0)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
};

cbuffer SceneConstantBuffer : register(b1)
{
	float4 lightDirection;
	float4 cameraPosition;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 normal = normalize(input.normal);
	float4 lightDir = normalize(lightDirection);
	float4 viewDirection = normalize(input.viewDir);

	float4 lightAmbient = float4(0.2, 0.2, 0.2, 1);

	float nDotL = max(0, dot(normal, lightDir));
	float4 reflection = normalize(2 * nDotL * normal - lightDir);
	float rDotV = max(0, dot(reflection, viewDirection));

	float4 ambient = materialAmbient * lightAmbient;
	float4 diffuse = materialDiffuse * nDotL;
	float4 specular = materialSpecular * pow(rDotV, 30);

	return ambient + diffuse + specular;
}