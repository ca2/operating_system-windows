#pragma once


#include "app-core/audio/_.h"
#include "app-core/audio/_.h"
#include "apex_windows/_.h"
#include "apex/operating_system.h"
#include <mmsystem.h>


#if defined(_MULTIMEDIA_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_MMSYSTEM  CLASS_DECL_IMPORT
#endif



CLASS_DECL_MULTIMEDIA_MMSYSTEM::e_status mmresult_to_status(MMRESULT mmr);




