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


            ::pointer<sequence>     m_psequence;


            sequence_thread(::music::midi::sequence * psequence);
            virtual ~sequence_thread();


            void install_message_routing(::channel * pchannel);

            //::music::midi::sequence * get_sequence();
            void Stop(::duration msEllapse);

            void PostNotifyEvent(::music::midi::e_notify_event eevent);

            void PrerollRateAndWait(double rate = 0.0);
            void PrerollAndWait(::duration tkStart);
            void PlayRate(double dRate = 0.0);
            void Play(::duration tkStart);
            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange();

            void ExecuteCommand(::music::midi::player_command * pcommand);
            void _ExecuteCommand(::music::midi::player_command * pcommand);


            virtual bool init_thread() override;
            virtual void term_thread() override;


            DECLARE_MESSAGE_HANDLER(OnMidiSequenceEvent);
            DECLARE_MESSAGE_HANDLER(OnDone);
            DECLARE_MESSAGE_HANDLER(OnPositionCB);


         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music





