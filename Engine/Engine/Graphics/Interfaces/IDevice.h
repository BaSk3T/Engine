#ifndef IDEVICE_H
#define IDEVICE_H

class IDeviceContext;
class IRenderTarget;

class IDevice
{
public:
	IDevice() {};
	virtual ~IDevice() {};

	virtual void Present() = 0;

	IDeviceContext* GetImmediateContext() const { return m_ImmediateContext; };
	IRenderTarget* GetMainRenderTarget() const { return m_MainRenderTarget; };

protected:
	IDeviceContext* m_ImmediateContext;
	IRenderTarget* m_MainRenderTarget;
};

#endif // !IDEVICE_H