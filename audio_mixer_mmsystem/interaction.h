#pragma once


#include "aura/user/user/interaction.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class audio_mixer;


      class interaction :
         public ::user::interaction
      {
      public:


         ::pointer<audio_mixer>  m_paudiomixer;


         interaction();
         ~interaction() override;


         void install_message_routing(::channel * pchannel);


         DECLARE_MESSAGE_HANDLER(_001OnMixerControlChange);
         DECLARE_MESSAGE_HANDLER(_001OnMixerLineChange);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia



