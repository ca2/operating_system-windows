#pragma once


#include "app-multimedia/multimedia/multimedia.h"
#include <Mmreg.h>
#include <dsound.h>



#if defined(_multimedia_directsound_project)
   #define CLASS_DECL_MULTIMEDIA_DIRECTSOUND  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_MULTIMEDIA_DIRECTSOUND  CLASS_DECL_IMPORT
#endif


#include "multimedia_directsound_translation.h"


#include "([a-z0-9_]+)_factory.h"
