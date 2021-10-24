#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((u32)(WORD)((BYTE)VERSION_MINOR | (((WORD)(BYTE)VERSION_MAJOR) << 8)))

#define MMSG_DONE                   (WM_USER+20)


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class file;
         class sequence;
         class sequence_thread;





         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM sequence :
            virtual public ::music::midi::sequence
         {
         public:


            __pointer(midi)                   m_pmidi;
            __pointer(file)                   m_pfile;
            __pointer(sequence_thread)        m_psequencethread;

            u32                        m_cbPreroll;         

            u32                        m_cbPrerollNominalMax;

            buffer_array               m_buffera;

            HMIDISTRM                  m_hstream;

            midi_callback_data         m_midicallbackdata;

            i32                        m_iBuffersInMMSYSTEM;



            sequence(midi * pmidi, const ::string & strDevice);
            virtual ~sequence();

            virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
            {

               return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            }

            virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
            {

               return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            }



            void MuteAll(bool bMute = true, i32 iExcludeTrack = -1);
            void MuteTrack(i32 iIndex, bool bMute = true);


            virtual i32 GetDefaultCodePage();

            void Prepare(::ikaraoke::data & data);
            void Prepare(i32 iTrack, ::ikaraoke::data & data);
            void Prepare(
            string2a & str2a,
            imedia_position_2darray & tka2DTokensTicks,
            i32 iMelodyTrack,
            int2a & ia2TokenLine,
            ::ikaraoke::data & data);

            void SetLevelMeter(i32 iLevel);
            ::e_status     CloseStream();
            ::e_status     close_device();
            //bool SetMidiOutDevice(u32 uiDevice);
            i32 SetKeyShift(i32 iKeyShift);
            i32 GetKeyShift();

            void on_midi_playback_end(::music::midi::sequence::event * pevent);
            virtual ::e_status     SetTempoShift(double dTempoShift);

            void OnPositionCB(LPMIDIHDR lpmidihdr);
            void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
            virtual void GetTimeLength(::duration & time);
            virtual void GetPositionLength(::duration & position);

            using ::ikaraoke::karaoke::TimeToPosition;
            using ::ikaraoke::karaoke::PositionToTime;

            virtual ::duration TimeToPosition(::duration time);
            virtual ::duration PositionToTime(::duration position);

            virtual bool IsOpened();

            virtual bool IsNull();
            virtual void SetTempoChangeFlag(bool bSet = true);
            virtual bool IsChangingTempo();

            virtual double GetTempoShift();
            //virtual void GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd);
            //virtual bool is_in_operation();
            //virtual bool WasInSpecialModeV001();

            virtual void OnEvent(::music::midi::sequence::event * pevent);


            ::e_status     close_file() override;

            ::e_status     Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
            ::e_status     Start();

            ::e_status     Pause();

            ::e_status     Restart();

            ::e_status     Stop();

            virtual ::duration get_position_ticks() override;
            virtual void karaoke_get_time(::duration  & time) override;

            virtual ::e_status     get_ticks(::duration & time) override;
            virtual ::e_status     get_millis(::duration & time) override;


            bool IsPlaying();

            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = true);

            ::duration GetQuarterNote();



            using ::music::midi::sequence::create_new_event;
            virtual ::music::midi::sequence::event * create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr);

            virtual ::e_status     SendGMReset();

            virtual ::e_status     mm_start();

            virtual void music_midi_on_playback_end();


         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music







