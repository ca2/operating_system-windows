#include "framework.h"
///#include "acme/operating_system.h"




//#include "atom.h"
//#include "acme/node/windows/_windows.h"


namespace user
{


   string _os_get_user_theme()
   {

      return "";

   }


//   void _os_process_user_theme(string strTheme)
//   {
//
//      __UNREFERENCED_PARAMETER(strTheme);
//
//   }



   void os_calc_dark_mode()
   {


   }


} // namespace user


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd)
//{
//
//   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
//
//}


//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle()
//{
//
//   const ::int_point pointZero = { 0,0 };
//
//   return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);
//
//}


//CLASS_DECL_ACME bool GetPrimaryMonitorRect(::int_rectangle * lprect)
//{
//
//   MONITORINFO mi;
//
//   zero(mi);
//
//   mi.cbSize = sizeof(MONITORINFO);
//
//   if (GetMonitorInfo(GetPrimaryMonitorHandle(), &mi))
//   {
//
//      *lprect = mi.rcMonitor;
//
//   }
//   else
//   {
//
//      if (!::GetWindowRect(::get_desktop_window(), lprect))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//






