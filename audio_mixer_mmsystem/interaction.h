#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class audio_mixer;


      class interaction :
         public ::user::interaction
      {
      public:


         __reference(::multimedia::audio_mixer::audio_mixer)   m_pmixer;


         interaction();
         virtual ~interaction();


         void install_message_routing(::channel * pchannel);


         DECLARE_MESSAGE_HANDLER(_001OnMixerControlChange);
         DECLARE_MESSAGE_HANDLER(_001OnMixerLineChange);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia



