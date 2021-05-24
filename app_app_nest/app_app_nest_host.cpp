#include "framework.h"
#include <eh.h>

u32 g_nRedrawThreadID;
extern bool g_bAppStarted;
extern void * g_pvoidPluginSystem;


namespace ca2plugin_container
{


   ATOM register_class(HINSTANCE hInstance);


   host::host(__pointer(::ca2plugin_container::application) papp) :
      ::object(papp),
      ::aura::application(papp),
      ::axis::application(papp),
      ::base::application(papp),
      ::simple_ui::style(papp),
      ::user::interaction(papp),
      hotplugin::plugin(papp),
      aura::session(papp),
      axis::session(papp),
      ::base::session(papp),
      ::aura::ipc::base(papp),
      ::aura::ipc::tx(papp),
      ::aura::ipc::ipc(papp)
   {

      m_pcontainerapp         = papp;

      m_pbasecomposer         = papp;

      m_phost                 = nullptr;
      m_bInitialized          = false;
      m_bOk                   = false;

      m_bRunningSpaAdmin      = false;

      m_vssPluginName         = "ca2 plugin";
      m_vssPluginDescription  = "ca2 plugin for Firefox";

      ::ca2plugin_container::register_class((HINSTANCE) ::GetModuleHandleA("ca2plugin_container.dll"));

      m_oswindowMessage       = ::CreateWindowExA(0, "npca2_message_queue", "npca2_message_queue", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);

      m_pfile                 = nullptr;

      m_oswindow              = nullptr;
      m_bStream               = false;

   }

   host::~host()
   {
      ::DestroyWindow(m_oswindowMessage);
   }


   void host::install_message_routing(::channel * pchannel)
   {

      ::hotplugin::host::install_message_routing(pchannel);

      ////MESSAGE_LINK(WM_TIMER, pchannel, this,&host::_001OnTimer);

   }


   void host::_001OnTimer(::timer * ptimer)
   {

      ::hotplugin::host::_001OnTimer(ptimer);

      if(ptimer->m_uEvent == 2000 + 77 + 3)
      {

         _001UpdateWindow();

         on_paint(nullptr,m_rectClient);

         //if(!m_bMayProDevian && get_parent() == nullptr)
         //{

         //   //set_need_redraw();

         //}

      }


   }


   bool host::init()
   {

      if(m_bInitialized)
         return true;

      m_bInitialized    = true;

      if(!::user::interaction::create_message_queue("ca2plugin_container::host::init create_message_queue"))
         return false;

      start_plugin();

      if(!plugin_initialize())
         return false;

      return true;


   }


   void host::start_plugin()
   {

      ::plugin::instance * pplugin           = new ::plugin::instance(this);

      m_pplugin                              = pplugin;

      m_pplugin->::aura::application::m_psession              = ::aura::application::m_psession;

      m_pplugin->m_psystem               = m_psystem;

      m_pplugin->get_application()                  = get_application();

      m_pplugin->m_phost                     = this;

      m_pcontainerapp->m_psystem->m_pplugin  = pplugin;

      m_pplugin->m_strBitmapChannel          = m_strBitmapChannel;

      m_bInstalling                          = false;

   }


   bool host::is_ok()
   {

      return m_bStream && m_bOk;

   }


   void host::post_message(u32 emessage, wparam wparam, lparam lparam)
   {

      ::PostMessage(m_oswindow, emessage, wparam, lparam);

   }


   void host::shut()
   {

      m_bInitialized = false;

      ::KillTimer(m_oswindowMessage, (uptr) this);

      plugin_finalize();

      m_oswindow = nullptr;

   }


   bool host::open_link(const string & strLink,const string & strTarget)
   {

      ensure_tx(::hotplugin::message_open_url,(void *)strLink.c_str(),(i32)strLink.get_length(), 2000);

      return true;

   }


   void host::restart_aura_ipc()
   {

      m_pcontainerapp->restart_aura_ipc();

   }



   bool host::reload_plugin()
   {

      ::TerminateProcess(::GetCurrentProcess(), 0);

      return true;

   }


   oswindow host::get_host_window()
   {
      return m_oswindow;
   }


   void host::message_handler(::user::message * pusermessage)
   {

      ::hotplugin::host::message_handler(pusermessage);

   }


   LRESULT CALLBACK window_proc(oswindow oswindow, u32 message, WPARAM wParam, LPARAM lParam)
   {
      return DefWindowProc(oswindow, message, wParam, lParam);
   }

   ATOM register_class(HINSTANCE hInstance)
   {
      WNDCLASSEXW wcex;

      wcex.cbSize = sizeof(WNDCLASSEXW);

      wcex.style			   = 0;
      wcex.lpfnWndProc	   = &window_proc;
      wcex.cbClsExtra	   = 0;
      wcex.cbWndExtra	   = 0;
      wcex.hInstance		   = hInstance;
      wcex.hIcon			   = nullptr;
      wcex.hCursor		   = LoadCursor(nullptr, IDC_ARROW);
      wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
      wcex.lpszMenuName	   = nullptr;
      wcex.lpszClassName	= L"npca2_message_queue";
      wcex.hIconSm		   = nullptr;

      return RegisterClassExW(&wcex);
   }


   bool host::plugin_finalize()
   {

      ::KillTimer(m_oswindowMessage, (uptr) this);

      return ::hotplugin::host::plugin_finalize();

   }


   /*   NPError host::GetValue(NPPVariable variable, void *value)
      {

         switch (variable)
         {
         case NPPVpluginNameString:
            *((const char **)value) = m_vssPluginName;
            break;
         case NPPVpluginDescriptionString:
            *((const char **)value) = m_vssPluginDescription;
            break;
         case NPPVpluginScriptableNPObject:
            *(NPObject **)value = getScriptableObject();
            break;
         default:
            return NPERR_GENERIC_ERROR;
         }
         return NPERR_NO_ERROR;
      }*/

   /*

   NPObject * host::getScriptableObject()
   {
       if(m_phostjs == nullptr)
       {
           m_phostjs = host_js::NewObject(this);
       }
       /* Bugfix from Facebook: Certain older versions of webkit do a retain when
        * you return an NPObject from NPP_GetValue instead of assuming that we do
        * it before returninglike the NPAPI spec instructs; this results in a memory
        * leak if we don't fix it.
        */
   /* //today// if (m_retainReturnedNPObject)
       m_npHost->RetainObject(m_obj);*/

   //  return m_phostjs;
   //}
//   */
   // This is the preferred method to get strings from NPIdentifiers, since you
// don't have to worry about cleaning it up =]
   /*string host::StringFromIdentifier(NPIdentifier identifier)
   {
    //   assertMainThread();
       NPUTF8* idStr = NPN_UTF8FromIdentifier(identifier);
       string str;
       if (idStr != nullptr)
           str = idStr;
       NPN_MemFree(idStr);
       return str;
   }
   */
   void * host::get_context_system()
   {

      return get_application()->m_psystem;

   }


   void host::set_system(void * pvoidSystem)
   {

      //::hotplugin::host::set_system(pvoidSystem);

      get_application() = (::base::system *) pvoidSystem;


   }



   void host::start_ca2()
   {


      //if(psystem->install().is_installing_ca2())
      //{

      //   if(!m_bInstalling)
      //   {
      //      m_bInstalling = true;
      //      // shouldn't do advanced operations using ca2
      //      // starter_start will only kick a default app_app_admin.exe if one isn't already running, cleaning file lock if any
      //      start_app_install(": app=session session_start=session app_type=application install");
      //   }
      //   return;
      //}

      //psystem->install().update_ca2_installed(false);

      //if (psystem->install().is_ca2_installed())
      //{

      //   if(!init())
      //      return;

      //   return;

      //}
      //else
      //{

      //   start_app_install(": app=session session_start=session app_type=application install");

      //}

   }


   void host::on_receive(::aura::ipc::rx * prx, i32 message, void * pdata, i32 len)
   {

      if(prx == &m_rx)
      {

         //if(message == ::hotplugin::message_init)
         //{
         //
         //   NPWindow * pwindow = (NPWindow *) pdata;

         //   try
         //   {

         //      init(pwindow);

         //   }
         //   catch(...)
         //   {
         //   }


         //}
//         else if(message == ::hotplugin::message_set_window)
         if(message == ::hotplugin::message_set_window)
         {

            const RECT & rectangle = *((LPCRECT) pdata);

            //if(m_rectangle != rectangle)
            {

               m_rectangle = rectangle;

               m_rectClient = rectangle;

               m_rectClient.offset(-m_rectClient.top_left());

               m_rectangleWindow = rectangle;

               try
               {

                  SetPlacement(rectangle);

               }
               catch(...)
               {
               }

            }

         }
         else if(message == ::hotplugin::message_paint)
         {


            const ::rectangle_i32 & rectangle = *((LPCRECT) pdata);

            try
            {

               _001UpdateWindow();

               //::draw2d::graphics_pointer g(e_create);

               //g->CreateCompatibleDC(nullptr);

               //on_paint(g, rectangle);

               on_paint(nullptr,rectangle_i32);

            }
            catch(...)
            {
            }

         }
         else if(message == WM_APP+WM_PAINT)
         {


            try
            {

               //::draw2d::graphics_pointer g(e_create);

               //g->CreateCompatibleDC(nullptr);

               //on_paint(g,m_rectClient);

               on_paint(nullptr,m_rectClient);

            }
            catch(...)
            {
            }

         }
         else if(message == ::hotplugin::message_set_ready)
         {

            if(pdata != nullptr)
            {

               m_memory.assign(pdata, len);

//  xxx             if(m_puchMemory != nullptr)
               //                m_bStream = true;


               string str((const char *) m_memory.get_data(), len);

               xxdebug_box(str, "ca2plugincontainer::host::on_receive", 0);


            }

            m_bStream = true;

            set_ready();

         }
         else if(message == ::hotplugin::message_set_plugin_url)
         {


            string str((const char *) pdata, len);

            xxdebug_box(str, "ca2plugincontainer::host::on_receive", 0);

            m_pbasecomposer->m_strPluginUrl = str;

         }
         else if(message == ::hotplugin::message_message)
         {

            MSG * pmsg = (MSG *) pdata;

            if(pmsg->message == e_message_activate)
            {

               if(LOWORD(pmsg->wParam) == WA_ACTIVE)
               {

                  psession->m_puiActive = this;

               }
               else
               {

                  psession->m_puiActive = nullptr;

               }

               return;

            }
            else if(pmsg->message == e_message_set_focus)
            {

               psession->set_keyboard_focus(this);

               return;

            }
            else if(pmsg->message == e_message_kill_focus)
            {

               psession->set_keyboard_focus(nullptr);

               return;

            }
            else if(pmsg->message == e_message_close)
            {

               m_pcontainerapp->set_finish();

               return;

            }

            try
            {

               message_handler(::user::interaction::get_message_base(pmsg->message, pmsg->wParam, pmsg->lParam));

            }
            catch(...)
            {
            }


         }

      }

   }

   bool host::set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags)
   {

      bool bOk = ::hotplugin::host::set_window_position(z,x,y,cx,cy,nFlags);


      try
      {

         if(m_pcontainerapp != nullptr)
         {

            if(m_pcontainerapp->m_psystem != nullptr)
            {

               if(m_pcontainerapp->m_psystem->m_pplugin != nullptr)
               {

                  if(m_pcontainerapp->m_psystem->m_pplugin->m_puserinteractionHost != nullptr)
                  {

                     m_pcontainerapp->m_psystem->m_pplugin->m_puserinteractionHost->set_window_position(z,x,y,cx,cy,nFlags);

                  }

               }

            }

         }

      }
      catch(...)
      {
      }

      return bOk;

   }


   void host::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_pcontainerapp != nullptr)
      {

         if(m_pcontainerapp->m_psystem != nullptr)
         {

            if(m_pcontainerapp->m_psystem->m_pplugin != nullptr)
            {

               if(m_pcontainerapp->m_psystem->m_pplugin->m_puserinteractionHost != nullptr)
               {

                  m_pcontainerapp->m_psystem->m_pplugin->m_puserinteractionHost->_001Print(pgraphics);

                  {

                     static tick dwLast = 0;
                     static ::count c = 0;
                     static double dLast = 0.0;

                     c++;

                     auto tickNow = ::tick::now();

                     auto tickSpan = tickNow - dwLast;

                     if(tickSpan > 1000)
                     {

                        dLast = c * 1000.0 / __double(tickSpan);

                        c = 0;

                        dwLast = tickNow;

                     }

#if 0

                     string str;

                     str.Format("%0.1f fps",dLast);

                     pgraphics->set_text_color(argb(255,255,255,0));

                     pgraphics->text_out(300,20,str);

#endif

                  }

               }

            }

         }

      }

   }


} // namespace ca2plugin_container



