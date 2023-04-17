#pragma once


#include "app-core/multimedia/_.h"
#include "audio-system/audio_mixer/_.h"
#include "multimedia_mmsystem/_.h"



#if defined(_audio_mixer_mmsystem_project)
#define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_IMPORT
#endif




//
//namespace multimedia
//{


namespace audio_mixer_mmsystem
{


   class callback;
   class device;
   class source;
   class destination;
   //class thread;
   class audio_mixer;
   class department;
   class interaction;
   class control;


} // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
