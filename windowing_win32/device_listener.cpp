// Created by camilo on 2022-02-20 12:08 <3ThomasBorregaardSørensen!! (Thomas Likes number 5)! I like also this Infinity up!!
#include "framework.h"
#include "_windows.h"


namespace windows
{

   extern devices * g_pdevices;


   device_listener::device_listener()
   {

      m_hdevnotify = nullptr;

   }


   device_listener::~device_listener()
   {

      if (m_hdevnotify != nullptr)
      {

         UnregisterDeviceNotification(m_hdevnotify);

         m_hdevnotify = nullptr;

      }


   }


   void device_listener::register_device_listener(GUID guid)
   {

      auto psession = m_psystem->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = (::windowing_win32::windowing *)puser->windowing()->m_pWindowing;

      auto psysteminteraction = pwindowing->m_psysteminteraction;

      initialize_windows_devices(psysteminteraction);

      ::windows::g_pdevices->register_device_listener(this, guid);

   }


   void device_listener::on_device_change(wparam wparam, lparam lparam)
   {

      //
      // This is the actual message from the interface via Windows messaging.
      // This code includes some additional decoding for this particular device type
      // and some common validation checks.
      //
      // Note that not all devices utilize these optional parameters in the same
      // way. Refer to the extended information for your particular device type 
      // specified by your GUID.
      //
      //PDEV_BROADCAST_DEVICEINTERFACE b = (PDEV_BROADCAST_DEVICEINTERFACE)lparam.m_lparam;
      //TCHAR strBuff[256];


      if (wparam.m_number == DBT_DEVICEARRIVAL)
      {

         DEV_BROADCAST_HDR * phdr = (DEV_BROADCAST_HDR * ) lparam.m_lparam;

         on_device_arrival(phdr);

      }
      else if (wparam.m_number == DBT_DEVICEREMOVECOMPLETE)
      {

         DEV_BROADCAST_HDR * phdr = (DEV_BROADCAST_HDR *)lparam.m_lparam;

         on_device_remove_complete(phdr);

      }

   //// Output some messages to the window.
   //switch (wparam.m_wparam)
   //{
   //case DBT_DEVICEARRIVAL:

   //   //msgCount++;
   //   //StringCchPrintf(
   //      //strBuff, 256,
   //     // TEXT("Message %d: DBT_DEVICEARRIVAL\n"), (int)msgCount);
   //   break;
   //case DBT_DEVICEREMOVECOMPLETE:
   //   //msgCount++;
   //   //StringCchPrintf(
   //   //   strBuff, 256,
   //   //   TEXT("Message %d: DBT_DEVICEREMOVECOMPLETE\n"), (int)msgCount);
   //   break;
   //case DBT_DEVNODES_CHANGED:
   //   //msgCount++;
   //   //StringCchPrintf(
   //   //   strBuff, 256,
   //   //   TEXT("Message %d: DBT_DEVNODES_CHANGED\n"), (int)msgCount);
   //   break;
   //default:
   //   //msgCount++;
   //   //StringCchPrintf(
   //   //   strBuff, 256,
   //   //   TEXT("Message %d: WM_DEVICECHANGE message received, value %d unhandled.\n"),
   //   //   (int)msgCount, wParam);
   //   break;
   }
   //OutputMessage(hEditWnd, wParam, (LPARAM)strBuff);

   void device_listener::on_device_arrival(DEV_BROADCAST_HDR * phdr)
   {
      
      if (phdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
      {
      
         DEV_BROADCAST_DEVICEINTERFACE * pdeviceinterface = (DEV_BROADCAST_DEVICEINTERFACE *) phdr;

         string str(pdeviceinterface->dbcc_name);

         if (str.begins_ci("\\\\?\\USB#VID"))
         {

            on_video_input_plugged();

         }

      }

   }

   void device_listener::on_device_remove_complete(DEV_BROADCAST_HDR * phdr)
   {

      if (phdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
      {

         DEV_BROADCAST_DEVICEINTERFACE * pdeviceinterface = (DEV_BROADCAST_DEVICEINTERFACE *)phdr;

         string str(pdeviceinterface->dbcc_name);

         if (str.begins_ci("\\\\?\\USB#VID"))
         {

            on_video_input_unplugged();

         }

      }

   }

   void device_listener::on_video_input_plugged()
   {

   }

   void device_listener::on_video_input_unplugged()
   {

   }

} // namespace windows