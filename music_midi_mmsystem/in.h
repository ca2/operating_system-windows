#pragma once


#include "app-veriwell/multimedia/music/midi/in.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM in :
            virtual public ::music::midi::in
         {
         public:


            
            HMIDIIN        m_hmidiin;

            ::pointer < midi > m_pmidi;


            in();
            ~in() override;


            virtual void     open(int iDeviceId) override;
            virtual void     start() override;
            virtual void     stop() override;
            virtual void     close() override;

            virtual void on_os_message(unsigned char b, unsigned char b1, unsigned char b2) override;

            void     send_short_message(::music::midi::enum_midi_message emessage, int iChannel, int iData1, int iData2);

            static void CALLBACK MidiInProc(
               HMIDIIN   hMidiIn,
               UINT      wMsg,
               DWORD_PTR dwInstance,
               DWORD_PTR dwParam1,
               DWORD_PTR dwParam2
            );

            void midi_in_proc(
               HMIDIIN   hMidiIn,
               UINT      wMsg,
               DWORD_PTR dwParam1,
               DWORD_PTR dwParam2
            );


         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




