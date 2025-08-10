#pragma once


#include "audio/audio/wave/out.h"


namespace audio_mmsystem
{


   class  CLASS_DECL_AUDIO_MMSYSTEM out :
      virtual public ::wave::out
   {
   public:


      HWAVEOUT                         m_hwaveout;
      WAVEFORMATEX                     m_waveformatex;
      class ::time                       m_time;
      class ::time                       m_timePosition;
      manual_reset_happening               m_happeningFree;
      ::int_array_base                        m_iaFree;
      ::particle                       m_pparticleMutexFree;


      out();
      ~out() override;


      void install_message_routing(::channel * pchannel);

      
      class ::time                 out_get_position() override;
      virtual class ::time         out_get_time();
      virtual class ::time         device_out_get_time();
      virtual void               out_filled(::collection::index iBuffer) override;
      virtual void               out_filled(LPWAVEHDR lpwavehdr);

      virtual void               out_open_ex(::thread * pthreadCallback,  unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample, ::wave::enum_purpose epurpose) override;
      virtual void               out_stop() override;
      virtual void               out_close() override;
      virtual void               out_pause() override;
      virtual void               out_restart() override;
      virtual void *             get_os_data();
      HWAVEOUT                   out_get_safe_HWAVEOUT();

      virtual void               out_on_playback_end();
      virtual void               out_free(::collection::index iBuffer) override;

      virtual void               init_task() override;
      virtual void               term_task() override;


      WAVEFORMATEX *             wave_format();
      LPWAVEHDR                  wave_hdr(::collection::index iBuffer);


   };


} // namespace audio_mmsystem



