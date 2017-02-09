#ifndef FORMATCONVERTER_H
#define FORMATCONVERTER_H

#include <d3d11.h>

#include "Formats.h"

DXGI_FORMAT ConvertResourceDataFormat(RESOURCE_DATA_FORMAT type);
D3D_PRIMITIVE_TOPOLOGY ConvertPrimitive(PRIMITIVE_TOPOLOGY_TYPE type);

#endif // !FORMATCONVERTER_H
