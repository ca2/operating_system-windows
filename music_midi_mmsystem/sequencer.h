#pragma once



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


            bool     m_bHadNoteOn;

            KEYFRAME                   m_keyframe;
            __pointer(midi)                   m_pmidi;

            i32                        m_iBufferSize;
            
            
            manual_reset_event         m_eventLongMessage;
            HMIDIOUT                   m_hmidiout;


            i32                        m_iBufferNominalMax;

            __pointer(buffer_array)    m_pbuffera;

            HMIDISTRM                  m_hstream;

            midi_callback_data         m_midicallbackdata;

            i32                        m_iBuffersInMMSYSTEM;

            musical_tick                m_tkLastOp;
            bool                       m_bSendXGModeOn;
            bool                       m_bSendXGReset;
            bool                       m_bSendMasterVolumeReset;
            bool                       m_bSendXGDrumSetup1Reset;
            bool                       m_bSendXGDrumSetup2Reset;


            sequencer( sequence * psequence, const ::string & strDevice);
            virtual ~sequencer();



            virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
            {

               return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            }

            virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
            {

               return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            }


            virtual void install_message_routing(::channel* pchannel) override;


            virtual void play(player_command * pcommand) override;
            virtual void stop(player_command* pcommand) override;
            virtual void pause(player_command* pcommand) override;
            virtual void restart(player_command* pcommand) override;

            virtual i32 GetDefaultCodePage();

            virtual ::e_status     fill_buffer(LPMIDIHDR lpmidihdr);


            ::e_status     close_stream();
            ::e_status     close_device();

            void OnPositionCB(LPMIDIHDR lpmidihdr);
            void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
            ::e_status     preroll_operation(LPMIDIHDR lpmidihdr);

            virtual bool IsOpened();

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true);
            virtual bool IsChangingTempo();

            virtual void OnEvent(::music::midi::sequence::event* pevent);


            ::e_status     close_file();

            virtual void on_set_position() override;

            virtual musical_tick get_position_ticks();
            virtual void karaoke_get_time(imedia_time& time);

            virtual ::e_status     get_ticks(musical_tick& time);
            virtual ::e_status     get_millis(imedia_time& time);
            virtual imedia_time get_millis() override;


            bool IsPlaying();

            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = true);

            musical_tick GetQuarterNote();


            virtual ::e_status midi_out_open();
            virtual ::e_status midi_out_long_message(const block & block, const ::millis & millisWait = 0_ms);

            virtual ::e_status midi_out_xg_mode_on();
            virtual ::e_status midi_out_xg_mode_reset();
            virtual ::e_status midi_out_xg_drum_setup1_reset();
            virtual ::e_status midi_out_xg_drum_setup2_reset();
            virtual ::e_status midi_out_master_volume_reset();

            virtual ::e_status midi_out_close();


            virtual ::e_status     SendGMReset();

            virtual ::e_status     start_mmsystem_sequencer();

            virtual void music_midi_on_playback_end();


            ::e_status     WorkStreamRender(LPMIDIHDR lpmh, musical_tick tkMax, i32 iBufferNominalMax);

            ::e_status     WorkSeek(musical_tick tkPosition, LPMIDIHDR lpmh);

            ::e_status     StreamEvent(musical_tick tkDelta, ::music::midi::event* Event, LPMIDIHDR lpmh, musical_tick tkMax, u32 cbPrerollNomimalMax);

            ::e_status     StreamEventF1(musical_tick tkDelta, array < ::music::midi::event*, ::music::midi::event* >& eventptra, LPMIDIHDR lpmh, musical_tick tkMax, u32 cbPrerollNomimalMax);

            ::e_status     InsertParmData(musical_tick tkDelta, LPMIDIHDR lpmh);

            ::e_status     InsertPadEvent(musical_tick tkDelta, LPMIDIHDR lpmh);

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





