#pragma once


#include "audio-system/audio_mixer/audio_mixer.h"

//
//namespace multimedia
//{
//

   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM audio_mixer :
         virtual public ::audio_mixer::audio_mixer
      {
      public:


         ::pointer<::audio_mixer_mmsystem::interaction> m_pinteraction;


         audio_mixer();
         ~audio_mixer() override;


         void initialize(::particle * pparticle) override;
            
            
         void set_new_device(unsigned int uiMixerId);


         virtual void on_message(::message::message * pmessage);
         void OnMixerControlChange(HMIXER hMixer, unsigned int dwControlID);
         void OnMixerLineChange(HMIXER hMixer, unsigned int dwLineID);


         static bool get_component_name(LPMIXERLINE pmxl, string & strComponent);
         static bool get_control_type_name(LPMIXERCONTROL pmxctrl, string & strTypeName);



      };


   } // namespace audio_mixer_mmsystem
//
//
//} // namespace multimedia
//
//
//
