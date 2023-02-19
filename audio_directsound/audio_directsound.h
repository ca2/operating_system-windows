#pragma once


#include "platform/multimedia_directsound/multimedia_directsound.h"



#if defined(_audio_directsound_project)
   #define CLASS_DECL_AUDIO_DIRECTSOUND  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_DIRECTSOUND  CLASS_DECL_IMPORT
#endif


#include "audio_directsound_out.h"
#include "audio_directsound_in.h"


#include "([a-z0-9_]+)_factory.h"
