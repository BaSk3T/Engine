#ifndef SAMPLER_H
#define SAMPLER_H

struct ID3D11SamplerState;

class IDevice;

#include "Interfaces/ISampler.h"

class Sampler : public ISampler
{
public:
	Sampler(IDevice& device);
	~Sampler();

	ID3D11SamplerState* GetPointer() const { return m_Sampler; };

private:
	ID3D11SamplerState* m_Sampler;
};

#endif // !SAMPLER_H
