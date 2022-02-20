// Created by camilo on 2022-02-20 12:05 <3ThomasBorregaardSørensen!! (Thomas Likes number 5)!
#pragma once


namespace windows
{


   class CLASS_DECL_WINDOWING_WIN32 device_listener :
      virtual public ::matter
   {
   public:

   
      HDEVNOTIFY     m_hdevnotify;

      device_listener();

      ~device_listener() override;


      virtual void register_device_listener(GUID guid);


      virtual void on_device_change(wparam wparam, lparam lparam);

      virtual void on_device_arrival(DEV_BROADCAST_HDR * phdr);

      virtual void on_device_remove_complete(DEV_BROADCAST_HDR * phdr);

      virtual void on_video_input_plugged();

      virtual void on_video_input_unplugged();


   };

   
   using device_listener_array = __pointer_array(device_listener);


} //namespace windows


