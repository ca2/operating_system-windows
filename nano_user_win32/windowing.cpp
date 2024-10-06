//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
// Merged from windowing_system_win32 to
//     nano_user_win32 by camilo on 2024-10-05 10:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"
#include "acme_windows/registry.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>

namespace nano_user_win32
{


   windowing_system::windowing_system()
   {


   }


   windowing_system::~windowing_system()
   {


   }


   ::e_status windowing_system::defer_initialize_windowing_system()
   {

//      if (m_estatusInitializeX11 == error_not_initialized)
//      {
//
//         m_estatusInitializeX11 = initialize_windowing_system();
//
//      }
//
//      return m_estatusInitializeX11;

         return ::success;

   }


   ::e_status windowing_system::initialize_windowing_system()
   {

      informationf("windowing_system_win32::windowing_system::initialize_windowing_system");

      informationf("windowing_system_win32::windowing_system::initialize_windowing_system going to call init_threads");

      if (!nano()->user()->init_threads())
      {

         return ::error_failed;

      }

      // gdk_x11 does error handling?!?!?!
      //XSetErrorHandler(_c_XErrorHandler);

      //g_pmutexX11 = new ::pointer < ::mutex >();

      return ::success;

   }



   void * windowing_system::get_display()
   {

      //return ::acme::node::x11_get_display();

      defer_initialize_windowing_system();

//      if(m_pvoidX11Display == NULL)
//      {
//
//         m_pvoidX11Display = fetch_windowing_system_display();
//
//      }
//
//      return m_pvoidX11Display;

      return nullptr;

   }


   void windowing_system::sync(const ::procedure & procedure)
   {

      if(::is_main_thread())
      {

         procedure();

         return;

      }

      //__matter_send_procedure(this, this, &node::node_post, procedure);

//      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
//      {

      auto pevent = ::place(new manual_reset_event());

      user_post([ procedure, pevent ]
                {

                   procedure();

                   pevent->SetEvent();

                });

      if(!pevent->wait(procedure.m_timeTimeout))
      {

         throw ::exception(error_timeout);
         //pevent.release();

         //return false;

      }

      ///return true;
//
//      }


   }


   void windowing_system::async(const ::procedure & procedure)
   {

      node()->user_post(procedure);

   }


   void windowing_system::display_error_trap_push(int i)
   {


      //node()->windowing_system_display_error_trap_push(i);

//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_push (gdkdisplay);
//
//      }

   }


   void windowing_system::display_error_trap_pop_ignored(int i)
   {

      //node()->windowing_system_display_error_trap_pop_ignored(i);
//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
//
//      }

   }


//
//    void node::sync(const ::procedure & procedure)
//    {
//
//        nano()->user()->x11_sync(procedure);
//
//    }
//
//
//    void node::async(const ::procedure & procedure)
//    {
//
//        nano()->user()->x11_async(procedure);
//
//    }
//
//
//    void node::display_error_trap_push(int i)
//    {
//
//
//    }
//
//
//    void node::display_error_trap_pop_ignored(int i)
//    {
//
//
//    }

   bool windowing_system::dark_mode()
   {

      auto pthis = (windowing_system *)this;

      auto bDarkMode = pthis->_win32_registry_windows_darkness();

      return bDarkMode;


   }


   bool windowing_system::_win32_registry_windows_dark_mode_for_app()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dwAppUseLightTheme = 0;

         key._get("AppsUseLightTheme", dwAppUseLightTheme);

         return dwAppUseLightTheme == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   bool windowing_system::_win32_registry_windows_dark_mode_for_system()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dwSystemUseLightTheme = 0;

         key._get("SystemUsesLightTheme", dwSystemUseLightTheme);

         return dwSystemUseLightTheme == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   bool windowing_system::_win32_registry_windows_darkness()
   {

      return _win32_registry_windows_dark_mode_for_app() 
         ||  _win32_registry_windows_dark_mode_for_system();

   }



   void windowing_system::fetch_system_background_color()
   {

      //DWORD dwBackgroundWindowColor = ::GetSysColor(COLOR_WINDOW);

      //auto colorWindowBackground = argb(255, GetRValue(dwBackgroundWindowColor), GetGValue(dwBackgroundWindowColor), GetBValue(dwBackgroundWindowColor));

      auto colorWindowBackground = reinterpreted_background_color();

      string str;

      str.formatf("\n\n\nWindow Background Color rgb(%d,%d,%d)\n\n", colorWindowBackground.m_u8Red, colorWindowBackground.m_u8Green, colorWindowBackground.m_u8Blue);

      ::output_debug_string(str);

      system()->background_color(colorWindowBackground);


   }


   void windowing_system::set_dark_mode(bool bDarkMode)
   {

      _set_system_dark_mode1(bDarkMode);

      _set_app_dark_mode1(bDarkMode);

      DWORD_PTR res;
      SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("ImmersiveColorSet"), 0, 1000, &res);

      //return ::success;

   }


   void windowing_system::_set_system_dark_mode1(bool bSet)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

      ::u32 dwSystemUseLightTheme;
      if (bSet)
      {
         dwSystemUseLightTheme = 0;
      }
      else
      {
         dwSystemUseLightTheme = 1;
      }

      key._set("SystemUsesLightTheme", dwSystemUseLightTheme);
      //         return ::success;

   }


   void windowing_system::_set_app_dark_mode1(bool bSet)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

      ::u32 dwAppsUseLightTheme;
      if (bSet)
      {
         dwAppsUseLightTheme = 0;
      }
      else
      {
         dwAppsUseLightTheme = 1;
      }

      key._set("AppsUseLightTheme", dwAppsUseLightTheme);

      //return ::success;

   }



   void windowing_system::on_start_system()
   {

      auto * psystem = this->system();

      psystem->defer_post_initial_request();

   }


   void windowing_system::windowing_system_post_quit()
   {

      main_post([this]()
         {

            ::PostQuitMessage(0);

});

   }



} // namespace nano_user_win32



