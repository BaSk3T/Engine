#include "FormatConverter.h"

#include <assert.h>

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

D3D_PRIMITIVE_TOPOLOGY ConvertPrimitive(PRIMITIVE_TOPOLOGY_TYPE type)
{
	static D3D_PRIMITIVE_TOPOLOGY s_PrimitveTopologyTypes[]
	{
		D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	};

	// make sure number of elements in s_PrimitveTopologyTypes is equal to count in PRIMITIVE_TOPOLOGY_TYPE
	assert(sizeof(s_PrimitveTopologyTypes) / sizeof(s_PrimitveTopologyTypes[0]) == PRIMITIVE_TOPOLOGY_TYPE_COUNT);

	return s_PrimitveTopologyTypes[type];
}

D3D11_MAP ConvertMapType(MAP_TYPE type)
{
	static D3D11_MAP s_MapType[]
	{
		D3D11_MAP_READ,
		D3D11_MAP_WRITE,
		D3D11_MAP_READ_WRITE,
		D3D11_MAP_WRITE_DISCARD,
		D3D11_MAP_WRITE_NO_OVERWRITE
	};

	// make sure number of elements in s_MapType is equal to count in MAP_TYPE
	assert(sizeof(s_MapType) / sizeof(s_MapType[0]) == MAP_COUNT);

	return s_MapType[type];
}