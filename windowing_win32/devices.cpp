// Created by camilo on 2022-02-20 12:22 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_windows.h"
#include <initguid.h>
#include <ks.h>
#include <ksmedia.h>
#include <ntddvdeo.h>


namespace windowing_win32
{


   GUID get_device_guid(::hardware::enum_device edevice)
   {

      switch (edevice)
      {
      case ::hardware::e_device_video_input:
         return KSCATEGORY_CAPTURE;
      case ::hardware::e_device_monitor:
         return GUID_DEVINTERFACE_MONITOR;


      }
      return {};
   }


   devices::devices()
   {

   }


   devices::~devices()
   {

   }

   void devices::on_initialize_object()
   {

      auto psession = m_psystem->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = (::windowing_win32::windowing*)puser->m_pwindowing->m_pWindowing;

      auto psysteminteraction = pwindowing->m_psysteminteraction;

      m_hwnd = (HWND) psysteminteraction->get_oswindow();

   }


   void devices::register_device_listener(::hardware::device_listener* pdevicelistener, ::hardware::enum_device edevice)
   {

      auto& pmasterdevicelistener = m_mapmasterdevicelistener[edevice];

      if (!pmasterdevicelistener)
      {

         __construct_new(pmasterdevicelistener);

         pmasterdevicelistener->m_edevice = edevice;

         pmasterdevicelistener->m_pdevices = this;

         _register_device_listener(pmasterdevicelistener, get_device_guid(edevice));

      }

      ::hardware::devices::register_device_listener(pdevicelistener, edevice);

   }

   void devices::_register_device_listener(master_device_listener * plistener, GUID guid)
      // Parameters:
      //     guid - The interface class GUID for the device interfaces. 
      // Note:
      //     RegisterDeviceNotification also allows a service handle be used,
      //     so a similar wrapper function to this one supporting that scenario
      //     could be made from this template.
   {

      if (plistener->m_hdevnotify != nullptr)
      {

         throw exception(error_wrong_state);

      }

      DEV_BROADCAST_DEVICEINTERFACE NotificationFilter{};

      NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);

      NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

      NotificationFilter.dbcc_classguid = guid;

      auto hdevnotify = RegisterDeviceNotification(
         m_hwnd,                     // events recipient
         &NotificationFilter,        // type of device
         DEVICE_NOTIFY_WINDOW_HANDLE // type of recipient handle
      );

      if (NULL == hdevnotify)
      {
         
         auto lastError = ::GetLastError();
         
         ERROR("RegisterDeviceNotification");
         
         throw exception(last_error_to_status(lastError));

      }


      plistener->m_guid = guid;

      plistener->m_hdevnotify = hdevnotify;

      auto psession = m_psystem->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = (::windowing_win32::windowing*)puser->m_pwindowing->m_pWindowing;

      auto psysteminteraction = pwindowing->m_psysteminteraction;
      
      psysteminteraction->add_message_handler(e_message_device_change, { plistener, &master_device_listener::on_message_device_change });


   }




   //void devices::on_message_device_change(::message::message * pmessage)
   //{

   //   ASSERT(pmessage->m_atom == e_message_device_change);

   //   wparam wparam = pmessage->m_wparam;

   //   lparam lparam = pmessage->m_lparam;

   //   for (auto & pdevicelistener : m_devicelistenera)
   //   {

   //      pdevicelistener->on_device_change(wparam, lparam);

   //   }

   //}

   
   devices * g_pdevices = nullptr;


} // namespace windows
//
//
//void initialize_windows_devices(::windowing_win32::system_interaction * psysteminteraction)
//{
//
//   if (::is_set(::windows::g_pdevices))
//   {
//
//      return;
//
//   }
//
//   ::windows::g_pdevices = new ::windows::devices((HWND) psysteminteraction->m_oswindow);
//
//   ::windows::g_pdevices->initialize(psysteminteraction);
//
//   psysteminteraction->add_message_handler(e_message_device_change, { ::windows::g_pdevices, &::windows::devices::on_message_device_change } );
//   
//}


//void finalize_windows_devices()
//{
//
//   if (::is_null(::windows::g_pdevices))
//   {
//
//      return;
//
//   }
//
//   ::acme::del(::windows::g_pdevices);
//
//}



