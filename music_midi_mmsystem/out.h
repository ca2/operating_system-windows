#pragma once


#include "app-veriwell/multimedia/music/midi/out.h"

namespace music
{


   namespace midi
   {


      namespace mmsystem
      {

         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM out :
            virtual public ::music::midi::out
         {
         public:


            
            HMIDIOUT       m_hmidiout;


            out();
            virtual ~out();


            virtual ::e_status     open(int iDeviceId) override;
            virtual ::e_status     close() override;

            ::e_status     send_short_message(::music::midi::e_message emessage, int iChannel, int iData1, int iData2);
            ::e_status     send_long_message(const block& block);

            virtual void sysex(const block& block);

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




