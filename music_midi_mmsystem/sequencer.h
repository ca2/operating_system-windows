#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "buffer.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {
         

         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM sequencer :
            virtual public ::music::midi::sequencer
         {
         public:


            bool                       m_bHadNoteOn;

            KEYFRAME                   m_keyframe;
            ::pointer<midi>           m_pmidi;

            int                        m_iBufferSize;
            
            
            manual_reset_happening         m_happeningLongMessage;
            HMIDIOUT                   m_hmidiout;


            int                        m_iBufferNominalMax;

            ::pointer<buffer_array>   m_pbuffera;

            HMIDISTRM                  m_hstream;

            midi_callback_data         m_midicallbackdata;

            int                        m_iBuffersInMMSYSTEM;

            musical_tick               m_tkLastOp;
            bool                       m_bSendXGModeOn;
            bool                       m_bSendXGReset;
            bool                       m_bSendMasterVolumeReset;
            bool                       m_bSendXGDrumSetup1Reset;
            bool                       m_bSendXGDrumSetup2Reset;
            ::e_status                 m_estatusMidiOut;


            sequencer( sequence * psequence, const ::scoped_string & scopedstrDevice);
            ~sequencer() override;



            virtual long long increment_reference_count()
            {

               return ::object::increment_reference_count();

            }

            virtual long long decrement_reference_count()
            {

               return ::object::decrement_reference_count();

            }


            virtual void install_message_routing(::channel* pchannel) override;


            virtual void play(player_command * pcommand) override;
            virtual void stop(player_command* pcommand) override;
            virtual void pause(player_command* pcommand) override;
            virtual void restart(player_command* pcommand) override;

            virtual int GetDefaultCodePage();

            virtual ::e_status fill_buffer(LPMIDIHDR lpmidihdr);


            void     close_stream();
            void     close_device();

            void OnPositionCB(LPMIDIHDR lpmidihdr);
            void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
            ::e_status preroll_operation(LPMIDIHDR lpmidihdr);

            virtual bool IsOpened();

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true);
            virtual bool IsChangingTempo();

            virtual void OnHappening(::music::midi::sequence::happening* phappening);


            void     close_file();

            virtual void on_set_position() override;

            
            //virtual void karaoke_get_time(class ::time& time);

            
            virtual ::e_status      get_position(musical_tick & tick);
            virtual musical_tick    get_position();


            virtual ::e_status get_time_position(class ::time & time);
            virtual class ::time      get_time_position() override;


            bool IsPlaying();

            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = true);

            musical_tick GetQuarterNote();


            virtual void midi_out_open();
            virtual void midi_out_long_message(const block & block, const class ::time & millisWait = 0_ms);

            virtual void midi_out_xg_mode_on();
            virtual void midi_out_xg_mode_reset();
            virtual void midi_out_xg_drum_setup1_reset();
            virtual void midi_out_xg_drum_setup2_reset();
            virtual void midi_out_master_volume_reset();

            virtual void midi_out_close();


            virtual void     SendGMReset();

            virtual void     start_mmsystem_sequencer();

            virtual void music_midi_on_playback_end();


            ::e_status WorkStreamRender(LPMIDIHDR lpmh, musical_tick tickMax, int iBufferNominalMax);

            ::e_status WorkSeek(musical_tick tickPosition, LPMIDIHDR lpmh);

            ::e_status StreamEvent(musical_tick tickDelta, ::music::midi::happening* Event, LPMIDIHDR lpmh, musical_tick tickMax, unsigned int cbPrerollNomimalMax);

            ::e_status StreamEventF1(musical_tick tickDelta, array < ::music::midi::happening*, ::music::midi::happening* >& eventptra, LPMIDIHDR lpmh, musical_tick tickMax, unsigned int cbPrerollNomimalMax);

            ::e_status InsertParmData(musical_tick tickDelta, LPMIDIHDR lpmh);

            ::e_status InsertPadEvent(musical_tick tickDelta, LPMIDIHDR lpmh);

            //DECLARE_MESSAGE_HANDLER(_001OnMidiOutDone);
            //DECLARE_MESSAGE_HANDLER(_001OnMidiOutPositionCB);


            static void CALLBACK MidiOutProc(
               HMIDIOUT hmo,
               UINT wMsg,
               DWORD_PTR dwInstance,
               DWORD_PTR dwParam1,
               DWORD_PTR dwParam2
            );

            void midi_out_proc(               HMIDIOUT hmo,
               UINT wMsg,
               DWORD_PTR dwParam1,
               DWORD_PTR dwParam2
            );


         };


      }// namespace mmsystem


   } // namespace midi


} // namespace music





