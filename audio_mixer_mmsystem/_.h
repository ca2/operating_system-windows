#pragma once


#include "app-core/multimedia/multimedia/_.h"
#include "app-core/multimedia/audio_mixer/_.h"
#include "multimedia_mmsystem/_.h"



#if defined(_AUDIO_MIXER_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_IMPORT
#endif





namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class callback;
      class device;
      class source;
      class destination;
      class thread;
      class audio_mixer;
      class department;


   } // namespace audio_mixer_mmsystem


} // namespace multimedia

