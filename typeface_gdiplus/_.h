#pragma once


#include "bred/_.h"
#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#include "acme/_operating_system.h"
#endif
//#include "gpu_opengl/_.h"


#ifdef _TYPEFACE_GDIPLUS_STATIC
#define CLASS_DECL_TYPEFACE_GDIPLUS
#elif defined(_typeface_gdiplus_project)
#define CLASS_DECL_TYPEFACE_GDIPLUS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TYPEFACE_GDIPLUS  CLASS_DECL_IMPORT
#endif


namespace typeface_gdiplus
{

   class face;
   class face_freetype;
   class face_gdiplus;

} // namespace typeface_gdiplus