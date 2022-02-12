#include "framework.h"
#include "aura/message.h"


namespace audio_mmsystem
{


   void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
   {

      if (uMsg == WOM_DONE)
      {

         LPWAVEHDR lpwavehdr = (LPWAVEHDR) dwParam1;

         auto pwaveout = (::audio_mmsystem::out *) dwInstance;

         pwaveout->m_psynththread->on_free(lpwavehdr->dwUser);

      }

   }


   out::out()
   {

      m_bDirectOutput      = true;
      m_bMessageThread     = true;
      m_estate             = e_state_initial;
      m_pthreadCallback    = nullptr;
      m_hwaveout           = nullptr;

   }


   out::~out()
   {

   }


   void out::install_message_routing(::channel * pchannel)
   {

      ::wave::out::install_message_routing(pchannel);

   }


   void out::init_thread()
   {

      ::wave::out::init_thread();

      ////if (!::wave::out::init_thread())
      //{

      //   return ::error_failed;

      //}

      //return ::success;

   }


   void out::term_thread()
   {

      ::wave::out::term_thread();

      ::thread::term_thread();

   }


   void out::out_open_ex(thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample,::wave::e_purpose epurpose)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_hwaveout != nullptr && m_estate != e_state_initial)
      {

         //return ::success;

         return;

      }

      m_duration = 0_s;

      MMRESULT mmresult = MMSYSERR_NOERROR;

      m_pthreadCallback = pthreadCallback;

      ::e_status estatus;

      ASSERT(m_hwaveout == nullptr);
      ASSERT(m_estate == e_state_initial);

      m_pwaveformat->m_waveformat.wFormatTag        = WAVE_FORMAT_PCM;
      m_pwaveformat->m_waveformat.nChannels         = (WORD) uiChannelCount;
      m_pwaveformat->m_waveformat.nSamplesPerSec    = uiSamplesPerSec;
      m_pwaveformat->m_waveformat.wBitsPerSample    = (WORD) uiBitsPerSample;
      m_pwaveformat->m_waveformat.nBlockAlign       = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
      m_pwaveformat->m_waveformat.nAvgBytesPerSec   = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
      
      auto paudio = m_psystem->m_paquasystem->audio()->m_paudio;

      auto paudiowave = paudio->audiowave();

      //try
      //{

         mmresult = waveOutOpen(&m_hwaveout, paudiowave->m_uiWaveOutDevice, wave_format(), (DWORD_PTR) &waveOutProc, (DWORD_PTR) this, CALLBACK_FUNCTION);

         if (mmresult == MMSYSERR_NOERROR)
         {

            TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutOpen: Success!!");

         }
         else
         {

            TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutOpen: ERROR %d!!", mmresult);

            estatus = mmresult_to_status(mmresult);

            //if (estatus == ::success)
            //{

            //   goto Opened;

            //}

            throw ::exception(estatus);

            //}
            //catch(const ::exception &)
            //{

            //   return error_failed;

            //}
            //catch(...)
            //{

            //   return error_failed;

            //}

            //if(estatus != ::success)
            //{

            //   TRACE(status_short_description(estatus));

            //   return estatus;

            //}

      //Opened:

         }

      int iBufferCount;
      int iBufferSampleCount;

      if(epurpose == ::wave::purpose_playback)
      {

         iBufferSampleCount = uiSamplesPerSec / 8;

         iBufferCount = 4;

      }
      else if(epurpose == ::wave::purpose_playground)
      {

         iBufferSampleCount = uiSamplesPerSec / 30;

         iBufferCount = 3;

      }
      else
      {

         iBufferSampleCount = uiSamplesPerSec / 20;

         iBufferCount = 4;

      }

      //int iPower2Size = 2;

      //while (iPower2Size < iBufferSampleCount)
      //{

      //   iPower2Size *= 2;

      //}

      //iBufferSampleCount = iPower2Size;

      int iBufferSize = iBufferSampleCount * uiBitsPerSample * uiChannelCount / 8;

      out_get_buffer()->PCMOutOpen(this, iBufferSize, iBufferCount,128, m_pwaveformat, m_pwaveformat);

      m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, iBufferCount, iBufferSampleCount);

      index i;

      auto iSize = out_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         mmresult = waveOutPrepareHeader(m_hwaveout, ::multimedia::mmsystem::create_new_WAVEHDR(out_get_buffer(), i), sizeof(WAVEHDR));

         if (mmresult == MMSYSERR_NOERROR)
         {

            TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutPrepareHeader: Success!!");

         }
         else
         {

            TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutPrepareHeader: ERROR %d!!", mmresult);

         }

         estatus = mmresult_to_status(mmresult);

         if (estatus != ::success)
         {

            MMRESULT mmresult2;

            while (i >= 1)
            {

               i--;

               mmresult2 = waveOutUnprepareHeader(m_hwaveout, wave_hdr(i), sizeof(WAVEHDR));

               if (mmresult2 == MMSYSERR_NOERROR)
               {

                  TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutUnprepareHeader: Cascade Success");

               }
               else
               {

                  TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutUnprepareHeader: Cascade ERROR %d!!", mmresult);

               }

            }

            MMRESULT mmresult3;

            while (i >= 1)
            {

               i--;

               mmresult3 = waveOutClose(m_hwaveout);

               if (mmresult3 == MMSYSERR_NOERROR)
               {

                  TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutClose: Cascade Success");

               }
               else
               {

                  TRACE("multimedia::audio_mmsystem::out::out_open_ex waveOutClose: Cascade ERROR %d!!", mmresult);

               }

            }

            TRACE("ERROR !! Failed to prepare output device buffers");

            throw ::exception(estatus);

         }

      }

      m_estate = e_state_opened;

      m_epurpose = epurpose;

      //return ::success;

   }


   void out::out_close()
   {

      synchronous_lock synchronouslock(mutex());

      if(m_estate == e_state_playing)
      {

         out_stop();

      }

      if (m_estate != e_state_opened)
      {

         return;

      }

      ::e_status estatus;

      MMRESULT mmresult;

      index i;

      auto iSize = out_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         mmresult = waveOutUnprepareHeader(m_hwaveout, wave_hdr(i), sizeof(WAVEHDR));

         estatus = mmresult_to_status(mmresult);

         if(::succeeded(estatus))
         {

            ERROR("ERROR OPENING Unpreparing INPUT DEVICE buffer : " << estatus.m_estatus);

         }

         delete wave_hdr(i);

      }

      mmresult = waveOutClose(m_hwaveout);

      estatus = mmresult_to_status(mmresult);

      m_hwaveout = nullptr;

      ::wave::out::out_close();

   }


   void out::out_filled(index iBuffer)
   {

      out_filled(wave_hdr(iBuffer));

   }


   void out::out_filled(LPWAVEHDR lpwavehdr)
   {

      synchronous_lock synchronouslock(mutex());

      if(out_get_state() != e_state_playing)
      {

         TRACE("ERROR out::BufferReady while out_get_state() != e_state_playing");

         return;

      }

      m_iBufferedCount++;

      MMRESULT mmresult = waveOutWrite(m_hwaveout, lpwavehdr, sizeof(WAVEHDR));

      auto estatus = mmresult_to_status(mmresult);

      if(::failed(estatus))
      {

         m_iBufferedCount--;

      }

   }


   void out::out_stop()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_estate != e_state_playing && m_estate != e_state_paused)
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      //m_pprebuffer->stop();

      m_estate = e_state_stopping;

      // waveOutReset
      // The waveOutReset function stops playback on the given
      // waveform-audio_mmsystem output device and resets the current position
      // to zero. All pending playback buffers are marked as done and
      // returned to the application.

      MMRESULT mmresult = waveOutReset(m_hwaveout);

      m_estatusWave = mmresult_to_status(mmresult);

      if(m_estatusWave == ::success)
      {

         m_estate = e_state_opened;

      }

      //return m_estatusWave;

   }


   void out::out_pause()
   {

      single_lock sLock(mutex(), true);

      ASSERT(m_estate == e_state_playing);

      if (m_estate != e_state_playing)
      {

         throw ::exception(error_wrong_state);

      }

      // waveOutReset
      // The waveOutReset function stops playback on the given
      // waveform-audio_mmsystem output device and resets the current position
      // to zero. All pending playback buffers are marked as done and
      // returned to the application.

      m_estatusWave = mmresult_to_status(waveOutPause(m_hwaveout));

      ASSERT(m_estatusWave == ::success);

      if(m_estatusWave == ::success)
      {

         m_estate = e_state_paused;

      }

      //return m_estatusWave;

   }


   void out::out_restart()
   {

      synchronous_lock synchronouslock(mutex());

      ASSERT(m_estate == e_state_paused);

      if (m_estate != e_state_paused)
      {

         throw ::exception(error_failed);

      }

      // waveOutReset
      // The waveOutReset function stops playback on the given
      // waveform-audio_mmsystem output device and resets the current position
      // to zero. All pending playback buffers are marked as done and
      // returned to the application.

      MMRESULT mmresult = waveOutRestart(m_hwaveout);

      m_estatusWave = mmresult_to_status(mmresult);

      ASSERT(m_estatusWave == ::success);

      if(m_estatusWave == ::success)
      {

         m_estate = e_state_playing;

      }

      //return m_estatusWave;

   }


   ::duration out::out_get_position()
   {

      return device_out_get_time();

   }


   ::duration out::out_get_time()
   {

      return m_durationStart + device_out_get_time();

   }


   ::duration out::device_out_get_time()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_hwaveout == nullptr)
      {

         return 0_s;

      }

      MMTIME mmt = {};

      mmt.wType = TIME_BYTES;

      auto estatus = mmresult_to_status(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

      if (::success != estatus)
      {

         TRACE( "waveOutGetPosition() returned %lu", (u32)estatus.m_estatus);

         return 0_s;

      }

      if(mmt.wType == TIME_BYTES)
      {

         double d = (mmt.u.cb* 8.0)/ (m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels * m_pwaveformat->m_waveformat.nSamplesPerSec);

         //return FLOATING_SECOND((double) d / (double) wave_base_get_byte_count_per_second());

         return FLOATING_SECOND((double)d);

      }
      else
      {

         return FLOATING_SECOND((double) mmt.u.ms / 1'000.0);

      }

   }


   //::duration out::out_get_time()
   //{

   //   return m_positionStart + device_out_get_time();

   //}


   //::duration out::device_out_get_time()
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   void                    estatus;

   //   MMTIME                  mmt = {};

   //   mmt.wType = TIME_BYTES;

   //   if(m_hwaveout != nullptr)
   //   {

   //      estatus = mmresult_to_status(waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt)));

   //      try
   //      {

   //         if (::success != estatus)
   //         {

   //            TRACE( "waveOutGetPosition() returned %lu", (u32)estatus);

   //            return 0;

   //         }

   //      }
   //      catch(...)
   //      {

   //         return 0;

   //      }

   //      if(mmt.wType == TIME_MS)
   //      {

   //         ::duration position = (u32) mmt.u.ms;

   //         position *= m_pwaveformat->nSamplesPerSec;

   //         position /= 8 * 1000;

   //         return position;

   //      }
   //      else if (mmt.wType == TIME_BYTES)
   //      {

   //         return (mmt.u.cb * 8) / (m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels);

   //      }
   //      else
   //      {

   //         return 0;

   //      }

   //   }
   //   else
   //   {

   //      return 0;

   //   }

   //}


   void out::out_free(index iBuffer)
   {

      ::wave::out::out_free(iBuffer);

   }


   void out::out_on_playback_end()
   {

      out::enum_state estate = out_get_state();

      out_stop();

      m_pprebuffer->m_pstreameffectOut.release();

      m_pplayer->post_event(::wave::player::e_player_event_playback_end);

   }


   WAVEFORMATEX * out::wave_format()
   {

      ::multimedia::mmsystem::translate(m_waveformatex, m_pwaveformat);

      return &m_waveformatex;

   }


   HWAVEOUT out::out_get_safe_HWAVEOUT()
   {

      if (this == nullptr)
      {

         return nullptr;

      }

      return m_hwaveout;

   }


   void * out::get_os_data()
   {

      return m_hwaveout;

   }


   LPWAVEHDR out::wave_hdr(index iBuffer)
   {

      return ::multimedia::mmsystem::get_os_data(out_get_buffer(), iBuffer);

   }


} // namespace audio_mmsystem



