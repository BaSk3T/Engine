#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

class IDevice;
struct ID3D11InputLayout;

#include <vector>

#include "Shader.h"
#include "Formats.h"
#include "../Types.h"

struct InputElement
{
	char* m_SemanticName;
	UI32 m_SemanticIndex;
	RESOURCE_DATA_FORMAT m_Format;
	UI32 m_InputSlot;
	UI32 m_AlignedByteOffset;
};

class InputLayout
{
public:
	InputLayout(IDevice& device, Shader<VertexShader>& vertexShader, std::vector<InputElement>& inputElements);
	~InputLayout();
	
private:
	ID3D11InputLayout* m_Layout;
};

#endif // !INPUTLAYOUT_H
