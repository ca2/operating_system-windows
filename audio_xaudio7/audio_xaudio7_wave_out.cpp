#include "framework.h"


namespace multimedia
{


   namespace audio_xaudio7
   {



      out::out(::pointer<::axis::application>papp) :
         object(papp),
         ::thread(papp),
         wave_base(papp),
         ::wave::out(papp)
      {




         m_estate             = e_state_initial;
         m_pthreadCallback    = nullptr;
         m_pxaudio       = nullptr;
         m_pvoice       = nullptr;
         m_psourcevoice       = nullptr;
         m_iBufferedCount     = 0;
         m_peffect            = nullptr;
         m_dwLostSampleCount  = 0;

      }

      out::~out()
      {

      }

      void out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      bool out::initialize_instance()
      {

         if(!::wave::out::initialize_instance())
            return false;

         return true;

      }

      i32 out::run()
      {
         m_timeRunLock = ::time(1);
         while(m_bRun)
         {
            ::thread::run();
         }



         return 0;
      }

      bool out::on_run_step()
      {

         return ::thread::on_run_step();

      }

      i32 out::exit_thread()
      {

         ::wave::out::exit_thread();

         return ::thread::exit_thread();

      }

      void     out::out_open(thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount)
      {

         single_lock sLock(&m_mutex, true);


         if(m_pxaudio != nullptr && m_pvoice != nullptr && m_psourcevoice != nullptr && m_estate != e_state_initial)
            return ::success;


         m_pthreadCallback = pthreadCallback;
         void     mmr;
         ASSERT(m_pxaudio == nullptr);
         ASSERT(m_pvoice == nullptr);
         ASSERT(m_psourcevoice == nullptr);
         ASSERT(m_estate == e_state_initial);

         
         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return error_failed;

         }

         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice)))
         {
            return error_failed;
         }

         // Set up the source voice and register the callback class
         //VoiceCallback voiceCallback;

         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         ::pointer<::audio::wave>audiowave = papplication->audiowave();

         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(), 0,XAUDIO2_DEFAULT_FREQ_RATIO,this,nullptr,nullptr)))
         {
            return error_failed;
         }
         //if(mmr = xaudio7::translate(waveOutOpen(
         //   &m_hwaveout,
         //   audiowave->m_uiWaveInDevice,
         //   wave_format(),
         //   get_os_int(),
         //   (u32) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 22050;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = xaudio7::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   ,
         //   (u32) get_os_int(),
         //   (u32) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 11025;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = xaudio7::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   wave_format(),
         //   (u32) get_os_int(),
         //   (u32) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;

         //if(mmr != ::success)
         //{
         //   return mmr;
         //}

Opened:
         u32 uiBufferSizeLog2;
         u32 uiBufferSize;
         u32 uiAnalysisSize;
         u32 uiAllocationSize;
         u32 uiInterestSize;
         u32 uiSkippedSamplesCount;
         u32 uiBufferCount = iBufferCount;

         if(m_pwaveformat->nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(
         this, // callback thread (thread)
         m_pwaveformat->nChannels, // channel count
         uiBufferCount, // group count
         iBufferSampleCount); // group sample count


         // TODO: DSBCAPS_GETCURRENTPOSITION2




         m_estate = e_state_opened;

         return ::success;

      }

      void     out::out_open_ex(thread * pthreadCallback, i32 iBufferCount, i32 iBufferSampleCount, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample)
      {

         single_lock sLock(&m_mutex, true);

         if(m_pxaudio != nullptr && m_pvoice != nullptr && m_psourcevoice != nullptr && m_estate != e_state_initial)
            return ::success;

         m_iBuffer = 0;

         m_pthreadCallback = pthreadCallback;
         void     mmr;
         ASSERT(m_pxaudio == nullptr);
         ASSERT(m_pvoice == nullptr);
         ASSERT(m_psourcevoice == nullptr);
         ASSERT(m_estate == e_state_initial);

         CoInitializeEx(nullptr,COINIT_MULTITHREADED);

         
         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return error_failed;

         }

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
         // To see the trace output, you need to impact ETW logs for this application:
         //    Go to Control Panel, Administrative Tools, Event Viewer.
         //    View->Show Analytic and Debug Logs.
         //    Applications and Services Logs / Microsoft / Windows / xaudio72.
         //    Right click on Microsoft Windows xaudio72 debug logging, Properties, then Enable Logging, and hit OK
         XAUDIO2_DEBUG_CONFIGURATION debug = {0};
         debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
         debug.BreakMask = XAUDIO2_LOG_ERRORS;
         m_pxaudio->SetDebugConfiguration(&debug,0);
#endif


         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice,uiChannelCount, uiSamplesPerSec)))
         {
            return error_failed;
         }

         mmr = ::success;
         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = uiChannelCount;
         m_pwaveformat->nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         ::pointer<::audio::wave>audiowave = papplication->audiowave();

         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),XAUDIO2_VOICE_NOSRC | XAUDIO2_VOICE_NOPITCH,1.0f,this)))
         {
            return error_failed;
         }

         if(mmr != ::success)
         {

            TRACE0(::multimedia::strerror(mmr));

            return mmr;

         }

Opened:
         int iAlign = 2048;
         iBufferCount = 4;
         iBufferSampleCount = (1 << 10);

         u32 uiBufferSize = iBufferSampleCount * m_pwaveformat->nChannels * 2;

         ASSERT((uiBufferSize % 2048) == 0);// Streaming size_i32 must be 2K aligned to use for async I/O





         out_get_buffer()->PCMOutOpen(this, uiBufferSize, iBufferCount, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, iBufferCount, iBufferSampleCount);

         m_pprebuffer->SetMinL1BufferCount(out_get_buffer()->GetBufferCount() + 4);

         m_estate = e_state_opened;

         return ::success;

      }



      void     out::out_close()
      {

         single_lock sLock(&m_mutex, true);

         if(m_estate == e_state_playing)
         {
            out_stop();
         }

         if(m_estate != e_state_opened)
            return ::success;

         void     mmr;

         i32 i, iSize;

         iSize =  out_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         //   if(::success != (mmr = xaudio7::translate(waveOutUnprepareHeader(m_hwaveout, wave_hdr(i), sizeof(WAVEHDR)))))
         //   {
         //      information("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
         //   }

         //   delete wave_hdr(i);

         //}

         //;mmr = xaudio7::translate(waveOutClose(m_hwaveout));

         //m_hwaveout = nullptr;

         m_pprebuffer->Reset();

         m_estate = e_state_initial;

         return ::success;

      }



      void out::out_buffer_ready(int iBuffer)
      {

         if(out_get_state() != e_state_playing)
         {
            information("ERROR out::BufferReady while out_get_state() != e_state_playing");
            return;
         }

         ::wave::buffer * pwbuffer = out_get_buffer();
         ::wave::buffer::item * pbuffer = pwbuffer->get_buffer(iBuffer);

         void     mmr;
         if(m_peffect != nullptr)
         {
            m_peffect->Process16bits((i16 *)pbuffer->m_pData,pwbuffer->m_uiBufferSize / 2);
         }

         XAUDIO2_BUFFER b;
         zero(b);
         b.pContext = pbuffer;
         b.AudioBytes = pwbuffer->m_uiBufferSize;
         b.pAudioData = (const BYTE *)pbuffer->m_pData;

         //single_lock sLock(&m_mutex,true);



         mmr = xaudio7::translate(m_psourcevoice->SubmitSourceBuffer(&b));

         VERIFY(::success == mmr);

         if(mmr == ::success)
         {

            m_iBufferedCount++;

         }

      }




      void     out::out_stop()
      {

         single_lock sLock(&m_mutex, true);

         if(m_estate != e_state_playing && m_estate != e_state_paused)
            return error_failed;

         m_eventStopped.ResetEvent();

         m_pprebuffer->Stop();

         m_estate = e_state_stopping;

         //// waveOutReset
         //// The waveOutReset function stops playback on the given
         //// waveform-audio_xaudio7 output device and resets the current position
         //// to zero. All pending playback buffers are marked as done and
         //// returned to the application.
         m_estatusWave = xaudio7::translate(m_psourcevoice->Stop());

         if(m_estatusWave == ::success)
         {

            m_estate = e_state_opened;

         }

         return m_estatusWave;

      }


      void     out::out_pause()
      {

         single_lock sLock(&m_mutex, true);

         ASSERT(m_estate == e_state_playing);

         if(m_estate != e_state_playing)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio7 output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.

         //m_estatusWave = xaudio7::translate(waveOutPause(m_hwaveout));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {
            m_estate = e_state_paused;
         }

         return m_estatusWave;

      }

      void out::OnBufferEnd(void * pBufferContext)
      {

         ::wave::buffer::item * pbuffer = (::wave::buffer::item *)pBufferContext;

         i32 iBuffer = (i32)pbuffer->m_iIndex;

         out_out_buffer_done(iBuffer);

      }

      void     out::out_start(const ::time & position)
      {

         single_lock sLock(&m_mutex,true);

         if(m_estate == e_state_playing)
            return ::success;

         ASSERT(m_estate == e_state_opened || m_estate == state_stopped);

         m_estate = e_state_playing;

         for(index i = 0; i < out_get_buffer()->GetBufferCount(); i++)
         {

            out_free(i);

         }

         m_estatusWave = xaudio7::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         //         m_prunstepthread = new run_step_thread(this);


         return ::success;

      }


      void     out::out_restart()
      {

         single_lock sLock(&m_mutex, true);

         ASSERT(m_estate == e_state_paused);

         if(m_estate != e_state_paused)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio7 output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = xaudio7::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_estate = e_state_playing;

         }

         return m_estatusWave;

      }


      /*::time out::GetPositionMillisForSynch()
      {
         i64 dwMillis = GetPositionMillis();
         i64 dwPosition = m_pprebuffer->m_position * 8;
         dwPosition /= m_pwaveformat->wBitsPerSample;
         dwPosition *= 1000;
         dwPosition /= m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         if(m_pprebuffer != nullptr && m_pprebuffer->m_pdecoder != nullptr)
            return dwMillis + dwPosition - m_pprebuffer->m_pdecoder->audio_plugin_get_lost_millis(dwMillis + dwPosition) - (((i64) m_dwLostSampleCount) /  ((i64) m_pwaveformat->nSamplesPerSec));
         else
            return dwMillis + dwPosition - ((m_dwLostSampleCount) * 1000 / m_pwaveformat->nSamplesPerSec);
      }*/

      ::time out::out_get_time()
      {

         single_lock sLock(&m_mutex, true);

         void                    mmr;

         return 0;

         //MMTIME                  mmt;

         //mmt.wType = TIME_MS;

         //if(m_hwaveout != nullptr)
         //{

         //   mmr = xaudio7::translate(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

         //   try
         //   {
         //      if (::success != mmr)
         //      {
         //         information( "waveOutGetPosition() returned %lu", (u32)mmr);
         //         //      return MCIERR_DEVICE_NOT_READY;
         //         return 0;
         //      }
         //   }
         //   catch(...)
         //   {
         //      //return MCIERR_DEVICE_NOT_READY;
         //      return 0;
         //   }
         //   if(mmt.wType == TIME_BYTES)
         //   {
         //      i64 i = mmt.u.cb;
         //      i *= 8 * 1000;
         //      i /= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         //      return i;

         //   }
         //   else
         //   {
         //      //& ticka += mmt.u.ticks;
         //      return (u32) mmt.u.ms;
         //   }
         //}
         //else
         //   return 0;


      }

      /*::time out::get_position_for_synch()
      {
         ::time position = get_position();
         if(m_pprebuffer != nullptr && m_pprebuffer->m_pdecoder != nullptr)
            return m_pprebuffer->m_position + position - m_pprebuffer->m_pdecoder->audio_plugin_get_lost_position_offset(position) - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         else
            return m_pprebuffer->m_position + position - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
      }*/

      ::time out::out_get_time()
      {

         single_lock sLock(&m_mutex, true);

         void                    mmr;

         //MMTIME                  mmt;

         //mmt.wType = TIME_BYTES;

         //if(m_hwaveout != nullptr)
         //{
         //
         //   mmr = xaudio7::translate(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

         //   try
         //   {

         //      if (::success != mmr)
         //      {

         //         information( "waveOutGetPosition() returned %lu", (u32)mmr);

         //         return 0;

         //      }

         //   }
         //   catch(...)
         //   {
         //      return 0;
         //   }
         //   if(mmt.wType == TIME_MS)
         //   {
         //      ::time position = (u32) mmt.u.ms;
         //      position *= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         //      position /= 8 * 1000;
         //      return position;
         //   }
         //   else
         //   {
         //      return (u32) mmt.u.cb;
         //   }
         //}
         //else
         //   return 0;
         return 0;
      }

      void out::out_free(int iBuffer)
      {

         //out_free(wave_hdr(iBuffer));

         ::wave::out::out_free(iBuffer);

      }


      //void out::out_free(LPWAVEHDR lpwavehdr)
      //{


      //}

      void out::out_on_playback_end()
      {

         out_stop();

         //if(m_pprebuffer->m_pstreameffectOut != nullptr)
         //{
         //   ::multimedia::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
         //   m_pprebuffer->m_pstreameffectOut = nullptr;
         //   delete peffect;
         //}

         m_eventStopped.SetEvent();

         m_pplayer->OnEvent(::wave::player::EventPlaybackEnd);

      }



      WAVEFORMATEX * out::wave_format()
      {

         xaudio7::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }

      //HWAVEOUT out::out_get_safe_HWAVEOUT()
      //{
      //
      //   if(this == nullptr)
      //      return nullptr;

      //   return m_hwaveout;

      //}

      void * out::get_os_data()
      {
         //return m_hwaveout;
         return nullptr;
      }

      //LPWAVEHDR out::wave_hdr(int iBuffer)
      //{
      //   return ::multimedia::xaudio7::get_os_data(out_get_buffer(), iBuffer);
      //}




      void out::out_run_step()
      {

         int iPlay =  -1;

         //int r = WaitForMultipleObjects(m_haEvent.get_count(),m_haEvent.get_data(),false,INFINITE);
         //
         //if(r >= WAIT_OBJECT_0 && r < WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS)
         //{

         //   iPlay = r - WAIT_OBJECT_0;

         //   ::ResetEvent(m_haEvent[iPlay]);


         //}


         //while(true)
         //{

         //   int iNext = m_iBuffer + 1;

         //   if(iNext >= out_get_buffer()->GetBufferCount())
         //      iNext = 0;

         //   if(iNext == iPlay)
         //      break;

         //   out_out_buffer_done(iNext);

         //   m_iBuffer = iNext;

         //}




      }


      out::run_step_thread::run_step_thread(out * pout):
         ::thread(pout->get_application())
      {
         m_pout = pout;
         begin();
      }

      i32 out::run_step_thread::run()
      {

         while(m_bRun && m_pout->m_estate == out::e_state_playing)
         {
            m_pout->out_run_step();
         }


         return 0;
      }


   } // namespace audio_xaudio7


} // namespace multimedia






