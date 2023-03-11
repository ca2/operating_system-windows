#pragma once


#include "operating_system-windows/multimedia_mmsystem/_.h"


#if defined(_audio_mmsystem_project)
   #define CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_IMPORT
#endif



