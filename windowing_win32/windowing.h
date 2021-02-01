// Created by camilo on 2021-01-30 <3ThomasBS_!!
#pragma once


namespace windowing_win32
{


   class windowing :
      virtual public ::windowing::windowing
   {

#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      raw_array < MONITORINFO >                          m_monitorinfoa;
      raw_array < HMONITOR >                             m_hmonitora;
      raw_array < MONITORINFO >                          m_monitorinfoaDesk;

#else

      //rect_array                                         m_rectaMonitor;
      //rect_array                                         m_rectaWork;

      rect_array                                            m_rectaMonitor;
      rect_array                                            m_rectaWkspace;
#endif

      windowing();
      virtual ~windowing();


      __pointer(::windowing::monitor) get_main_monitor();


      virtual __pointer(::message::base) get_message_base(MESSAGE * pmsg);

      
      virtual __pointer(::windowing::window) _wrap(HWND hwnd);


      virtual __pointer(::windowing::window) get_desktop_window();


   };


} // namespace windowing_win32



