#include "framework.h"
#include "destination.h"
#include "device.h"

//
//namespace multimedia
//{


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

         ::pointer<::audio_mixer_mmsystem::source>    lpSource;

         int iConnections = (int) m_mixerline.cConnections;

         m_mixersourcea.set_size_create(this, iConnections);

         for (int i = 0; i < iConnections; i++)
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

         ::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(int i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->GetLineControls();

         }

         //return ::success;

      }


      void destination::update_all_controls()
      {

         ::audio_mixer::source::update_all_controls();

         ::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(int i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->update_all_controls();

         }

      }


      unsigned int destination::get_component_type()
      {

         return m_mixerline.dwComponentType;

      }


      ::audio_mixer::device * destination::get_device()
      {

         return m_pmixerdevice;

      }


      void destination::set_device(::audio_mixer::device * pdevice)
      {

         m_pmixerdevice = pdevice;

      }


      ::audio_mixer::source_array & destination::get_source_info()
      {

         return m_mixersourcea;

      }


      unsigned int destination::get_mixer_line_id()
      {

         return m_mixerline.dwLineID;

      }


   } // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
