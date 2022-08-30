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
            u32            m_uDeviceID;


            out();
            ~out() override;


            void open() override;
            void close() override;

            void send_short_message(::music::midi::enum_message emessage, int iChannel, int iData1, int iData2);
            void send_long_message(const block& block);

            virtual void sysex(const block& block);

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




