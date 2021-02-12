#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      interaction::interaction()
      {

         create_message_queue("");

      }


      interaction::~interaction()
      {
      }

      void interaction::install_message_routing(::channel * pchannel)
      {
         ::user::interaction::install_message_routing(pchannel);
         MESSAGE_LINK(MM_MIXM_CONTROL_CHANGE, pchannel, this, &interaction::_001OnMixerControlChange);
         MESSAGE_LINK(MM_MIXM_LINE_CHANGE, pchannel, this, &interaction::_001OnMixerLineChange);
      }


      void interaction::_001OnMixerControlChange(::message::message * pmessage)
      {

         __pointer(audio_mixer) pmixer = m_pmixer.get();
         
         pmixer->OnMixerControlChange((HMIXER)pmessage->m_wparam.m_number, (u32)pmessage->m_lparam);

         pmessage->m_lresult = 0;

      }


      void interaction::_001OnMixerLineChange(::message::message * pmessage)
      {

         __pointer(audio_mixer) pmixer = m_pmixer.get();

         pmixer->OnMixerLineChange((HMIXER)pmessage->m_wparam.m_number, (u32)pmessage->m_lparam);

         pmessage->m_lresult = 0;

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia






