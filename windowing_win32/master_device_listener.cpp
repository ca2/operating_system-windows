// Created by camilo on 2022-02-20 12:08 <3ThomasBorregaardSorensen!! (Thomas Likes number 5)! I like also this Infinity up!!
#include "framework.h"
#include "master_device_listener.h"
#include "devices.h"
#include "apex/message/message.h"


namespace windowing_win32
{


   master_device_listener::master_device_listener()
   {

      m_hdevnotify = nullptr;

   }


   master_device_listener::~master_device_listener()
   {

      if (m_hdevnotify != nullptr)
      {

         UnregisterDeviceNotification(m_hdevnotify);

         m_hdevnotify = nullptr;

      }


   }

   void master_device_listener::on_message_device_change(::message::message* pmessage)
   {

      on_device_change(pmessage->m_wparam, pmessage->m_lparam);

   }
   

   void master_device_listener::on_device_change(wparam wparam, lparam lparam)
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

   void master_device_listener::on_device_arrival(DEV_BROADCAST_HDR * phdr)
   {
      
      if (phdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
      {
      
         DEV_BROADCAST_DEVICEINTERFACE * pdeviceinterface = (DEV_BROADCAST_DEVICEINTERFACE *) phdr;

         auto guid = pdeviceinterface->dbcc_classguid;

         if (m_guid == guid)
         {

            //on_device_plugged(::hardware::e_device_video_input);

            on_device_plugged(m_edevice);

         }

      }

   }

   void master_device_listener::on_device_remove_complete(DEV_BROADCAST_HDR * phdr)
   {

      if (phdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
      {

         DEV_BROADCAST_DEVICEINTERFACE * pdeviceinterface = (DEV_BROADCAST_DEVICEINTERFACE *)phdr;

         string str(pdeviceinterface->dbcc_name);

         auto guid = pdeviceinterface->dbcc_classguid;

         if(guid == m_guid)
         {

            on_device_unplugged(m_edevice);

         }

      }

   }


   void master_device_listener::on_device_plugged(::hardware::enum_device edevice)
   {

      auto& pdevicelistenera = m_pdevices->m_mapdevicelistenera[m_edevice];

      if (pdevicelistenera)
      {

         for (auto& pdevice : *pdevicelistenera)
         {

            pdevice->on_device_plugged(edevice);

         }

      }

   }


   void master_device_listener::on_device_unplugged(::hardware::enum_device edevice)
   {

      auto& pdevicelistenera = m_pdevices->m_mapdevicelistenera[m_edevice];

      if (pdevicelistenera)
      {

         for (auto& pdevice : *pdevicelistenera)
         {

            pdevice->on_device_unplugged(edevice);

         }

      }

   }


} // namespace windowing_win32



