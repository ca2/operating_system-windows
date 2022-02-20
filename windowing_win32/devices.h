// Created by camilo on 2022-02-20 12:21 <3ThomasBorregaardSørensen!!
#pragma once


namespace windows
{


   class CLASS_DECL_WINDOWING_WIN32 devices :
      virtual public ::object
   {
   public:


      HWND                             m_hwnd;
      device_listener_array            m_devicelistenera;


      devices(HWND hwnd);
      ~devices() override;


      void on_message_device_change(::message::message * pmessage);

      void register_device_listener(::windows::device_listener * pdevicelistener, GUID InterfaceClassGuid);


   };


} // namespace windows



