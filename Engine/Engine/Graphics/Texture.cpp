#include "Texture.h"

#include <directxtex\DirectXTex.h>

#include "Device.h"
#include "../DebugHelper.h"

Texture::Texture(IDevice& device, wchar_t* path)
{
	Device& dev = static_cast<Device&>(device);
	DirectX::ScratchImage image;
	DirectX::TexMetadata metaData;

	LoadTexture(path, image, metaData);
	CreateTexture(dev.GetDevice(), image, metaData);
}

Texture::~Texture()
{
}

void Texture::LoadTexture(wchar_t* path, DirectX::ScratchImage& image, DirectX::TexMetadata& metaData)
{
	HRESULT hr = DirectX::LoadFromDDSFile(path, DirectX::DDS_FLAGS_NONE, &metaData, image);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to load texture: " << path << "\n");
	}
}

void Texture::CreateTexture(ID3D11Device* device, DirectX::ScratchImage& image, DirectX::TexMetadata& metaData)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.ArraySize = metaData.arraySize;
	desc.Height = metaData.height;
	desc.Width = metaData.width;
	desc.MipLevels = metaData.mipLevels;
	desc.Format = metaData.format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = NULL;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.MiscFlags = NULL;

	D3D11_SUBRESOURCE_DATA subresource;
	subresource.pSysMem = image.GetPixels();
	subresource.SysMemPitch = image.GetImages()->rowPitch;
	subresource.SysMemSlicePitch = image.GetImages()->slicePitch;

	HRESULT hr = device->CreateTexture2D(&desc, &subresource, &m_Texture);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create texture!\n");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC resorceDesc;
	resorceDesc.Format = metaData.format;
	resorceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resorceDesc.Texture2D.MostDetailedMip = 0;
	resorceDesc.Texture2D.MipLevels = metaData.mipLevels;

	hr = device->CreateShaderResourceView(m_Texture, &resorceDesc, &m_ResourceView);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG("Failed to create texture as shader resource view!\n");
	}
}
