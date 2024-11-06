#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class sequence_thread;



         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM player :
            virtual public ::music::midi::player
         {
         public:


            
            player(::particle * pparticle);
            virtual ~player();


            virtual void install_message_routing(::channel * psender) override;


            virtual bool PlayRate(double dRate = 0.0, unsigned int dwEllapse = (unsigned int) -1) override;
            virtual bool Play(::duration tickStart, unsigned int dwEllapse = (unsigned int)-1) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;
            virtual void pre_translate_message(::message::message * pmessage) override;
            virtual void OnMmsgDone(::music::midi::sequence *pSeq) override;
            //virtual void SaveFile(const ::string & lpszPathName) override;
            virtual void SetPosition(double dRate) override;
            virtual void pause() override;
            virtual void close_file() override;
            virtual bool ExecuteCommand(::music::midi::enum_command ecommand, unsigned int dwEllapse) override;
            virtual void OnMidiOutDeviceChange() override;

            //virtual var get_midi_out_device() override;
            virtual void PostNotifyEvent(::music::midi::e_notify_event eevent) override;

            virtual ::duration RateToTicks(double dRate) override;

            virtual void     SetTempoShift(double dTempoShift) override;

            //virtual bool set_midi_out_device(var varDevice) override;

            virtual void     set_client(::music::midi::player_client * pclient) override;

            virtual bool IsPlaying() override;

            virtual void PostGMReset() override;
            virtual void PostTempoChange() override;
            virtual void SendTempoChange() override;


            //DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessageDone);
            //DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessagePositionCB);
            DECLARE_MESSAGE_HANDLER(OnUserMessage);

            DECLARE_MESSAGE_HANDLER(on_attribute_change);


         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music



