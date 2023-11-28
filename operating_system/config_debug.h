#pragma once


//#define __VLD

//#define __MCRTDBG


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


#ifdef __VLD
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include "vld.h"
#define ::heap::management::memory(::heap::e_memory_main)->allocate malloc
#define memory_reallocate realloc
#define ::heap::management::memory(::heap::e_memory_main)->free free
#endif

#ifdef __MCRTDBG
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#define ::heap::management::memory(::heap::e_memory_main)->allocate malloc
#define memory_reallocate realloc
#define ::heap::management::memory(::heap::e_memory_main)->free free
#endif


#ifdef MEMDLEAK
#endif
