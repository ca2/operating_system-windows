#pragma once



namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM sequence_thread :
            virtual public ::music::midi::sequence_thread
         {
         public:


            __pointer(sequence)      m_psequence;


            sequence_thread(::music::midi::sequence * psequence);
            virtual ~sequence_thread();


            void install_message_routing(::channel * pchannel);

            //::music::midi::sequence * get_sequence();
            void Stop(imedia_time msEllapse);

            void PostNotifyEvent(::music::midi::e_notify_event eevent);

            void PrerollRateAndWait(double rate = 0.0);
            void PrerollAndWait(imedia_time tkStart);
            void PlayRate(double dRate = 0.0);
            void Play(imedia_time tkStart);
            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange();

            void ExecuteCommand(::music::midi::player_command * pcommand);
            void _ExecuteCommand(::music::midi::player_command * pcommand);


            virtual bool init_thread() override;
            virtual void term_thread() override;


            DECL_GEN_SIGNAL(OnMidiSequenceEvent);
            DECL_GEN_SIGNAL(OnDone);
            DECL_GEN_SIGNAL(OnPositionCB);


         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





