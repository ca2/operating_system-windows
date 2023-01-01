#pragma once


#undef INLINE

#ifdef __cplusplus
#define MOVE_SEMANTICS
#endif


#define PARALLELIZATION_WIN32




//#ifdef _DEBUG
//#define DEBUG
//#endif



#define __L(x) L#x






#define NOTHROW noexcept // as of C++17
#define THROWS // as of C++17

#ifdef DEBUG
#define RELEASENOTHROW // as of C++17
#else
#define RELEASENOTHROW noexcept // as of C++17
#endif




#define WINDOWS


#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <stdarg.h>



#ifdef _CUSTOM
// Put any custom configuration items in ::windows_definition::v_cfg.h
#include <::windows_definition::v_cfg.h>
#endif


#include <concepts>



#include "platform_dll.h"

// Define this virtual key for use by status bar
#ifndef VK_KANA
#define VK_KANA             0x15
#endif



#include <intrin.h>


#define DEBUG_BREAK __debugbreak()






#include "platform_cpu.h"






#include "cross/cross.h"




























//#if WINVER >= 0x600
//#include <D2d1_1.h>
//#endif
//
//#include <winreg.h>
//#include <winnls.h>
#include <stddef.h>
#include <limits.h>
//#include <malloc.h>
#ifdef VC6
#include <mbstring.h>
#endif
#include <new.h>
#include <eh.h>

#undef __window_procedure

//#define MAX_DWORD_PTR ((uptr)(-1))





#define IMPLEMENT_VISTA_TOOLS
#ifndef WIN32
#define WIN32
#endif
#define DRAWDIB_INCLUDE_STRETCHDIB

#ifdef __cplusplus

#include <typeinfo>

typedef std::type_info std_type_info;

#endif


typedef wchar_t unichar;

#ifdef UNICODE

using platform_char = wchar_t;

#else

using platform_char = char;

#endif

