#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include <sstream>
#include <Windows.h>

#define OUTPUT_DEBUG(string)				\
   std::ostringstream os_;                  \
   os_ << string;                           \
   OutputDebugStringA( os_.str().c_str() ); \

#endif // !DEBUGHELPER_H
