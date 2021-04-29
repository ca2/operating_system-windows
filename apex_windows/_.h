#pragma once


#include "apex/_.h"


#if defined(_WINDOWING_WIN32_LIBRARY)
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_IMPORT
#endif



