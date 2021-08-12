#pragma once


#include "app-core/audio/audio/_.h"
#include "apex_windows/_.h"


#if defined(_MULTIMEDIA_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_IMPORT
#endif



