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


         DECL_GEN_SIGNAL(_001OnMixerControlChange);
         DECL_GEN_SIGNAL(_001OnMixerLineChange);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia



