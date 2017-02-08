#ifndef FORMATCONVERTER_H
#define FORMATCONVERTER_H

#include <assert.h>
#include <d3d11.h>

#include "Formats.h"

DXGI_FORMAT ConvertResourceDataFormat(RESOURCE_DATA_FORMAT type)
{
	static DXGI_FORMAT s_ResourceDataFormats[]
	{
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R32_UINT
	};

	// make sure number of elements in s_ResourceDataFormats is equal to count in RESOURCE_DATA_FORMAT
	assert(sizeof(s_ResourceDataFormats) / sizeof(s_ResourceDataFormats[0]) == RESOURCE_DATA_FORMAT_COUNT);

	return s_ResourceDataFormats[type];
}

#endif // !FORMATCONVERTER_H
