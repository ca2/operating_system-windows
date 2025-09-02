#include "framework.h"
#include "interaction.h"
#include "audio_mixer.h"


//namespace multimedia
//{
//

namespace audio_mixer_mmsystem
{


   interaction::interaction()
   {

   }


   interaction::~interaction()
   {

   }


   void interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(MM_MIXM_CONTROL_CHANGE, pchannel, this, &interaction::_001OnMixerControlChange);
      USER_MESSAGE_LINK(MM_MIXM_LINE_CHANGE, pchannel, this, &interaction::_001OnMixerLineChange);

   }


   void interaction::_001OnMixerControlChange(::message::message * pmessage)
   {

      auto paudiomixer = m_paudiomixer;

      paudiomixer->OnMixerControlChange((HMIXER)pmessage->m_wparam.m_number, (unsigned int)pmessage->m_lparam);

      pmessage->m_lresult = 0;

   }


   void interaction::_001OnMixerLineChange(::message::message * pmessage)
   {

      auto paudiomixer = m_paudiomixer;

      paudiomixer->OnMixerLineChange((HMIXER)pmessage->m_wparam.m_number, (unsigned int)pmessage->m_lparam);

      pmessage->m_lresult = 0;

   }


} // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
//
//
//
