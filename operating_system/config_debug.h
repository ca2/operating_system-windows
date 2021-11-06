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
#define memory_allocate malloc
#define memory_reallocate realloc
#define memory_free free
#endif

#ifdef __MCRTDBG
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#define memory_allocate malloc
#define memory_reallocate realloc
#define memory_free free
#endif


#ifdef MEMDLEAK
#endif
