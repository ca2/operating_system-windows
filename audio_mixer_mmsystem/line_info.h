#pragma once


#include "audio-system/audio_mixer/line_info.h"

//
//namespace multimedia
//{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM line_info :
         virtual public ::audio_mixer::line_info
      {
      public:


         


         MIXERLINE       m_mixerLine;


         line_info();
         ~line_info() override;


      };


   } // namespace audio_mixer_mmsystem


//} // namespace multimedia
//
