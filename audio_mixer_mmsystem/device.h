#pragma once


#include "audio-system/audio_mixer/device.h"

//
//namespace multimedia
//{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM device :
         virtual public ::audio_mixer::device
      {
      public:


         HMIXER                        m_hMixer;
         MIXERCAPS                     m_mixercaps;


         device();
         ~device() override;

         
         void initialize_audio_mixer_device(::audio_mixer::audio_mixer * pmixer) override;


         ::audio_mixer::audio_mixer * get_mixer();

         virtual string get_product_name() override;
         virtual void on_message(::message::message * pmessage);
         void     close();
         void MapDlgCtrlIDToLineControls(::audio_mixer::source * pSource);
         void MapDlgCtrlIDToControls();
         void MapLineControls(::audio_mixer::source * pSource);
         void OnMixerControlChange(u32 dwControlID);
         void OnMixerLineChange(u32 dwLineID);
         void map_lines();
         void map_controls();
         
         ::pointer<::audio_mixer::destination>get_destination(::audio_mixer::e_destination edestination) override;

         void     initialize_destinations();
         void     initialize_capabilities();
         void     open(u32 uiMixerId, UINT_PTR dwCallback, u32 dwInstance, u32 fdwOpen);


      };


   } // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
//
//
