#ifndef IDEVICE_H
#define IDEVICE_H

class IDeviceContext;
class IRenderTarget;

class IDevice
{
public:
	IDevice() {};
	virtual ~IDevice() {};

	IDeviceContext* GetImmediateContext() { return m_ImmediateContext; };
	IRenderTarget* GetMainRenderTarget() { return m_MainRenderTarget; };

protected:
	IDeviceContext* m_ImmediateContext;
	IRenderTarget* m_MainRenderTarget;
};

#endif // !IDEVICE_H