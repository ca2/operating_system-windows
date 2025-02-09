#include "framework.h"


namespace multimedia
{


   namespace audio_directsound
   {


      out::out(::particle * pparticle) :
         ::object(pobject),
         ::thread(pobject),
         wave_base(pobject),
         ::wave::out(pobject)
      {

         m_estate             = e_state_initial;
         m_pthreadCallback    = nullptr;
         m_pdirectsound       = nullptr;
         m_psoundbuffer       = nullptr;

      }

      out::~out()
      {

      }

      void out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      bool out::init_thread()
      {

         if (!::wave::out::init_thread())
         {

            return false;

         }

         return true;

      }


      void     out::run()
      {

         return ::thread::run();

      }


      void out::term_thread()
      {

         ::wave::out::term_thread();
      }


      void     out::out_open(thread * pthreadCallback, int iBufferCount, int iBufferSampleCount)
      {

         synchronous_lock synchronouslock(synchronization());

         if (m_pdirectsound != nullptr && m_psoundbuffer != nullptr && m_estate != e_state_initial)
         {

            return ::success;

         }


         m_pthreadCallback = pthreadCallback;
         //void     mmr;
         ASSERT(m_pdirectsound == nullptr);
         ASSERT(m_psoundbuffer == nullptr);
         ASSERT(m_estate == e_state_initial);

         if(FAILED(DirectSoundCreate8(nullptr,&m_pdirectsound,nullptr)))
         {

            return error_failed;

         }


         if(FAILED(m_pdirectsound->SetCooperativeLevel((HWND) papplication->m_puiMain->get_safe_handle(),DSSCL_PRIORITY)))
         {

            return error_failed;

         }


         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         ::pointer<::audio::wave>audiowave = papplication->audiowave();

         {

            DSBUFFERDESC BufferDescription = {};
            BufferDescription.dwSize = sizeof(BufferDescription);
            BufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

            // NOTE: "Create" a primary buffer
            // TODO: DSBCAPS_GLOBALFOCUS?
            LPDIRECTSOUNDBUFFER PrimaryBuffer;
            if(SUCCEEDED(m_pdirectsound->CreateSoundBuffer(&BufferDescription,&PrimaryBuffer,0)))
            {
               HRESULT Error = PrimaryBuffer->SetFormat(wave_format());
               if(SUCCEEDED(Error))
               {
                  // NOTE: We have finally set the format!
                  OutputDebugStringA("Primary buffer format was set.\n");
                  m_pdirectsound->Release();
                  return error_failed;
               }
               else
               {
                  // TODO: Diagnostic
               }
            }
            else
            {
               // TODO: Diagnostic
            }


         }



         //if(mmr = directsound::translate(waveOutOpen(
         //   &m_hwaveout,
         //   audiowave->m_uiWaveInDevice,
         //   wave_format(),
         //   get_os_int(),
         //   (unsigned int) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 22050;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = directsound::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   ,
         //   (unsigned int) get_os_int(),
         //   (unsigned int) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 11025;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = directsound::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   wave_format(),
         //   (unsigned int) get_os_int(),
         //   (unsigned int) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;

         //if(mmr != ::success)
         //{
         //   return mmr;
         //}

//Opened:
         unsigned int uiBufferSizeLog2;
         unsigned int uiBufferSize;
         unsigned int uiAnalysisSize;
         unsigned int uiAllocationSize;
         unsigned int uiInterestSize;
         unsigned int uiSkippedSamplesCount;
         unsigned int uiBufferCount = iBufferCount;

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

         out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount,128,m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(
         m_pwaveformat->nChannels, // channel count
         uiBufferCount, // group count
         iBufferSampleCount); // group sample count


         // TODO: DSBCAPS_GETCURRENTPOSITION2
         DSBUFFERDESC BufferDescription = {};
         BufferDescription.dwSize = sizeof(BufferDescription);
         BufferDescription.dwFlags = 0;
         BufferDescription.dwBufferBytes = uiBufferSize * uiBufferCount;
         BufferDescription.lpwfxFormat = wave_format();
         //LPDIRECTSOUNDBUFFER SecondaryBuffer;
         HRESULT Error = m_pdirectsound->CreateSoundBuffer(&BufferDescription,&m_psoundbuffer,0);
         if(FAILED(Error))
         {
            OutputDebugStringA("Secondary buffer created successfully.\n");
            return error_failed;
         }

         //int i, iSize;
         //iSize = out_get_buffer()->GetBufferCount();
         //for(i = 0; i < iSize; i++)
         //{

         //   if(MMSYSERR_NOERROR != (mmr =  directsound::translate(waveOutPrepareHeader(m_hwaveout, directsound::create_new_WAVEHDR(m_pwavebuffer, i), sizeof(WAVEHDR)))))
         //   {
         //      informationf("ERROR OPENING Preparing INPUT DEVICE buffer");
         //      return mmr;
         //   }
         //}

         m_estate = e_state_opened;

         return ::success;

      }

      void     out::out_open_ex(thread * pthreadCallback, int iBufferCount, int iBufferSampleCount, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample)
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_pdirectsound != nullptr && m_psoundbuffer != nullptr && m_estate != e_state_initial)
            return ::success;

         m_iBuffer = 0;

         m_pthreadCallback = pthreadCallback;
         void     mmr;
         ASSERT(m_pdirectsound == nullptr);
         ASSERT(m_psoundbuffer == nullptr);
         ASSERT(m_estate == e_state_initial);

         
         if(FAILED(DirectSoundCreate8(nullptr,&m_pdirectsound,nullptr)))
         {

            return error_failed;

         }


         if(FAILED(m_pdirectsound->SetCooperativeLevel((HWND)papplication->m_puiMain->get_safe_handle(),DSSCL_PRIORITY)))
         {

            return error_failed;

         }

         mmr = ::success;
         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         ::pointer<::audio::wave>audiowave = papplication->audiowave();

         {

            DSBUFFERDESC BufferDescription = {};
            BufferDescription.dwSize = sizeof(BufferDescription);
            BufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

            // NOTE: "Create" a primary buffer
            // TODO: DSBCAPS_GLOBALFOCUS?
            LPDIRECTSOUNDBUFFER PrimaryBuffer;
            if(FAILED(m_pdirectsound->CreateSoundBuffer(&BufferDescription,&PrimaryBuffer,0)))
            {
               // TODO: Diagnostic
               m_pdirectsound->Release();
               return error_failed;
            }
            else
            {
               HRESULT Error = PrimaryBuffer->SetFormat(wave_format());
               if(FAILED(Error))
               {
                  // TODO: Diagnostic
                  m_pdirectsound->Release();
                  return error_failed;
               }
               else
               {
                  // NOTE: We have finally set the format!
                  OutputDebugStringA("Primary buffer format was set.\n");
               }
            }


         }

         if(mmr != ::success)
         {

            //informationf("%s", ::multimedia::strerror(mmr));
            informationf("%d", mmr);

            return mmr;

         }

//Opened:

         iBufferCount = 4;
         iBufferSampleCount = (1 << 10);

         unsigned int uiBufferSize = iBufferSampleCount * m_pwaveformat->nChannels * 2;



         // TODO: DSBCAPS_GETCURRENTPOSITION2
         DSBUFFERDESC BufferDescription = {};
         BufferDescription.dwSize = sizeof(BufferDescription);
         BufferDescription.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY;
         BufferDescription.dwBufferBytes = uiBufferSize * iBufferCount;
         BufferDescription.lpwfxFormat = wave_format();
         //LPDIRECTSOUNDBUFFER SecondaryBuffer;
         HRESULT Error = m_pdirectsound->CreateSoundBuffer(&BufferDescription,&m_psoundbuffer,0);
         if(FAILED(Error))
         {
            OutputDebugStringA("Secondary buffer created successfully.\n");
            return error_failed;
         }
         //Query DirectSoundNotify
         if(FAILED(m_psoundbuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID *)&m_psoundnotify)))
         {
            OutputDebugString(_T("QueryInterface DirectSoundNotify Failed!"));
            //m_strLastError = _T("MyDirectSound SetFormat Failed!");
            return error_failed;
         }

         m_haEvent.erase_all();
         m_notifya.erase_all();

         for(::collection::index i = 0; i < iBufferCount; i++)
         {

            m_haEvent.add(CreateEvent(nullptr,false,false,nullptr));
            m_notifya.element_at_grow(i).dwOffset = (DWORD) (uiBufferSize * i);
            m_notifya.element_at_grow(i).hEventNotify = m_haEvent[i];
         }


         if(FAILED(m_psoundnotify->SetNotificationPositions((DWORD) m_notifya.get_count(),m_notifya.get_data())))
         {
            OutputDebugString(_T("Set NotificationPosition Failed!"));
            return error_failed;
         }



         out_get_buffer()->PCMOutOpen(this, uiBufferSize, iBufferCount,128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->nChannels, iBufferCount, iBufferSampleCount);

         m_estate = e_state_opened;

         return ::success;

      }



      void     out::out_close()
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_estate == e_state_playing)
         {
            out_stop();
         }

         if(m_estate != e_state_opened)
            return ::success;

         //void     mmr;

         ::collection::count iSize;

         iSize =  out_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         //   if(::success != (mmr = directsound::translate(waveOutUnprepareHeader(m_hwaveout, wave_hdr(i), sizeof(WAVEHDR)))))
         //   {
         //      informationf("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
         //   }

         //   delete wave_hdr(i);

         //}

         //;mmr = directsound::translate(waveOutClose(m_hwaveout));

         //m_hwaveout = nullptr;

//         m_pprebuffer->Reset();

         m_estate = e_state_initial;

         return ::success;

      }


      void out::out_filled(::collection::index i)
      {

         synchronous_lock synchronouslock(synchronization());

         LPVOID lpvAudio1 = nullptr,lpvAudio2 = nullptr;

         DWORD dwBytesAudio1 = 0,dwBytesAudio2 = 0;

         DWORD dwRetSamples = 0,dwRetBytes = 0;

         if (i < 0 || i >= out_get_buffer()->GetBufferCount())
         {

            return ;

         }

         m_iBufferedCount++;

         {

            HRESULT hr = m_psoundbuffer->Lock((DWORD)(i * out_get_buffer_size()), (DWORD) out_get_buffer_size(),&lpvAudio1,&dwBytesAudio1,&lpvAudio2,&dwBytesAudio2,0);

            if(FAILED(hr))
            {

               m_iBufferedCount--;

               return;

            }

            if(nullptr == lpvAudio2)
            {

               memory_copy(lpvAudio1,out_get_buffer_data(i),dwBytesAudio1);

            }
            else
            {

               memory_copy(lpvAudio1,out_get_buffer_data(i),dwBytesAudio1);

               memory_copy(lpvAudio2,(unsigned char *)out_get_buffer_data(i) + dwBytesAudio1,dwBytesAudio2);

            }

            hr = m_psoundbuffer->Unlock(lpvAudio1,dwBytesAudio1,lpvAudio2,dwBytesAudio2);

            if (FAILED(hr))
            {

               m_iBufferedCount--;

               return;

            }

         }

      }


      void     out::out_stop()
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_estate != e_state_playing && m_estate != e_state_paused)
            return error_failed;

         m_estate = e_state_stopping;

         //// waveOutReset
         //// The waveOutReset function stops playback on the given
         //// waveform-audio_directsound output device and resets the current position
         //// to zero. All pending playback buffers are marked as done and
         //// returned to the application.
         //m_estatusWave = directsound::translate(waveOutReset(m_hwaveout));

         if(m_estatusWave == ::success)
         {

            m_estate = e_state_opened;

         }

         return m_estatusWave;

      }


      void     out::out_pause()
      {

         synchronous_lock synchronouslock(synchronization());

         ASSERT(m_estate == e_state_playing);

         if(m_estate != e_state_playing)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_directsound output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.

         //m_estatusWave = directsound::translate(waveOutPause(m_hwaveout));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {
            m_estate = e_state_paused;
         }

         return m_estatusWave;

      }

      void     out::out_start(const ::time & position)
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_estate == e_state_playing)
            return ::success;

         ASSERT(m_estate == e_state_opened || m_estate == state_stopped);

         m_estate = e_state_playing;

         for(::collection::index i = 0; i < out_get_buffer()->GetBufferCount(); i++)
         {

            out_free(i);

         }

         m_estatusWave = directsound::translate(m_psoundbuffer->Play(0,0,DSBPLAY_LOOPING));

         //m_prunstepthread = ___new run_step_thread(this);


         return ::success;

      }


      void     out::out_restart()
      {

         synchronous_lock synchronouslock(synchronization());

         ASSERT(m_estate == e_state_paused);

         if(m_estate != e_state_paused)
            return error_failed;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_directsound output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = directsound::translate(m_psoundbuffer->Play(0,0,DSBPLAY_LOOPING));

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_estate = e_state_playing;

         }

         return m_estatusWave;

      }


      /*::time out::GetPositionMillisForSynch()
      {
         long long dwMillis = GetPositionMillis();
         long long dwPosition = m_pprebuffer->m_position * 8;
         dwPosition /= m_pwaveformat->wBitsPerSample;
         dwPosition *= 1000;
         dwPosition /= m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         if(m_pprebuffer != nullptr && m_pprebuffer->m_pdecoder != nullptr)
            return dwMillis + dwPosition - m_pprebuffer->m_pdecoder->audio_plugin_get_lost_millis(dwMillis + dwPosition) - (((long long) m_dwLostSampleCount) /  ((long long) m_pwaveformat->nSamplesPerSec));
         else
            return dwMillis + dwPosition - ((m_dwLostSampleCount) * 1000 / m_pwaveformat->nSamplesPerSec);
      }*/

      ::time out::out_get_time()
      {

         synchronous_lock synchronouslock(synchronization());

         //void                    mmr;

         return 0;

         //MMTIME                  mmt;

         //mmt.wType = TIME_MS;

         //if(m_hwaveout != nullptr)
         //{

         //   mmr = directsound::translate(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

         //   try
         //   {
         //      if (::success != mmr)
         //      {
         //         information( "waveOutGetPosition() returned %lu", (unsigned int)mmr);
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
         //      long long i = mmt.u.cb;
         //      i *= 8 * 1000;
         //      i /= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         //      return i;

         //   }
         //   else
         //   {
         //      //& ticka += mmt.u.ticks;
         //      return (unsigned int) mmt.u.ms;
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

         synchronous_lock synchronouslock(synchronization());

         //void                    mmr;

         //MMTIME                  mmt;

         //mmt.wType = TIME_BYTES;

         //if(m_hwaveout != nullptr)
         //{
         //
         //   mmr = directsound::translate(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

         //   try
         //   {

         //      if (::success != mmr)
         //      {

         //         information( "waveOutGetPosition() returned %lu", (unsigned int)mmr);

         //         return 0;

         //      }

         //   }
         //   catch(...)
         //   {
         //      return 0;
         //   }
         //   if(mmt.wType == TIME_MS)
         //   {
         //      ::time position = (unsigned int) mmt.u.ms;
         //      position *= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         //      position /= 8 * 1000;
         //      return position;
         //   }
         //   else
         //   {
         //      return (unsigned int) mmt.u.cb;
         //   }
         //}
         //else
         //   return 0;
         return 0;
      }


      void out::out_free(::collection::index iBuffer)
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

         m_pplayer->OnHappening(::wave::player::EventPlaybackEnd);

      }



      WAVEFORMATEX * out::wave_format()
      {

         directsound::translate(m_waveformatex, m_pwaveformat);

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
      //   return ::multimedia::directsound::get_os_data(out_get_buffer(), iBuffer);
      //}




      void out::out_run_step()
      {

         int iPlay =  -1;

         int r = WaitForMultipleObjects((DWORD) m_haEvent.get_count(), m_haEvent.get_data(),false,INFINITE);

         if(r >= WAIT_OBJECT_0 && r < WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS)
         {

            iPlay = r - WAIT_OBJECT_0;

            ::ResetEvent(m_haEvent[iPlay]);


         }


         while(true)
         {

            int iNext = m_iBuffer + 1;

            if(iNext >= out_get_buffer()->GetBufferCount())
               iNext = 0;

            if(iNext == iPlay)
               break;

            // xxx out_out_buffer_done(iNext);

            m_iBuffer = iNext;

         }

      }


      //out::run_step_thread::run_step_thread(out * pout):
      //   ::thread(pout->get_application())
      //{
      //   m_pout = pout;
      //   begin();
      //}


      //void out::run_step_thread::run()
      //{

      //   while(task_get_run() && m_pout->m_estate == out::e_state_playing)
      //   {

      //      m_pout->out_run_step();

      //   }

      //}


   } // namespace audio_directsound


} // namespace multimedia






