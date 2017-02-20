#ifndef TEXTURE_H
#define TEXTURE_H

class IDevice;

struct ID3D11Device;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

namespace DirectX
{
	class ScratchImage;
	struct TexMetadata;
};

#include "Interfaces\ITexture.h"

class Texture : public ITexture
{
public:
	Texture(IDevice& device, wchar_t* path);
	~Texture();

	ID3D11Texture2D* GetTexturePointer() const { return m_Texture; };
	ID3D11ShaderResourceView* GetResourcePointer() const { return m_ResourceView; };

private:
	void LoadTexture(wchar_t* path, DirectX::ScratchImage& image, DirectX::TexMetadata& metaData);
	void CreateTexture(ID3D11Device* device, DirectX::ScratchImage& image, DirectX::TexMetadata& metaData);

	ID3D11Texture2D* m_Texture;
	ID3D11ShaderResourceView* m_ResourceView;
};

#endif // !TEXTURE_H
