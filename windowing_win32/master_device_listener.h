// Created by camilo on 2022-02-20 12:05 <3ThomasBorregaardS�rensen!! (Thomas Likes number 5)!
#pragma once


#include "aura/hardware/device_listener.h"
#include "acme/operating_system.h"

#include <dbt.h>


namespace windowing_win32
{

   
   class devices;


   class CLASS_DECL_WINDOWING_WIN32 master_device_listener :
      virtual public ::hardware::device_listener
   {
   public:



      HDEVNOTIFY                 m_hdevnotify;

      ::pointer<devices>        m_pdevices;

      ::hardware::enum_device    m_edevice;

      GUID                       m_guid;


      master_device_listener();

      ~master_device_listener() override;



      void on_message_device_change(::message::message* pmessage);



      virtual void on_device_change(wparam wparam, lparam lparam);

      virtual void on_device_arrival(DEV_BROADCAST_HDR* phdr);

      virtual void on_device_remove_complete(DEV_BROADCAST_HDR* phdr);

      void on_device_plugged(::hardware::enum_device edevice) override;

      void on_device_unplugged(::hardware::enum_device edevice) override;


   };



} //namespace windowing_win32


