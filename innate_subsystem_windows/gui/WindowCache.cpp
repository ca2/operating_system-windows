//
// Created by camilo on 2026-04-08 18:45 <3ThomasBorregaardSørensen!!
//
#include "../framework.h"
#include "../WindowCache.h"
#include "Window.h"


namespace innate_subsystem_windows
{


   void WindowCache::initialize_window_cache(Window * pwindow)
   {

      m_hwnd = ::as_HWND(pwindow->operating_system_window());

   }



} //namespace innate_subsystem_windows


