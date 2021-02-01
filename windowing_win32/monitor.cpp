// created by Camilo 2021-01-31 06:25 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "window.h"



namespace windowing_win32
{


   monitor::monitor(HMONITOR hmonitor) :
      m_hmonitor(hmonitor)
   {


   }


   monitor::~monitor()
   {

   }


   ::e_status monitor::update_cache()
   {

      MONITORINFO mi;

      __zero(mi);

      mi.cbSize = sizeof(MONITORINFO);

      if (!GetMonitorInfo(m_hmonitor, &mi))
      {

         return ::error_failed;

      }

      __copy(m_rectangle, mi.rcMonitor);

      __copy(m_rectangleWorkspace, mi.rcWorkspace);

      return true;

   }



} // namespace windowing_win32



