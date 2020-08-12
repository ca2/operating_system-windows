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


            
            player(::object * pobject);
            virtual ~player();


            virtual void install_message_routing(::channel * psender) override;


            virtual bool PlayRate(double dRate = 0.0, u32 dwEllapse = (u32) -1) override;
            virtual bool Play(imedia_position tkStart, u32 dwEllapse = (u32)-1) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;
            virtual void pre_translate_message(::message::message * pmessage) override;
            virtual void OnMmsgDone(::music::midi::sequence *pSeq) override;
            //virtual void SaveFile(const char * lpszPathName) override;
            virtual void SetPosition(double dRate) override;
            virtual void pause() override;
            virtual void close_file() override;
            virtual bool ExecuteCommand(::music::midi::enum_command ecommand, u32 dwEllapse) override;
            virtual void OnMidiOutDeviceChange() override;

            //virtual var get_midi_out_device() override;
            virtual void PostNotifyEvent(::music::midi::e_notify_event eevent) override;

            virtual imedia_position RateToTicks(double dRate) override;

            virtual ::estatus     SetTempoShift(double dTempoShift) override;

            //virtual bool set_midi_out_device(var varDevice) override;

            virtual ::estatus     set_client(::music::midi::player_client * pclient) override;

            virtual bool IsPlaying() override;

            virtual void PostGMReset() override;
            virtual void PostTempoChange() override;
            virtual void SendTempoChange() override;


            //DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone);
            //DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB);
            DECL_GEN_SIGNAL(OnUserMessage);

            DECL_GEN_SIGNAL(on_attribute_change);


         };


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music



