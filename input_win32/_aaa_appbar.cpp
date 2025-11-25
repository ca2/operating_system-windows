// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-02-01 23:31
#include "framework.h"
//#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/_win32_gdi.h"


#ifdef WINDOWS_DESKTOP
#include <dwmapi.h>
#include <VersionHelpers.h>
#include <VersionHelpers.h>
#include <shellapi.h>
#ifndef WM_NCUAHDRAWCAPTION
#define WM_NCUAHDRAWCAPTION (0x00AE)
#endif
#ifndef WM_NCUAHDRAWFRAME
#define WM_NCUAHDRAWFRAME (0x00AF)
#endif


CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure();


CLASS_DECL_WINDOWING_WIN32 wstring windows_register_window_class(::particle * pparticle, unsigned int nClassStyle, HICON hCursor, HBRUSH hbrBackground, HICON hIcon);


bool has_autohide_appbar(unsigned int edge, const int_rectangle & mon)
{

   if (IsWindows8Point1OrGreater())
   {

      APPBARDATA data = {};

      data.cbSize = sizeof(APPBARDATA);

      data.uEdge = edge;

      data.rc.left = mon.left;
      data.rc.top = mon.top;
      data.rc.right = mon.right;
      data.rc.bottom = mon.bottom;

      return SHAppBarMessage(0x0000000b, &data);

   }


   /* Before Windows 8.1, it was not possible to specify a monitor when
    checking for hidden appbars, so check only on the primary monitor */
   if (mon.left != 0 || mon.top != 0)
      return false;
   APPBARDATA data = {};
   data.cbSize = sizeof(APPBARDATA);
   data.uEdge = edge;
   return SHAppBarMessage(ABM_GETAUTOHIDEBAR, &data);
}
#endif

