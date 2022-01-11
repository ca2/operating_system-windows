#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM source :
         virtual public ::multimedia::audio_mixer::source
      {
      public:


         


         MIXERLINE                     m_mixerline;
         MIXERLINECONTROLS             m_mixerlinecontrols;


         source();
         virtual ~source();


         void     mixerGetLineInfo(u32 dwSource, u32 dwDestination, u32 fdwInfo);
         void     mixerGetLineInfo(u32 dwSource, ::multimedia::audio_mixer::destination * pdestination);

         virtual ::id GetLineID() override;

         virtual string get_source_name() override;
         virtual string get_source_short_name() override;

         void update_all_controls();
         MIXERLINECONTROLS & get_mixer_line_controls();
         MIXERLINE & get_mixer_line();
         ::multimedia::audio_mixer::control_array & get_control_array();

         ::multimedia::audio_mixer::device * get_device();

         void SetDestination(::multimedia::audio_mixer::destination * pdestination);
         ::multimedia::audio_mixer::destination * get_destination();

         void OnMixerLineChange();
         //void OnArrayReallocation(void *pNewPointer);
         //void     GetControl(u32 dwControlType, u32 dwControlFlags, ::multimedia::audio_mixer::control ** ppControl);
         void     GetLineControls();

         inline bool HasV001Controls();

      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia







