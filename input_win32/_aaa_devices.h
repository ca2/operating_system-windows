// Created by camilo on 2022-02-20 12:21 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/hardware/devices.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 devices :
      virtual public ::hardware::devices
   {
   public:


      HWND                                                                       m_hwnd;
      map < ::hardware::enum_device, ::pointer<master_device_listener >>        m_mapmasterdevicelistener;


      devices();
      ~devices() override;

      virtual void on_initialize_object();

      void on_message_device_change(::message::message * pmessage);

      void register_device_listener(::hardware::device_listener* pdevicelistener, ::hardware::enum_device edevice) override;

      void _register_device_listener(master_device_listener * pdevicelistener, GUID InterfaceClassGuid);


   };


} // namespace windowing_win32



