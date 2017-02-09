
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn643748(v=vs.85).aspx

struct PS_INPUT
{
	float4 position : SV_POSITION;	// interpolated vertex position (system value)
	float4 color    : COLOR;	    // interpolated diffuse color
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return input.color;
}