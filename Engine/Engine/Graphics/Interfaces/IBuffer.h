#ifndef IBUFFER_H
#define IBUFFER_H

class IDeviceContext;

#include "../Formats.h"

class IBuffer
{
public:
	IBuffer() {};
	virtual ~IBuffer() {};

	virtual void* Map(IDeviceContext* deviceContext, MAP_TYPE map) = 0;
	virtual void Unmap(IDeviceContext* deviceContext) = 0;
};

#endif // !IBUFFER_H
