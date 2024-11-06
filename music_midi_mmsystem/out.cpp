#include "framework.h"
#include "out.h"
#include "midi.h"
#include "multimedia_mmsystem/translation.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/prototype/memory.h"
#include "acme_windows/mmresult.h"
#include "app-veriwell/multimedia/music/midi/midi.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {

         out::out()
         {

            m_hmidiout = nullptr;

         }


         out::~out()
         {

            close();

         }


         void out::open(bool bForSequencing)
         {

            synchronous_lock synchronouslock(((midi*)m_pmidi->m_pMidi)->get_midi_mutex());

            MMRESULT estatus;

            m_hmidiout = nullptr;

            auto iDeviceId = ((midi*)m_pmidi->m_pMidi)->get_os_out_device_id(m_strDeviceId);

            if (iDeviceId < 0)
            {

               throw ::exception(error_not_found);

            }

            UINT uDeviceID = (UINT) iDeviceId;

            estatus = midiOutOpen(&m_hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);

            if (estatus != MMSYSERR_NOERROR)
            {

               throw ::exception(error_failed);

            }

            //return ::success;

         }

         void     out::close()
         {

            if(m_hmidiout != nullptr)
            {

               midiOutClose(m_hmidiout);

            }

            //return ::success;

         }


         void     out::send_short_message(::music::midi::enum_midi_message emessage, int iChannel, int iData1, int iData2)
         {

//            return mmresult_status(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)), "out::send_short_message");
            MMRESULT mmresult = midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2));

            auto estatus = mmresult_status(mmresult);

            if (!estatus)
            {

               throw ::exception(estatus);

            }

         }


         void out::send_long_message(const block& block)
         {

            MIDIHDR midihdr;

            zero(midihdr);

            memory m;

            DWORD dwRounded = (block.size() + 3) & ~3;

            m.set_size(3 * sizeof(unsigned int) + dwRounded);

            midihdr.lpData = (LPSTR) m.data();

            midihdr.dwBufferLength = (DWORD) m.size();

            //midihdr.lpData = (LPSTR) block.get_data();

            //midihdr.dwBufferLength = block.get_size();

            auto lpdw = (LPDWORD)m.data();

            m.zero();

            *lpdw++ = 0;
            *lpdw++ = 0;
            *lpdw++ = ((MEVT_LONGMSG << 24) & 0xff000000) | (block.size() & 0xffffff);
            memory_copy(lpdw, block.data(), block.size());

            auto e = midiOutPrepareHeader(
               m_hmidiout,
               &midihdr,
               sizeof(midihdr)
            );

            if (e == MMSYSERR_NOERROR)
            {

               auto e2 = midiOutLongMsg(m_hmidiout, &midihdr, sizeof(midihdr));

               auto e3 = midiOutUnprepareHeader(
                  m_hmidiout,
                  &midihdr,
                  sizeof(midihdr)
               );

            }

            //return mmresult_status(e);

         }

         void out::sysex(const block& block)
         {

            send_long_message(block);

         }


      } //


   } // namespace midi_mmsystem


} // namespace music




