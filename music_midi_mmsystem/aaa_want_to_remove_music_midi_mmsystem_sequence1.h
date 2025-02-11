#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((unsigned int)(WORD)((BYTE)VERSION_MINOR | (((WORD)(BYTE)VERSION_MAJOR) << 8)))

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


            ::pointer<midi>                  m_pmidi;
            ::pointer<file>                  m_pfile;
            ::pointer<sequence_thread>       m_psequencethread;

            unsigned int                        m_cbPreroll;         

            unsigned int                        m_cbPrerollNominalMax;

            buffer_array               m_buffera;

            HMIDISTRM                  m_hstream;

            midi_callback_data         m_midicallbackdata;

            int                        m_iBuffersInMMSYSTEM;



            sequence(midi * pmidi, const ::string & strDevice);
            virtual ~sequence();

            virtual long long increment_reference_count()
            {

               return ::object::increment_reference_count();

            }

            virtual long long decrement_reference_count()
            {

               return ::object::decrement_reference_count();

            }



            void MuteAll(bool bMute = true, int iExcludeTrack = -1);
            void MuteTrack(int iIndex, bool bMute = true);


            virtual int GetDefaultCodePage();

            void Prepare(::ikaraoke::data & data);
            void Prepare(int iTrack, ::ikaraoke::data & data);
            void Prepare(
            string_array_array & straa,
            imedia_position_2darray & tickaaTokensTicks,
            int iMelodyTrack,
            int2a & ia2TokenLine,
            ::ikaraoke::data & data);

            void SetLevelMeter(int iLevel);
            void     CloseStream();
            void     close_device();
            //bool SetMidiOutDevice(unsigned int uiDevice);
            int SetKeyShift(int iKeyShift);
            int GetKeyShift();

            void on_midi_playback_end(::music::midi::sequence::happening * phappening);
            virtual void     SetTempoShift(double dTempoShift);

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

            virtual void OnHappening(::music::midi::sequence::happening * phappening);


            void     close_file() override;

            void     Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
            void     Start();

            void     Pause();

            void     Restart();

            void     Stop();

            virtual ::duration get_position_ticks() override;
            virtual void karaoke_get_time(::duration  & time) override;

            virtual void     get_ticks(::duration & time) override;
            virtual void     get_millis(::duration & time) override;


            bool IsPlaying();

            bool IsSettingPosition();
            void SetSettingPositionFlag(bool bSet = true);

            ::duration GetQuarterNote();



            using ::music::midi::sequence::create_new_event;
            virtual ::music::midi::sequence::happening * create_new_event(::music::midi::sequence::e_happening ehappening, LPMIDIHDR lpmidihdr);

            virtual void     SendGMReset();

            virtual void     mm_start();

            virtual void music_midi_on_playback_end();


         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music







