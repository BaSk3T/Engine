#ifndef BUFFER_H
#define BUFFER_H

struct ID3D11Buffer;
class IDeviceContext;

#include "Interfaces/IBuffer.h"
#include "Formats.h"

class Buffer : public IBuffer
{
public:
	Buffer();
	virtual ~Buffer();

	virtual void* Map(IDeviceContext* deviceContext, MAP_TYPE map);
	virtual void Unmap(IDeviceContext* deviceContext);

protected:
	ID3D11Buffer* m_Buffer;
};

#endif // !BUFFER_H
