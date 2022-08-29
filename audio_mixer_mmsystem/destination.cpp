#include "framework.h"
#include "destination.h"
#include "device.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      destination::destination()
      {

         m_pdestination = this;

      }


      destination::~destination()
      {

      }


      void destination::initialize_source_info()
      {

         __pointer(::multimedia::audio_mixer_mmsystem::source)     lpSource;

         i32 iConnections = (i32) m_mixerline.cConnections;

         m_mixersourcea.set_size_create(this, iConnections);

         for (i32 i = 0; i < iConnections; i++)
         {

            lpSource = m_mixersourcea[i];

            lpSource->SetDestination(this);

            lpSource->get_line_info(i, this);

         }

         //return ::success;

      }


      void     destination::initialize_all_controls()
      {

         GetLineControls();

         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->GetLineControls();

         }

         //return ::success;

      }


      void destination::update_all_controls()
      {

         ::multimedia::audio_mixer::source::update_all_controls();

         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->update_all_controls();

         }

      }


      u32 destination::get_component_type()
      {

         return m_mixerline.dwComponentType;

      }


      ::multimedia::audio_mixer::device * destination::get_device()
      {

         return m_pmixerdevice;

      }


      void destination::set_device(::multimedia::audio_mixer::device * pdevice)
      {

         m_pmixerdevice = pdevice;

      }


      ::multimedia::audio_mixer::source_array & destination::get_source_info()
      {

         return m_mixersourcea;

      }


      u32 destination::get_mixer_line_id()
      {

         return m_mixerline.dwLineID;

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia







