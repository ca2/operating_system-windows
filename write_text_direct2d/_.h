// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/_.h"
#include "aura/operating_system.h"
#include "direct2d/_.h"
#include "apex_windows/process_data.h"


#ifdef _WRITE_TEXT_DIRECT2D_STATIC
#define CLASS_DECL_WRITE_TEXT_WIN32
#elif defined(_WRITE_TEXT_DIRECT2D_LIBRARY)
#define CLASS_DECL_WRITE_TEXT_DIRECT2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WRITE_TEXT_DIRECT2D  CLASS_DECL_IMPORT
#endif


#include "font_department.h"


#include "write_text.h"



