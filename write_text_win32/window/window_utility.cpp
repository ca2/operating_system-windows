// created by Camilo 2021-01-31 04:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "window.h"




//__STATIC bool CLASS_DECL_WINDOWING_WIN32 __modify_style(HWND hwnd, i32 nStyleOffset,
//   u32 dwRemove, u32 dwAdd, ::u32 nFlags)
//{
//   ASSERT(oswindow != nullptr);
//   u32 uStyle = ::GetWindowLong(oswindow, nStyleOffset);
//   u32 dwNewStyle = (uStyle & ~dwRemove) | dwAdd;
//   if (uStyle == dwNewStyle)
//      return false;
//
//   ::SetWindowLong(oswindow, nStyleOffset, dwNewStyle);
//   if (nFlags != 0)
//   {
//      ::SetWindowPos(oswindow, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
//   }
//   return true;
//}
