// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/_.h"


#ifdef _WINDOWING_WIN32_STATIC
#define CLASS_DECL_WRITE_TEXT_WIN32
#elif defined(_WRITE_TEXT_WIN32_LIBRARY)
#define CLASS_DECL_WRITE_TEXT_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WRITE_TEXT_WIN32  CLASS_DECL_IMPORT
#endif





