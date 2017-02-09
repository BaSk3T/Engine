#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

class IDevice;
struct ID3D11InputLayout;

#include <vector>

#include "Interfaces\IInputLayout.h"
#include "Shader.h"

class InputLayout : public IInputLayout
{
public:
	InputLayout(IDevice& device, Shader<VertexShader>& vertexShader, std::vector<InputElement>& inputElements);
	~InputLayout();
	
	ID3D11InputLayout* GetPointer() const { return m_Layout; };

private:
	ID3D11InputLayout* m_Layout;
};

#endif // !INPUTLAYOUT_H
