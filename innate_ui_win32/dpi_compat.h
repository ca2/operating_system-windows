#pragma once
#include <windows.h>

inline UINT ca2_window_dpi(HWND window)
{
#if defined(__REACTOS__)
   HDC dc = GetDC(window);
   if (!dc)
      return 96;
   int dpi = GetDeviceCaps(dc, LOGPIXELSY);
   ReleaseDC(window, dc);
   return dpi > 0 ? static_cast<UINT>(dpi) : 96;
#else
   return GetDpiForWindow(window);
#endif
}
