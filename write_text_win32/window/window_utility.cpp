// created by Camilo 2021-01-31 04:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "window.h"




//__STATIC bool CLASS_DECL_WINDOWING_WIN32 __modify_style(HWND hwnd, int nStyleOffset,
//   unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
//{
//   ASSERT(oswindow != nullptr);
//   unsigned int uStyle = ::GetWindowLong(oswindow, nStyleOffset);
//   unsigned int dwNewStyle = (uStyle & ~dwRemove) | dwAdd;
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
