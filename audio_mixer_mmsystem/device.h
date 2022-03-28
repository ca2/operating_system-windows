#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM device :
         virtual public ::multimedia::audio_mixer::device
      {
      public:


         HMIXER                        m_hMixer;
         MIXERCAPS                     m_mixercaps;


         device();
         ~device() override;

         
         void initialize_audio_mixer_device(::multimedia::audio_mixer::audio_mixer * pmixer) override;


         ::multimedia::audio_mixer::audio_mixer * get_mixer();

         virtual string get_product_name() override;
         virtual void on_message(::message::message * pmessage);
         void     close();
         void MapDlgCtrlIDToLineControls(::multimedia::audio_mixer::source * pSource);
         void MapDlgCtrlIDToControls();
         void MapLineControls(::multimedia::audio_mixer::source * pSource);
         void OnMixerControlChange(u32 dwControlID);
         void OnMixerLineChange(u32 dwLineID);
         void map_lines();
         void map_controls();
         
         __pointer(::multimedia::audio_mixer::destination) get_destination(::multimedia::audio_mixer::e_destination edestination) override;

         void     initialize_destinations();
         void     initialize_capabilities();
         void     open(u32 uiMixerId, UINT_PTR dwCallback, u32 dwInstance, u32 fdwOpen);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia





