// from win32.cpp by camilo on 2022-08-27 21:14 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "window_util.h"
#include "top_level_enum.h"


namespace windowing_win32
{


   top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
      m_bVisible(bVisible)
   {

      m_phwnda = __new(::windows::hwnd_array);

      if (bDesktop)
      {

         ::EnumDesktopWindows(nullptr, &top_level_enum::EnumWindowsProc, (lparam)this);

      }
      else
      {

         ::EnumWindows(&top_level_enum::EnumWindowsProc, (lparam)this);

      }

   }


   top_level_enum::~top_level_enum()
   {


   }


   BOOL CALLBACK top_level_enum::EnumWindowsProc(HWND hwnd, LPARAM lParam)
   {

      top_level_enum * ptoplevelenum = (top_level_enum *)lParam;

      if (ptoplevelenum->m_bVisible && !IsWindowVisible(hwnd))
      {

         return true;

      }

      ptoplevelenum->m_phwnda->add(hwnd);

      return true;

   }


} // namespace windowing_win32



