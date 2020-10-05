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


            KEYFRAME                   m_keyframe;
            __pointer(midi)                   m_pmidi;

            i32                        m_iBufferSize;

            i32                        m_iBufferNominalMax;

            buffer_array               m_buffera;

            HMIDISTRM                  m_hstream;

            midi_callback_data         m_midicallbackdata;

            i32                        m_iBuffersInMMSYSTEM;

            imedia_time                m_tkLastOp;


            sequencer( sequence * psequence, const string & strDevice);
            virtual ~sequencer();



            virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
            {

               return ::object::add_ref(OBJ_REF_DBG_ARGS);

            }

            virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
            {

               return ::object::dec_ref(OBJ_REF_DBG_ARGS);

            }


            virtual void install_message_routing(::channel* pchannel) override;


            virtual void play(player_command * pcommand) override;
            virtual void stop(player_command* pcommand) override;
            virtual void pause(player_command* pcommand) override;
            virtual void restart(player_command* pcommand) override;

            virtual i32 GetDefaultCodePage();

            virtual ::estatus     fill_buffer(LPMIDIHDR lpmidihdr);


            ::estatus     close_stream();
            ::estatus     close_device();

            void OnPositionCB(LPMIDIHDR lpmidihdr);
            void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
            ::estatus     preroll_operation(LPMIDIHDR lpmidihdr);

            virtual bool IsOpened();

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true);
            virtual bool IsChangingTempo();

            virtual void OnEvent(::music::midi::sequence::event* pevent);


            ::estatus     close_file();

            virtual void on_set_position() override;

            virtual imedia_time get_position_ticks();
            virtual void karaoke_get_time(imedia_time& time);

            virtual ::estatus     get_ticks(imedia_time& time);
            virtual ::estatus     get_millis(imedia_time& time);
            virtual imedia_time get_millis() override;


            bool IsPlaying();

            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = TRUE);

            imedia_time GetQuarterNote();



            virtual ::estatus     SendGMReset();

            virtual ::estatus     start_mmsystem_sequencer();

            virtual void music_midi_on_playback_end();


            ::estatus     WorkStreamRender(LPMIDIHDR lpmh, imedia_time tkMax, i32 iBufferNominalMax);

            ::estatus     WorkSeek(imedia_time tkPosition, LPMIDIHDR lpmh);

            ::estatus     StreamEvent(imedia_time tkDelta, ::music::midi::event* Event, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::estatus     StreamEventF1(imedia_time tkDelta, array < ::music::midi::event*, ::music::midi::event* >& eventptra, LPMIDIHDR lpmh, imedia_time tkMax, u32 cbPrerollNomimalMax);

            ::estatus     InsertParmData(imedia_time tkDelta, LPMIDIHDR lpmh);

            ::estatus     InsertPadEvent(imedia_time tkDelta, LPMIDIHDR lpmh);

            DECL_GEN_SIGNAL(_001OnMidiOutDone);
            DECL_GEN_SIGNAL(_001OnMidiOutPositionCB);


         };


      }// namespace mmsystem


   } // namespace midi


} // namespace music





