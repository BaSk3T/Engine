
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx
// https://en.wikipedia.org/wiki/Phong_reflection_model

struct PS_INPUT
{
	float4 position		: SV_POSITION;	// interpolated vertex position (system value)
	float4 normal		: TEXCOORD0;	// interpolated normal
	float2 textureCoord : TEXCOORD1;
	float4 viewDir		: TEXCOORD2;
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

Texture2D tex2D : register(t0);

SamplerState MeshTextureSampler : register(s0)
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 normal = normalize(input.normal);
	float4 lightDir = normalize(lightDirection);
	float4 viewDirection = normalize(input.viewDir);

	float4 lightAmbient = float4(0.2, 0.2, 0.2, 1);
	float4 lightDiffuse = float4(1, 1, 1, 1);
	float4 lightSpecular = float4(1, 1, 1, 1);

	float nDotL = max(0, dot(normal, lightDir));
	float4 reflection = normalize(2 * nDotL * normal - lightDir);
	float rDotV = max(0, dot(reflection, viewDirection));

	float4 ambient = materialAmbient * lightAmbient;
	float4 diffuse = materialDiffuse * nDotL * lightDiffuse;
	float4 specular = materialSpecular * pow(rDotV, 30) * lightSpecular;

	float3 color = tex2D.Sample(MeshTextureSampler, input.textureCoord).rgb;

	return float4(color, 1) * (ambient + diffuse + specular);
}