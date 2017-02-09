#ifndef SHADER_H
#define SHADER_H

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class IDevice;
struct ID3D11VertexShader;
struct ID3D11PixelShader;

#include "Interfaces/IShader.h"

struct VertexShader
{
	ID3D11VertexShader* m_Pointer;
};

struct PixelShader
{
	ID3D11PixelShader* m_Pointer;
};

template <class ShaderType>
class Shader : public IShader
{
public:
	Shader(IDevice& device, wchar_t* path, char* entryPoint, char* shaderTarget);
	~Shader();

	ID3DBlob* GetBlob() const { return m_Blob; };
	ShaderType& GetShader() { return m_Shader; };

private:
	void CreateShader(IDevice& device);

	ID3DBlob* m_Blob;
	ShaderType m_Shader;
};

#endif // !SHADER_H