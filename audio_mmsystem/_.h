#pragma once


#include "platform-windows/multimedia_mmsystem/_.h"


#if defined(_AUDIO_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_MMSYSTEM  CLASS_DECL_IMPORT
#endif


#include "out.h"
#include "in.h"


#include "factory_exchange.h"