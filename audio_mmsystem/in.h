#pragma once


#include "audio/audio/wave/in.h"


namespace audio_mmsystem
{


   class  CLASS_DECL_AUDIO_MMSYSTEM in :
      virtual public ::wave::in
   {
   public:


         


      HWAVEIN              m_hwavein;

      WAVEFORMATEX         m_waveformatex;


      in();
      ~in() override;


      virtual void in_initialize_encoder();

      virtual void     in_add_buffer(i32 iBuffer);
      virtual void     in_add_buffer(LPWAVEHDR lpwavehdr);

      HWAVEIN in_get_safe_HWAVEIN();
      virtual void * get_os_data();

      void     in_open(i32 iBufferCount, i32 iBufferSampleCount);
      void     in_close();
      void     in_stop();
      void     in_start();
      void     in_reset();

      virtual void translate_in_message(::message::message * pmessage);

      virtual void init_task() override;
      virtual void term_task() override;
      virtual void pre_translate_message(::message::message * pmessage);

      static void CALLBACK in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

      WAVEFORMATEX * wave_format();
      LPWAVEHDR wave_hdr(int iBuffer);


   };


} // namespace audio_mmsystem



