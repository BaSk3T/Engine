#include "Sampler.h"

#include "Device.h"

#include "../DebugHelper.h"

Sampler::Sampler(IDevice& device)
{
	ID3D11Device* dev = static_cast<Device&>(device).GetDevice();

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	HRESULT hr = dev->CreateSamplerState(&samplerDesc, &m_Sampler);
	
	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create sampler state!\n");
	}
}

Sampler::~Sampler()
{
	m_Sampler->Release();
}
