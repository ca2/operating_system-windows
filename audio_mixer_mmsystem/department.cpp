#include "framework.h"
#include "department.h"

//
//namespace multimedia
//{


namespace audio_mixer_mmsystem
{


   department::department()
   {

   }


   department::~department()
   {

   }


   bool department::initialize1()
   {

      return true;

   }


   void department::destroy()
   {

      destroy_window();


      //return true;

      //return ::success;

   }



   /*void     department::CreateNewDevice(u32 uiMixerID)
   {
   void     mmrc;
   if(MMSYSERR_NOERROR != (mmrc = m_pmixer->set_new_device(
   uiMixerID,
   (u32) m_oswindow_,
   0,
   CALLBACK_WINDOW)))
   {
   output_error_message("Could not open audio_mixer device!");
   PostMessage(MESSAGE_CLOSE);
   return mmrc;
   }
   m_pmixer->m_pdevice->initialize_capabilities();
   return mmrc;
   }

   void     department::CreateNewDestination(u32 dwComponentType)
   {
   void     mmrc;
   ::audio_mixer::destination * pdestination = nullptr;

   if(MMSYSERR_NOERROR != (mmrc =  m_pmixer->m_pdevice->get_destination(
   dwComponentType,
   &pdestination)))
   {
   output_error_message("Could not open default audio_mixer destination!");
   PostMessage(MESSAGE_CLOSE);
   return mmrc;
   }

   m_destinationpa.add(pdestination);

   pdestination->initialize_source_info();

   pdestination->initialize_all_controls();

   m_pmixer->m_pdevice->map_lines();
   m_pmixer->m_pdevice->map_controls();

   pdestination->update_all_controls();

   return mmrc;
   }*/


   bool department::initialize()
   {
      //   m_pmixerthread = (::audio_mixer::thread *) __begin_thread(__type(::audio_mixer::thread));
      //   if(m_pmixerthread == nullptr)
      //      return false;
      //   return true
      return true;
   }


} // namespace audio_mixer_mmsystem

//
//} // namespace multimedia
//
//
//
//
