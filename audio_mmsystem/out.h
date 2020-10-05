#pragma once


namespace audio_mmsystem
{


   class  CLASS_DECL_AUDIO_MMSYSTEM out :
      virtual public ::wave::out
   {
   public:


      HWAVEOUT                         m_hwaveout;
      WAVEFORMATEX                     m_waveformatex;
      imedia_time                      m_imediatime;
      imedia_time                      m_imediaposition;
      manual_reset_event               m_evFree;
      int_array                        m_iaFree;
      ::mutex                          m_mutexFree;


      out();
      virtual ~out();


      void install_message_routing(::channel * pchannel);


      virtual imedia_time        out_get_time();
      virtual imedia_time        device_out_get_time();
      virtual void               out_filled(index iBuffer) override;
      virtual void               out_filled(LPWAVEHDR lpwavehdr);

      virtual ::estatus          out_open_ex(::thread * pthreadCallback,  u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::e_purpose epurpose) override;
      virtual ::estatus          out_stop() override;
      virtual ::estatus          out_close() override;
      virtual ::estatus          out_pause() override;
      virtual ::estatus          out_restart() override;
      virtual void *             get_os_data();
      HWAVEOUT                   out_get_safe_HWAVEOUT();

      virtual void               out_on_playback_end();
      virtual void               out_free(index iBuffer) override;

      virtual ::estatus          init_thread() override;
      virtual void               term_thread() override;


      WAVEFORMATEX *             wave_format();
      LPWAVEHDR                  wave_hdr(index iBuffer);


      //virtual bool raw_pump_message() override;

      //virtual void out_launch_buffers() override;


   };


} // namespace audio_mmsystem


