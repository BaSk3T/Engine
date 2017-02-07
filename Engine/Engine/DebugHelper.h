#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include <sstream>
#include <Windows.h>

#define OUTPUT_DEBUG									\
std::stringstream ss;									\
OutputDebugStringA(ss.str().c_str());					\

#endif // !DEBUGHELPER_H
