#ifndef BUFFER_H
#define BUFFER_H

struct ID3D11Buffer;

#include "Interfaces/IBuffer.h"

class Buffer : public IBuffer
{
public:
	Buffer();
	virtual ~Buffer();

protected:
	ID3D11Buffer* m_Buffer;
};

#endif // !BUFFER_H
