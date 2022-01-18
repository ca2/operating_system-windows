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


         void out::open()
         {

            synchronous_lock synchronouslock(&get_midi_mutex());

            MMRESULT estatus;

            m_hmidiout = nullptr;

            auto iDeviceId = ((midi*)m_pmidi->m_pMidi)->get_os_out_device_id(m_strDeviceId);

            if (iDeviceId < 0)
            {

               throw_status(error_not_found);

            }

            UINT uDeviceID = (UINT) iDeviceId;

            estatus = midiOutOpen(&m_hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);

            if (estatus != MMSYSERR_NOERROR)
            {

               throw_status(error_failed);

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


         void     out::send_short_message(::music::midi::e_message emessage, int iChannel, int iData1, int iData2)
         {

//            return mmresult_to_status(midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2)), "out::send_short_message");
            MMRESULT mmresult = midiOutShortMsg(m_hmidiout, MIDIMSG(((int)emessage) >> 4, iChannel, iData1, iData2));

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               throw_status(estatus);

            }

         }


         void out::send_long_message(const block& block)
         {

            MIDIHDR midihdr;

            __zero(midihdr);

            memory m;

            DWORD dwRounded = (block.get_size() + 3) & ~3;

            m.set_size(3 * sizeof(u32) + dwRounded);

            midihdr.lpData = (LPSTR) m.get_data();

            midihdr.dwBufferLength = (DWORD) m.get_size();

            //midihdr.lpData = (LPSTR) block.get_data();

            //midihdr.dwBufferLength = block.get_size();

            auto lpdw = (LPDWORD)m.get_data();

            m.zero();

            *lpdw++ = 0;
            *lpdw++ = 0;
            *lpdw++ = ((MEVT_LONGMSG << 24) & 0xff000000) | (block.get_size() & 0xffffff);
            memcpy(lpdw, block.get_data(), block.get_size());

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

            //return mmresult_to_status(e);

         }

         void out::sysex(const block& block)
         {

            send_long_message(block);

         }


      } //


   } // namespace midi_mmsystem


} // namespace music




