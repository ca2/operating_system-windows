#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


typedef ::u32 FN_GetDpiForWindow(HWND hwnd);


float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;


::u32 legacy_get_dpi_for_system()
{

   HDC hdc = ::GetDC(nullptr);

   ::u32 dpiX = 72;

   ::u32 dpiY = 72;

   if (hdc)
   {

      dpiX = static_cast<::u32>(::GetDeviceCaps(hdc, LOGPIXELSX));

      dpiY = static_cast<::u32>(::GetDeviceCaps(hdc, LOGPIXELSY));

      ::ReleaseDC(nullptr, hdc);

   }

   return maximum(dpiX, dpiY);

}


void dpi_os_initialize()
{

   ::u32 uDpi = legacy_get_dpi_for_system();

   g_DPIScaleX = uDpi / 72.0f;

   g_DPIScaleY = uDpi / 72.0f;

}


::u32 get_dpi_for_window(oswindow oswindow)
{

   static auto pfn_get_dpi_for_window = ::windows::function < FN_GetDpiForWindow * >::get_address("User32.dll", "GetDPiForWindow");

   if (pfn_get_dpi_for_window)
   {

      return pfn_get_dpi_for_window(__hwnd(oswindow));

   }

   return legacy_get_dpi_for_system();

}


//CLASS_DECL_AURA float point_dpi(oswindow hwnd, float points)
//{
//
//   float fDpi = (float)get_dpi_for_window(hwnd);
//
//   return points * fDpi / 72.f;
//
//}
//
//
//CLASS_DECL_AURA float dpiy(oswindow hwnd, float y)
//{
//
//   float fDpi = (float)get_dpi_for_window(hwnd);
//
//   return y * fDpi / 96.f;
//
//}
//
//
//CLASS_DECL_AURA float dpix(HWND hwnd, float x)
//{
//
//   float fDpi = (float)get_dpi_for_window(hwnd);
//
//   return x * fDpi / 96.f;
//
//}
//
//
//
//CLASS_DECL_WINDOWING_WIN32 float os_get_dpi()
//{
//
//   return 96.0f;
//
//}



