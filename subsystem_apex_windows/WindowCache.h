//
// Created by camilo on 2026-04-08 18:41 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 WindowCache :
   virtual public ::particle
   {
   public:

      HWND m_hwnd;


      virtual void initialize_window_cache(Window * pwindow);

   };


} // namespace innate_subsystem_win32



