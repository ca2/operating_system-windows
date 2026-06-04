#pragma once


#include "aura/_.h"
#include "acme/operating_system/windows/_gdiplus.h"



#if defined(_gdiplus_library_project)
#define CLASS_DECL_GDIPLUS_LIBRARY CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GDIPLUS_LIBRARY CLASS_DECL_IMPORT
#endif



CLASS_DECL_GDIPLUS_LIBRARY void initialize_gdiplus();
CLASS_DECL_GDIPLUS_LIBRARY void terminate_gdiplus();
