#pragma once


#undef INLINE

#ifdef __cplusplus
#define MOVE_SEMANTICS
#endif


#define PARALLELIZATION_WIN32




#define __L(x) L#x






#define NOTHROW noexcept // as of C++17
#define THROWS // as of C++17

#ifdef DEBUG
#define RELEASENOTHROW // as of C++17
#else
#define RELEASENOTHROW noexcept // as of C++17
#endif




#define WINDOWS


//#include <stdio.h>
//#include <memory.h>
//#include <string.h>
//#include <wchar.h>
//#include <ctype.h>
#include <stdarg.h>
//

#include <concepts>


#include <tuple>


#include <intrin.h>


#define DEBUG_BREAK __debugbreak()



//#include "cross/cross.h"
#define __time_t time_t
#define stat64 _stat64
using int_bool = int;


#include <stddef.h>
#include <limits.h>
#include <new.h>
#include <eh.h>
#include <new>

#undef __window_procedure


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

