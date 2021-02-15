#include "framework.h"

#include "multimedia_mmsystem/translation.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {

         ::mutex & get_midi_mutex();

         out::out()
         {

            m_hmidiout = nullptr;

         }


         out::~out()
         {

            close();

         }


         ::e_status     out::open(int iDeviceId)
         {

            synchronization_lock synchronizationlock(&get_midi_mutex());

            MMRESULT estatus;

            u32 uDeviceID = iDeviceId;

            m_hmidiout = nullptr;

            estatus = midiOutOpen(&m_hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);

            if(estatus != MMSYSERR_NOERROR)
               return error_failed;


            return ::success;

         }

         ::e_status     out::close()
         {

            if(m_hmidiout != nullptr)
            {

               midiOutClose(m_hmidiout);

            }

            return ::success;

         }


         ::e_status     out::send_short_message(::music::midi::e_message emessage, int iChannel, int iData1, int iData2)
         {

//            return ::multimedia::mmsystem::translate(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)), "out::send_short_message");
            return ::multimedia::mmsystem::translate(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)));

         }


      } //


   } // namespace midi_mmsystem


} // namespace music




