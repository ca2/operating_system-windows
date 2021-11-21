#pragma once


#include "app-core/multimedia/multimedia/multimedia.h"
#include <Mmreg.h>
#include <dsound.h>



#if defined(_MULTIMEDIA_DIRECTSOUND_LIBRARY)
   #define CLASS_DECL_MULTIMEDIA_DIRECTSOUND  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_DIRECTSOUND  CLASS_DECL_IMPORT
#endif


#include "multimedia_directsound_translation.h"


#include "([a-z0-9_]+)_factory.h"
