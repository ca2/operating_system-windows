#include "framework.h"
#include "in.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/message/message.h"
#include "aqua/platform/system.h"
#include "audio/audio/audio.h"
#include "audio/audio/wave/wave.h"
#include "audio/audio/decode/encoder.h"
#include "acme_windows/mmresult.h"


namespace audio_mmsystem
{


   in::in()
   {

      m_pencoder = nullptr;
      m_hwavein = nullptr;
      m_einstate = ::wave::e_in_state_initial;
      m_bResetting = false;

   }

   in::~in()
   {
   }


   void in::init_task()
   {

      informationf("in::initialize_instance %X\n", get_itask());

      //SetMainWnd(nullptr);
      //ASSERT(GetMainWnd() == nullptr);

      set_thread_priority(::e_priority_highest);

//         m_evInitialized.SetEvent();

//      return true;

   }


   void in::term_task()
   {

      m_eventExitInstance.SetEvent();

      thread::term_task();

   }


   void in::pre_translate_message(::message::message * pmessage)
   {

      //ASSERT(GetMainWnd() == nullptr);
      if(pmessage->m_atom == MM_WIM_OPEN ||
         pmessage->m_atom == MM_WIM_CLOSE ||
         pmessage->m_atom == MM_WIM_DATA)
      {
         
         translate_in_message(pmessage);

         if (pmessage->m_bRet)
         {

            return;

         }

      }

      return thread::pre_translate_message(pmessage);

   }


   void in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
   {

      if(m_hwavein != nullptr && m_einstate != ::wave::e_in_state_initial)
      {

         in_initialize_encoder();

         //return ::success;

         return;

      }

      single_lock sLock(synchronization(), true);

      ::e_status estatus = ::success;

      MMRESULT mmresult = MMSYSERR_NOERROR;

      ASSERT(m_hwavein == nullptr);

      ASSERT(m_einstate == ::wave::e_in_state_initial);

      array < ::wave::WAVE_FORMAT > waveformata;

      {

         ::wave::WAVE_FORMAT waveformat;

         waveformat.wFormatTag = WAVE_FORMAT_PCM;
         waveformat.nChannels = 2;
         waveformat.wBitsPerSample = sizeof(::wave::WAVEBUFFERDATA) * 8;
         waveformat.nBlockAlign = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;

         waveformat.nSamplesPerSec = 44100;
         waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;

         waveformata.add(waveformat);

         waveformat.nSamplesPerSec = 22050;
         waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;

         waveformata.add(waveformat);

         waveformat.nSamplesPerSec = 11025;
         waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;

         waveformata.add(waveformat);

      }

      for (auto& waveformat : waveformata)
      {

         m_pwaveformat->m_waveformat = waveformat;

         auto paudio = system()->m_paquasystem->audio()->m_paudio;

         auto audiowave = paudio->audiowave();

         m_iBuffer = 0;

         information() << "waveInOpen";
         information() << waveformat.nSamplesPerSec << " Hz";

         mmresult = waveInOpen(
            &m_hwavein,
            audiowave->m_uiWaveInDevice,
            wave_format(),
            get_itask(),
            (u32)0,
            CALLBACK_THREAD);

         estatus = mmresult_status(mmresult);

         if (estatus.succeeded())
         {

            break;

         }

         if (mmresult == MMSYSERR_ALLOCATED)
         {

            error() <<"Specified resource is already allocated.";

         }
         else if (mmresult == MMSYSERR_BADDEVICEID)
         {

            error() <<"Specified device identifier is out of range.";

         }
         else if (mmresult == WAVERR_BADFORMAT)
         {

            error() <<"Attempted to open with an unsupported waveform-audio_mmsystem format.";

         }
         else
         {

            error() <<"ERROR OPENING WAVE INPUT DEVICE";

         }

      }

      if (estatus.failed())
      {

         throw ::exception(estatus);

      }

      u32 uiBufferSizeLog2;
      u32 uiBufferSize;
      u32 uiAnalysisSize;
      u32 uiAllocationSize;
      u32 uiInterestSize;
      u32 uiSkippedSamplesCount;

      if(m_pwaveformat->m_waveformat.nSamplesPerSec == 44100)
      {
         uiBufferSizeLog2 = 16;
         uiBufferSize = m_pwaveformat->m_waveformat.nChannels * 2 * iBufferSampleCount; // 512 kbytes
         uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
         if(iBufferCount > 0)
         {
            uiAllocationSize = iBufferCount * uiBufferSize;
         }
         else
         {
            uiAllocationSize = 8 * uiAnalysisSize;
         }
         uiInterestSize = 200;
         uiSkippedSamplesCount = 2;
      }
      else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 22050)
      {
         uiBufferSizeLog2 = 9;
         uiBufferSize = 4 * 1 << uiBufferSizeLog2;
         uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
         uiAllocationSize = 4 * uiAnalysisSize;
         uiInterestSize = 600;
         uiSkippedSamplesCount = 1;
      }
      else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 11025)
      {
         uiBufferSizeLog2 = 9;
         uiBufferSize = 2 * 1 << uiBufferSizeLog2;
         uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
         uiAllocationSize = 4 * uiAnalysisSize;
         uiInterestSize = 600;
         uiSkippedSamplesCount = 1;
      }
      in_get_buffer()->FFTOpen(
      uiAllocationSize,
      uiBufferSize,
      uiAnalysisSize,
      uiInterestSize,
      uiSkippedSamplesCount);

      i32 i, iSize;

      iSize = (i32) in_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         MMRESULT mmresult = waveInPrepareHeader(m_hwavein, ::multimedia::mmsystem::create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR));

         auto estatus = mmresult_status(mmresult);

         //if(::success != (estatus = mmresult_status()))
         if(estatus.failed())
         {
            
            informationf("ERROR OPENING Preparing INPUT DEVICE buffer");
            
            throw ::exception(estatus);

         }

         in_add_buffer(i);

      }

      if(m_pencoder != nullptr)
      {

         in_initialize_encoder();

         //m_einstate = ::wave::e_in_state_opened;

         //in_close();

         //return (void    ) -1;

      }

      m_einstate = ::wave::e_in_state_opened;

      //return ::success;

   }


   void in::in_close()
   {

      single_lock sLock(synchronization(), true);

      ::e_status estatus;

      if (m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
      {

         return;

      }

      in_reset();

      i32 i, iSize;

      iSize = (i32) in_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         MMRESULT mmresult = waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR));

         auto estatus = mmresult_status(mmresult);

         if(estatus.failed())
         {

            error() <<"ERROR OPENING Unpreparing INPUT DEVICE buffer";
            //return estatus;
         }

         delete wave_hdr(i);

      }

      MMRESULT mmresult = waveInClose(m_hwavein);

      estatus = mmresult_status(mmresult);

      if (estatus.failed())
      {

         throw ::exception(estatus);

      }

      m_hwavein = nullptr;

      m_einstate = ::wave::e_in_state_initial;

      //return ::success;

   }

   
   void in::in_start()
   {

      single_lock sLock(synchronization(), true);

      if (m_einstate == ::wave::e_in_state_recording)
      {

         return;

      }

      //ASSERT(m_einstate == ::wave::e_in_state_opened || m_einstate == state_stopped);

      if (m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
      {

         //return ::success;

         return;

      }

      ::e_status estatus;

      if(::success != (estatus = mmresult_status(waveInStart(m_hwavein))))
      {
         
         informationf("ERROR starting INPUT DEVICE ");
         
         //return estatus;

         return;

      }

      m_einstate = ::wave::e_in_state_recording;

      //return ::success;

   }


   void in::in_stop()
   {

      single_lock sLock(synchronization(), true);

      if (m_einstate != ::wave::e_in_state_recording)
      {
       
         throw ::exception(error_wrong_state);

      }

      m_einstate = ::wave::e_in_state_stopping;

      MMRESULT mmresult = waveInStop(m_hwavein);

      ::e_status estatus = mmresult_status(mmresult);

      if(estatus.failed())
      {

         informationf("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");

      }

      m_einstate = ::wave::e_in_state_stopped;

      m_eventStopped.SetEvent();

      //return ::success;

   }


   void CALLBACK in::in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
   {

      UNREFERENCED_PARAMETER(hwi);
      UNREFERENCED_PARAMETER(dwInstance);
      UNREFERENCED_PARAMETER(dwParam1);
      UNREFERENCED_PARAMETER(dwParam2);
      if(uMsg == WIM_DATA)
      {
         ASSERT(false);
         /*      u32 msSampleTime = timeGetTime();
         thread * pthread = (thread *) dwInstance;
         ASSERT(pthread != nullptr);
         LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
         LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
         lpxfwm->bDelete = true;
         lpxfwm->msSampleTime = msSampleTime;
         //      lpxfwm->tickSamplePosition = tickPosition;
         lpxfwm->lpWaveHdr = lpWaveHdr;
         pthread->post_thread_message(
         WM_USER,
         (WPARAM) WAVM_WAVE_PROC_DATA,
         (LPARAM) lpxfwm);
         //      i++;
         //      if( i > 2)
         //         i = 0;*/
      }

   }


   void in::in_reset()
   {

      single_lock sLock(synchronization(), true);

      m_bResetting = true;

      if(m_hwavein == nullptr)
      {

         return;

      }

      if(m_einstate == ::wave::e_in_state_recording)
      {

         in_stop();

      }

      MMRESULT mmresult = waveInReset(m_hwavein);

      auto estatus = mmresult_status(mmresult);

      if(estatus.failed())
      {

         error() <<"in::Reset error resetting input device";

         throw ::exception(estatus);

      }

      m_einstate = ::wave::e_in_state_opened;

      m_bResetting = false;

      //return ::success;

   }


   void in::translate_in_message(::message::message * pmessage)
   {

      ASSERT(pmessage->m_atom == MM_WIM_OPEN || pmessage->m_atom == MM_WIM_CLOSE || pmessage->m_atom == MM_WIM_DATA);

      if(pmessage->m_atom == MM_WIM_DATA)
      {

         m_iBuffer--;

         u32 msSampleTime = timeGetTime();

         LPWAVEHDR lpwavehdr = (LPWAVEHDR)pmessage->m_lparam.m_lparam;

         in_get_buffer()->get_buffer((i32) lpwavehdr->dwUser)->OnMultimediaDone();

         m_listenerset.in_data_proc(this, msSampleTime, (i32) lpwavehdr->dwUser);

         if(m_pencoder != nullptr)
         {
            
            m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);

         }

         if(!in_is_resetting() && in_is_recording())
         {
            in_add_buffer((i32) lpwavehdr->dwUser);
         }

      }

      pmessage->m_bRet = true;

   }


   void     in::in_add_buffer(i32 iBuffer)
   {

      return in_add_buffer(wave_hdr(iBuffer));

   }


   void in::in_add_buffer(LPWAVEHDR lpwavehdr)
   {

      ::e_status estatus;

      MMRESULT mmresult = waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR));

      estatus = mmresult_status(mmresult);

      if(estatus.failed())
      {

         informationf("ERROR OPENING Adding INPUT DEVICE buffer");

      }

      m_iBuffer++;

      //return estatus;

   }


   void in::in_initialize_encoder()
   {

      if (m_pencoder == nullptr)
      {

         //return false;
         return;

      }

      ::wave::in::in_initialize_encoder();

      //if (!::wave::in::in_initialize_encoder())
      //{

      //   //return false;

      //}

      //return true;

   }

   WAVEFORMATEX * in::wave_format()
   {

      ::multimedia::mmsystem::translate(m_waveformatex, m_pwaveformat);

      return &m_waveformatex;

   }


   HWAVEIN in::in_get_safe_HWAVEIN()
   {

      if (this == nullptr)
      {

         return nullptr;

      }

      return m_hwavein;

   }


   void * in::get_os_data()
   {

      return m_hwavein;

   }


   LPWAVEHDR in::wave_hdr(int iBuffer)
   {

      return ::multimedia::mmsystem::get_os_data(in_get_buffer(), iBuffer);

   }


} // namespace audio_mmsystem



