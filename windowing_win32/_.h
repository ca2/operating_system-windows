#pragma once


#include "aura/_.h"
#include "aura_windows/_.h"


#ifdef _WINDOWING_WIN32_STATIC
#define CLASS_DECL_WINDOWING_WIN32
#elif defined(_WINDOWING_WIN32_LIBRARY)
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_WIN32  CLASS_DECL_IMPORT
#endif


namespace windowing_win32
{

   
   class windowing;
   class hwnd_array;


} // namespace windowing_win32



