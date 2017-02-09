#ifndef IINPUTLAYOUT_H
#define IINPUTLAYOUT_H

#include "../Formats.h"
#include "../../Types.h"

struct InputElement
{
	char* m_SemanticName;
	UI32 m_SemanticIndex;
	RESOURCE_DATA_FORMAT m_Format;
	UI32 m_InputSlot;
	UI32 m_AlignedByteOffset;
};

class IInputLayout
{
public:
	IInputLayout() {};
	virtual ~IInputLayout() {};
};

#endif // !IINPUTLAYOUT_H
