//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/constant/message.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"
#include "acme_windows/registry.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>

namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         windowing::windowing()
         {

            m_bKeepRunningPostedProcedures = true;
         }


         windowing::~windowing()
         {


         }


         // ::e_status windowing::defer_initialize_windowing()
         // {
         //
         //    //      if (m_estatusInitializeX11 == error_not_initialized)
         //    //      {
         //    //
         //    //         m_estatusInitializeX11 = initialize_windowing_system();
         //    //
         //    //      }
         //    //
         //    //      return m_estatusInitializeX11;
         //
         //    return ::success;
         //
         // }


         void windowing::initialize_windowing()
         {

            informationf("windowing_system_win32::windowing::initialize_windowing_system");

            informationf("windowing_system_win32::windowing::initialize_windowing_system going to call init_threads");

            if (!system()->acme_windowing()->init_threads())
            {

               throw ::exception(::error_failed, "Failed to init threads for initializing windowing");

            }

            // gdk_x11 does error handling?!?!?!
            //XSetErrorHandler(_c_XErrorHandler);

            //g_pmutexX11 = ___new ::pointer < ::mutex >();

            //return ::success;

         }

         //void windowing::show(::particle_pointer pparticle)
         //{


         //}

         ::acme::windowing::display * windowing::acme_display()
         {

            return ::acme::windowing::windowing::acme_display();

         }


         void windowing::_main_send(const ::procedure & procedure)
         {

            if (::is_main_thread())
            {

               procedure();

               return;

            }

            //__matter_send_procedure(this, this, &node::node_post, procedure);

      //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
      //      {

            auto pevent = __allocate manual_reset_event();

            _user_post([procedure, pevent]
                      {

                         procedure();

                         pevent->SetEvent();

                      });


            auto timeout = procedure.timeout();

            if (!pevent->wait(timeout))
            {

               throw ::exception(error_timeout);
               //pevent.release();

               //return false;

            }

            ///return true;
      //
      //      }


         }


         void windowing::_main_post(const ::procedure & procedure)
         {

            //system()->_post(procedure);

            _post(procedure);

         }


         void windowing::display_error_trap_push(int i)
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


         void windowing::display_error_trap_pop_ignored(int i)
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
         //        system()->acme_windowing()->x11_sync(procedure);
         //
         //    }
         //
         //
         //    void node::async(const ::procedure & procedure)
         //    {
         //
         //        system()->acme_windowing()->x11_async(procedure);
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

         bool windowing::dark_mode()
         {

            auto pthis = (windowing *)this;

            auto bDarkMode = pthis->_win32_registry_windows_darkness();

            return bDarkMode;


         }


         bool windowing::_win32_registry_windows_dark_mode_for_app()
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


         bool windowing::_win32_registry_windows_dark_mode_for_system()
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


         bool windowing::_win32_registry_windows_darkness()
         {

            return _win32_registry_windows_dark_mode_for_app()
               || _win32_registry_windows_dark_mode_for_system();

         }



         void windowing::fetch_system_background_color()
         {

            //DWORD dwBackgroundWindowColor = ::GetSysColor(COLOR_WINDOW);

            //auto colorWindowBackground = argb(255, GetRValue(dwBackgroundWindowColor), GetGValue(dwBackgroundWindowColor), GetBValue(dwBackgroundWindowColor));

            auto colorWindowBackground = reinterpreted_background_color();

            string str;

            str.formatf("\n\n\nWindow Background Color rgb(%d,%d,%d)\n\n", colorWindowBackground.m_uchRed, colorWindowBackground.m_uchGreen, colorWindowBackground.m_uchBlue);

            ::output_debug_string(str);

            system()->background_color(colorWindowBackground);


         }


         void windowing::set_dark_mode(bool bDarkMode)
         {

            _set_system_dark_mode1(bDarkMode);

            _set_app_dark_mode1(bDarkMode);

            DWORD_PTR res;
            SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("ImmersiveColorSet"), 0, 1000, &res);

            //return ::success;

         }


         void windowing::_set_system_dark_mode1(bool bSet)
         {

            ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

            unsigned int dwSystemUseLightTheme;
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


         void windowing::_set_app_dark_mode1(bool bSet)
         {

            ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

            unsigned int dwAppsUseLightTheme;
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



         void windowing::on_start_system()
         {

            auto * psystem = this->system();

            psystem->defer_post_initial_request();

         }


         void windowing::set_finish()
         {

            //if (m_itask)
            //{

            //   ::PostThreadMessage((DWORD)m_itask, e_message_quit, 0, 0);

            //}

            ::acme::windowing::windowing::set_finish();

         }


         void windowing::kick_idle()
         {

            ::PostThreadMessage((DWORD)m_itask, e_message_kick_idle, 0, 0);

         }


         void windowing::windowing_post_quit()
         {

            ::procedure procedure;

            procedure = [this]()
               {

                  ::PostQuitMessage(0);

               };

            main_post(procedure);

         }


         bool windowing::handle_messages()
         {

            ASSERT(is_current_task());

            MSG msg;

            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {

               if (msg.message == WM_QUIT)
               {

                  set_finish();

                  return false;

               }
               else if (msg.message == e_message_kick_idle)
               {

                  return true;

               }

               //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
               {

                  TranslateMessage(&msg);

                  DispatchMessage(&msg);

               }

            }

            return true;

         }


         void windowing::windowing_application_main_loop()
         {

            //set_current_handles();

            //::set_main_thread();

            //system()->defer_post_initial_request();

            //run();

            system()->defer_post_initial_request();

            main();

            //while (true)
            //{

            //   if (!_process_windowing_messages())
            //   {

            //      break;

            //   }

            //}

            if (::system()->m_pmanualreseteventMainLoopEnd)
            {

               ::system()->m_pmanualreseteventMainLoopEnd->set_event();

            }

         }


         //void windowing::_do_tasks()
         //{

         //   _process_windowing_messages();

         //}


      } // namespace windowing


   } // namespace acme


} // namespace windowing_system_win32



