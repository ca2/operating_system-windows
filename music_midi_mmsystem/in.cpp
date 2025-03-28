#include "framework.h"
#include "in.h"
#include "midi.h"
#include "multimedia_mmsystem/translation.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme_windows/mmresult.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         in::in()
         {

            m_hmidiin = nullptr;

         }


         in::~in()
         {

            close();

         }


         void in::open(int iDeviceId)
         {

            synchronous_lock synchronouslock(m_pmidi->get_midi_mutex());

            //MMRESULT estatus;

            unsigned int uDeviceID = iDeviceId;

            m_hmidiin = nullptr;

            MMRESULT mmresult = midiInOpen(&m_hmidiin,
                  uDeviceID,
                  (DWORD_PTR) &in::MidiInProc,
                  (DWORD_PTR) this,
                  CALLBACK_FUNCTION
                  );

            auto estatus = mmresult_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

            //return ::success;

         }


         void in::start()
         {

            if (m_hmidiin != nullptr)
            {

               midiInStart(m_hmidiin);

            }

            //return ::success;

         }



         void in::stop()
         {

            if (m_hmidiin != nullptr)
            {

               midiInStop(m_hmidiin);

            }

            //return ::success;

         }


         void in::close()
         {

            if(m_hmidiin != nullptr)
            {

               midiInClose(m_hmidiin);

            }

            //return ::success;

         }


         void CALLBACK in::MidiInProc(
            HMIDIIN   hMidiIn,
            UINT      wMsg,
            DWORD_PTR dwInstance,
            DWORD_PTR dwParam1,
            DWORD_PTR dwParam2
         )
         {

            in* pin = (in*)dwInstance;

            pin->midi_in_proc(hMidiIn, wMsg, dwParam1, dwParam2);

         }

         void in::on_os_message(unsigned char b, unsigned char b1, unsigned char b2)
         {

            //fork([this, b, b1, b2]()
               //{

                  ::music::midi::in::on_os_message(b, b1, b2);


               //});

         }



         void in::midi_in_proc(
            HMIDIIN   hMidiIn,
            UINT      wMsg,
            DWORD_PTR dwParam1,
            DWORD_PTR dwParam2
         )
         {


            if (wMsg == MIM_DATA)
            {

               BYTE b = (unsigned char)dwParam1;
               BYTE b1 = (unsigned char)(dwParam1 >> 8);
               BYTE b2 = (unsigned char)(dwParam1 >> 16);

               on_os_message(b, b1, b2);

            }

         }


         void in::send_short_message(::music::midi::enum_midi_message emessage, int iChannel, int iData1, int iData2)
         {

//            return mmresult_status(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)), "out::send_short_message");
            //return mmresult_status(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)));

            //return ::error_failed;

         }


      } //


   } // namespace midi_mmsystem


} // namespace music




