#include "framework.h"
#include "sequencer.h"
#include "midi.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "aqua/multimedia/exception.h"
#include "app-veriwell/multimedia/multimedia.h"
#include "app-veriwell/multimedia/ikaraoke/lyric_event_v1.h"
#include "app-veriwell/multimedia/music/midi/file.h"
#include "app-veriwell/multimedia/music/midi/player_command.h"
#include "app-veriwell/multimedia/music/midi/event.h"


template < typename TYPE, std::size_t N >
inline ::block memory_block(TYPE(&type)[N])
{

   return { (void *)__memory_address_of(type), N };

}


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         ::mutex & get_midi_mutex();


         sequencer::sequencer(sequence * psequence, const string & strDevice) :
            ::music::midi::sequencer(psequence, strDevice)
         {

            initialize(psequence);

            __construct_new(m_pbuffera);

            m_pbuffera->m_psequencer = this;

            m_bMessageThread = true;

            defer_create_synchronization();

            auto psystem = acmesystem()->m_paquasystem;

            auto pmultimedia = psystem->multimedia()->m_pveriwellmultimediaThis;

            m_pmidi = pmultimedia->midi()->get_device_midi(strDevice);

            //m_pmessageout = pmultimedia->midi()->get_message_out(strDevice);

            m_hstream = nullptr;

            m_iBufferSize = 8192;

            m_iBufferNominalMax = 4096;

            m_midicallbackdata.m_psequence = psequence;

            m_pbuffera->Initialize(4, m_iBufferSize, &m_midicallbackdata);

         }


         sequencer::~sequencer()
         {

            close_file();

         }


         void CALLBACK sequencer::MidiOutProc(
            HMIDIOUT hmo,
            UINT wMsg,
            DWORD_PTR dwInstance,
            DWORD_PTR dwParam1,
            DWORD_PTR dwParam2
         )
         {

            auto psequencer = (sequencer *)dwInstance;

            psequencer->midi_out_proc(hmo, wMsg, dwParam1, dwParam2);

         }

         void  sequencer::midi_out_proc(
            HMIDIOUT hmo,
            UINT wMsg,
            DWORD_PTR dwParam1,
            DWORD_PTR dwParam2
         )
         {
            if (wMsg == MM_MOM_DONE)
            {

               OnDone((HMIDISTRM)hmo, (LPMIDIHDR)dwParam1);


            }
            else if (wMsg = MM_MOM_POSITIONCB)
            {

               OnPositionCB((LPMIDIHDR)dwParam1);

            }

         }


         void     sequencer::close_file()
         {

            synchronous_lock synchronouslock(synchronization());

            m_psequence->m_pfile->close_file();

            if (m_hstream != nullptr)
            {

               close_device();

            }

            m_psequence->set_state(sequence::e_state_no_file);

            //return ::success;

         }


         void     sequencer::start_mmsystem_sequencer()
         {

            //m_pmessageout->reset_all_controllers();

            bool bThrow = false;

            m_tkLastOp = m_psequence->m_tkBase;

            UINT uDeviceID = (UINT)m_iDevice;

            ::e_status estatus = ::success;

            MIDIPROPTIMEDIV mptd;

            //
            // We've successfully opened the file and all of the tracks; now
            // open the MIDI device and set the time division.
            //
            // NOTE: seqPreroll is equivalent to seek; device might already be open
            //

            //m_bSendXGModeOn = true;

            //m_bSendXGReset = true;

            //m_bSendXGDrumSetup1Reset = true;

            //m_bSendXGDrumSetup2Reset = true;

            //m_bSendMasterVolumeReset = true;

            m_bHadNoteOn = true;

            //SendGMReset();

            //::preempt(500_ms);

            //if (m_bSendXGModeOn || m_bSendXGReset || m_bSendXGDrumSetup1Reset || m_bSendXGDrumSetup2Reset || m_bSendMasterVolumeReset)
            //{

            //   midi_out_open();

            //   if (m_bSendXGModeOn)
            //   {

            //      //midi_out_open();

            //      midi_out_xg_mode_on();

            //      //midi_out_close();

            //      m_bSendXGModeOn = false;

            //   }

            //   if (!m_bSendXGModeOn && m_bSendXGReset)
            //   {

            //      //midi_out_open();

            //      midi_out_xg_mode_reset();

            //      //midi_out_close();

            //      m_bSendXGReset = false;

            //   }

            //   if (!m_bSendXGModeOn && !m_bSendXGReset && m_bSendXGDrumSetup1Reset)
            //   {

            //      //midi_out_open();

            //      midi_out_xg_drum_setup1_reset();

            //      //midi_out_close();

            //      m_bSendXGDrumSetup1Reset = false;

            //   }

            //   if (!m_bSendXGModeOn && !m_bSendXGReset && !m_bSendXGDrumSetup1Reset && m_bSendXGDrumSetup2Reset)
            //   {

            //      //midi_out_open();

            //      midi_out_xg_drum_setup2_reset();

            //      //midi_out_close();

            //      m_bSendXGDrumSetup2Reset = false;

            //   }

            //   if (!m_bSendXGModeOn && !m_bSendXGReset && !m_bSendXGDrumSetup1Reset && !m_bSendXGDrumSetup2Reset && m_bSendMasterVolumeReset)
            //   {

            //      //midi_out_open();

            //      midi_out_master_volume_reset();

            //      //midi_out_close();

            //      m_bSendMasterVolumeReset = false;

            //   }

            //   midi_out_close();

            //}

            //midi_out_open();

            //midi_out_xg_mode_on();

            //midi_out_xg_mode_reset();

            //midi_out_xg_drum_setup1_reset();

            //midi_out_xg_drum_setup2_reset();

            //midi_out_master_volume_reset();

            //midi_out_close();




            if (m_hstream == nullptr)
            {

               MMRESULT mmresult = midiStreamOpen(&m_hstream, &uDeviceID, 1, (DWORD_PTR)&sequencer::MidiOutProc, (DWORD_PTR)(sequencer *)this, CALLBACK_FUNCTION);

               //estatus = translate_os_result(mmr, "sequencer::mm_start", "midiStreamOpen error");

               auto estatus = mmresult_to_status(mmresult);

               if (!estatus)
               {

                  m_hstream = nullptr;

                  m_psequence->set_state(sequence::e_state_opened);

                  throw multimedia::exception(multimedia::e_exception_midi, estatus);

               }

               mptd.cbStruct = sizeof(mptd);

               mptd.dwTimeDiv = m_psequence->m_pfile->m_dwTempoDivision;

               estatus = translate_os_result(midiStreamProperty(m_hstream, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV), "mm_start", "midiStreamProperty(timeDiv)");

               if (estatus != ::success)
               {

                  TRACE("midiStreamProperty() -> %04X", (WORD)estatus.m_estatus);

                  close_device();

                  m_psequence->set_state(sequence::e_state_opened);

                  throw multimedia::exception(multimedia::e_exception_midi, estatus);

               }

            }


            //pplayer->m_psequencer->m_pmessageout->xg_system_on();

            //preempt(100_ms);



            estatus = ::success;

            m_pbuffera->midiOutPrepareHeader((HMIDIOUT)m_hstream);

            for (auto & pbuffer : m_pbuffera->m_buffera)
            {

               fill_buffer(&pbuffer->m_midihdr);

            }

            m_pbuffera->midiStreamOut(m_hstream);

            if (estatus != ::success)
            {

               m_psequence->set_state(sequence::e_state_pre_rolled);

               m_psequence->m_flags.erase(sequence::e_flag_waiting);

            }
            else
            {

               m_psequence->set_state(sequence::e_state_playing);

               auto mmresult = midiStreamRestart(m_hstream);

               estatus = translate_os_result(mmresult, "mm_start", "midiStreamRestart");

               if (estatus != ::success)
               {

                  m_psequence->set_state(sequence::e_state_pre_rolled);

               }
               else
               {

                  post_midi_sequence_event(sequence::e_event_midi_playback_start);

               }

            }

            //return estatus;

         }


         void sequencer::on_set_position()
         {

         }


         void sequencer::install_message_routing(::channel * pchannel)
         {

            ::music::midi::sequencer::install_message_routing(pchannel);

            //MESSAGE_LINK(MM_MOM_DONE, pchannel, this, &sequencer::_001OnMidiOutDone);
            //MESSAGE_LINK(MM_MOM_POSITIONCB, pchannel, this, &sequencer::_001OnMidiOutPositionCB);

         }


         void sequencer::play(player_command * pcommand)
         {

            synchronous_lock synchronouslock(synchronization());

            start_mmsystem_sequencer();

         }


         void sequencer::pause(player_command * pcommand)
         {

            synchronous_lock synchronouslock(synchronization());

            if (sequence::e_state_playing != m_psequence->get_state())
            {

               pcommand->m_estatus = error_unsupported_function;

               return;

            }

            m_psequence->set_state(sequence::e_state_paused);

            pcommand->m_estatus = ::success;

            if (m_hstream != nullptr)
            {

               pcommand->m_estatus = translate_os_result(midiStreamPause(m_hstream), "Pause", "midiStreamPause");

            }

            m_psequence->SetLevelMeter(0);

         }


         void sequencer::restart(player_command * pcommand)
         {

            synchronous_lock synchronouslock(synchronization());

            if (sequence::e_state_paused != m_psequence->get_state())
            {

               pcommand->m_estatus = error_unsupported_function;

               return;

            }

            m_psequence->set_state(sequence::e_state_playing);

            if (m_hstream != nullptr)
            {

               pcommand->m_estatus = translate_os_result(midiStreamRestart(m_hstream), "Restart", "midiStreamRestart");

            }

         }


         void sequencer::stop(player_command * pcommand)
         {

            synchronous_lock synchronouslock(synchronization());

            if (m_psequence->get_state() == sequence::e_state_stopping)
            {

               pcommand->m_estatus = ::success;

               return;

            }

            m_psequence->set_state(sequence::e_state_stopping);

            m_psequence->m_flags.add(sequence::e_flag_waiting);

            if (m_hstream != nullptr)
            {

               MMRESULT mmr = midiStreamStop(m_hstream);

               m_psequence->m_estatusLastError = translate_os_result(mmr, "Stop", "midiStreamStop");

               if (::success != m_psequence->m_estatusLastError)
               {

                  WARNING("::music::midi::sequencer::stop -> midiStreamStop returned %lu", (u32)m_psequence->m_estatusLastError.m_estatus);

                  m_psequence->m_flags.erase(sequence::e_flag_waiting);

                  pcommand->m_estatus = error_not_ready;

                  return;

               }

            }

            m_psequence->SetLevelMeter(0);

         }


         ::e_status sequencer::get_position(musical_tick & tk)
         {

            synchronous_lock synchronouslock(synchronization());

            //void mmr;

            MMTIME mmt;

            if ((sequence::e_state_playing != m_psequence->get_state() &&
               sequence::e_state_paused != m_psequence->get_state() &&
               sequence::e_state_opened != m_psequence->get_state() &&
               sequence::e_state_stopping != m_psequence->get_state())
               || m_hstream == nullptr)
            {

               return error_unsupported_function;

            }

            tk = 0;

            if (sequence::e_state_opened != m_psequence->get_state())
            {

               tk = m_psequence->m_tkBase;

               if (sequence::e_state_pre_rolled != m_psequence->get_state())
               {

                  mmt.wType = TIME_TICKS;

                  if (m_hstream == nullptr)
                  {

                     TRACE("m_hmidi == nullptr!!!!");

                     return error_not_ready;

                  }
                  else
                  {

                     try
                     {

                        MMRESULT mmresult = midiStreamPosition(m_hstream, &mmt, sizeof(mmt));

                        auto estatus = mmresult_to_status(mmresult);

                        if (!estatus)
                        {

                           WARNING("midiStreamPosition() returned :" << estatus.m_estatus);

                           return estatus;

                        }

                     }
                     catch (...)
                     {

                        return error_not_ready;

                     }

                     tk += mmt.u.ticks;

                  }

               }

            }

            return ::success;

         }


         ::duration sequencer::get_time_position()
         {

            ::duration duration;

            get_time_position(duration);

            return duration;

         }


         ::e_status sequencer::get_time_position(::duration & duration)
         {

            synchronous_lock synchronouslock(synchronization());

            ::e_status estatus;

            MMTIME mmtime;

            if (sequence::e_state_playing != m_psequence->get_state() &&
               sequence::e_state_paused != m_psequence->get_state() &&
               sequence::e_state_pre_rolling != m_psequence->get_state() &&
               sequence::e_state_pre_rolled != m_psequence->get_state() &&
               sequence::e_state_opened != m_psequence->get_state() &&
               sequence::e_state_stopping != m_psequence->get_state())
            {

               TRACE("seqTime(): State wrong! [is %u]", m_psequence->get_state());

               return error_unsupported_function;

            }

            if (sequence::e_state_opened != m_psequence->get_state())
            {

               duration = m_psequence->m_durationBase;

               if (sequence::e_state_pre_rolled != m_psequence->get_state())
               {

                  mmtime.wType = TIME_MS;

                  if (m_hstream == nullptr)
                  {

                     TRACE("m_hmidi == nullptr!!!!");

                     return error_not_ready;

                  }
                  else
                  {

                     try
                     {

                        estatus = translate_os_result(midiStreamPosition(m_hstream, &mmtime, sizeof(mmtime)), "get_millis", "midiStreamPosition");

                        if (::success != estatus)
                        {

                           TRACE("midiStreamPosition() returned %lu", (u32)estatus.m_estatus);

                           return error_not_ready;

                        }

                     }
                     catch (...)
                     {

                        return error_not_ready;

                     }

                     duration += INTEGRAL_MILLISECOND(mmtime.u.ms);

                  }

               }

            }

            return ::success;

         }


         ::e_status sequencer::preroll_operation(LPMIDIHDR lpmh)
         {

            LPDWORD lpdw;

            /* Build lpmh from keyframe
            */

            //lpmh->dwBytesRecorded = 0;
            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            while (lpmh->dwBufferLength - lpmh->dwBytesRecorded >= 3 * sizeof(DWORD))
            {

               if (m_iPrerollPhase == 0)
               {

                  // Tempo change event
                  if (KF_EMPTY != m_keyframe.rbTempo[0] || KF_EMPTY != m_keyframe.rbTempo[1] || KF_EMPTY != m_keyframe.rbTempo[2])
                  {

                     *lpdw++ = 0;
                     *lpdw++ = 0;

                     DWORD tempo = 0;

                     reverse_memcpy(&tempo, m_keyframe.rbTempo, 3);

                     double dTempoShiftRate = m_psequence->m_pfile->GetTempoShiftRate();

                     tempo = (DWORD)((double)tempo / dTempoShiftRate);

                     DWORD dw = (((DWORD)MEVT_TEMPO) << 24) | tempo;

                     *lpdw++ = dw;

                     lpmh->dwBytesRecorded += 3 * sizeof(DWORD);
                  }

               }
               else if (m_iPrerollPhase < 17)
               {

                  int idx = m_iPrerollPhase - 1;

                  // Program change events
                  if (KF_EMPTY != m_keyframe.rbProgram[idx])
                  {

                     *lpdw++ = 0;
                     *lpdw++ = 0;
                     *lpdw++ = (((DWORD)MEVT_SHORTMSG) << 24) |
                        ((DWORD)program_change) |
                        ((DWORD)idx) |
                        (((DWORD)m_keyframe.rbProgram[idx]) << 8);

                     lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

                  }

               }
               else if (m_iPrerollPhase < 1 + 16 + 120 * 16)
               {

                  // Controller events

                  int i = m_iPrerollPhase - 17;

                  int idxChannel = i / 120;

                  int idxController = i % 120;

                  int iVal = m_keyframe.rbControl[idxChannel][idxController];

                  if (iVal != KF_EMPTY)
                  {

                     *lpdw++ = 0;
                     *lpdw++ = 0;
                     *lpdw++ = (((DWORD)MEVT_SHORTMSG << 24) |
                        ((DWORD)control_change) |
                        ((DWORD)idxChannel) |
                        (((DWORD)idxController) << 8) |
                        (((DWORD)iVal) << 16));

                     lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

                  }

               }
               else
               {

                  return success;

               }

               m_iPrerollPhase++;

            }

            return error_would_reach_buffer_limit;

         }


         ::e_status sequencer::fill_buffer(LPMIDIHDR lpmidihdr)
         {

            lpmidihdr->dwBytesRecorded = 0;

            ::e_status estatus = ::success;

            if (m_psequence->has_operation())
            {

               if (m_psequence->has_operation(e_operation_general_midi_reset))
               {

                  const uchar gmModeOn[] =
                  {
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x06, 0x00, 0x00, MEVT_LONGMSG,
                     0xf0, 0x7e, 0x7f, 0x09,
                     0x01, 0xf7, 0x00, 0x00
                  };

                  lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);

                  memcpy_dup(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));

                  m_psequence->clear_operation(e_operation_general_midi_reset);

                  return ::success;

               }
               else if (m_psequence->has_operation(e_operation_xg_system_on))
               {

                  const uchar xgSystemOn[] =
                  {
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x09, 0x00, 0x00, MEVT_LONGMSG,
                     0xf0, 0x43, 0x10, 0x4c,
                     0x00, 0x00, 0x7e, 0x00,
                     0xf7, 0x00, 0x00, 0x00
                  };

                  lpmidihdr->dwBytesRecorded = sizeof(xgSystemOn);

                  memcpy_dup(lpmidihdr->lpData, xgSystemOn, sizeof(xgSystemOn));

                  m_psequence->clear_operation(e_operation_xg_system_on);

                  return ::success;

               }
               else if (m_psequence->has_operation(e_operation_preroll))
               {

                  while (lpmidihdr->dwBufferLength - lpmidihdr->dwBytesRecorded > 16)
                  {

                     if (m_iPrerollPhase < 0)
                     {

                        estatus = m_psequence->m_pfile->WorkPreroll(&m_keyframe, m_psequence->m_tkBase);

                        if (estatus != success)
                        {

                           m_psequence->clear_operation(e_operation_preroll);

                           break;

                        }

                        estatus = success_skip;

                     }
                     else
                     {

                        estatus = preroll_operation(lpmidihdr);

                     }

                     if (estatus == error_would_reach_buffer_limit)
                     {

                        break;

                     }
                     else if (estatus == ::success)
                     {

                        m_psequence->clear_operation(e_operation_preroll);

                        m_psequence->set_state(::music::midi::sequence::e_state_pre_rolled);

                        break;

                     }

                     m_iPrerollPhase++;

                  }

               }
               else if (m_psequence->has_operation(e_operation_tempo_change))
               {

                  ::music::midi::event event;

                  m_psequence->m_pfile->GetTempoEvent(event);

                  StreamEvent(event.GetDelta(), &event, lpmidihdr, 0x7fffffff, 256);

                  m_psequence->clear_operation(e_operation_tempo_change);

                  return ::success;

               }

            }

            estatus = ::success;

            if (lpmidihdr->dwBufferLength - lpmidihdr->dwBytesRecorded > 16)
            {

               estatus = WorkStreamRender(lpmidihdr, m_psequence->m_tkEnd, m_iBufferNominalMax);

               switch (estatus.m_estatus)
               {
               case ::success:

                  break;

               case success_end_of_file:

                  m_psequence->m_flags.add(sequence::e_flag_end_of_file);

                  estatus = ::success;

                  break;

               default:


                  TRACE("smfReadEvents returned %lu in callback!", (u32)estatus.m_estatus);

                  m_psequence->set_state(sequence::e_state_stopping);

                  break;

               }

            }

            return estatus;

         }


         void sequencer::OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr)
         {

            __UNREFERENCED_PARAMETER(hmidistream);

            ASSERT(lpmidihdr != nullptr);

            midi_callback_data * pcallbackdata = buffer::get(lpmidihdr)->get_midi_callback_data();

            ASSERT(pcallbackdata != nullptr);

            ASSERT(nullptr != lpmidihdr);

            --m_iBuffersInMMSYSTEM;

            if (sequence::e_state_reset == m_psequence->get_state())
            {

               return;

            }

            bool bStopping = sequence::e_state_stopping == m_psequence->get_state();

            bool bEOF = m_psequence->m_flags.has(sequence::e_flag_end_of_file);

            bool bOperationEnd = m_psequence->m_flags.has(sequence::e_flag_operation_end);

            if (bStopping || bEOF || bOperationEnd)
            {

               if (bOperationEnd)
               {

                  m_psequence->m_flags.erase(sequence::e_flag_operation_end);

                  TRACE("::music::midi::sequencer::MidiOutProc m_flags.has(flag_operation_end)\n");

                  post_midi_sequence_event(sequence::e_event_operation, lpmidihdr);

               }
               else if (m_iBuffersInMMSYSTEM <= 0)
               {

                  TRACE("::music::midi::sequencer::MidiOutProc sequence::e_state_stopping == pSeq->m_psequence->get_state()\n");

                  music_midi_on_playback_end();

               }

            }
            else
            {

               //post_midi_sequence_event(sequence::e_event_midi_stream_out, lpmidihdr);
               synchronous_lock synchronouslock(synchronization());

               //LPMIDIHDR lpmidihdr = (LPMIDIHDR)pevent->m_puserdata;

               auto estatus = fill_buffer(lpmidihdr);

               switch (estatus.m_estatus)
               {
               case ::success:

                  break;

               case ::success_end_of_file:

                  m_psequence->m_flags.add(sequence::e_flag_end_of_file);

                  estatus = ::success;

                  break;

               default:

                  INFORMATION("sequencer::fill_buffer returned %lu", (u32)estatus.m_estatus);

                  m_psequence->set_state(sequence::e_state_stopping);

                  break;

               }

               if (m_hstream != nullptr && m_psequence->get_state() == sequence::e_state_playing)
               {

                  estatus = translate_os_result(midiStreamOut(m_hstream, lpmidihdr, sizeof(*lpmidihdr)), "OnEvent", "midiStreamOut");

                  if (estatus == ::success)
                  {

                     ++m_iBuffersInMMSYSTEM;

                  }
                  else
                  {

                     INFORMATION("e_event_midi_stream_out : midiStreamOut returned %lu", (u32)estatus.m_estatus);

                     m_psequence->set_state(sequence::e_state_stopping);

                  }

               }


            }

         }


         void sequencer::OnPositionCB(LPMIDIHDR lpmidihdr)
         {

            return;

            ASSERT(lpmidihdr != nullptr);
            LPBYTE lpbData = (LPBYTE)(lpmidihdr->lpData + lpmidihdr->dwOffset);
            MIDIEVENT * lpme = (MIDIEVENT *)lpbData;
            file::midi_stream_event_header * pheader = (file::midi_stream_event_header *)&lpme->dwParms[0];
            lpbData = (LPBYTE)pheader;
            LPDWORD lpdwParam;

            i32 iSize = pheader->m_dwLength;
            switch (pheader->m_dwType)
            {
            case 0:
            {
               array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> * plyriceventa = nullptr;
               array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> lyriceventa;
               for (i32 i = sizeof(file::midi_stream_event_header); i < iSize;)
               {
                  pheader = (file::midi_stream_event_header *)&lpbData[i];
                  lpdwParam = (LPDWORD)&lpbData[i + sizeof(file::midi_stream_event_header)];
                  ASSERT(*lpdwParam == pheader->m_dwType);
                  switch (pheader->m_dwType)
                  {
                  case EVENT_ID_LYRIC_V1:
                  {
                     if (plyriceventa == nullptr)
                     {
                        plyriceventa = new array <::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &>;
                     }
                     ::memory_file memFile((LPBYTE)&lpdwParam[1], pheader->m_dwLength - sizeof(DWORD));
                     /* x2x                  CArchive ar(&memFile, CArchive::load);
                     lyriceventa.Serialize(ar);
                     plyriceventa->append(lyriceventa); */
                  }
                  break;
                  case EVENT_ID_PAD:
                  {
                  }
                  break;
                  case EVENT_ID_NOTE_ON:
                  {

                     auto pfile = create_memory_file();

                     pfile->memory().assign((LPBYTE)&lpdwParam[1], pheader->m_dwLength - sizeof(DWORD));

                     auto stream = __binary_stream(pfile);

                     for (i32 i = 0; i < m_psequence->m_iaLevel.get_size(); i++)
                     {

                        BYTE b;

                        stream >> b;

                        m_psequence->m_iaLevel.element_at(i) = b;

                     }

                  }
                  break;
                  }
                  i += pheader->m_dwLength + sizeof(file::midi_stream_event_header);
               }
               /*         if(plyriceventa != nullptr)
               {
               ::PostMessage(m_midicallbackdata.oswindow, WM_APP + 3388, 3388, (LPARAM) plyriceventa);
               }*/
            }
            break;
            case EVENT_ID_PAD:
               break;
            default:
               ASSERT(false);
               break;
            }

         }

         /*
         void CALLBACK sequencer::MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
         {

            __UNREFERENCED_PARAMETER(hmo);
            __UNREFERENCED_PARAMETER(dwParam2);

            LPMIDIHDR lpmidihdr     = (LPMIDIHDR) dwParam1;
            sequencer * psequence    = (sequencer *)dwInstance;

            switch(wMsg)
            {
            case MOM_POSITIONCB:
               psequence->OnPositionCB(lpmidihdr);
               break;

            case MOM_DONE:
               psequence->OnDone(nullptr, lpmidihdr);
               break;

            default:
               break;

            }

         }
         */

         bool sequencer::IsPlaying()
         {

            return m_psequence->get_state() == sequence::e_state_playing || m_psequence->get_state() == sequence::e_state_stopping;

         }



         void     sequencer::close_stream()
         {

            synchronous_lock synchronouslock(synchronization());

            m_pbuffera->midiOutUnprepareHeader((HMIDIOUT)m_hstream);

            if (m_hstream != nullptr)
            {

               close_device();

            }

            m_psequence->set_state(sequence::e_state_opened);

            //return ::success;

         }


         void sequencer::close_device()
         {

            synchronous_lock synchronouslock(synchronization());

            if (m_hstream == nullptr)
            {

               return;

            }

            m_psequence->set_state(sequence::e_state_reset);

            midiOutReset((HMIDIOUT)m_hstream);

            //while (m_iBuffersInMMSYSTEM > 0)
            // Sleep(100);

            auto estatus = m_pbuffera->midiOutUnprepareHeader((HMIDIOUT)m_hstream);

            if (!estatus)
            {

               TRACE("midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (u32)estatus.m_estatus);

            }

            midiStreamClose(m_hstream);

            m_hstream = nullptr;

            m_psequence->set_state(sequence::e_state_opened);

         }


         //void sequencer::on_midi_playback_end(sequence::event * pevent)
         //{



         //}


         void sequencer::OnEvent(sequence::event * pevent)
         {

            ::music::midi::sequencer::OnEvent(pevent);

            switch (pevent->m_eevent)
            {
            case sequence::e_event_operation:
            {

               //               m_psequence->set_operation_on(false);

               m_psequence->set_state(m_psequence->m_estatePreOperation);

            }
            break;
            case sequence::e_event_midi_playback_end:
            {

               m_psequence->set_state(sequence::e_state_opened);

            }
            break;
            case sequence::e_event_midi_stream_out:
            {

               //synchronous_lock synchronouslock(synchronization());

               //LPMIDIHDR lpmidihdr = (LPMIDIHDR)pevent->m_puserdata;

               //void     estatus = fill_buffer(lpmidihdr);

               //switch (estatus.m_estatus)
               //{
               //case ::success:

               //   break;

               //case ::success_end_of_file:

               //   m_psequence->m_flags.add(sequence::e_flag_end_of_file);

               //   estatus = ::success;

               //   break;

               //default:

               //   INFORMATION("sequencer::fill_buffer returned %lu", (u32)estatus.m_estatus);

               //   m_psequence->set_state(sequence::e_state_stopping);

               //   break;

               //}

               //if (m_hstream != nullptr && m_psequence->get_state() == sequence::e_state_playing)
               //{

               //   estatus = translate_os_result(midiStreamOut(m_hstream, lpmidihdr, sizeof(*lpmidihdr)), "OnEvent", "midiStreamOut");

               //   if (estatus == ::success)
               //   {

               //      ++m_iBuffersInMMSYSTEM;

               //   }
               //   else
               //   {

               //      INFORMATION("e_event_midi_stream_out : midiStreamOut returned %lu", (u32)estatus.m_estatus);

               //      m_psequence->set_state(sequence::e_state_stopping);

               //   }

               //}

            }
            default:
               break;
            }

         }


         musical_tick sequencer::get_position()
         {

            single_lock synchronouslock(mutex());

            MMTIME mmt;

            mmt.wType = TIME_TICKS;

            if (::success !=
               midiStreamPosition(
                  m_hstream,
                  &mmt,
                  sizeof(mmt)))
               return -1;

            return mmt.u.ticks + m_psequence->m_tkPrerollBase;


         }


         bool sequencer::IsChangingTempo()
         {

            return m_psequence->m_flags.has(sequence::e_flag_tempo_change);

         }


         void sequencer::SetTempoChangeFlag(bool bSet)
         {

            m_psequence->m_flags.set(sequence::e_flag_tempo_change, bSet);

         }


         bool sequencer::IsNull()
         {

            if (this == nullptr)
            {

               return true;

            }

            return false;

         }


         //musical_tick sequencer::TimeToPosition(::duration ::duration)
         //{
         //   return musical_tick(MillisecsToTicks((iptr)::duration));
         //}

         //::duration sequencer::PositionToTime(musical_tick tk)
         //{
         //   return ::duration(TicksToMillisecs((musical_tick)(iptr)tk));
         //}


         //void sequencer::get_time(::duration & time)
         //{

         //   get_time_position(time);

         //}


         bool sequencer::IsOpened()
         {

            return m_psequence->get_state() != sequence::e_state_no_file;

         }


         musical_tick sequencer::GetQuarterNote()
         {

            return m_psequence->m_pfile->midi_file_header()->GetQuarterNoteTicks();

         }


         i32 sequencer::GetDefaultCodePage()
         {
            return 1252;
         }


         bool sequencer::IsSettingPosition()
         {
            return  m_psequence->m_flags.has(sequence::e_flag_setting_position);
         }


         void sequencer::SetSettingPositionFlag(bool bSet)
         {

            m_psequence->m_flags.set(sequence::e_flag_setting_position, bSet);

         }


         //::music::midi::sequencer::event* sequencer::create_new_event(::music::midi::sequencer::e_event eevent, LPMIDIHDR lpmidihdr)
         //{

         //   ASSERT(this != nullptr);

         //   event * pevent = new event();

         //   ptopic->m_atom = eevent;
         //   ptopic->m_psequence = this;
         //   ptopic->m_puserdata = lpmidihdr;

         //   return pevent;

         //}


         void sequencer::midi_out_open()
         {

            TRACE("::music::midi::mmsystem::player::SendReset : (0)");

            m_hmidiout = nullptr;

            UINT uDeviceID = (UINT)m_iDevice;

            m_eventLongMessage.ResetEvent();

            MMRESULT mmresult = midiOutOpen(&m_hmidiout, uDeviceID, (DWORD_PTR)m_eventLongMessage.hsync(), 0, CALLBACK_EVENT);

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

         }


         void sequencer::midi_out_long_message(const block & block, const ::duration & duration)
         {

            if ((block.get_size() & 0x3) != 0)
            {

               ASSERT(FALSE);

               m_estatusMidiOut = error_bad_argument;

               return;

            }

            TRACE("::music::midi::mmsystem::player::SendReset : (0)");

            ::e_status estatus = ::success;

            MMRESULT mmresult;

            memory m1;

            m1.set_size(sizeof(MIDIHDR));

            MIDIHDR * pmidihdr = (MIDIHDR *)m1.get_data();

            memory m;

            m.assign(block.get_data(), block.get_size());

            pmidihdr->lpData = (LPSTR)m.get_data();

            pmidihdr->dwBufferLength = (DWORD)m.get_size();

            auto hmidiout = m_hmidiout;

            mmresult = midiOutPrepareHeader(hmidiout, pmidihdr, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               m_estatusMidiOut = estatus;

               return;

            }

            mmresult = midiOutLongMsg(hmidiout, pmidihdr, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               m_estatusMidiOut = estatus;

               return;

            }

            ::preempt(duration);

            while (!(pmidihdr->dwFlags & MHDR_DONE))
            {

               m_eventLongMessage.wait();

            }

            mmresult = midiOutUnprepareHeader(hmidiout, pmidihdr, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               m_estatusMidiOut = estatus;

               return;

            }

            m_estatusMidiOut = ::success;

            m_eventLongMessage.ResetEvent();

         }


         void sequencer::midi_out_xg_mode_on()
         {

            const uchar XGModeOn[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x09, 0x00, 0x00, MEVT_LONGMSG,
               0xF0, 0x43, 0x10, 0x4C,
               0x00, 0x00, 0x7E, 0x00,
               0xF7, 0x00, 0x00, 0x00
            };

            midi_out_long_message(memory_block(XGModeOn), 800_ms);

         }


         void sequencer::midi_out_xg_mode_reset()
         {

            const uchar XGModeReset[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x09, 0x00, 0x00, MEVT_LONGMSG,
               0xF0, 0x43, 0x10, 0x4C,
               0x00, 0x00, 0x7F, 0x00,
               0xF7, 0x00, 0x00, 0x00
            };

            midi_out_long_message(memory_block(XGModeReset), 800_ms);

         }


         void sequencer::midi_out_xg_drum_setup1_reset()
         {

            const uchar XGDrumSetup1Reset[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x09, 0x00, 0x00, MEVT_LONGMSG,
               0xF0, 0x43, 0x10, 0x4C,
               0x00, 0x00, 0x7D, 0x00,
               0xF7, 0x00, 0x00, 0x00
            };

            midi_out_long_message(memory_block(XGDrumSetup1Reset), 800_ms);

         }


         void sequencer::midi_out_xg_drum_setup2_reset()
         {

            const uchar XGDrumSetup2Reset[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x0c, 0x00, 0x00, MEVT_LONGMSG,
               0xF0, 0x43, 0x10, 0x4C,
               0x00, 0x00, 0x7D, 0x01,
               0xF7, 0x00, 0x00, 0x00
            };

            midi_out_long_message(memory_block(XGDrumSetup2Reset), 800_ms);

         }


         void sequencer::midi_out_master_volume_reset()
         {

            const uchar MasterVolume[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x08, 0x00, 0x00, MEVT_LONGMSG,
               0xF0, 0x7F, 0x7F, 0x04,
               0x01, 0x00, 0x64, 0xF7
            };

            midi_out_long_message(memory_block(MasterVolume), 200_ms);

         }


         void sequencer::midi_out_close()
         {

            ::e_status estatus = ::success;

            auto mmr = midiOutClose(m_hmidiout);

            estatus = translate_os_result(mmr);

            if (!estatus)
            {

               ERROR("midiOutClose error");

            }

            //return estatus;

         }


         void sequencer::SendGMReset()
         {

            synchronous_lock synchronouslock(&get_midi_mutex());

            TRACE("::music::midi::mmsystem::player::SendReset : (0)");

            HMIDIOUT hmidiout = nullptr;

            MMRESULT mmresult;

            UINT uDeviceID = (UINT)m_iDevice;

            manual_reset_event event;

            event.ResetEvent();

            mmresult = midiOutOpen(&hmidiout, uDeviceID, (DWORD_PTR)event.hsync(), 0, CALLBACK_THREAD);

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

            const uchar gmModeOn[] =
            {
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x06, 0x00, 0x00, MEVT_LONGMSG,
               0xf0, 0x7e, 0x7f, 0x09,
               0x01, 0xf7, 0x00, 0x00
            };

            MIDIHDR mh;

            LPMIDIHDR lpmh = &mh;

            __zero(mh);

            lpmh->lpData = (char *)gmModeOn;
            lpmh->dwBufferLength = sizeof(gmModeOn);

            mmresult = midiOutPrepareHeader(hmidiout, lpmh, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

            lpmh->dwBytesRecorded = sizeof(gmModeOn);

            mmresult = midiOutLongMsg(hmidiout, lpmh, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

            while (!(mh.dwFlags & MHDR_DONE))
            {

               event.wait();

            }

            mmresult = midiOutUnprepareHeader(hmidiout, lpmh, sizeof(MIDIHDR));

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

            mmresult = midiOutClose(hmidiout);

            estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

         }


         void sequencer::music_midi_on_playback_end()
         {

            {

               synchronous_lock synchronouslock(synchronization());

               ASSERT(m_iBuffersInMMSYSTEM <= 0);

               INFORMATION("music_midi_on_playback_end");

               close_device();

               m_psequence->m_estatusLastError = ::success;

               m_psequence->m_flags.erase(sequence::e_flag_waiting);

            }

            post_midi_sequence_event(sequence::e_event_midi_playback_end, nullptr);

         }


         ::e_status sequencer::StreamEventF1(musical_tick tkDelta,
            array < ::music::midi::event *, ::music::midi::event * > & eventptra,
            LPMIDIHDR lpmh,
            musical_tick tkMax,
            u32 cbPrerollNomimalMax
         )
         {

            __UNREFERENCED_PARAMETER(tkMax);
            __UNREFERENCED_PARAMETER(cbPrerollNomimalMax);

            ::e_status estatus;

            if (eventptra.get_size() <= 0)
            {
               return ::success;
            }

            ::music::midi::event * pevent;
            i32 iSize = sizeof(file::midi_stream_event_header);
            i32 i;
            for (i = 0; i < eventptra.get_size(); i++)
            {
               pevent = eventptra[i];
               ASSERT(pevent->GetFlags() & 1);
               iSize += (i32)pevent->GetDataSize();
               iSize += sizeof(file::midi_stream_event_header);
            }

            m_psequence->m_pfile->m_memstorageF1.set_size(iSize);
            byte * lpbParam;
            LPDWORD lpdwType;
            file::midi_stream_event_header * pheader;
            pheader = (file::midi_stream_event_header *)&m_psequence->m_pfile->m_memstorageF1.get_data()[0];
            pheader->m_dwLength = iSize - sizeof(file::midi_stream_event_header);
            pheader->m_dwType = 0;
            iSize = sizeof(file::midi_stream_event_header);
            for (i = 0; i < eventptra.get_size(); i++)
            {
               pevent = eventptra[i];
               lpbParam = pevent->GetData();
               lpdwType = (LPDWORD)lpbParam;
               pheader = (file::midi_stream_event_header *)&m_psequence->m_pfile->m_memstorageF1.get_data()[iSize];
               pheader->m_dwLength = (DWORD)pevent->GetDataSize();
               pheader->m_dwType = *lpdwType;
               memcpy_dup(
                  &m_psequence->m_pfile->m_memstorageF1.get_data()[iSize + sizeof(file::midi_stream_event_header)],
                  lpbParam,
                  pheader->m_dwLength);
               iSize += pheader->m_dwLength + sizeof(file::midi_stream_event_header);
            }

            m_psequence->m_pfile->m_cbPendingUserEvent = (u32)m_psequence->m_pfile->m_memstorageF1.get_size();
            m_psequence->m_pfile->m_hpbPendingUserEvent = m_psequence->m_pfile->m_memstorageF1.get_data();
            ASSERT(m_psequence->m_pfile->m_hpbPendingUserEvent);
            m_psequence->m_pfile->m_flags &= ~InsertSysEx;
            m_psequence->m_pfile->m_dwPendingUserEvent = ((MEVT_F_CALLBACK | MEVT_F_LONG | (((DWORD)MEVT_COMMENT) << 24)) & 0xFF000000L);

            estatus = InsertParmData(tkDelta, lpmh);

            if (!estatus)
            {

               WARNING("smfInsertParmData[2] : " << estatus.m_estatus);

            }

            return estatus;

         }


         ::e_status sequencer::StreamEvent(
            musical_tick tkDelta,
            ::music::midi::event * pevent,
            LPMIDIHDR lpmh,
            musical_tick tkMax,
            u32 cbPrerollNominalMax)
         {

            __UNREFERENCED_PARAMETER(tkMax);

            if (pevent->GetFlags() & 1)
            {

               return ::success;

            }

            DWORD dwTempo;
            LPDWORD lpdw;
            ::e_status estatus;

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            if (pevent->GetFlags() & 1)
            {

               ASSERT(false);

            }
            else if (pevent->GetFullType() < msg)
            {

               output_debug_string("Running Status");

            }
            else if (pevent->GetFullType() < sys_ex)
            {

               if (pevent->GetType() == program_change)
               {

                  i32 iTrack = pevent->GetTrack();

                  i32 iProgramChange = pevent->GetChB1();

                  m_keyframe.rbProgram[iTrack] = (byte)iProgramChange;

               }
               else if (pevent->GetType() == control_change)
               {

                  i32 iTrack = pevent->GetTrack();

                  i32 iController = pevent->GetChB1();

                  i32 iControllerValue = pevent->GetChB2();

                  if (iController >= 0 && iController < 120)
                  {

                     m_keyframe.rbControl[iTrack][iController] = (byte)iControllerValue;

                  }

                  if (iController == 94)
                  {

                     if (iTrack == 7)
                     {

                        output_debug_string("what is the controller value?");

                     }
                     else if (iTrack == 6)
                     {

                        output_debug_string("what is the controller value?");

                     }


                  }
               }

               if (!m_bHadNoteOn)
               {

                  if (pevent->GetType() == note_on)
                  {

                     m_bHadNoteOn = true;

                  }

               }

               if (m_psequence->m_pfile->m_iKeyShift)
               {

                  if ((pevent->GetType() == note_on || pevent->GetType() == note_off)
                     && !((m_keyframe.rbProgram[pevent->GetTrack()] == 0)))
                  {

                     i32 iNotePitch = pevent->GetNotePitch();

                     iNotePitch += m_psequence->m_pfile->m_iKeyShift;

                     while (iNotePitch >= 0x80)
                     {

                        iNotePitch -= 12;

                     }

                     while (iNotePitch < 0)
                     {

                        iNotePitch += 12;

                     }

                     pevent->SetNotePitch((byte)iNotePitch);

                  }

               }

               if (3 * sizeof(DWORD) > cbPrerollNominalMax)
               {

                  return error_would_reach_buffer_limit;

               }

               *lpdw++ = (DWORD)tkDelta;
               *lpdw++ = 0;
               *lpdw++ = (((DWORD)MEVT_SHORTMSG) << 24) |
                  ((DWORD)pevent->GetFullType()) |
                  (((DWORD)pevent->GetChB1()) << 8) |
                  (((DWORD)pevent->GetChB2()) << 16);

               lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

            }
            else if (pevent->GetFullType() == ::music::midi::meta &&
               pevent->GetMetaType() == e_meta_end_of_track)
            {
               /* These are ignoreable since smfReadNextEvent()
               ** takes care of track merging
               */
            }
            else if (::music::midi::meta == pevent->GetFullType() && e_meta_tempo == pevent->GetMetaType())
            {

               if (pevent->GetDataSize() != 3)
               {

                  TRACE("smfReadEvents: Corrupt tempo event");

                  return error_invalid_file;

               }

               if (3 * sizeof(DWORD) > cbPrerollNominalMax)
               {

                  return error_would_reach_buffer_limit;

               }

               dwTempo = (((DWORD)pevent->GetData()[0]) << 16) |
                  (((DWORD)pevent->GetData()[1]) << 8) |
                  ((DWORD)pevent->GetData()[2]);

               dwTempo = (DWORD)((double)dwTempo / m_psequence->m_pfile->GetTempoShiftRate());

               DWORD dw = (((DWORD)MEVT_TEMPO) << 24) | dwTempo;

               *lpdw++ = (DWORD)tkDelta;
               *lpdw++ = 0;
               *lpdw++ = dw;

               lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

            }
            //       else if ((Meta == pEvent->GetType()) &&
            //          (05 == pEvent->GetType()))
            ///      {
            /**lpdw++ = (DWORD)pEvent->tkDelta;
            *lpdw++ = 0;
            *lpdw++ = MEVT_F_SHORT | MEVT_F_CALLBACK |
            (((DWORD)MEVT_SHORTMSG )<<24) |
            ((DWORD)7) |
            (((DWORD)13) << 8) |
            (((DWORD)31) << 16);
            lpmh->dwBytesRecorded += 3*sizeof(DWORD);*/
            //m_psequence->m_pfile->m_cbPendingUserEvent = ((DWORD)MEVT_SHORTMSG )<<24;
            //         str = (char *) malloc(pEvent->cbParm + 1);
            //         strncpy(str, (const ::string &) pEvent->hpbParm,  pEvent->cbParm);
            //         str[pEvent->cbParm] = 0;
            //         printf("%s", str);

            //         m_psequence->m_pfile->m_cbPendingUserEvent = pEvent->cbParm;
            //            m_psequence->m_pfile->m_hpbPendingUserEvent = pEvent->hpbParm;
            //            m_fdwSMF &= ~FlagInsertSysEx;
            //         m_dwPendingUserEvent = MEVT_F_CALLBACK |(((DWORD)MEVT_LONGMSG )<<24);
            //m_dwPendingUserEvent = (((DWORD)MEVT_LONGMSG )<<24);
            //         smfrc = smfInsertParmData(pSmf, pEvent->tkDelta, lpmh);
            //            if (::success != smfrc)
            //            {
            //                TRACE( "smfInsertParmData[2] %u", (DWORD)smfrc);
            //                return smfrc;
            //            }

            //            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);


            //smfrc = smfInsertParmData(pSmf, pEvent->tkDelta, lpmh);
            //if (::success != smfrc)
            //{
            //    TRACE( "smfInsertParmData[2] %u", (DWORD)smfrc);
            //    return smfrc;
            //}
            //         _CrtSetReportFile(_CRT_WARN, debugFile);
            //         _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);

            //_RPT0(_CRT_WARN, "Lyric:");
            //_RPT1(_CRT_WARN, "%s", lpmh->lpData);
            //_RPT0(_CRT_WARN, "\n");

            //    }
            else if (pevent->GetFullType() != ::music::midi::meta)
            {

               int iFullType = pevent->GetFullType();
            
               //if (iFullType == sys_ex || iFullType == sys_ex_end)
               if (iFullType == sys_ex)
               {

                  //            if(pEvent->GetFullType() == SysEx)
                  //         {
                  //                break;
                  //            }
                  ///* Must be F0 (ended with F7) system exclusive or FF meta
                  //** that we didn't recognize
                  //*/

                  if (3 * sizeof(DWORD) + pevent->GetDataSize() > cbPrerollNominalMax)
                  {

                     return error_would_reach_buffer_limit;

                  }

                  int iSize = (DWORD)pevent->GetDataSize();
                  auto pdata = pevent->GetData();

                  m_psequence->m_pfile->m_cbPendingUserEvent = iSize;
                  m_psequence->m_pfile->m_hpbPendingUserEvent = pdata;


                  if (iSize == 9)
                  {
                     if (pdata[0] == 0xf0 && pdata[1] == 0x43
                        && pdata[2] == 0x10 && pdata[3] == 0x4c
                        && pdata[4] == 0x08)
                     {

                        int NNMultiPartChannel = pdata[5];

                        if (pdata[6] == 0x14)
                        {

                           int iVariationSend = pdata[7];

                           output_debug_string("MULTIPART VARIATION SEND");



                        }



                     }

                  }
                  m_psequence->m_pfile->m_dwPendingUserEvent = ((DWORD)MEVT_LONGMSG) << 24;
                  //m_psequence->m_pfile->m_flags &= ~InsertSysEx;

                  //if (pEvent->GetFullType() == sys_ex_end)
                  //{
                  //   m_psequence->m_pfile->m_dwPendingUserEvent = ((DWORD)MEVT_LONGMSG) << 24;
                  //}
                  //else if (pEvent->GetFullType() == sys_ex)
                  //{
                  //   //m_psequence->m_pfile->m_flags |= InsertSysEx;
                  //   //m_psequence->m_pfile->m_cbPendingUserEvent;

                  //   /* Falling through...
                  //   */

                  //   m_psequence->m_pfile->m_dwPendingUserEvent = ((DWORD)MEVT_LONGMSG) << 24;

                  //}

                  estatus = InsertParmData(tkDelta, lpmh);

                  if (!estatus)
                  {

                     WARNING("smfInsertParmData[2] : " << estatus.m_estatus);

                     return estatus;

                  }

                  lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

               }
               else
               {

                  output_debug_string("WHAT MIDI FULL TYPE ?!?!?!");

               }

            }
            else // Meta
            {

               // if the meta event has tkDelta > 0,
               // the meta event is inserted in the stream
               // so syncing is maintained.
               if (tkDelta > 0)
               {

                  if (16 * sizeof(DWORD) > cbPrerollNominalMax)
                  {

                     return error_would_reach_buffer_limit;

                  }

                  InsertPadEvent(tkDelta, lpmh);

                  lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

               }

            }

            return ::success;

         }


         ::e_status sequencer::InsertPadEvent(musical_tick tkDelta, LPMIDIHDR lpmh)
         {

            LPDWORD     lpdw;
            DWORD    dwRounded;
            DWORD    dwLength;


            ASSERT(tkDelta >= 0);
            ASSERT(lpmh != nullptr);

            /* Can't fit 4 DWORD's? (tkDelta + stream-atom + event + some data)
            ** Can't do anything.
            */
            ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
            //   m_psequence->m_pfile->m_dwPendingUserEvent = MEVT_F_CALLBACK |
            //             (((DWORD)MEVT_LONGMSG)<<24);
            //   m_psequence->m_pfile->m_cbPendingUserEvent = 2 * sizeof(DWORD);
            //   if(!m_cbPendingLyricEventV1)
            //   if(!1)
            //   {
            //      return ::success;
            //   }

            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(DWORD))
            {
               if (0 == tkDelta)
                  return ::success;

               /* If we got here with a real delta, that means smfReadEvents screwed
               ** up calculating left space and we should flag it somehow.
               */
               TRACE("Can't fit initial piece of SysEx into file!");
               return error_invalid_file;

            }

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
            dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3 * sizeof(DWORD);
            dwLength = minimum(dwLength, 8);

            //DWORD dwa = MEVT_F_CALLBACK;
            //   DWORD dwb = MEVT_LONGMSG;
            //   DWORD dwc = MEVT_F_LONG;
            //   DWORD dwd = MEVT_COMMENT;

            dwRounded = (dwLength + 3) & (~3L);

            //tkOffset = tkDelta;
            *lpdw++ = (DWORD)tkDelta;
            *lpdw++ = 0;
            //*lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((DWORD)MEVT_LONGMSG)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            //   *lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((DWORD)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = ((MEVT_F_LONG | (((DWORD)MEVT_COMMENT) << 24)) & 0xFF000000L) | (dwLength & 0x00FFFFFFL);;
            *lpdw++ = 0;
            *lpdw++ = EVENT_ID_PAD;

            //   if(m_cbPendingLyricEventV1 >= (3 * sizeof(DWORD)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nType;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (2 * sizeof(DWORD)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nTrack;
            //   }
            //   if(m_cbPendingLyricEventV1 >= (1 * sizeof(DWORD)))
            //   {
            //      // offset Lyric CallBack Event Code
            //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex;
            //      m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex++;
            //   }
            //   m_pPendingLyricEventV1->ToData(lpdw, m_cbPendingLyricEventV1);
            //   if (0 == (m_cbPendingLyricEventV1 -= dwLength))
            //   {
            //   }
            //   else
            //   {
            //      i32 i = 5;
            //   }

            lpmh->dwBytesRecorded += 3 * sizeof(DWORD) + dwRounded;

            return ::success;

         }


         ::e_status sequencer::InsertParmData(musical_tick tkDelta, LPMIDIHDR lpmh)
         {

            DWORD             dwLength;
            DWORD             dwRounded;
            LPDWORD           lpdw;

            //    assert(pSmf != nullptr);
            ASSERT(lpmh != nullptr);

            /* Can't fit 4 DWORD's? (tkDelta + stream-atom + event + some data)
            ** Can't do anything.
            */
            ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);

            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(DWORD))
            {
               if (0 == tkDelta)
                  return ::success;

               /* If we got here with a real delta, that means smfReadEvents screwed
               ** up calculating left space and we should flag it somehow.
               */
               TRACE("Can't fit initial piece of SysEx into file!");
               return error_invalid_file;
            }

            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

            dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3 * sizeof(DWORD);
            auto cbPendingUserEvent = m_psequence->m_pfile->m_cbPendingUserEvent;

            if (cbPendingUserEvent < dwLength)
            {

               dwLength = cbPendingUserEvent;

            }
            else
            {

               ::output_debug_string("didn't fit");

            }



            //if (!m_bHadNoteOn)
            //{

            //   if (tkDelta == 0)
            //   {

            //      *lpdw++ = (DWORD)480;

            //   }
            //   else
            //   {

            //      *lpdw++ = (DWORD) (*lpdw + 240);

            //   }

            //}
            //else
            //{
            * lpdw++ = (DWORD)tkDelta;
            //}
            *lpdw++ = 0L;
            *lpdw++ = (m_psequence->m_pfile->m_dwPendingUserEvent & 0xFF000000L) | (dwLength & 0x00FFFFFFL);

            dwRounded = (dwLength + 3) & (~3L);

            //if (m_psequence->m_pfile->m_flags & InsertSysEx)
            //{
            //   byte* lpb = (byte*)lpdw;
            //   //*lpb++ = sys_ex;
            //   m_psequence->m_pfile->m_flags &= ~InsertSysEx;
            //   //dwLength;
            //   //m_psequence->m_pfile->m_cbPendingUserEvent;
            //   lpdw = (LPDWORD)lpb;
            //}

            if (dwLength & 0x80000000L)
            {
               TRACE("dwLength %08lX  dwBytesRecorded %08lX  dwBufferLength %08lX", dwLength, lpmh->dwBytesRecorded, lpmh->dwBufferLength);
               TRACE("cbPendingUserEvent %08lX  dwPendingUserEvent %08lX dwRounded %08lX", m_psequence->m_pfile->m_cbPendingUserEvent, m_psequence->m_pfile->m_dwPendingUserEvent, dwRounded);
               TRACE("offset into MIDI image %08lX", (DWORD)(m_psequence->m_pfile->m_hpbPendingUserEvent - m_psequence->m_pfile->GetImage()));
               TRACE("!hmemcpy is about to fault");
            }

            memcpy_dup(lpdw, m_psequence->m_pfile->m_hpbPendingUserEvent, dwLength);

            byte * pb = (byte *)lpdw;

            string strMessageText;

            for (DWORD dw = 0; dw < dwLength; dw++)
            {

               strMessageText += ::hex::upper_from(pb[dw]);

               strMessageText += " ";

            }

            FORMATTED_INFORMATION("sysex:%s", strMessageText.c_str());

            auto remainingBytes = dwRounded - dwLength;

            if (remainingBytes > 0)
            {

               zero(m_psequence->m_pfile->m_hpbPendingUserEvent + dwLength, remainingBytes);

            }

            m_psequence->m_pfile->m_cbPendingUserEvent -= dwLength;

            if (m_psequence->m_pfile->m_cbPendingUserEvent == 0)
            {

               m_psequence->m_pfile->m_dwPendingUserEvent = 0;

            }

            lpmh->dwBytesRecorded += 3 * sizeof(DWORD) + dwRounded;

            return ::success;

         }


         ::e_status sequencer::WorkStreamRender(LPMIDIHDR lpmh, musical_tick tkMax, i32 iBufferNominalMax)
         {

            ::e_status              estatus;
            musical_tick            tkDelta;
            musical_tick            tkLastPosition;

            ASSERT(lpmh != nullptr);

            //            lpmh->dwBytesRecorded = 0;

            if (m_psequence->m_pfile->m_dwPendingUserEvent)
            {

               estatus = InsertParmData((musical_tick)0, lpmh);

               if (!estatus)
               {

                  WARNING("smfInsertParmData() -> : " << estatus.m_estatus);

                  return estatus;

               }

            }

            if (m_psequence->m_pfile->m_flags & EndOfFile)
            {

               return success_end_of_file;

            }

            tkLastPosition = m_psequence->m_pfile->GetPosition();

            while (true)
            {

               ASSERT(lpmh->dwBytesRecorded <= lpmh->dwBufferLength);

               if (m_psequence->m_pfile->GetPosition() > 0)
               {

                  if (::comparison::gt(lpmh->dwBytesRecorded, iBufferNominalMax) && lpmh->dwBytesRecorded > 0)
                  {

                     break;

                  }

               }

               // If we know ahead of time we won't have room for the
               // event, just break out now. We need 2 DWORD's for the
               // terminator event and at least 2 DWORD's for any
               // event we might store - this will allow us a full
               // i16 event or the delta time and stub for a long
               // event to be split.
               //
               //


               // now 16 DWORDS
               //
               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(DWORD))
               {

                  break;

               }

               ::music::midi::event * pevent = nullptr;

               int iLeft = iBufferNominalMax - lpmh->dwBytesRecorded;

               estatus = m_psequence->m_pfile->WorkGetNextEvent(pevent, tkMax, true, &iLeft);

               if (estatus == ::error_would_reach_buffer_limit)
               {

                  break;

               }
               else if (estatus == ::success_end_of_file)
               {

                  break;

               }
               else if (!estatus)
               {

                  return estatus;

               }

               ASSERT(m_psequence->m_pfile->GetPosition() >= tkLastPosition);

               musical_tick tkPosition = m_psequence->m_pfile->GetPosition();

               if (m_psequence->m_eeffect == e_effect_fade_in || m_psequence->m_eeffect == e_effect_fade_out)
               {

                  musical_tick tkDiv = m_psequence->GetQuarterNote();

                  while ((m_psequence->tick_to_time(tkLastPosition + tkDiv) - m_psequence->tick_to_time(tkLastPosition)) > 100_ms)
                  {

                     tkDiv /= 2;

                  }

                  while (true)
                  {

                     musical_tick tkOp = ((m_tkLastOp + tkDiv) / tkDiv) * tkDiv;

                     if (tkOp > tkPosition)
                     {

                        break;

                     }

                     if (tkOp < tkLastPosition)
                     {

                        tkOp = tkPosition;

                     }

                     tkDelta = tkOp - tkLastPosition;

                     LPDWORD lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);

                     int iBytesRecorded = 0;

                     if (m_psequence->m_eeffect == e_effect_fade_in || m_psequence->m_eeffect == e_effect_fade_out)
                     {

                        double dVolume = m_psequence->get_fade_volume(m_psequence->tick_to_time(tkOp));

                        for (int iTrack = 0; iTrack < 16; iTrack++)
                        {

                           clip(0, 127, m_psequence->m_iaRefVolume[iTrack]);

                           byte bVolume = (byte)(m_psequence->m_iaRefVolume[iTrack] * maximum(0.0, minimum(1.0, dVolume)));

                           if (abs((int)m_keyframe.rbControl[iTrack][e_control_change_volume] - (int)bVolume) < 3)
                           {

                              TRACE("too few difference!! opt-ed out");

                           }
                           else
                           {

                              DWORD dwFullType = control_change;
                              dwFullType |= iTrack & 0xf;
                              DWORD dwChB1 = e_control_change_volume;
                              DWORD dwChB2 = bVolume;

                              *lpdw++ = (DWORD)tkDelta;
                              *lpdw++ = 0;
                              *lpdw++ = (((DWORD)MEVT_SHORTMSG) << 24) |
                                 (dwFullType) |
                                 (dwChB1 << 8) |
                                 (dwChB2 << 16);


                              tkLastPosition += tkDelta;

                              tkDelta = 0;

                              lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

                              iBytesRecorded += 3 * sizeof(DWORD);

                           }

                        }

                     }
                     else
                     {

                        for (int iTrack = 0; iTrack < 16; iTrack++)
                        {

                           if (m_keyframe.rbControl[iTrack][e_control_change_volume] == KF_EMPTY)
                           {

                              m_keyframe.rbControl[iTrack][e_control_change_volume] = 100;

                           }

                           clip(0, 127, m_keyframe.rbControl[iTrack][e_control_change_volume]);

                           int iVolume = m_keyframe.rbControl[iTrack][e_control_change_volume];

                           m_psequence->m_iaRefVolume.set_at_grow(iTrack, iVolume);

                        }

                        *lpdw++ = (DWORD)tkDelta;
                        *lpdw++ = 0;
                        *lpdw++ = (MEVT_NOP << 24);

                        tkLastPosition += tkDelta;

                        tkDelta = 0;

                        lpmh->dwBytesRecorded += 3 * sizeof(DWORD);

                        iBytesRecorded += 3 * sizeof(DWORD);


                     }

                     m_tkLastOp = tkOp;

                  }

               }

               tkDelta = tkPosition - tkLastPosition;

               iLeft = lpmh->dwBufferLength - lpmh->dwBytesRecorded;

               estatus = StreamEvent(tkDelta, pevent, lpmh, tkMax, minimum(iBufferNominalMax, iLeft));

               if (estatus == ::error_would_reach_buffer_limit)
               {

                  break;

               }

               tkLastPosition = tkPosition;

            }

            return (m_psequence->m_pfile->m_flags & EndOfFile) ? success_end_of_file : ::success;

         }


         //void sequencer::_001OnMidiOutDone(::message::message* pmessage)
         //{

         //   OnDone((HMIDISTRM)pmessage->m_wparam.m_number, (LPMIDIHDR) pmessage->m_lparam.m_lparam);

         //}


         //void sequencer::_001OnMidiOutPositionCB(::message::message* pmessage)
         //{

         //   OnPositionCB((LPMIDIHDR)pmessage->m_lparam.m_lparam);


         //}



      } // namespace mmsystem


   } // namespace midi


} // namespace music



