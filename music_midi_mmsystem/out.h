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


            virtual ::estatus     open(int iDeviceId) override;
            virtual ::estatus     close() override;

            ::estatus     send_short_message(::music::midi::e_message emessage, int iChannel, int iData1, int iData2);

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




