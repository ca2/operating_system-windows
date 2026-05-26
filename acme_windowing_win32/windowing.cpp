//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "activation_token.h"
#include "windowing.h"
#include "window.h"
#include "acme/constant/user_message.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
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

            m_bRunMainLoop = true;
            m_bMessageThread = true;

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

            debugf("::win32::acme::windowing::initialize_windowing");

#if defined(LINUX) || defined(__BSD__)

            informationf("::win32::acme::windowing::initialize_windowing going to call init_threads");

            if (!system()->acme_windowing()->init_threads())
            {

               throw ::exception(::error_failed, "Failed to init threads for initializing windowing");

            }

#endif

            //fetch_system_background_color();

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


         void windowing::main_send(const ::procedure & procedure)
         {

            if (::is_main_thread())
            {

               procedure();

               return;

            }

            //__matter_send_procedure(this, this, &node::node_post, procedure);

      //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
      //      {

            auto phappening = allocateø manual_reset_happening();

            user_postø()<<[procedure, phappening]
                      {

                         procedure();

                         phappening->set_happening();

                      };


            auto timeout = procedure.timeout();

            if (!phappening->wait(timeout))
            {

               throw ::exception(error_timeout);
               //phappening.release();

               //return false;

            }

            ///return true;
      //
      //      }


         }


         void windowing::user_send(const ::procedure & procedure)
         {

            main_send(procedure);

         }


         void windowing::user_post(const ::procedure & procedure)
         {

            main_post(procedure);

         }


         void windowing::main_post(const ::procedure & procedure)
         {

            //system()->_post(procedure);

            post(procedure);

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

         //
         // bool g_bNanoWindowClassRegistered = false;
         //
         //
         //
         // //CLASS_DECL_ACME_WINDOWING_WIN32 LRESULT CALLBACK acme_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#define DEFAULT_WINDOW_CLASS "default_window_class"


         windows::window_class windowing::_custom_window_class(const scoped_string &scopedstrClassName,
                                                               void *pHICON_Big, void *pHICON_Small)
         {

            auto & windowclass = m_mapWindowClass[scopedstrClassName];

            if (!windowclass.m_wstrClassName.has_character())
            {

               windowclass = _register_custom_window_class(scopedstrClassName, pHICON_Big, pHICON_Small);

            }

            return windowclass;

         }


         windows::window_class windowing::_register_custom_window_class(const scoped_string &scopedstrClassName,
                                                                        void *pHICON_Big, void *pHICON_Small)
         {


            windows::window_class windowclass;

            windowclass.m_wstrClassName = scopedstrClassName;

            windowclass.m_hinstance = ::windows::hinstance_from_function(::windows::window::s_window_procedure);

            WNDCLASSEXW wndclassex{};

            //Step 1: Registering the Window Class
            wndclassex.cbSize = sizeof(WNDCLASSEXW);
            wndclassex.style = CS_DBLCLKS;
            wndclassex.lpfnWndProc = &::windows::window::s_window_procedure;
            wndclassex.cbClsExtra = 0;
            wndclassex.cbWndExtra = 0;
            wndclassex.hInstance = (HINSTANCE) windowclass.m_hinstance;
            wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndclassex.lpszMenuName = NULL;
            wndclassex.lpszClassName = windowclass.m_wstrClassName;
            wndclassex.hIcon = (HICON) pHICON_Big;
            wndclassex.hIconSm = (HICON) pHICON_Small;

            if (!RegisterClassEx(&wndclassex))
            {

               windowclass.m_wstrClassName.clear();

               throw ::exception(error_failed, "Failed to register nano message box window class.");

            }

            return windowclass;

         }


         ::windows::window_class windowing::_default_window_class()
         {

            if (m_windowclassDefault.m_wstrClassName.is_empty())
            {

               _register_default_window_class();

            }

            return m_windowclassDefault;

         }

         void windowing::_register_default_window_class()
         {

            _register_default_window_class(::windows::window::s_window_procedure);

         //
         //    WNDCLASSEXW wndclassex{};
         //
         //    //Step 1: Registering the Window Class
         //    wndclassex.cbSize = sizeof(WNDCLASSEXW);
         //    wndclassex.style = CS_DBLCLKS;
         //    wndclassex.lpfnWndProc = &windows::window::s_window_procedure;
         //    wndclassex.cbClsExtra = 0;
         //    wndclassex.cbWndExtra = 0;
         //    wndclassex.hInstance = hinstanceWndProc;
         //    wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
         //    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
         //    wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
         //    wndclassex.lpszMenuName = NULL;
         //    wndclassex.lpszClassName = m_wstrNanoWindowClassName;
         //    wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
         //
         //    if (!RegisterClassEx(&wndclassex))
         //    {
         //
         //       m_wstrNanoWindowClassName.clear();
         //
         //       throw ::exception(error_failed, "Failed to register nano message box window class.");
         //
         //    }
         //
         //    //g_bNanoWindowClassRegistered = true;
         //
          }

         void windowing::_register_default_window_class(hinstance hinstance)
         {

            if (m_windowclassDefault.m_wstrClassName.has_character())
            {

               return;

            }

            m_windowclassDefault.m_wstrClassName = DEFAULT_WINDOW_CLASS;

            m_windowclassDefault.m_hinstance = hinstance;

            WNDCLASSEXW wndclassex{};

            //Step 1: Registering the Window Class
            wndclassex.cbSize = sizeof(WNDCLASSEXW);
            wndclassex.style = CS_DBLCLKS;
            wndclassex.lpfnWndProc = &::windows::window::s_window_procedure;
            wndclassex.cbClsExtra = 0;
            wndclassex.cbWndExtra = 0;
            wndclassex.hInstance = (HINSTANCE) m_windowclassDefault.m_hinstance;
            wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndclassex.lpszMenuName = NULL;
            wndclassex.lpszClassName = m_windowclassDefault.m_wstrClassName;
            wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

            if (!RegisterClassEx(&wndclassex))
            {

               m_windowclassDefault.m_wstrClassName.clear();

               throw ::exception(error_failed, "Failed to register nano message box window class.");

            }

            //g_bNanoWindowClassRegistered = true;

         }


#define ACME_NANO_WINDOW_CLASS "acme_nano_window_class"


         ::windows::window_class windowing::_acme_nano_window_class()
         {

            if (m_windowclassAcmeNano.m_wstrClassName.is_empty())
            {

               _register_acme_nano_window_class();

            }

            return m_windowclassAcmeNano;

         }

         void windowing::_register_acme_nano_window_class()
         {

            _register_acme_nano_window_class(::windows::window::s_window_procedure);

         //
         //    WNDCLASSEXW wndclassex{};
         //
         //    //Step 1: Registering the Window Class
         //    wndclassex.cbSize = sizeof(WNDCLASSEXW);
         //    wndclassex.style = CS_DBLCLKS;
         //    wndclassex.lpfnWndProc = &windows::window::s_window_procedure;
         //    wndclassex.cbClsExtra = 0;
         //    wndclassex.cbWndExtra = 0;
         //    wndclassex.hInstance = hinstanceWndProc;
         //    wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
         //    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
         //    wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
         //    wndclassex.lpszMenuName = NULL;
         //    wndclassex.lpszClassName = m_wstrNanoWindowClassName;
         //    wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
         //
         //    if (!RegisterClassEx(&wndclassex))
         //    {
         //
         //       m_wstrNanoWindowClassName.clear();
         //
         //       throw ::exception(error_failed, "Failed to register nano message box window class.");
         //
         //    }
         //
         //    //g_bNanoWindowClassRegistered = true;
         //
          }

         void windowing::_register_acme_nano_window_class(hinstance hinstance)
         {

            if (m_windowclassAcmeNano.m_wstrClassName.has_character())
            {

               return;

            }

            m_windowclassAcmeNano.m_wstrClassName = ACME_NANO_WINDOW_CLASS;

            m_windowclassAcmeNano.m_hinstance = hinstance;

            WNDCLASSEXW wndclassex{};

            //Step 1: Registering the Window Class
            wndclassex.cbSize = sizeof(WNDCLASSEXW);
            wndclassex.style = CS_DBLCLKS;
            wndclassex.lpfnWndProc = &::windows::window::s_window_procedure;
            wndclassex.cbClsExtra = 0;
            wndclassex.cbWndExtra = 0;
            wndclassex.hInstance = (HINSTANCE) m_windowclassAcmeNano.m_hinstance;
            wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndclassex.lpszMenuName = NULL;
            wndclassex.lpszClassName = m_windowclassAcmeNano.m_wstrClassName;
            wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

            if (!RegisterClassEx(&wndclassex))
            {

               m_windowclassAcmeNano.m_wstrClassName.clear();

               throw ::exception(error_failed, "Failed to register nano message box window class.");

            }

            //g_bNanoWindowClassRegistered = true;

         }


#define COM_HOST_WINDOW_CLASS "com_host_window_class"

         ::windows::window_class windowing::_com_host_window_class()
         {

            if (m_windowclassComHost.m_wstrClassName.is_empty())
            {

               _register_com_host_window_class();

            }

            return m_windowclassComHost;

         }

         void windowing::_register_com_host_window_class()
         {

            _register_com_host_window_class(::windows::window::s_window_procedure);

         //
         //    WNDCLASSEXW wndclassex{};
         //
         //    //Step 1: Registering the Window Class
         //    wndclassex.cbSize = sizeof(WNDCLASSEXW);
         //    wndclassex.style = CS_DBLCLKS;
         //    wndclassex.lpfnWndProc = &windows::window::s_window_procedure;
         //    wndclassex.cbClsExtra = 0;
         //    wndclassex.cbWndExtra = 0;
         //    wndclassex.hInstance = hinstanceWndProc;
         //    wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
         //    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
         //    wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
         //    wndclassex.lpszMenuName = NULL;
         //    wndclassex.lpszClassName = m_wstrNanoWindowClassName;
         //    wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
         //
         //    if (!RegisterClassEx(&wndclassex))
         //    {
         //
         //       m_wstrNanoWindowClassName.clear();
         //
         //       throw ::exception(error_failed, "Failed to register nano message box window class.");
         //
         //    }
         //
         //    //g_bNanoWindowClassRegistered = true;
         //
          }

         void windowing::_register_com_host_window_class(hinstance hinstance)
         {

            if (m_windowclassComHost.m_wstrClassName.has_character())
            {

               return;

            }

            m_windowclassComHost.m_wstrClassName = COM_HOST_WINDOW_CLASS;

            m_windowclassComHost.m_hinstance = hinstance;

            WNDCLASSEXW wndclassex{};

            //Step 1: Registering the Window Class
            wndclassex.cbSize = sizeof(WNDCLASSEXW);
            wndclassex.style = CS_DBLCLKS;
            wndclassex.lpfnWndProc = &::windows::window::s_window_procedure;
            wndclassex.cbClsExtra = 0;
            wndclassex.cbWndExtra = 0;
            wndclassex.hInstance = (HINSTANCE) m_windowclassComHost.m_hinstance;
            wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndclassex.lpszMenuName = NULL;
            wndclassex.lpszClassName = m_windowclassComHost.m_wstrClassName;
            wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

            if (!RegisterClassEx(&wndclassex))
            {

               m_windowclassComHost.m_wstrClassName.clear();

               throw ::exception(error_failed, "Failed to register nano message box window class.");

            }

            //g_bNanoWindowClassRegistered = true;

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

            system()->set_background_color(colorWindowBackground);

            set_dark_mode_time(::time::now());

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



         void windowing::windowing_application_on_system_start()
         {

            //auto * psystem = this->system();

            //psystem->defer_post_initial_request();

         }


         void windowing::set_finish()
         {

            //if (m_itask)
            //{

            //   ::PostThreadMessage((DWORD)m_itask, ::user::e_message_quit, 0, 0);

            //}

            ::acme::windowing::windowing::set_finish();

         }


         void windowing::kick_idle()
         {

            ::PostThreadMessage((DWORD)m_itask.m_i, ::user::e_message_kick_idle, 0, 0);

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


         /// <summary>
         ///  Actually this function may be called from a different thread, but it is the thread that is responsible for
         ///  windowing messages, so it is the thread that should be processing windowing messages.
         /// </summary>
         /// <returns></returns>
         bool windowing::handle_messages()
         {

            ASSERT(::get_task()->is_current_task());

            MSG msg;

            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {

               if (msg.message == WM_QUIT)
               {

                  ::get_task()->set_finish();

                  return false;

               }
               else if (msg.message == ::user::e_message_kick_idle)
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


         void windowing::run()
         {

            system()->prepare_application();

            //m_papplication->prepare_application();

            //__task_init();


            //init_task();

            //set_current_handles();

            //::set_main_thread();

            //system()->defer_post_initial_request();

            //run();

            
            
            
            
            //on_activate();




            //system()->defer_post_application_start_file_open_request

            m_papplication->send(
               [this]()
               {
                  
                  m_papplication->process_command_line_options();

               });



            //system()->defer_post_initial_request();

//            ::string strAppId = m_papplication->m_strAppId;
//
            //session()->get_application(strAppId, true);

            //m_papplication->postø() << [this]()
            //   {

            //      m_papplication->m_bReadyToAttendRequests = true;

            //   });

            run_main_loop();

            //while (true)
            //{

            //   if (!_process_windowing_messages())
            //   {

            //      break;

            //   }

            //}

            //if (::system()->m_pmanualresethappeningMainLoopEnd)
            //{

            //   ::system()->m_pmanualresethappeningMainLoopEnd->set_happening();

            //}

            information() << "windowing_win32::windowing::windowing::run ending!!";

         }


         //void windowing::_do_tasks()
         //{

         //   _process_windowing_messages();

         //}

         ::color::color windowing::get_operating_system_background_color()
         {

            auto colorWindowBackground = reinterpreted_background_color();

            return colorWindowBackground;

         }


         ::pointer < ::user::activation_token > windowing::get_user_activation_token()
         {

            auto puseractivationtoken = allocateø ::win32::acme::windowing::activation_token(::get_task());

            puseractivationtoken->initialize(this);

            return puseractivationtoken;


         }



      } // namespace windowing


   } // namespace acme


} // namespace windowing_system_win32



