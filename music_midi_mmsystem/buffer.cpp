#include "framework.h"


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

               this->buffer_at(i) = __new(buffer);

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

            __zero(m_midihdr);

            m_midihdr.lpData = (char*)m_storage.get_data();
            m_midihdr.dwBufferLength = (u32)m_storage.get_size();
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


         buffer_array::buffer_array(sequencer * psequencer) :
            m_psequencer(psequencer)
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


         ::e_status     buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {

            ::e_status     mmr = ::success;

            if (hmidiout == nullptr)
               return mmr;

            if (m_bPrepared)
               return mmr;

            mmr = m_pbuffera->translate_os_result(::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr)));

            if (mmr == ::success)
            {

               m_bPrepared = true;

            }
            else
            {

               throw "failed to prepare midi Out Header";

            }

            return mmr;

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


         ::e_status     buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {

            ::e_status     mmr = ::success;

            if (hmidiout == nullptr)
               return mmr;

            if (!m_bPrepared)
               return mmr;

            mmr = m_pbuffera->translate_os_result(::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr)));

            if (mmr == ::success)
            {

               m_bPrepared = false;


            }

            return mmr;

         }


         ::e_status     buffer_array::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {

            ::e_status     mmr = ::success;

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               ::e_status     mmrBuffer = this->buffer_at(i)->midiOutUnprepareHeader(hmidiout);

               if (mmrBuffer != ::success)
               {

                  mmr = mmrBuffer;

               }

            }

            return mmr;

         }


         ::e_status     buffer_array::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {

            ::e_status     estatus = ::success;

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               estatus = this->buffer_at(i)->midiOutPrepareHeader(hmidiout);

               if (estatus != ::success)
               {

                  for (; i >= 0; i--)
                  {

                     this->buffer_at(i)->midiOutUnprepareHeader(hmidiout);

                  }

                  return estatus;

               }

            }

            return estatus;

         }


         ::e_status     buffer::midiStreamOut(HMIDISTRM hmidiout)
         {

            ASSERT(hmidiout != nullptr);

            if (m_midihdr.dwBytesRecorded == 0)
            {

               return error_failed;

            }

            return m_pbuffera->translate_os_result(::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr)));

         }


         ::e_status     buffer_array::midiStreamOut(HMIDISTRM hmidiout)
         {

            ::e_status     estatus = ::success;

            for (i32 i = 0; i < this->buffer_count(); i++)
            {

               {

                  synchronous_lock synchronouslock(m_pcallbackdata->m_psequence->mutex());

                  estatus = this->buffer_at(i)->midiStreamOut(hmidiout);

                  if (estatus == ::success)
                  {

                     m_psequencer->m_iBuffersInMMSYSTEM++;

                  }
                  else
                  {

                     if (i <= 0)
                     {
                        return estatus;

                     }

                     return ::success;

                  }

               }

            }

            return estatus;

         }



      } // namespace mmsystem


   } // namespace midi


} // namespace music









