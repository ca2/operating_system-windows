#include "framework.h"
#include "buffer.h"
#include "sequencer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         void buffer::Initialize(i32 iSize, buffer_array* pbuffera)
         {

            m_pbuffera = pbuffera;

            m_storage.set_size(iSize);

            Reset();

            m_bPrepared = false;

         }


         void buffer_array::Initialize(i32 iCount, i32 iSize, midi_callback_data* pcallbackdata)
         {

            m_pcallbackdata = pcallbackdata;

            m_buffera.set_size(iCount);

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               this->buffer_at(i) = __create_new<buffer>();

               this->buffer_at(i)->Initialize(iSize, this);

            }

         }


         void buffer_array::Reset()
         {

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               this->buffer_at(i)->Reset();

            }

         }

         void buffer::Reset()
         {

            zero(m_midihdr);

            m_midihdr.lpData = (char*)m_storage.data();
            m_midihdr.dwBufferLength = (u32)m_storage.size();
            m_midihdr.dwUser = (DWORD_PTR)this;

            zero(m_midihdr.lpData, m_midihdr.dwBufferLength);

         }

         buffer::buffer()
         {

            m_pbuffera = nullptr;

         }


         buffer::~buffer()
         {


         }


         buffer_array::buffer_array()
         {

            m_pcallbackdata = nullptr;

         }


         buffer_array::~buffer_array()
         {

         }


         bool buffer::IsPrepared()
         {
            return m_bPrepared;
         }


         ::e_status buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {

            if (hmidiout == nullptr)
            {

               return error_bad_argument;

            }

            if (m_bPrepared)
            {

               return error_wrong_state;

            }

            MMRESULT mmresult = ::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               return estatus;

            }

            m_bPrepared = true;

            return estatus;

         }


         midi_callback_data* buffer::get_midi_callback_data()
         {

            if (m_pbuffera == nullptr)
               return nullptr;

            return m_pbuffera->m_pcallbackdata;

         }


         buffer* buffer::get(LPMIDIHDR lpmidihdr)
         {

            return (buffer*)(void*)lpmidihdr->dwUser;

         }


         sequence* buffer::get_sequence(LPMIDIHDR lpmidihdr)
         {

            return get(lpmidihdr)->get_midi_callback_data()->m_psequence;

         }


         ::e_status buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {

            if (hmidiout == nullptr)
            {

               return error_invalid_empty_argument;

            }

            if (!m_bPrepared)
            {
               
               return error_wrong_state;

            }

            MMRESULT mmresult = ::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               return estatus;

            }

            m_bPrepared = false;

            return estatus;

         }


         ::e_status buffer_array::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               auto estatus = this->buffer_at(i)->midiOutUnprepareHeader(hmidiout);

               if (!estatus)
               {

                  return estatus;

               }

            }

            return ::success;

         }


         ::e_status buffer_array::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               auto estatus = this->buffer_at(i)->midiOutPrepareHeader(hmidiout);

               if (!estatus)
               {

                  return estatus;

               }

            }

            return ::success;

         }


         ::e_status buffer::midiStreamOut(HMIDISTRM hmidiout)
         {

            ASSERT(hmidiout != nullptr);

            if (m_midihdr.dwBytesRecorded == 0)
            {

               return ::success_none;

            }

            MMRESULT mmresult = ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));

            auto estatus = mmresult_to_status(mmresult);

            if (!estatus)
            {

               return estatus;

            }

            return estatus;

         }


         ::e_status buffer_array::midiStreamOut(HMIDISTRM hmidiout)
         {

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               synchronous_lock synchronouslock(m_pcallbackdata->m_psequence->synchronization());

               auto estatus = this->buffer_at(i)->midiStreamOut(hmidiout);

               if (!estatus)
               {

                  return estatus;

               }

               m_psequencer->m_iBuffersInMMSYSTEM++;

            }

            return ::success;

         }


      } // namespace mmsystem


   } // namespace midi


} // namespace music









