#include "framework.h"


namespace multimedia
{


   namespace audio_xaudio7
   {


      in::in(::pointer<::axis::application>papp) :
         object(papp),
         ::thread(papp),
         wave_base(papp),
         ::wave::in(papp)
      {

         m_pencoder = nullptr;
//         m_hwavein = nullptr;
         m_estate = e_state_initial;
         m_bResetting = false;

      }

      in::~in()
      {
      }

      bool in::initialize_instance()
      {
         informationf("in::initialize_instance %X\n", get_os_int());
         //SetMainWnd(nullptr);
         //ASSERT(GetMainWnd() == nullptr);
         set_thread_priority(::e_priority_highest);
         m_happeningInitialized.set_happening();
         return true;
      }

      int in::exit_thread()
      {
         m_happeningExitInstance.set_happening();
         return thread::exit_thread();
      }

      void in::pre_translate_message(::message::message * pmessage)
      {
         ::pointer<::user::message>pusermessage(pmessage);
         //ASSERT(GetMainWnd() == nullptr);
         //if(pusermessage->id() == MM_WIM_OPEN ||
         //   pusermessage->id() == MM_WIM_CLOSE ||
         //   pusermessage->id() == MM_WIM_DATA)
         //{
         //   translate_in_message(pusermessage);
         //   if(pusermessage->m_bRet)
         //      return;
         //}
         return thread::pre_translate_message(pusermessage);
      }

      void     in::in_open(int iBufferCount, int iBufferSampleCount)
      {

//         if(m_hwavein != nullptr && m_estate != e_state_initial)
//         {
//            in_initialize_encoder();
//
//            return ::success;
//
//         }
//
//         single_lock sLock(&m_mutex, true);
//         void     mmr;
//         ASSERT(m_hwavein == nullptr);
//         ASSERT(m_estate == e_state_initial);
//
//         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
//         m_pwaveformat->nChannels = 2;
//         m_pwaveformat->nSamplesPerSec = 44100;
//         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
//         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize = 0;
//         ::pointer<::audio::wave>audiowave = papplication->audiowave();
//         m_iBuffer = 0;
//
//         if(MMSYSERR_NOERROR == (mmr = xaudio7::translate(waveInOpen(
//            &m_hwavein,
//            audiowave->m_uiWaveInDevice,
//            wave_format(),
//            get_os_int(),
//            (unsigned int) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//
//         m_pwaveformat->nSamplesPerSec = 22050;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(MMSYSERR_NOERROR == (mmr = xaudio7::translate(waveInOpen(
//            &m_hwavein,
//            WAVE_MAPPER,
//            wave_format(),
//            (unsigned int) get_os_int(),
//            (unsigned int) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 11025;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(MMSYSERR_NOERROR == (mmr = xaudio7::translate(waveInOpen(
//            &m_hwavein,
//            WAVE_MAPPER,
//            wave_format(),
//            (unsigned int) get_os_int(),
//            (unsigned int) 0,
//            CALLBACK_THREAD))))
//            goto Opened;
//
//         if(mmr !=MMSYSERR_NOERROR)
//         {
//            if(mmr == MMSYSERR_ALLOCATED)
//            {
//               informationf("Specified resource is already allocated.");
//            }
//            else if(mmr == MMSYSERR_BADDEVICEID)
//            {
//               informationf("Specified device identifier is out of range.");
//            }
//            else if(mmr == WAVERR_BADFORMAT)
//            {
//               informationf("Attempted to open with an unsupported waveform-audio_xaudio7 format.");
//            }
//            informationf("ERROR OPENING WAVE INPUT DEVICE");
//            return mmr;
//         }
//
//Opened:
//         unsigned int uiBufferSizeLog2;
//         unsigned int uiBufferSize;
//         unsigned int uiAnalysisSize;
//         unsigned int uiAllocationSize;
//         unsigned int uiInterestSize;
//         unsigned int uiSkippedSamplesCount;
//
//         if(m_pwaveformat->nSamplesPerSec == 44100)
//         {
//            uiBufferSizeLog2 = 16;
//            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            if(iBufferCount > 0)
//            {
//               uiAllocationSize = iBufferCount * uiBufferSize;
//            }
//            else
//            {
//               uiAllocationSize = 8 * uiAnalysisSize;
//            }
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 2;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
//         in_get_buffer()->FFTOpen(
//            uiAllocationSize,
//            uiBufferSize,
//            uiAnalysisSize,
//            uiInterestSize,
//            uiSkippedSamplesCount);
//
//         int i, iSize;
//
//         iSize = (int) in_get_buffer()->GetBufferCount();
//
//         for(i = 0; i < iSize; i++)
//         {
//
//            if(MMSYSERR_NOERROR != (mmr = xaudio7::translate(waveInPrepareHeader(m_hwavein, xaudio7::create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR)))))
//            {
//               informationf("ERROR OPENING Preparing INPUT DEVICE buffer");
//               return mmr;
//            }
//
//            in_add_buffer(i);
//
//         }
//
//         if(m_pencoder != nullptr && !in_initialize_encoder())
//         {
//
//            m_estate = e_state_opened;
//
//            in_close();
//
//            return (void    ) -1;
//
//         }
//
//         m_estate = e_state_opened;
//
         return ::success;

      }


      void     in::in_close()
      {

         single_lock sLock(&m_mutex, true);

         //void     mmr;

         //if(m_estate != e_state_opened && m_estate != state_stopped)
         //   return ::success;

         //mmr = in_reset();

         //int i, iSize;

         //iSize = (int) in_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         //   if(::success != (mmr = xaudio7::translate(waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR)))))
         //   {
         //      informationf("ERROR OPENING Unpreparing INPUT DEVICE buffer");
         //      //return mmr;
         //   }

         //   delete wave_hdr(i);

         //}

         //mmr = xaudio7::translate(waveInClose(m_hwavein));

         //m_hwavein = nullptr;

         //m_estate = e_state_initial;

         return ::success;

      }

      void     in::in_start()
      {

         single_lock sLock(&m_mutex, true);

         if(m_estate == state_recording)
            return ::success;

         //ASSERT(m_estate == e_state_opened || m_estate == state_stopped);

         if(m_estate != e_state_opened && m_estate != state_stopped)
            return ::success;

         //void     mmr;

         //if(::success != (mmr = xaudio7::translate(waveInStart(m_hwavein))))
         //{
         //   informationf("ERROR starting INPUT DEVICE ");
         //   return mmr;
         //}

         m_estate = state_recording;

         return ::success;

      }

      void     in::in_stop()
      {

         single_lock sLock(&m_mutex, true);

         if(m_estate != state_recording)
            return error_failed;

         void     mmr;

         m_estate = e_state_stopping;

         //try
         //{

         //   if(::success != (mmr = xaudio7::translate(waveInStop(m_hwavein))))
         //   {

         //      informationf("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");

         //   }

         //}
         //catch(...)
         //{

         //   informationf("in::in_stop : Exception OPENING stopping INPUT DEVICE ");

         //}

         m_estate = state_stopped;

         m_happeningStopped.set_happening();

         return ::success;

      }


      //void CALLBACK in::in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
      //{

      //   __UNREFERENCED_PARAMETER(hwi);
      //   __UNREFERENCED_PARAMETER(dwInstance);
      //   __UNREFERENCED_PARAMETER(dwParam1);
      //   __UNREFERENCED_PARAMETER(dwParam2);
      //   if(uMsg == WIM_DATA)
      //   {
      //      ASSERT(false);
      //      /*      unsigned int msSampleTime = timeGetTime();
      //      thread * pthread = (thread *) dwInstance;
      //      ASSERT(pthread != nullptr);
      //      LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
      //      LPWAVEPROCDATAMESSAGE lpxfwm = ___new WAVEPROCDATAMESSAGE;
      //      lpxfwm->bDelete = true;
      //      lpxfwm->msSampleTime = msSampleTime;
      //      //      lpxfwm->tickSamplePosition = tickPosition;
      //      lpxfwm->lpWaveHdr = lpWaveHdr;
      //      pthread->post_thread_message(
      //      WM_USER,
      //      (WPARAM) WAVM_WAVE_PROC_DATA,
      //      (LPARAM) lpxfwm);
      //      //      i++;
      //      //      if( i > 2)
      //      //         i = 0;*/
      //   }

      //}


      void     in::in_reset()
      {

         single_lock sLock(&m_mutex, true);

         m_bResetting = true;

         //if(m_hwavein == nullptr)
         //{

         //   return ::success;

         //}

         //void     mmr;

         //if(m_estate == state_recording)
         //{

         //   if(::success != (mmr = in_stop()))
         //   {

         //      informationf("in::Reset error stopping input device");

         //      return mmr;

         //   }

         //}


         //try
         //{

         //   if(::success != (mmr = xaudio7::translate(waveInReset(m_hwavein))))
         //   {
         //
         //      informationf("in::Reset error resetting input device");

         //      return mmr;

         //   }

         //}
         //catch(...)
         //{
         //}

         //m_estate = e_state_opened;

         m_bResetting = false;

         return ::success;

      }


      void in::translate_in_message(::message::message * pmessage)
      {

         ::pointer<::user::message>pusermessage(pmessage);

         //ASSERT(pusermessage->id() == MM_WIM_OPEN || pusermessage->id() == MM_WIM_CLOSE || pusermessage->id() == MM_WIM_DATA);

         //if(pusermessage->id() == MM_WIM_DATA)
         //{
         //
         //   m_iBuffer--;
         //
         //   unsigned int msSampleTime = timeGetTime();
         //
         //   LPWAVEHDR lpwavehdr = (LPWAVEHDR) pusermessage->m_lparam.m_lparam;

         //   in_get_buffer()->get_buffer((int) lpwavehdr->dwUser)->OnMultimediaDone();

         //   m_listenerset.in_data_proc(this, msSampleTime, (int) lpwavehdr->dwUser);

         //   if(m_pencoder != nullptr)
         //   {
         //      m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
         //   }

         //   if(!in_is_resetting() && in_is_recording())
         //   {
         //      in_add_buffer((int) lpwavehdr->dwUser);
         //   }

         //}

         pusermessage->m_bRet = true;

      }


      void     in::in_add_buffer(int iBuffer)
      {

         //return in_add_buffer(wave_hdr(iBuffer));

         return ::success;

      }


      //void     in::in_add_buffer(LPWAVEHDR lpwavehdr)
      //{

      //   void     mmr;

      //   if(::success != (mmr = xaudio7::translate(waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR)))))
      //   {

      //      informationf("ERROR OPENING Adding INPUT DEVICE buffer");

      //   }

      //   m_iBuffer++;

      //   return mmr;

      //}


      bool in::in_initialize_encoder()
      {

         if(m_pencoder == nullptr)
            return false;

         if(!::wave::in::in_initialize_encoder())
            return false;

         return true;

      }

      WAVEFORMATEX * in::wave_format()
      {

         xaudio7::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }

      //HWAVEIN in::in_get_safe_HWAVEIN()
      //{
      //
      //   if(this == nullptr)
      //      return nullptr;

      //   return m_hwavein;

      //}

      void * in::get_os_data()
      {

         //return m_hwavein;

         return nullptr;
      }


      //LPWAVEHDR in::wave_hdr(int iBuffer)
      //{

      //   return ::multimedia::xaudio7::get_os_data(in_get_buffer(), iBuffer);

      //}


   } // namespace audio_xaudio7


} // namespace multimedia






