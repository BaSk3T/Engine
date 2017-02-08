#ifndef RENDERTARGET_H
#define RENDERTARGET_H

class IDevice;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;

#include "Interfaces\IRenderTarget.h"

class RenderTarget : public IRenderTarget
{
public:
	RenderTarget(IDevice& device, ID3D11Texture2D* tex);
	~RenderTarget();

	ID3D11RenderTargetView* GetPointer() { return m_RenderTarget; };
private:
	ID3D11RenderTargetView* m_RenderTarget;
};

#endif // !RENDERTARGET_H
