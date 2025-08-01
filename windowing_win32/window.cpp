// created by Camilo 2021-01-31 04:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "buffer.h"
#include "display.h"
#include "monitor.h"
#include "window.h"
#include "windowing.h"
#include "icon.h"
#include "cursor.h"
#include "top_level_enum.h"
#include "system_interaction.h"
#include "window_util.h"
#include "acme/constant/activate.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/exception/exception.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/topic.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/windowing/windowing.h"
//#include "aura_windows/interaction_impl.h"
#include "apex/gpu/approach.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/user/user/interaction_graphics_thread.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/message/user.h"
#include "aura/user/user/user.h"
#include "aura/user/user/system.h"
//#include "acme/operating_system/windows/nano/user/user.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/windowing/placement_log.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include "acme_windowing_win32/activation_token.h"

#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/_string.h"
#include "acme/operating_system/windows/windows.h"


#include <dwmapi.h>
#include <shellapi.h>

#define IDI_ICON_WINDOW 256
HRESULT SetTouchDisableProperty(HWND hwnd, BOOL fDisableTouch);

unsigned int get_dpi_for_window(oswindow hwnd);
bool is_registered_windows_message(unsigned int message);

//CLASS_DECL_ACME HWND windows_get_mouse_capture();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)
//wstring CLASS_DECL_WINDOWING_WIN32 windows_get_user_interaction_window_class(::user::interaction * puserinteraction);

extern CLASS_DECL_ACME const unichar gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_ACME const unichar gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_ACME const unichar gen_WndMDIFrame[];
extern CLASS_DECL_ACME const unichar gen_WndFrameOrImpact[];
extern CLASS_DECL_ACME const unichar gen_WndOleControl[];



CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure();


bool has_autohide_appbar(unsigned int edge, const int_rectangle & mon);


CLASS_DECL_WINDOWING_WIN32 bool __is_combo_box_control(HWND hwnd, unsigned int nStyle);
CLASS_DECL_WINDOWING_WIN32 bool __check_center_dialog(const ::scoped_string & scopedstrResource);

CLASS_DECL_WINDOWING_WIN32 bool __compare_class_name(HWND hwnd, const ::scoped_string & scopedstrClassName);

CLASS_DECL_WINDOWING_WIN32 bool hook_window_create(::windowing_win32::window * pwindow);
CLASS_DECL_WINDOWING_WIN32 bool unhook_window_create();
CLASS_DECL_WINDOWING_WIN32 void reset_message_cache();


namespace windowing_win32
{


   window::window()
   {

      //m_hbitmapProto = nullptr;
      //m_hdcProto = nullptr;
      //m_pbitsProto = nullptr;
      m_hglrcProto = nullptr;
      //m_bSizeMoveMode = false;
      m_uOpacity = 255;

      //m_hmenuSystem = nullptr;

      //m_pWindow4 = this;

      m_uExtraFlagsSetWindowPos = 0;

      m_uSetWindowPosLastFlags = 0;
      m_hwndSetWindowPosLastInsertAfter = nullptr;

      //set_layer(LAYERED_IMPL, this);
      //m_plongmap  = ___new iptr_to_iptr;

//      m_iXic = 0;
//
//      m_xic = nullptr;
//
//      for (auto &i : m_iaNetWmState)
//      {
//
//         i = -1;
//
//      }
//
//      m_hcursorLast = 0;
//
//      m_htask = 0;
//
//      m_window = None;

      m_bTrackMouseLeave = false;

      //m_pwindow = nullptr;

      m_bMessageOnlyWindow = false;

      //      m_osdisplay = nullptr;
      //
      //      zero(m_visual);
      //
      //      m_iDepth = -1;
      //
      //      m_iScreen = -1;
      //
      //      m_colormap = None;
      //
      //      m_iXic = 0;

   }


   window::~window()
   {

      //::acme::del(m_plongmap);

   }


#ifdef _DEBUG


   long long window::increment_reference_count()
   {

      return ::windowing::window::increment_reference_count();

   }


   long long window::decrement_reference_count()
   {

      return ::windowing::window::decrement_reference_count();

   }


#endif

   //void window::assert_ok() const
   //{

   //   //::windowing_win32::window::assert_ok();

   //   //if (((::windowing_win32::window *)this)->get_hwnd() == nullptr)
   //   //   return;     // null (unattached) windows are valid

   //   //// check for special wnd??? values
   //   //ASSERT(HWND_TOP == nullptr);       // same as desktop
   //   //if (((::windowing_win32::window *)this)->get_hwnd() == HWND_BOTTOM)
   //   //{
   //   //}
   //   //else if (((::windowing_win32::window *)this)->get_hwnd() == HWND_TOPMOST)
   //   //{
   //   //}
   //   //else if (((::windowing_win32::window *)this)->get_hwnd() == HWND_NOTOPMOST)
   //   //{
   //   //}
   //   //else
   //   //{
   //   //   // should be a normal window
   //   //   ASSERT(::IsWindow(((::windowing_win32::window *)this)->get_hwnd()));

   //   //}
   //}

   //
   //void window::dump(dump_context & dumpcontext) const
   //{

   //   //::windowing_win32::window::dump(dumpcontext);

   //   //dumpcontext << "\nm_oswindow_ = " << ((::windowing_win32::window *)this)->get_hwnd();

   //   //if (((::windowing_win32::window *)this)->get_hwnd() == nullptr || ((::windowing_win32::window *)this)->get_hwnd() == HWND_BOTTOM ||
   //   //   ((::windowing_win32::window *)this)->get_hwnd() == HWND_TOPMOST || ((::windowing_win32::window *)this)->get_hwnd() == HWND_NOTOPMOST)
   //   //{
   //   //   // not a normal window - nothing more to dump
   //   //   return;
   //   //}

   //   //if (!::IsWindow(((::windowing_win32::window *)this)->get_hwnd()))
   //   //{
   //   //   // not a valid window
   //   //   dumpcontext << " (illegal hwnd)";
   //   //   return; // don't do anything more
   //   //}

   //   ////auto puserinteraction = psystem->ui_from_handle(((::windowing_win32::window *)this)->get_hwnd());
   //   ////if (puserinteraction->m_pwindow != (::user::window *)this)
   //   ////   dumpcontext << " (Detached or temporary window)";
   //   ////else
   //   ////   dumpcontext << " (permanent window)";

   //   ////wchar_t szBuf[64];
   //   ////::GetClassNameW(((::windowing_win32::window *)this)->get_hwnd(), szBuf, _countof(szBuf));
   //   ////dumpcontext << "\nclass name = \"" << szBuf << "\"";

   //   ////::int_rectangle rectangle;
   //   ////((::windowing_win32::window *)this)->puserinteraction->layout().window().screen_rect(&rectangle);
   //   ////dumpcontext << "\nrect = " << int_rectangle;
   //   ////dumpcontext << "\nparent ::user::window * = " << ::hex::lower_from((::iptr)((::windowing_win32::window *)this)->get_parent());

   //   ////dumpcontext << "\nstyle = " << (uptr)::GetWindowLong(((::windowing_win32::window *)this)->get_hwnd(), GWL_STYLE);
   //   ////if (::GetWindowLong(((::windowing_win32::window *)this)->get_hwnd(), GWL_STYLE) & WS_CHILD)
   //   ////   dumpcontext << "\nid = " << __get_dialog_control_id(((::windowing_win32::window *)this)->get_hwnd());

   //   ////dumpcontext << "\n";

   //}


   //void window::install_system_interaction_message_handling(::user::interaction * puserinteraction)
   //{

   //   auto pchannel = puserinteraction->m_pwindow;

   //   MESSAGE_LINK(WM_SETTINGCHANGE, pchannel, this, &window::_001OnMessage);
   //   MESSAGE_LINK(WM_FONTCHANGE, pchannel, this, &window::_001OnMessage);

   //}


   void window::prio_install_message_routing(::channel * pchannel)
   {

      ::windowing::window::prio_install_message_routing(pchannel);

      MESSAGE_LINK(e_message_paint, pchannel, this, &window::on_message_paint);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_destroy, pchannel, this, &window::on_message_non_client_destroy);
      MESSAGE_LINK(WM_GETICON, pchannel, this, &window::on_message_get_icon);
      //MESSAGE_LINK(WM_SETTINGCHANGE, pchannel, this, &window::_001OnMessage);
      //MESSAGE_LINK(WM_FONTCHANGE, pchannel, this, &window::_001OnMessage);


      //MESSAGE_LINK(e_message_create, pchannel, pimpl, &::windowing::window::_001OnPrioCreate);
      auto psystem = system();

      //auto pnode = psystem->m_pnode->m_pWindowingWin32Node;

      //auto emessageTaskbarCreated = pnode->m_emessageWindowsTaskbarCreatedMessage;

      auto pwin32windowing = win32_windowing();

      auto emessageTaskbarCreated = pwin32windowing->m_emessageWindowsTaskbarCreatedMessage;

      if (emessageTaskbarCreated != e_message_undefined)
      {

         MESSAGE_LINK(emessageTaskbarCreated, pchannel, this, &window::_001OnTaskbarCreated);

      }

   }


   void window::last_install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &window::_001OnCreate);
      MESSAGE_LINK(e_message_window_position_changed, pchannel, this, &window::on_message_window_position_changed);
      MESSAGE_LINK(WM_SYSCOMMAND, pchannel, this, &window::_001OnSysCommand);
      MESSAGE_LINK(WM_COMMAND, pchannel, this, &window::_001OnSysCommand);

      ::windowing::window::last_install_message_routing(pchannel);

      MESSAGE_LINK(WM_ACTIVATE, pchannel, this, &window::_001OnActivate);
      MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &window::_001OnDwmNcRenderingChanged);

   }


   //void window::install_message_routing(channel * pchannel)
   //{

   //   //::windowing::window::install_message_routing(pchannel);

   //   MESSAGE_LINK(e_message_create, pchannel, this, &window::_001OnCreate);
   //   MESSAGE_LINK(e_message_window_position_changed, pchannel, this, & window::on_message_window_position_changed);

   //   auto puserinteraction = user_interaction();

   //   //auto pimpl = m_pwindow.m_p;

   //   if (!puserinteraction->m_bMessageWindow)
   //   {

   //      //MESSAGE_LINK(e_message_redraw, pchannel, pimpl, &::windowing::window::_001OnRedraw);
   //      //MESSAGE_LINK(e_message_apply_visual, pchannel, pimpl, &::windowing::window::_001OnApplyVisual);


   //      //#ifndef LINUX
   //      //MESSAGE_LINK(e_message_move, pchannel, this, &window::on_message_move);
   //      //MESSAGE_LINK(e_message_size, pchannel, this, &window::on_message_size);
   //      //#endif


   //      //MESSAGE_LINK(e_message_show_window, pchannel, this, &window::on_message_show_window);
   //      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &window::on_message_kill_focus);
   //      //MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::on_message_set_focus);
   //      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &window::on_message_set_cursor);

   //   }

   //   MESSAGE_LINK(WM_ACTIVATE, pchannel, this, &window::_001OnActivate);
   //   MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &window::_001OnDwmNcRenderingChanged);

   //   user_interaction()->install_message_routing(pchannel);


   //   MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);
   //   MESSAGE_LINK(WM_GETICON, pchannel, this, &window::on_message_get_icon);

   //   //MESSAGE_LINK(e_message_create, pchannel, pimpl, &::windowing::window::_001OnPrioCreate);
   //   auto psystem = system();

   //   //auto pnode = psystem->m_pnode->m_pWindowingWin32Node;

   //   //auto emessageTaskbarCreated = pnode->m_emessageWindowsTaskbarCreatedMessage;

   //   auto pwin32windowing = win32_windowing();

   //   auto emessageTaskbarCreated = pwin32windowing->m_emessageWindowsTaskbarCreatedMessage;

   //   if (emessageTaskbarCreated != e_message_undefined)
   //   {

   //      MESSAGE_LINK(emessageTaskbarCreated, pchannel, this, &window::_001OnTaskbarCreated);

   //   }

   //}
   
   
   ::oswindow window::oswindow() const
   {

      return (::oswindow) m_hwnd;

   }


   void window::_set_oswindow(::oswindow oswindow)
   {

      m_hwnd = (HWND) oswindow;

   }


   void window::destroy()
   {

      WNDPROC pfnWndProc = WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC));

      if (WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC)) == pfnWndProc)
      {

         WNDPROC pfnSuper = *GetSuperWndProcAddr();

         if (pfnSuper != nullptr)
         {

            ::SetWindowLongPtr(get_hwnd(), GWLP_WNDPROC, reinterpret_cast<iptr>(pfnSuper));

         }

      }

      auto pacmewindowing = system()->m_pacmewindowing;

      if (pacmewindowing)
      {

         ::pointer < ::windowing::windowing > pwindowing;

         pwindowing = pacmewindowing;

         if (pwindowing)
         {

            pwindowing->erase_window(this);

         }

      }

      set_hwnd(nullptr);

      ::windowing::window::destroy();

      ::win32::acme::windowing::window::destroy();

   }


   ::windowing_win32::windowing * window::win32_windowing()
   {

      return  dynamic_cast < ::windowing_win32::windowing * > (windowing());

   }


   //void window::create_window(::windowing::window * pimpl)
   void window::create_window()
   {

      ::windowing::window::create_window();

   }


   void window::_create_window()
   {

      auto pwindowing = this->windowing();

      //auto pimpl = m_pwindow;

      //m_pimpl2 = m_pImpl2;

      wstring wstrClassName;

      auto puserinteraction = user_interaction();

      wstrClassName = pwindowing->_windows_get_user_interaction_window_class(puserinteraction);

      //if (!puserinteraction->m_pusersystem)
      //{

      //   puserinteraction->m_pusersystem = __allocate ::user::system();

      //}

      ::pointer<::user::system> pusersystem;

      if (user_interaction()->is_system_message_window())
      {

         pusersystem = __allocate::user::system();

      }
      else
      {

         if (user_interaction()->m_pusersystem)
         {

            pusersystem = user_interaction()->m_pusersystem;

         }
         else
         {

            pusersystem = __allocate ::user::system();

         }

      }

      if (!puserinteraction->pre_create_window(puserinteraction->m_pusersystem))
      {

         //return false;

         throw ::exception(error_failed);

      }

      //m_pwindow = pimpl;

      //m_pwindow = this;

      //puserinteraction->m_pwindow = this;

      if (puserinteraction->m_bMessageOnlyWindow)
      {

         puserinteraction->m_ewindowflag -= e_window_flag_graphical;

      }

      //install_message_routing(puserinteraction);

      wstring wstrWindowName;

#if 0

      WCHAR szTitle[256];
      WCHAR szWindowClass[256];

      wcscpy(szTitle, L"123");
      wcscpy(szWindowClass, L"WindowsDestkop1");

      //HWND hwnd = CreateWindowExW(pusersystem->m_createstruct.dwExStyle, szWindowClass, wstrWindowName, pusersystem->m_createstruct.style,
        // pusersystem->m_createstruct.x(), pusersystem->m_createstruct.y(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), pusersystem->m_createstruct.hwndParent, pusersystem->m_createstruct.hMenu, pusersystem->m_createstruct.hInstance, pusersystem->m_createstruct.lpCreateParams);
      HWND hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED,
         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, pusersystem->m_createstruct.hInstance, nullptr);
      //if (!hwnd)
      //{
         //return false;
      //}

      ::ShowWindow(hwnd, SW_SHOWNORMAL);
      ::UpdateWindow(hwnd);

#if 0

      MSG msg;

      // Main message loop:
      while (mq_get_message(&msg, nullptr, 0, 0))
      {
         //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }

#else

      m_puserthread->run();

#endif

      //return true;

#else

      unsigned int dwExStyle = 0;

      unsigned int dwStyle = 0;

      //auto pusersystem = puserinteraction->m_pusersystem.get();

      wstrWindowName = puserinteraction->m_strWindowText2;

      int x = 0;
      int y = 0;
      int cx = 0;
      int cy = 0;

      HWND hwndParent = nullptr;

      if (user_interaction()->m_bMessageOnlyWindow)
      {

         hwndParent = HWND_MESSAGE;
         dwExStyle = 0;
         dwStyle = 0;

      }
      else
      {
       
         win32_windowing()->__synthesizes_creates_styles(puserinteraction, dwExStyle, dwStyle);

         x = puserinteraction->const_layout().sketch().origin().x();
         y = puserinteraction->const_layout().sketch().origin().y();
         cx = puserinteraction->const_layout().sketch().size().cx();
         cy = puserinteraction->const_layout().sketch().size().cy();

      }

      //pusersystem->m_pwindow = this;

      HMENU hmenu = nullptr;

      HINSTANCE hinstance = windows::get_window_procedure_hinstance();

      void * lpCreateParams = (::windows::window*)this;

      bool bWsChildStyle = dwStyle & WS_CHILD;

      DWORD dwLastErrorPreCreateWindow = ::GetLastError();

      auto edisplaySketch = user_interaction()->const_layout().sketch().display();

      if (is_equivalent_in_equivalence_sink(edisplaySketch, e_display_normal))
      {

         ::int_rectangle rectangleRequest;

         rectangleRequest.left() = x;
         rectangleRequest.top() = y;
         rectangleRequest.set_size({ cx, cy });

         user_interaction()->set_window_normal_stored_rectangle(rectangleRequest);

      }

      if (puserinteraction->is_graphical())
      {

         if(m_papplication->m_bGpu)
         {
            
            auto pgpuapproach = m_papplication->get_gpu_approach();

            pgpuapproach->on_before_create_window(this);

         }

         //draw2d()->on_before_create_window(this);

      }


      //dwStyle = WS_VISIBLE | WS_POPUP;

      //dwExStyle = 0;

       //dwExStyle &=~ WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST; // Using WS_EX_LAYERED loses the GPU-friendliness
       //dwExStyle &=  ~WS_EX_LAYERED ; // Using WS_EX_LAYERED loses the GPU-friendliness
      //dwStyle |= WS_EX_NOREDIRECTIONBITMAP;
      //dwExStyle |= WS_EX_NOREDIRECTIONBITMAP;
      //dwExStyle |= WS_EX_LAYERED;

      if (dwExStyle & WS_EX_LAYERED)
      {

         warning() << "layered";

      }

      HWND hwnd = ::CreateWindowExW(
         dwExStyle,
         wstrClassName,
         wstrWindowName,
         dwStyle,
         x,
         y,
         cx,
         cy,
         hwndParent,
         hmenu,
         hinstance,
         lpCreateParams);

      m_hwnd = hwnd;

      if (::is_set(hwnd) && ::is_set(hwndParent))
      {

         ::cast < ::windows::windowing > pwindowing = system()->acme_windowing();

         pwindowing->m_windowmap[(::oswindow)hwnd] = this;

      }

#endif

      if (m_hwnd == nullptr)
      {

         unsigned int dwLastError = ::GetLastError();

         string strLastError = ::windows::last_error_message(dwLastError);

         string strMessage;

         strMessage.formatf("%s\n\nSystem Error Code: %d", strLastError.c_str(), dwLastError);

         warning()(e_trace_category_appmsg) << "Warning: Window creation failed: get_last_error returned:";

         warning()(e_trace_category_appmsg) << strMessage;

         if (dwLastError == 0x0000057e)
         {

            informationf("Cannot create a top-level child window.");

         }
         else
         {

            informationf("%s", strMessage);

         }

         throw ::exception(error_failed);

      }

      if (puserinteraction->is_graphical())
      {

         if(m_papplication->m_bGpu)
         {
            auto pgpuapproach = m_papplication->get_gpu_approach();
            pgpuapproach->on_create_window(this);
         }
         //draw2d()->on_create_window(this);

      }

      //SendMessage(m_hwnd, e_message_after_create, 0, 0);

      if (puserinteraction->m_bEdgeGestureDisableTouchWhenFullscreen)
      {

         SetTouchDisableProperty(m_hwnd, true);

      }

      puserinteraction->m_ewindowflag += ::e_window_flag_is_window;

      bool bUnicode = ::IsWindowUnicode(m_hwnd) != false;

      if (bUnicode)
      {

         output_debug_string("window is unicode");

      }
      else
      {

         output_debug_string("window is ANSI");

      }

      if (m_hwnd != get_hwnd())
      {

         set_hwnd(m_hwnd);

      }


      if (_get_ex_style() & WS_EX_LAYERED)
      {


         m_uExtraFlagsSetWindowPos =
            SWP_NOZORDER |
            SWP_ASYNCWINDOWPOS
            //| SWP_FRAMECHANGED
            //| SWP_NOSENDCHANGING
            | SWP_NOREDRAW
            | SWP_NOCOPYBITS
            //| SWP_DEFERERASE
            | SWP_NOACTIVATE;
         //| SWP_SHOWWINDOW;
      }



      ////puserinteraction->increment_reference_count();

      //puserinteraction->on_finished_window_creation();

      ////puserinteraction->m_ewindowflag |= e_window_flag_window_created;

   }


   //void window::_create_window()
   //{


   //}


   void window::window_update_screen()
   {

      //      if(m_interlockedPostedScreenUpdate > 0)
      //      {
      //
      //         return;
      //
      //      }
      //
      //      m_interlockedPostedScreenUpdate++;

            //windowing()->windowing_post([this]()
              //                          {
      if(m_pgraphicsgraphics)
      {

         //_synchronous_lock synchronouslock(user_synchronization());

         //display_lock displayLock(x11_display()->Display());

         //auto pimpl = m_pwindow;

         //configure_window_unlocked();

         //user_interaction()->user_send([pimpl]()
           // {




               m_pgraphicsgraphics->update_screen();

//});
               //bool bWindowsApplyVisual = true;

               auto puserinteraction = user_interaction();

               if (!puserinteraction)
               {

                  return;

               }

               auto & edisplayOutput = user_interaction()->const_layout().output().m_edisplay;

               auto & edisplayDesign = user_interaction()->const_layout().design().m_edisplay;

               if (edisplayOutput != edisplayDesign)
               {

                  user_interaction()->layout().m_statea[::user::e_layout_output].m_edisplay = edisplayDesign;

                  //user_interaction()->send_message(e_message_show_window, ::is_screen_visible(edisplayDesign) ? 1 : 0);

               }

         //pbuffer->_update_screen_lesser_lock();

      }



      //auto pimpl = m_pwindow;

      m_pgraphicsthread->on_graphics_thread_iteration_end();

      //                                  });

            //m_interlockedPostedScreenUpdate--;

   }



   //bool window::has_capture() const
   //{

   //   return ::GetCapture() == get_hwnd();

   //}


   //bool window::has_keyboard_focus() const
   //{

   //   return ::GetFocus() == get_hwnd();

   //}


   //void window::_001OnMessage(::message::message * pmessage)
   //{

   //   if (pmessage != nullptr)
   //   {

   //      wparam wparam = pmessage->m_wparam;

   //      lparam lparam = pmessage->m_lparam;

   //      string strLparamString;

   //      if (pmessage->m_emessage == WM_SETTINGCHANGE && wparam == 0)
   //      {

   //         strLparamString = (const WCHAR *)(LPARAM(lparam));

   //      }

   //      if (pmessage->m_emessage == WM_FONTCHANGE)
   //      {

   //         auto psystem = system();

   //         ::cast < ::manager > pmanager = psystem;

   //         if (pmanager)
   //         {

   //            pmanager->signal(id_operating_system_font_list_change);

   //         }

   //         //auto ptopic = psystem->topic(id_os_font_change);

   //         //psystem->handle_subject(ptopic);

   //         //fork([this]()
   //           // {

   //              // psession->call(e_routine_font_change);

   //            //});

   //      //}
   //      }
   //      else if (pmessage->m_emessage == WM_SETTINGCHANGE && strLparamString == "ImmersiveColorSet")
   //      {

   //         //auto pnode = system()->m_pnode;

   //         //pnode->fetch_user_color();

   //         system()->acme_windowing()->fetch_system_background_color();

   //      }
   //      else if (pmessage->m_emessage == e_message_display_change ||
   //         (pmessage->m_emessage == WM_SETTINGCHANGE &&
   //            (pmessage->m_wparam == SPI_SETWORKAREA)))
   //      {

   //         output_debug_string("WM_SETTINGCHANGE SPI_SETWORKAREA");

   //         //throw_todo();

   //         //psystem->enum_display_monitors();

   //         //::pointer<::user::interaction>puserinteraction;

   //         //while(psystem->get_frame(puserinteraction))
   //         //{

   //         //   try
   //         //   {

   //         //      puserinteraction->post_message(e_message_display_change);

   //         //   }
   //         //   catch(...)
   //         //   {
   //         //   }

   //         //}


   //      }

   //   }

   //}


   void window::_001OnTaskbarCreated(::message::message * pmessage)
   {

      ::topic topic(id_task_bar_created);

      user_interaction()->handle(&topic, nullptr);

   }


   //bool window::defer_set_icon()
   //{

   //   //int iSmallIconCx = ::GetSystemMetrics(SM_CXSMICON);
   //   //int iSmallIconCy = ::GetSystemMetrics(SM_CYSMICON);
   //   //int iIconCx = ::GetSystemMetrics(SM_CXICON);
   //   //int iIconCy = ::GetSystemMetrics(SM_CXICON);
   //   int iSmallIconCx = 256;
   //   int iSmallIconCy = 256;
   //   int iIconCx = 256;
   //   int iIconCy = 256;

   //   //HICON hiconSmall = (HICON) ::LoadIcon((HINSTANCE)system()->m_hinstanceThis, MAKEINTRESOURCE(128));

   //   HICON hiconSmall =(HICON) ::LoadImage((HINSTANCE)system()->m_hinstanceThis, MAKEINTRESOURCE(128), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
   //   //HICON hicon = (HICON)::LoadImage((HINSTANCE)system()->m_hinstanceThis, MAKEINTRESOURCE(128), IMAGE_ICON, iIconCx, iIconCy, LR_DEFAULTCOLOR);
   //   HICON hicon = nullptr;

   //   if (!hicon)
   //   {

   //      hicon = hiconSmall;

   //   }
   //   if (!hiconSmall)
   //   {

   //      hiconSmall = hicon;

   //   }
   //   if (!hicon || !hiconSmall)
   //   {

   //      return false;

   //   }

   //   //SetLastError(0);
   //   {
   //      //HWND hwnd = get_hwnd();
   //      user_interaction()->post_message(WM_SETICON, ICON_SMALL, (LPARAM)hiconSmall);
   //      //DWORD dwLastError = ::GetLastError();
   //      //information() << "ICON_BIT_SMALLER" << dwLastError;
   //   }
   //   //SetLastError(0);
   //   {
   //     // HWND hwnd = get_hwnd();
   //      user_interaction()->post_message(WM_SETICON, ICON_BIG, (LPARAM)hicon);
   //      //::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
   //      //DWORD dwLastError = ::GetLastError();

   //      //information() << "ICON_LARGER" << dwLastError;
   //   }
   //   SetLastError(0);

   //   return true;

   //}


   //void window::set_wm_class(const ::scoped_string & scopedstr)
   //{

   //   //      m_strWMClass = psz;
   //   //
   //   //      xdisplay d(display());
   //   //
   //   //      XClassHint classHint;
   //   //
   //   //      classHint.res_name = m_strWMClass;
   //   //
   //   //      classHint.res_class = m_strWMClass;
   //   //
   //   //      XSetClassHint(display(), window(), &classHint);

   //}


   //int window::map_window()
   //{

   //   //      int i = 0;
   //   //
   //   //      {
   //   //
   //   //         windowing_output_debug_string("\nwindow::map_window");
   //   //
   //   //         xdisplay d(display());
   //   //
   //   //         i = XMapWindow(display(), window());
   //   //
   //   //      }
   //   //
   //   //#ifndef RASPBIAN
   //   //
   //   //      if (g_psncontext != nullptr)
   //   //      {
   //   //
   //   //         sn_launchee_context_complete(g_psncontext);
   //   //
   //   //         g_psncontext = nullptr;
   //   //
   //   //      }
   //   //
   //   //#endif // RASPBIAN
   //   //
   //   //      windowing_output_debug_string("\nwindow::map_window END");

   //   return 0;

   //}


   //int window::unmap_window(bool bWithdraw)
   //{

   //   //windowing_output_debug_string("\nwindow::unmap_window");

   //   //xdisplay d(display());

   //   //int i;

   //   //if (bWithdraw)
   //   //{

   //   //   i = XWithdrawWindow(display(), window(), m_iScreen);

   //   //}
   //   //else
   //   //{

   //   //   i = XUnmapWindow(display(), window());

   //   //}

   //   //windowing_output_debug_string("\nwindow::unmap_window END");

   //   //return i;

   //}


   //oswindow_dataptra * window::s_pdataptra = nullptr;


   //::mutex * window::s_pmutex = nullptr;


   //int oswindow_find_message_only_window(::user::window * pimpl)
   //{

   //   if (pimpl == nullptr)
   //      return -1;

   //   single_lock slOsWindow(window::s_pmutex, true);

   //   for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //   {

   //      if (::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //         && ::window::s_pdataptra->element_at(i)->m_pwindow == pimpl)
   //      {

   //         return i;

   //      }

   //   }

   //   return -1;

   //}

   //int oswindow_find(Display * pdisplay, Window window)
   //{

   //   single_lock slOsWindow(::window::s_pmutex, true);

   //   for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //   {
   //      if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //         && ::window::s_pdataptra->element_at(i)->m_osdisplay->display() == pdisplay
   //         && ::window::s_pdataptra->element_at(i)->m_window == window)
   //      {
   //         return i;
   //      }
   //   }

   //   return -1;

   //}

   //int oswindow_find(Window window)
   //{

   //   single_lock slOsWindow(::window::s_pmutex, true);

   //   for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //   {
   //      if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //         && ::window::s_pdataptra->element_at(i)->m_window == window)
   //      {
   //         return i;
   //      }
   //   }

   //   return -1;

   //}


   //window * oswindow_get_message_only_window(::user::window * puserinteraction)
   //{

   //   if (puserinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   single_lock slOsWindow(::window::s_pmutex, true);

   //   iptr iFind = oswindow_find_message_only_window(puserinteraction);

   //   if (iFind >= 0)
   //   {

   //      return ::window::s_pdataptra->element_at(iFind);

   //   }

   //   ::window * pdata = ___new window;

   //   pdata->m_bMessageOnlyWindow = true;
   //   pdata->m_window = None;
   //   pdata->m_pwindow = puserinteraction;
   //   pdata->m_osdisplay = nullptr;
   //   pdata->m_parent = 0;
   //   pdata->m_pmq = puserinteraction->puserinteraction->user_thread()->aaa_get_message_queue();

   //   ::window::s_pdataptra->add(pdata);

   //   return pdata;

   //}


   //window * oswindow_defer_get(Display * pdisplay, Window window)
   //{

   //   single_lock slOsWindow(::window::s_pmutex, true);

   //   iptr iFind = oswindow_find(pdisplay, window);

   //   if (iFind < 0)
   //   {

   //      return nullptr;

   //   }

   //   return ::window::s_pdataptra->element_at(iFind);

   //}


   //window *
   //   oswindow_get(Display * pdisplay, Window window, Visual * pvisual, int iDepth, int iScreen, Colormap colormap)
   //{

   //   single_lock slOsWindow(::window::s_pmutex, true);

   //   iptr iFind = oswindow_find(pdisplay, window);

   //   if (iFind >= 0)
   //   {

   //      return ::window::s_pdataptra->element_at(iFind);

   //   }

   //   ::window * pdata = ___new ::window;

   //   pdata->m_bMessageOnlyWindow = false;
   //   pdata->m_osdisplay = osdisplay_get(pdisplay);
   //   pdata->m_window = window;

   //   if (pvisual != nullptr)
   //   {

   //      pdata->m_visual = *pvisual;

   //   }

   //   pdata->m_iDepth = iDepth;
   //   pdata->m_iScreen = iScreen;
   //   pdata->m_colormap = colormap;
   //   pdata->m_parent = 0;

   //   ::window::s_pdataptra->add(pdata);

   //   return pdata;

   //}


   //void x11_on_start_session()
   //{

   //   Display * dpy = x11_get_display();
   //
   //   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
   //
   //   g_oswindowDesktop->m_pwindow = nullptr;
   //
   //   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->window(), StructureNotifyMask);
   //
   //}


   /*window * oswindow_get(Window window)
   {

      single_lock slOsWindow(::window::s_pmutex, true);

      iptr iFind = oswindow_find(window);

      if (iFind < 0)
      {

         return nullptr;

      }

      return ::window::s_pdataptra->element_at(iFind);

   }*/


   //bool window::bamf_set_icon()
   //{

   //   ::linux::desktop_file file;

   //   file.bamf_set_icon(this);

   //   return true;

   //}


   //int window::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data,
   //   int nelements)
   //{

   //   return XChangeProperty(display(), window(), property, type, format, mode, data, nelements);

   //}


   //Atom window::intern_atom(const ::scoped_string & scopedstrAtomName, bool bCreate)
   //{

   //   return m_osdisplay->intern_atom(pszAtomName, bCreate);

   //}


   //Atom window::intern_atom(e_net_wm_state estate, bool bCreate)
   //{

   //   return m_osdisplay->intern_atom(estate, bCreate);

   //}

//
//   bool window::set_icon(::image::image * pimage)
//   {
//
//      // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
//      // http://stackoverflow.com/users/432509/ideasman42
//
//#if 0
//
//      unsigned int buffer[] =
//      {
//         16, 16,
//         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
//         32, 32,
//         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
//      };
//
//      xdisplay d(display());
//
//      int iScreen = DefaultScreen(d);
//
//      Atom net_wm_icon = d.intern_atom("_NET_WM_ICON", False);
//
//      Atom cardinal = d.intern_atom("CARDINAL", False);
//
//      int length = 2 + 16 * 16 + 2 + 32 * 32;
//
//      int status = XChangeProperty(d, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *)buffer, length);
//
//      if (status != 0)
//      {
//
//         return false;
//
//      }
//
//#elif 1
//
//      auto d1 = create_image({ 32, 32 });
//
//      if (!::is_ok(d1))
//      {
//
//         return false;
//
//      }
//
//      d1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
//
//      d1->g()->stretch(d1->rectangle(), pimage->g(), pimage->rectangle());
//
//      memory m(puserinteraction->get_application());
//
//      int length = 2 + d1->area();
//
//      m.set_size(length * 4);
//
//      unsigned int * pcr = (unsigned int *)m.get_data();
//
//      pcr[0] = d1->width();
//
//      pcr[1] = d1->height();
//
//      int c = d1->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + 2] = d1->colorref()[i];
//
//      }
//
//      windowing_output_debug_string("\nwindow::set_icon");
//
//      xdisplay d(display());
//
//      Atom net_wm_icon = intern_atom("_NET_WM_ICON", False);
//
//      Atom cardinal = intern_atom("CARDINAL", False);
//
//      int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *)pcr, length);
//
//      if (status == BadAlloc)
//      {
//
//
//      }
//      else if (status != 0)
//      {
//
//         return false;
//
//      }
//
//      windowing_output_debug_string("\nwindow::set_icon END");
//
//      fflush(stdout);
//
//#else
//
//      image d1(w->puserinteraction->create_new, this);
//
//      if (!d1->create(24, 24))
//      {
//
//         return false;
//
//      }
//
//      d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), int_point->get_graphics(), 0, 0, point.width(), point.height());
//
//      image d2(w->puserinteraction->create_new, this);
//
//      if (!d2->create(54, 54))
//      {
//
//         return false;
//
//      }
//
//      d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), int_point->get_graphics(), 0, 0, point.width(), point.height());
//
//      memory m(w->puserinteraction->get_application());
//
//      int length = 2 + d1->area() + 2 + d2->area();
//
//      m.set_size(length * 4);
//
//      unsigned int * pcr = (unsigned int *)m.get_data();
//
//      pcr[0] = d1.width();
//
//      pcr[1] = d1.height();
//
//      int c = d1->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + 2] = d1->m_pcolorref[i];
//
//      }
//
//      memsize o;
//
//      o = 2 + d1->area();
//
//      pcr[o] = d2.width();
//
//      pcr[o + 1] = d2.height();
//
//      c = d2->area();
//
//      for (int i = 0; i < c; i++)
//      {
//
//         pcr[i + o + 2] = d2->m_pcolorref[i];
//
//      }
//
//      Display * display = w->display();
//
//      Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
//
//      Atom cardinal = XInternAtom(display, "CARDINAL", False);
//
//      int status = XChangeProperty(display, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *)pcr, length);
//
//      if (status != 0)
//      {
//
//         //file_system()->put_contents("/home/camilo/window.txt", ::as_string((int)w->window()));
//         return false;
//
//      }
//#endif
//      return true;
//
//   }
//

   //int window::store_name(const ::scoped_string & scopedstr)
   //{

   //   windowing_output_debug_string("\nwindow::store_name");

   //   xdisplay d(display());

   //   int i = XStoreName(display(), window(), psz);

   //   windowing_output_debug_string("\nwindow::store_name END");

   //   return i;

   //}


   //int window::select_input(int iInput)
   //{

   //   windowing_output_debug_string("\nwindow::select_input");

   //   xdisplay d(display());

   //   int i = XSelectInput(display(), window(), iInput);

   //   windowing_output_debug_string("\nwindow::select_input END");

   //   return i;

   //}


   //int window::select_all_input()
   //{

   //   windowing_output_debug_string("\nwindow::select_all_input");

   //   xdisplay d(display());

   //   int i = select_input(ExposureMask | ButtonPressMask);

   //   windowing_output_debug_string("\nwindow::select_all_input");

   //   return i;

   //}


   //void window::destroy()
   //{


   //   WNDPROC pfnWndProc = WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC));

   //   if (WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC)) == pfnWndProc)
   //   {

   //      WNDPROC pfnSuper = *GetSuperWndProcAddr();

   //      if (pfnSuper != nullptr)
   //      {

   //         ::SetWindowLongPtr(get_hwnd(), GWLP_WNDPROC, reinterpret_cast<iptr>(pfnSuper));

   //      }

   //   }

   //   this->windowing()->erase_window(this);

   //   set_hwnd(nullptr);

   //   //if (!::is_null(this))
   //   //{

   //   //   oswindow_erase(display(), window());

   //   //}

   //   //m_pimpl2.release();

   //   ::windowing::window::destroy();

   //}
   //void window::destroy()
   //{


   //   WNDPROC pfnWndProc = WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC));

   //   if (WNDPROC(::GetWindowLongPtr(get_hwnd(), GWLP_WNDPROC)) == pfnWndProc)
   //   {

   //      WNDPROC pfnSuper = *GetSuperWndProcAddr();

   //      if (pfnSuper != nullptr)
   //      {

   //         ::SetWindowLongPtr(get_hwnd(), GWLP_WNDPROC, reinterpret_cast<iptr>(pfnSuper));

   //      }

   //   }

   //   this->windowing()->erase_window(this);

   //   set_hwnd(nullptr);

   //   //if (!::is_null(this))
   //   //{

   //   //   oswindow_erase(display(), window());

   //   //}

   //   //m_pimpl2.release();

   //   ::windowing::window::destroy();

   //}


   //::windowing::window * window::get_parent() const
   //{

   //   auto oswindow = get_parent_oswindow();

   //   auto pwindow = win32_windowing()->window(oswindow);

   //   return pwindow;

   //}


   //oswindow window::get_parent_oswindow() const
   //{

   //   auto hwnd = get_hwnd();

   //   auto hwndParent = ::GetParent(hwnd);

   //   auto oswindowParent = __oswindow(hwndParent);

   //   return oswindowParent;

   //}


   void window::set_parent(::windowing::window * pwindowParent)
   {

      auto hwnd = get_hwnd();

      HWND hwndParent = nullptr;

      if (::is_set(pwindowParent))
      {

         hwndParent = as_hwnd(pwindowParent->oswindow());

      }

      if (!::SetParent(hwnd, hwndParent))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder, const ::user::activation & useractivation, bool bNoZorder, ::e_display edisplay)
   {

      auto iShowWindow = windows::show_window(edisplay, useractivation);

      HWND hwnd = get_hwnd();

      //if (iShowWindow == SW_MAXIMIZE)
      //{

      //   if (_get_ex_style() & WS_EX_LAYERED)
      //   {

      //      iShowWindow = SW_NORMAL;

      //   }

      //}

      if (iShowWindow == SW_MAXIMIZE)
      {


         ::ShowWindow(hwnd, iShowWindow);

      }
      //{

      //   //return ::error_failed;

      //   throw ::exception(error_failed);

      //}

      ////return ::success;

      if (useractivation & ::user::e_activation_set_popup
         || useractivation & ::user::e_activation_for_context_menu)
      {

         _modify_style(0, WS_POPUP);

      }

      if (useractivation & ::user::e_activation_set_foreground)
      {

         ::SetForegroundWindow(hwnd);

         ::BringWindowToTop(hwnd);

      }


      return true;

   }


   void window::full_screen(const ::int_rectangle & rectangle)
   {

      //::int_rectangle rBest;

      //int iMonitor = best_xinerama_monitor(puserinteraction, rectangle, rBest);

      //windowing_output_debug_string("\n::window::full_screen 1");

      //xdisplay d(display());

      //if (d.is_null())
      //{

      //   windowing_output_debug_string("\n::window::full_screen 1.1");

      //   return;

      //}

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(display(), window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::full_screen 1.2");

      //   fflush(stdout);

      //   return;

      //}

      //::int_rectangle rWindow;

      //rWindow.left() = attr.x();
      //rWindow.top() = attr.y();
      //rWindow.right() = attr.x() + attr.width;
      //rWindow.bottom() = attr.y() + attr.height;

      //if (rBest != rWindow)
      //{

      //   puserinteraction->place(rBest);

      //   XMoveResizeWindow(d, m_window, rBest.left(), rBest.top(), rBest.width(), rBest.height());

      //}

      //if (attr.map_state == IsImpactable)
      //{

      //   mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);

      //}
      //else
      //{

      //   unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);

      //   XMapWindow(display(), window());

      //}

      //windowing_output_debug_string("\n::window::full_screen 2");

      //::fflush(stdout);

      //return ::success;

   }


   //void window::_user_post(const ::procedure & procedure)
   //{

   //   user_interaction()->_user_post(procedure);

   //}


   //void window::_main_post(const ::procedure & procedure)
   //{

   //   user_interaction()->_main_post(procedure);

   //}


   void window::exit_iconify()
   {

      //xdisplay d(display());

      //if (d.is_null())
      //{

      //   windowing_output_debug_string("\n::window::exit_iconify 1.1");

      //   return;

      //}

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(display(), window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_full_screen 1.2");

      //   fflush(stdout);

      //   return;

      //}

      //if (attr.map_state == IsImpactable)
      //{

      //   mapped_net_state_raw(false, d, window(), m_iScreen, intern_atom(net_wm_state_hidden, false), 0);

      //}

      //return ::success;

   }


   void window::exit_full_screen()
   {

      //xdisplay d(display());

      //if (d.is_null())
      //{

      //   windowing_output_debug_string("\n::window::exit_full_screen 1.1");

      //   return;

      //}

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(display(), window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_full_screen 1.2");

      //   fflush(stdout);

      //   return;

      //}

      //if (attr.map_state == IsImpactable)
      //{

      //   mapped_net_state_raw(false, d, window(), m_iScreen, intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

      //}

      //return ::success;

   }


   void window::exit_zoomed()
   {

      //synchronous_lock synchronouslock(x11_mutex());

      //xdisplay d(display());

      //if (d.is_null())
      //{

      //   windowing_output_debug_string("\n::window::exit_zoomed 1.1");

      //   return;

      //}

      //XWindowAttributes attr;

      //if (!XGetWindowAttributes(display(), window(), &attr))
      //{

      //   windowing_output_debug_string("\n::window::exit_zoomed 1.2");

      //   fflush(stdout);

      //   return;

      //}

      //if (attr.map_state == IsImpactable)
      //{

      //   mapped_net_state_raw(false, d, window(), m_iScreen,
      //      intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", false),
      //      intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", false));

      //}

      //return ::success;

   }


   void window::set_keyboard_focus()
   {

      information() << "set_keyboard_focus";

      HWND hwnd = get_hwnd();

      HWND hwndThreadPreviousFocus = ::SetFocus(hwnd);

      //{
      //   
      //   DWORD lasterror = ::GetLastError();
      //   //return ::error_failed;

      //   if (lasterror != NO_ERROR)
      //   {

      //      throw ::exception(error_failed);

      //   }

      //}

      //return ::success;

   }


   //::pointer<window>window::get_active_window()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void window::set_active_window()
   {

      information() << "set_active_window";

      HWND hwnd = get_hwnd();

      if (!::SetActiveWindow(hwnd))
      {

         //return ::error_failed;

         information() << "failed to window::set_active_window";

         //throw ::exception(error_failed);

      }

      //return ::success;

   }


   void window::bring_to_front()
   {

      HWND hwnd = get_hwnd();

      if (!::BringWindowToTop(hwnd))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   void window::switch_to_this_window(bool b)
   {

      HWND hwnd = get_hwnd();

      ::SwitchToThisWindow(hwnd, b ? TRUE : FALSE);

   }


   void window::set_mouse_capture()
   {
      
      ::win32::acme::windowing::window::set_mouse_capture();

   }


   void window::release_mouse_capture()
   {

      ::win32::acme::windowing::window::release_mouse_capture();

   }


   bool window::has_mouse_capture()
   {

      return ::win32::acme::windowing::window::has_mouse_capture();

   }


   bool window::has_keyboard_focus()
   {

      auto itask = get_itask();

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      HWND hwndFocus;

      if (GetGUIThreadInfo((DWORD)itask.m_i, &info))
      {

         hwndFocus = info.hwndFocus;

      }
      else
      {

         hwndFocus = ::GetFocus();

      }

      if (hwndFocus == get_hwnd())
      {

         if (::GetForegroundWindow() == hwndFocus)
         {

            return true;

         }

      }

      return false;

   }


   bool window::is_active_window()
   {

      itask itask;

      auto puserinteraction = user_interaction();

      if (puserinteraction && puserinteraction->user_thread())
      {

         itask = puserinteraction->user_thread()->get_itask();

      }

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      HWND hwndActive;

      if (GetGUIThreadInfo((DWORD)itask.m_i, &info))
      {

         hwndActive = info.hwndActive;

      }
      else
      {

         hwndActive = ::GetActiveWindow();

      }

      if (hwndActive == get_hwnd())
      {

         return true;

      }

      //auto puserinteraction = psystem->ui_from_handle(oswindowActive);

      //if (::is_set(puserinteraction))
      //{

      //   if (puserinteraction->user_thread() == puserinteraction->user_thread())
      //   {

      //      if (puserinteraction->m_ewindowflag & e_window_flag_satellite_window)
      //      {

      //         return true;

      //      }

      //   }

      //}

      return false;

   }


   //void window::start_destroying_window()
   //{

   //   if (!m_bUserImplCreated)
   //   {

   //      return;

   //   }

   //   m_bUserImplCreated = false;

   ////   if (m_puserinteraction == nullptr && !m_bDestroyImplOnly)
   ////   {

   ////      return;

   ////   }

   ////   //::pointer<::windowing::window>pimplThis = this;

   ////   //::pointer<::user::interaction>puiThis = m_puserinteraction;

   ////   //if (puiThis)
   ////   //{

   ////   //   try
   ////   //   {

   ////   //      puiThis->send_message(e_message_destroy);

   ////   //   }
   ////   //   catch (...)
   ////   //   {

   ////   //   }

   ////   //   try
   ////   //   {

   ////   //      puiThis->send_message(e_message_non_client_destroy);

   ////   //   }
   ////   //   catch (...)
   ////   //   {

   ////   //   }

   ////   //}

   ////   ////return true;

   ////}


   void window::destroy_window()
   {

      if (has_destroying_flag())
      {

         return;

      }

      auto puserinteraction = user_interaction();

      ::string strType = ::type(puserinteraction).name();

      set_destroying_flag();

      main_send()
         << [this, strType]()
         {

            if (::IsWindowVisible(m_hwnd))
            {

               ::ShowWindow(m_hwnd, SW_HIDE);

            }

            if (m_pgraphicsthread)
            {

               m_pgraphicsthread->stop_task();

            }

            HWND hwnd = get_hwnd();

            if (!::DestroyWindow(hwnd))
            {

               DWORD dwLastError = ::GetLastError();
               //return ::error_failed;

               throw ::exception(error_failed);

            }

            //return ::success;

            ::windowing::window::destroy_window();

         };

   }


   //void window::show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation)
   //{

   //   int nCmdShow = windows_show_window(edisplay, useractivation);

   //   if(!::XXXShowWindow(get_hwnd(), nCmdShow))
   //   {

   //      return ::error_failed;

   //   }

   //   return ::success;

   //}


   iptr window::_get_window_long_ptr(int nIndex) const
   {

      HWND hwnd = get_hwnd();

      auto iptr = GetWindowLongPtr(hwnd, nIndex);

      return iptr;

   }


   bool window::_set_window_position_unlocked(
      const class ::zorder & zorderParam,
      int xParam,
      int yParam,
      int cxParam,
      int cyParam,
      const ::user::activation & useractivationParam,
      bool bNoZorderParam,
      bool bNoMoveParam,
      bool bNoSizeParam,
      ::e_display edisplayParam)
   {

      if (!is_window())
      {

         return false;

      }

      auto puserinteraction = user_interaction();

      auto hwnd = get_hwnd();
      auto zorder = zorderParam;
      auto x = xParam;
      auto y = yParam;
      auto cx = cxParam;
      auto cy = cyParam;
      auto useractivation = useractivationParam;
      auto bNoZorder = bNoZorderParam;
      auto bNoMove = bNoMoveParam;
      auto bNoSize = bNoSizeParam;
      auto edisplay = edisplayParam;

      bool bOk = false;

      main_send([
         this,
            hwnd,
            zorder,
            x,
            y,
            cx,
            cy,
            useractivation,
            bNoZorder,
            bNoMove,
            bNoSize,
            edisplay,
      &bOk]()
         {

            if (!is_window())
            {

               return;

            }

            information() << "windowing_win32::window::_set_window_position_unlocked";

            ::e_display edisplayOutput = e_display_none;

            ::e_display edisplayWindow = e_display_none;

            if (::IsWindowVisible(hwnd))
            {

               if (::IsIconic(hwnd))
               {

                  edisplayWindow = e_display_iconic;

               }
               else if (::IsZoomed(hwnd))
               {

                  edisplayWindow = e_display_zoomed;

               }
               else
               {

                  edisplayWindow = e_display_normal;

               }

            }

            if (edisplay == e_display_iconic)
            {

               edisplayOutput = edisplay;

            }
            else if (edisplay == e_display_notify_icon)
            {

               edisplayOutput = edisplay;

            }
            else if (edisplay == e_display_zoomed)
            {

               edisplayOutput = edisplay;

            }
            else if (windowing()->is_screen_visible(edisplay))
            {

               edisplayOutput = e_display_normal;

            }

            if (!is_equivalent_in_equivalence_sink(edisplayOutput, edisplayWindow))
            {

               //bool bToolWindow = (edisplayOutput == e_display_notify_icon);

               //if (is_different(bToolWindow, is_tool_window()))
               //{

               //   bool bShowTask = !bToolWindow;

               //   show_task(bShowTask);

               //}

               if (is_equivalent_in_equivalence_sink(edisplayOutput, e_display_normal))
               {

                  if (edisplayWindow == e_display_zoomed)
                  {

                     ::ShowWindow(hwnd, SW_RESTORE);

                  }
                  else
                  {

                     if (useractivation & ::user::e_activation_set_active
                     || useractivation & ::user::e_activation_set_foreground
                     || useractivation & ::user::e_activation_on_center_of_screen)
                     {

                        if (::IsZoomed(hwnd) 
                           || ::IsIconic(hwnd)
                           || !::IsWindowVisible(hwnd))
                        {

                           ::ShowWindow(hwnd, SW_NORMAL);

                        }

                     }
                     else
                     {

                        if (
                           ::IsZoomed(hwnd) 
                           || ::IsIconic(hwnd)
                           || !::IsWindowVisible(hwnd))
                        {

                           ::ShowWindow(hwnd, SW_SHOWNOACTIVATE);

                        }

                     }

                  }

               }
               else if (edisplayOutput == e_display_zoomed)
               {

                  ::ShowWindow(hwnd, SW_MAXIMIZE);

               }
               else if (edisplayOutput == e_display_iconic)
               {

                  ::ShowWindow(hwnd, SW_MINIMIZE);

               }
               else if (edisplayOutput == e_display_notify_icon)
               {

                  ::ShowWindow(hwnd, SW_HIDE);

                  //bToolWindow = false;

               }
               else
               {

                  ::ShowWindow(hwnd, SW_HIDE);

               }

            }

            bool bShow = windowing()->is_screen_visible(edisplayOutput) || edisplay == e_display_iconic;

            bool bHide = !windowing()->is_screen_visible(edisplayOutput) && edisplay != e_display_iconic;

            ::string strType;

            auto puserinteraction = user_interaction();

            strType = ::type(puserinteraction).name();

            if (strType.contains("list_box"))
            {

               output_debug_string("list_box");

            }

            bOk = __set_window_position(
               zorder, x, y, cx, cy,
               useractivation, bNoZorder, bNoMove, bNoSize,
               bShow, bHide);


});

      return bOk;

   }


   void window::_set_window_position_unchanged()
   {

      if (_get_ex_style() & WS_EX_LAYERED)
      {

         // If the window is layered, SetWindowPos gonna be called
         // very close to UpdateLayeredWindow call.

         m_uSetWindowPosLastFlags = m_uExtraFlagsSetWindowPos;

      }

   }


   bool window::_set_window_long_ptr(int nIndex, iptr i)
   {

      HWND hwnd = get_hwnd();

      SetWindowLongPtr(hwnd, nIndex, i);

      return true;

   }


   bool window::client_to_screen(::int_point * ppoint)
   {

      HWND hwnd = get_hwnd();

      ClientToScreen(hwnd, (POINT *)ppoint);

      return true;

   }


   bool window::screen_to_client(::int_point * ppoint)
   {

      HWND hwnd = get_hwnd();

      ScreenToClient(hwnd, (POINT *)ppoint);

      return true;

   }


   //   bool window::strict_set_window_position_unlocked()
   //   {
   //
   //
   //      int_rectangle rectangleWindowCurrent;
   //
   //      GetWindowRect(get_hwnd(), (RECT *)&rectangleWindowCurrent);
   //
   //      //               }
   //                     //else
   //                     //{
   //
   //                     //   informationf("Update discarded");
   //
   //                     //}
   //
   //
   //                     //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
   //                     //{
   //
   //
   //
   //
   //      UINT uFlagsSetWindowPos = SWP_NOZORDER
   //         | SWP_ASYNCWINDOWPOS
   //         //| SWP_FRAMECHANGED
   //         //| SWP_NOSENDCHANGING
   //         | SWP_NOREDRAW
   //         | SWP_NOCOPYBITS
   //         //| SWP_DEFERERASE
   //         //| SWP_NOACTIVATE
   //         | SWP_SHOWWINDOW;
   //
   //      /*             if (!::IsWindowVisible(hwnd))
   //                   {
   //
   //                      warning() << "Window is not visible!!";
   //
   //                   }*/
   //
   //                   //::procedure p = [&, this]()
   //                   //   {
   //
   //      bool bSetWindowPos = false;
   //
   //      if (rectangleWindowCurrent.top_left() != point
   //|| rectangleWindowCurrent.size() != size
   //|| m_pimpl->user_interaction()->const_layout().design().has_activation_request())
   //      {
   //
   //         ::pointer < ::windowing_win32::window > pwindow;
   //
   //         pwindow = m_pimpl->m_pwindow;
   //
   //         __set_window_position(
   //            m_pimpl->user_interaction()->const_layout().design().zorder(),
   //            point.x(),
   //            point.y(),
   //            size.cx(),
   //            size.cy(),
   //            m_pimpl->user_interaction()->const_layout().design().activation(),
   //            true, false, false, true, false,
   //            uFlagsSetWindowPos);
   //
   //         bSetWindowPos = true;
   //
   //         bSizeOrPositionChanged = true;
   //
   //         m_pimpl->user_interaction()->reset_pending();
   //
   //
   //      }
   //
   //      if (bSetWindowPos)
   //      {
   //
   //         //::Sleep(4);
   //
   //      }
   //
   //      //::GdiFlush();
   //
   //      if (::IsWindowVisible(hwnd))
   //      {
   //
   //         ::UpdateLayeredWindow(hwnd, m_hdcScreen, (POINT *)&point, (SIZE *)&size, playeredwindowbuffer->m_hdc, (POINT *)&pointSrc, make_unsigned_int(0, 0, 0, 0), &blendPixelFunction, ULW_ALPHA);
   //
   //      }
   //
   //      //::GdiFlush();
   //
   //      if (bSetWindowPos)
   //      {
   //
   //         //::Sleep(8);
   //
   //      }
   //
   //   }


      //long window::get_state()
      //{

      //   windowing_output_debug_string("\n::window::get_state 1");

      //   xdisplay d(display());

      //   static const long WM_STATE_ELEMENTS = 2L;

      //   unsigned long nitems = 0;

      //   unsigned long leftover = 0;

      //   Atom atomWmState = 0;

      //   Atom actual_type = 0;

      //   int actual_format = 0;

      //   int status = 0;

      //   unsigned char * point = nullptr;

      //   if (d.m_pdata->m_atomWmState == None)
      //   {

      //      d.m_pdata->m_atomWmState = d.intern_atom("WM_STATE", false);

      //   }

      //   atomWmState = d.m_pdata->m_atomWmState;

      //   status = XGetWindowProperty(d, m_window, atomWmState, 0L, WM_STATE_ELEMENTS, False, AnyPropertyType, &actual_type,
      //      &actual_format, &nitems, &leftover, &point);

      //   if (status == 0)
      //   {

      //      long lStatus = -1;

      //      if (point != nullptr)
      //      {

      //         lStatus = (long)*int_point;

      //      }

      //      XFree(point);

      //      windowing_output_debug_string("\n::window::get_state 1.1");

      //      return lStatus;

      //   }

      //   windowing_output_debug_string("\n::window::get_state 2");

      //   return -1;

      //}


      //bool window::is_iconic()
      //{

      //   HWND hwnd = get_hwnd();

      //   auto bIconic = ::IsIconic(hwnd);

      //   return bIconic != FALSE;

      //}


   bool window::is_window()
   {

      HWND hwnd = get_hwnd();

      auto bWindow = ::IsWindow(hwnd);

      return bWindow != FALSE;

   }


   bool window::is_window_visible()
   {

      HWND hwnd = get_hwnd();

      auto bWindowVisible = ::IsWindowVisible(hwnd);

      return bWindowVisible != FALSE;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      //if (m_pwindow == nullptr)
      //{

      //   return true;

      //}

      auto puserinteraction = user_interaction();

      if (!puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


   //bool window::on_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::e_activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   //{

   //   //if (!(_get_ex_style() & WS_EX_LAYERED))
   //   {

   //      ::windowing::window::on_set_window_position(zorder, x, y, cx, cy, useractivation, 
   //         bNoZorder, bNoMove, bNoSize, bShow, bHide);

   //   }

   //   return false;

   //}


#undef SET_WINDOW_POS_LOG
   //::int_rectangle get_task_bar_rectangle() {
   //   APPBARDATA abd = { 0 };
   //   abd.cbSize = sizeof(abd);
   //   if (!::SHAppBarMessage(ABM_GETTASKBARPOS, &abd)) {
   //      throw ::exception(error_failed, "SHAppBarMessage failed.");
   //   }
   //   return abd.rc;
   //}

   class task_bar :
      virtual public ::particle
   {
   public:

      HWND                    m_hwnd;
      int_rectangle           m_rectangle;
      bool                    m_bSecondary;
      ::windowing::monitor *  m_pmonitor;

   };

   class task_bar_array :
      virtual public ::pointer_array < task_bar >
   {
   public:

      task_bar_array(::windowing::display * pdisplay)
      {

         ::EnumWindows(&task_bar_array::enum_window, (LPARAM) (iptr) (void *) this);

         fill_monitor(pdisplay);

      }

      static BOOL enum_window(HWND hwnd, LPARAM lparam)
      {

         char sz[256];

         GetClassNameA(hwnd, sz, sizeof(sz));

         if (strcmp(sz, "Shell_TrayWnd") == 0)
         {

            auto ptaskbara = (task_bar_array *)lparam;

            ptaskbara->a_task_bar_question(hwnd, false);

         }
         else if (strcmp(sz, "Shell_SecondaryTrayWnd") == 0)
         {

            auto ptaskbara = (task_bar_array *)lparam;

            ptaskbara->a_task_bar_question(hwnd, true);

         }

         return TRUE;

      }


      void a_task_bar_question(HWND hwnd, bool bSecondary)
      {

         RECT r;

         if (GetWindowRect(hwnd, &r))
         {

            auto ptaskbar = __create_new < task_bar >();

            ptaskbar->m_hwnd = hwnd;

            ptaskbar->m_rectangle = r;

            this->add(ptaskbar);

         }

      }


      void fill_monitor(::windowing::display * pdisplay)
      {

         for (auto & ptaskbar : *this)
         {

            ptaskbar->m_pmonitor = pdisplay->get_best_monitor(ptaskbar->m_rectangle);

         }

      }


      task_bar * get_best_task_bar(const int_rectangle & rectangle)
      {

         int iArea = 0;
         ::collection::index iFound = -1;

         for (::collection::index i = 0; i < this->get_count(); i++)
         {

            ::int_rectangle rIntersect;

            auto ptaskbar = this->element_at(i);

            rIntersect.intersect(ptaskbar->m_pmonitor->m_rectangle, rectangle);

            if (rIntersect.area() > iArea)
            {

               iArea = rIntersect.area();

               iFound = i;

            }

         }

         if (iFound < 0)
         {

            return nullptr;

         }

         return this->element_at(iFound);

      }


   };



   bool window::__set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy, const ::user::activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide, unsigned int nOverrideFlags)
   {

      if (m_bSizeMoveMode)
      {

         return true;

      }

      if (!is_window())
      {

         return false;

      }

      information() << "windowing_win32::window::__set_window_position";

      HWND hwnd = get_hwnd();

      auto pwin32windowing = win32_windowing();

      HWND hwndInsertAfter = pwin32windowing->zorder_to_hwnd(zorder);

      UINT nFlags = m_uExtraFlagsSetWindowPos;

      if (zorder.is_change_request())
      {

         nFlags &= ~SWP_NOZORDER;

      }


      if (useractivation & ::user::e_activation_set_active)
      {

         nFlags &= ~SWP_NOACTIVATE;

      }
      else
      {

         nFlags |= SWP_NOACTIVATE;

      }

      if (bNoZorder)
      {

         nFlags |= SWP_NOZORDER;

      }

      if (bNoMove || bHide)
      {

         nFlags |= SWP_NOMOVE;

      }

      if (bNoSize || bHide)
      {

         nFlags |= SWP_NOSIZE;

      }

      if (bShow)
      {

         nFlags |= SWP_SHOWWINDOW;
         nFlags &= ~SWP_HIDEWINDOW;

      }
      else if (bHide)
      {

         nFlags |= SWP_HIDEWINDOW;
         nFlags &= ~SWP_SHOWWINDOW;

      }


      //if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LAYERED)
      //{

      //   nFlags |= SWP_NOMOVE;

      //   nFlags |= SWP_NOSIZE;

      //}

      if (_get_ex_style() & WS_EX_LAYERED)
      {

         // If the window is layered, SetWindowPos gonna be called
         // very close to UpdateLayeredWindow call.

         m_uSetWindowPosLastFlags = nFlags;

         m_hwndSetWindowPosLastInsertAfter = hwndInsertAfter;

         m_activationSetWindowPosLast = useractivation;

         return true;

      }

      information() << "::SetWindowPos " << ::int_rectangle_dimension(x, y, cx, cy);

      if (!(nFlags & SWP_NOMOVE))
      {

         m_pointWindow.x() = x;

         m_pointWindow.y() = y;

      }

      if (!(nFlags & SWP_NOSIZE))
      {

         m_sizeWindow.cx() = cx;

         m_sizeWindow.cy() = cy;

      }

      if (useractivation & ::user::e_activation_set_popup
         || useractivation & ::user::e_activation_for_context_menu)
      {

         _modify_style(0, WS_POPUP);

         nFlags |= SWP_FRAMECHANGED;

         nFlags &= ~SWP_NOACTIVATE;

         nFlags &= ~SWP_NOREDRAW;

         nFlags &= ~SWP_NOCOPYBITS;

         nFlags &= ~SWP_ASYNCWINDOWPOS;

      }

      //if (useractivation.eflag() & ::user::e_activation_for_context_menu)
      //{

      //   int bottom = y + cy;

      //   auto rectangle = ::int_rectangle_dimension(x, y, cx, cy);

      //   task_bar_array taskbara(windowing()->display());

      //   auto ptaskbar = taskbara.get_best_task_bar(rectangle);

      //   int iBottomTaskBar = ptaskbar->m_rectangle.bottom();

      //   int iBottomMonitor = ptaskbar->m_pmonitor->m_rectangle.bottom();

      //   if (iBottomTaskBar == iBottomMonitor)
      //   {

      //      if (bottom > ptaskbar->m_rectangle.top())
      //      {

      //         bottom = ptaskbar->m_rectangle.top() - 16;

      //         y = bottom - cy;

      //      }

      //   }

      //}

      auto bSetWindowPos = ::SetWindowPos(
         hwnd, hwndInsertAfter,
         x, y, cx, cy, nFlags);

      if (useractivation & ::user::e_activation_set_foreground)
      {

         information() << "__set_window_position SetForegroundWindow BringWindowToTop SetActiveWindow";

         ::SetForegroundWindow(hwnd);

         ::BringWindowToTop(hwnd);

         ::SetActiveWindow(hwnd);

      }

      return bSetWindowPos != FALSE;

   }


   ////bool window::_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::e_activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide, unsigned int nOverrideFlags)
   //bool window::_configure_window_unlocked(const class ::zorder & zorder, const ::user::e_activation & useractivation, bool bNoZorder, ::e_display edisplay)
   //{

   //   //::int_rectangle rectangle;

   //   //rectangle.left() = x;
   //   //rectangle.top() = y;
   //   //rectangle.set_width(cx);
   //   //rectangle.set_height(cy);

   //   //placement_log()->add(rectangle);

   //   //if (nOverrideFlags == 0)
   //   //{

   //   //   if (bNoMove)
   //   //   {

   //   //      nOverrideFlags |= SWP_NOMOVE;

   //   //   }

   //   //   if (bNoSize)
   //   //   {

   //   //      nOverrideFlags |= SWP_NOSIZE;

   //   //   }

   //   //   if (bNoZorder)
   //   //   {

   //   //      nOverrideFlags |= SWP_NOZORDER;

   //   //   }

   //   //   if (bShow)
   //   //   {

   //   //      nOverrideFlags |= SWP_SHOWWINDOW;

   //   //   }

   //   //   if (bHide)
   //   //   {

   //   //      nOverrideFlags |= SWP_HIDEWINDOW;

   //   //   }

   //   //}

   //   //if (useractivation.eflag() & ::user::e_activation_no_activate)
   //   //{

   //   //   nOverrideFlags |= SWP_NOACTIVATE;

   //   //}

   //   //if (useractivation.eflag() & ::user::e_activation_set_popup)
   //   //{

   //   //   _modify_style(0, WS_POPUP);

   //   //}


   //   HWND hwnd = get_hwnd();

   //   ::pointer < class windowing > pwindowing = this->windowing();

   //   HWND hwndZorder = pwindowing->zorder_to_hwnd(zorder);

   //   //if (hwndZorder != nullptr)
   //   //{

   //   //   nOverrideFlags &= ~SWP_NOZORDER;

   //   //}

   //   /*bool bIsWindowVisible = ::IsWindowVisible(hwnd);

   //   if (!(GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LAYERED)
   //      || (bIsWindowVisible && bHide)
   //      || !(bIsWindowVisible && bShow))
   //   {

   //      ::SetWindowPos(hwnd, hwndZorder, x, y, cx, cy, nOverrideFlags);

   //   }*/

   //   if (useractivation & ::user::e_activation_set_foreground)
   //   {

   //      ::SetForegroundWindow(hwnd);

   //      ::BringWindowToTop(hwnd);

   //   }

   //   //user_interaction()->set_position({x, y}, ::user::e_layout_window);
   //   //user_interaction()->set_size({ cx, cy }, ::user::e_layout_window);

   //   return true;

   //}

//
//      synchronous_lock synchronouslock(x11_mutex());
//
//      windowing_output_debug_string("\n::window::set_window_position 1");
//
//      auto pdisplay = display();
//
//      xdisplay d(pdisplay);
//
//      XWindowAttributes attrs = {};
//
//      Window w = window();
//
//      if (!XGetWindowAttributes(pdisplay, w, &attrs))
//      {
//
//         windowing_output_debug_string("\n::window::set_window_position 1.1 xgetwindowattr failed");
//
//         return false;
//
//      }
//
//      if (nFlags & SWP_SHOWWINDOW)
//      {
//
//         if (attrs.map_state == IsUnmapped)
//         {
//
//            windowing_output_debug_string("\n::window::set_window_position Mapping Window 1.2");
//
//            XMapWindow(display(), window());
//
//         }
//
//         if (!XGetWindowAttributes(display(), window(), &attrs))
//         {
//
//            windowing_output_debug_string("\n::window::set_window_position 1.3 xgetwindowattr failed");
//
//            return false;
//
//         }
//
//      }
//
//      bool bMove = !(nFlags & SWP_NOMOVE);
//
//      bool bSize = !(nFlags & SWP_NOSIZE);
//
//      if (bMove)
//      {
//
//         if (bSize)
//         {
//
//            windowing_output_debug_string("\n::window::set_window_position Move Resize Window 1.4");
//
//#ifdef SET_WINDOW_POS_LOG
//
//            information() << "XMoveResizeWindow (%d, %d) - (%d, %d)", x, y, cx, cy;
//
//#endif
//
//            if (cx <= 0 || cy <= 0)
//            {
//
//               cx = 1;
//
//               cy = 1;
//
//#ifdef SET_WINDOW_POS_LOG
//
//               information() << "Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy;
//
//#endif
//
//            }
//
//            XMoveResizeWindow(display(), window(), x, y, cx, cy);
//
//         }
//         else
//         {
//
//            windowing_output_debug_string("\n::window::set_window_position Move Window 1.4.1");
//
//            XMoveWindow(display(), window(), x, y);
//
//         }
//
//      }
//      else if (bSize)
//      {
//
//         windowing_output_debug_string("\n::window::set_window_position Resize Window 1.4.2");
//
//         XResizeWindow(display(), window(), cx, cy);
//
//      }
//
//      //   if(bMove || bSize)
//      //   {
//      //
//      //      if(attrs.override_redirect)
//      //      {
//      //
//      //         if(!(puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
//      //         {
//      //
//      //            XSetWindowAttributes set;
//      //
//      //            set.override_redirect = False;
//      //
//      //            if(!XChangeWindowAttributes(display(), window(), CWOverrideRedirect, &set))
//      //            {
//      //
//      //               information() << "linux::window::_native_create_window_ex failed to clear override_redirect";
//      //
//      //            }
//      //
//      //         }
//      //
//      //      }
//      //
//      //   }
//
//
//      if (nFlags & SWP_HIDEWINDOW)
//      {
//
//         if (attrs.map_state == IsImpactable)
//         {
//
//            windowing_output_debug_string("\n::window::set_window_position Withdraw Window 1.4.3");
//
//            XWithdrawWindow(display(), window(), m_iScreen);
//
//         }
//
//      }
//
//      if (!XGetWindowAttributes(display(), window(), &attrs))
//      {
//
//         windowing_output_debug_string("\n::window::set_window_position xgetwndattr 1.4.4");
//
//         return false;
//
//      }
//
//      if (attrs.map_state == IsImpactable || (nFlags & SWP_SHOWWINDOW))
//      {
//
//         if (!(nFlags & SWP_NOZORDER))
//         {
//
//            if (zorder.m_ezorder == e_zorder_top_most)
//            {
//
//               if (m_iaNetWmState[net_wm_state_above] != 1)
//               {
//
//                  wm_state_above_raw(this, true);
//
//               }
//
//               XRaiseWindow(display(), window());
//
//            }
//            else if (zorder.m_ezorder == e_zorder_top)
//            {
//
//               if (m_iaNetWmState[net_wm_state_above] != 0
//                  || m_iaNetWmState[net_wm_state_below] != 0
//                  || m_iaNetWmState[net_wm_state_hidden] != 0
//                  || m_iaNetWmState[net_wm_state_maximized_horz] != 0
//                  || m_iaNetWmState[net_wm_state_maximized_vert] != 0
//                  || m_iaNetWmState[net_wm_state_fullscreen] != 0)
//               {
//
//                  wm_state_clear_raw(this, false);
//
//               }
//
//               XRaiseWindow(display(), window());
//
//            }
//            else if (zorder.m_ezorder == e_zorder_bottom)
//            {
//
//               if (m_iaNetWmState[net_wm_state_below] != 1)
//               {
//
//                  wm_state_below_raw(this, true);
//
//               }
//
//               XLowerWindow(display(), window());
//
//            }
//
//         }
//
//         puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
//
//      }
//      else
//      {
//
//         puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
//
//      }
//
//      //on_change_visibility();
//
//      windowing_output_debug_string("\n::window::set_window_position 2");
//
//      return 1;
//
//   }


   void window::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (m_bSizeMoveMode)
      {

         return;

      }

      ::windowing::window::set_mouse_cursor(pcursor);

      windowing()->set_mouse_cursor2(pcursor);

      //HCURSOR hcursor = nullptr;
      //
      //if (::is_set(pcursor))
      //{

      //   hcursor = (HCURSOR)pcursor->get_os_data();

      //   if (hcursor == nullptr)
      //   {

      //      //auto estatus = 
      //      
      //      pcursor->_create_os_cursor();

      //      //if (!estatus)
      //      //{

      //      //   return estatus;

      //      //};

      //      hcursor = (HCURSOR)pcursor->get_os_data();

      //      //if (!hcursor)
      //      //{

      //      //   return error_resource;

      //      //}

      //   }

      //}

      //// At windows SetMouseCursor(nullptr) removes the cursor from screen
      //// similar apis in other platforms behave the same?

      //if (!::SetCursor(hcursor))
      //{

      //   throw ::exception(error_failed);

      //}

      ////return ::success;

   }


   //::int_point window::get_mouse_cursor_host_position()
   //{

   //   POINT point;

   //   ::GetCursorPos(&point);

   //   ::ScreenToClient(get_hwnd(), &point);

   //   ::int_point int_point;

   //   int_point.x() = point.x;

   //   int_point.y() = point.y;

   //   return int_point;

   //}
   //

   //::int_point window::get_mouse_cursor_absolute_position()
   //{

   //   POINT point;

   //   ::GetCursorPos(&point);

   //   ::int_point int_point;

   //   int_point.x() = point.x;

   //   int_point.y() = point.y;

   //   return int_point;

   //}


   //bool window::reset(::windowing::cursor * pcursor, ::aura::session * psession)
   //{

   //   synchronous_lock synchronouslock(psession->synchronization());

   //   if (::is_null(puserinteraction))
   //   {

   //      return false;

   //   }

   //   App(puserinteraction).window_set_mouse_cursor(puserinteraction->get_hwnd(), 0);

   //   return true;

   //}


   //void window::message_handler(::message::message * pmessage)
   //{
   //   
   //   if (pmessage->m_emessage == (enum_message)WM_SYSCOMMAND)
   //   {

   //      if (pmessage->m_wparam == SC_SCREENSAVE)
   //      {

   //         auto puserinteraction = user_interaction();

   //         if (puserinteraction && !puserinteraction->_001CanEnterScreenSaver())
   //         {

   //            pmessage->m_bRet = true;

   //            pmessage->m_lresult = 0;

   //         }

   //         return;

   //      }
   //      else if (pmessage->m_wparam == SC_MAXIMIZE)
   //      {

   //         auto puserinteraction = user_interaction();

   //         if (puserinteraction && !puserinteraction->_001Maximize())
   //         {

   //            pmessage->m_bRet = true;

   //            pmessage->m_lresult = 0;

   //         }

   //         return;
   //      }
   //      else if (pmessage->m_wparam == SC_RESTORE)
   //      {

   //         auto puserinteraction = user_interaction();

   //         if (puserinteraction && !puserinteraction->_001Restore())
   //         {

   //            pmessage->m_bRet = true;

   //            pmessage->m_lresult = 0;

   //         }

   //         return;
   //      }

   //   }

   //   auto puserinteraction = user_interaction();

   //   if (puserinteraction)
   //   {

   //      puserinteraction->message_handler(pmessage);

   //   }

   //}


//   int_bool window::set_mouse_cursor(hwnd window, hcursor hcursor)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      __UNREFERENCED_PARAMETER(window);
//
//      if (!::SetCursor(hcursor))
//      {
//
//         return false;
//
//      }
//
//#endif
//
//      return true;
//
//   }


   bool window::get_window_placement(WINDOWPLACEMENT * puserinteractionpl)
   {

      puserinteractionpl->length = sizeof(WINDOWPLACEMENT);

      return ::GetWindowPlacement(get_hwnd(), puserinteractionpl) != false;

   }


   bool window::set_window_placement(const WINDOWPLACEMENT * puserinteractionpl)
   {

      auto puserinteraction = user_interaction();

      synchronous_lock synchronouslock(puserinteraction->synchronization());

      ASSERT(::IsWindow(get_hwnd()));

      ((WINDOWPLACEMENT *)puserinteractionpl)->length = sizeof(WINDOWPLACEMENT);

      return ::SetWindowPlacement(get_hwnd(), puserinteractionpl) != false;

   }


   void window::set_foreground_window(::user::activation_token * puseractivationtoken)
   {

      return _set_foreground_window_unlocked(puseractivationtoken);

   }


   void window::_set_foreground_window_unlocked(::user::activation_token * puseractivationtoken)
   {

      bool bPosted = false;

      if (puseractivationtoken)
      {

         ::cast < ::win32::acme::windowing::activation_token > pactivationtoken = puseractivationtoken;

         if (pactivationtoken)
         {

            pactivationtoken->m_ptaskForeground->post([this]()
            {

               HWND hwnd = get_hwnd();

               ::SetForegroundWindow(hwnd);

            });

            bPosted = true;

         }

      }

      if (!bPosted)
      {

         HWND hwnd = get_hwnd();

         ::SetForegroundWindow(hwnd);

      }

      //// special activate logic for floating toolbars and palettes
      //auto pActiveWnd = GetForegroundWindow();

      //if (!pActiveWnd || !((pActiveWnd)->get_hwnd() == get_hwnd() || ::IsChild((pActiveWnd)->get_hwnd(), get_hwnd())))
      //{
      //   // clicking on floating frame when it does not have
      //   // focus itself -- activate the toplevel frame instead.

      //   auto puserinteractionTopLevel = get_top_level();

      //   if (puserinteractionTopLevel)
      //   {

      //      puserinteractionTopLevel->set_foreground_window();

      //   }

   }



   void window::_001OnSysCommand(::message::message * pmessage)
   {

      auto wparam = pmessage->m_wparam;

      if (wparam == SC_SCREENSAVE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction && !puserinteraction->_001CanEnterScreenSaver())
         {

            pmessage->m_bRet = true;

            pmessage->m_lresult = 0;

         }

         return;

      }
      else if (wparam == SC_MAXIMIZE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {
            puserinteraction->_001Maximize();

            pmessage->m_bRet = true;

            pmessage->m_lresult = 0;

         }

         return;

      }
      else if (wparam == SC_CLOSE)
      {

         post_message(e_message_close);

      }
      else if (wparam == SC_RESTORE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            puserinteraction->on_display_restore(pmessage->user_activation_token());

         }

         pmessage->m_bRet = true;

         pmessage->m_lresult = 0;

         return;

      }
      else if (wparam == SC_TASKLIST)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            puserinteraction->on_display_task_list(pmessage->user_activation_token());

         }

         pmessage->m_bRet = true;

         pmessage->m_lresult = 0;

         return;

      }
      else if (wparam == SC_MINIMIZE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            //if (puserinteraction->layout().m_statea[::user::e_layout_normal].m_bAutoRefresh)
            {

               // puserinteraction->clear_prodevian();

            }

            //if (puserinteraction->layout().m_statea[::user::e_layout_normal].display() == e_display_zoomed)
            //{

            //   puserinteraction->_001Maximize();

            //}
            //else
            //{

            puserinteraction->on_system_command(e_system_command_minimize);

            //            }

            pmessage->m_bRet = true;

            pmessage->m_lresult = 0;

         }

         return;

      }
      else if (wparam == SC_MOVE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            puserinteraction->m_ekeyboardmode = ::user::e_keyboard_mode_reposition;

            puserinteraction->set_keyboard_focus();

         }

      }
      else if (wparam == SC_SIZE)
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            puserinteraction->m_ekeyboardmode = ::user::e_keyboard_mode_resize;

            puserinteraction->set_keyboard_focus();

         }

      }
      else if (wparam == 123)
      {

         application()->show_about_box(pmessage->user_activation_token());

      }

   }

   void window::_001OnPaint(::message::message * pmessage)
   {

      //HideCaret();

      //PAINTSTRUCT ps;
      //HDC hdc1 = BeginPaint(m_oswindow, &ps);
      //// TODO: Add any drawing code that uses hdc here...
      //EndPaint(m_oswindow, &ps);

      //return
      //   ;
      //if (GetExStyle() & WS_EX_LAYERED)
      //{


      //   return;

      //}

      ::int_rectangle rectangleWindow;

      auto puserinteraction = user_interaction();

      rectangleWindow = puserinteraction->screen_rectangle();

      PAINTSTRUCT paint;

      memory_set(&paint, 0, sizeof(paint));

      HDC hdc = ::BeginPaint(get_hwnd(), &paint);

      ::SelectClipRgn(hdc, nullptr);

      ::int_rectangle rectanglePaint;

      ::int_rectangle rectangleUpdate;

      rectanglePaint = paint.rcPaint;


      throw ::exception(todo);

      //if (rectanglePaint.is_null() || (GetExStyle() & WS_EX_LAYERED))
      //{

      //   rectangleUpdate = rectangleWindow;

      //   rectanglePaint = rectangleWindow;

      //   puserinteraction->_001ScreenToClient(rectanglePaint, ::user::e_layout_design);

      //}
      //else
      //{

      //   rectangleUpdate = rectanglePaint;

      //}

      //if (m_pgraphics.is_null())
      //{

      //   update_graphics_resources();

      //}

      //::pointer<::windows::buffer>pbuffer = m_pgraphics;

      //ASSERT(pbuffer.is_set());

      //single_lock synchronouslock(pbuffer->mutex());

      //auto & buffer = pbuffer->m_osbuffera[!pbuffer->m_iCurrentBuffer];

      //::BitBlt(hdc, rectangleUpdate.left(), rectangleUpdate.top(), rectangleUpdate.width(), rectangleUpdate.height(), buffer.m_hdc, 0, 0, SRCCOPY);








      //if (m_spgraphics.is_set())
      //{

      //   ::draw2d::graphics_pointer & pgraphics = m_spgraphics->on_begin_draw();

      //   if (pgraphics != nullptr)
      //   {

      //      try
      //      {

      //         _001Print(pgraphics);

      //      }
      //      catch (...)
      //      {


      //      }

      //      ::draw2d::graphics_pointer g(e_create);

      //      try
      //      {

      //         if (pgraphics != nullptr && g->attach_hdc(hdc))
      //         {

      //            pgraphics->SetViewportOrg(0, 0);

      //            g->BitBlt(rectanglePaint.left(), rectanglePaint.top(), rectanglePaint.width(), rectanglePaint.height(), pgraphics, rectangleUpdate.left(), rectangleUpdate.top());

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}

      ::EndPaint(get_hwnd(), &paint);

      pmessage->m_bRet = true;

      pmessage->m_lresult = 0;

      //ShowCaret();

   }


   //::user::interaction * window::set_parent(::user::interaction * pWndNewParent)
   //{

   //   return nullptr;

   //   //ASSERT(::IsWindow(get_hwnd()));

   //   //return psystem->ui_from_handle(::SetParent(get_hwnd(), pWndNewParent->get_hwnd()));

   //}


   //::user::interaction * window::get_parent() const
   //{

   //   return nullptr;

   //   //if (!::IsWindow(get_hwnd()))
   //   //{

   //   //   return nullptr;

   //   //}

   //   //if (get_hwnd() == nullptr)
   //   //{

   //   //   return nullptr;

   //   //}

   //   //HWND hwndParent = ::GetParent(get_hwnd());

   //   //if (hwndParent == nullptr)
   //   //{

   //   //   return nullptr;

   //   //}

   //   //return psystem->ui_from_handle(hwndParent);

   //}


   bool window::is_iconic()
   {

      //if (_get_ex_style() & WS_EX_LAYERED)
      //{
      //   
      //   auto puserinteraction = user_interaction();

      //   return puserinteraction->const_layout().sketch().display() == ::e_display_iconic;

      //}
      //else
      {

         if (!::IsWindow(get_hwnd()))
         {

            return false;

         }

         return ::IsIconic(get_hwnd()) != false;

      }

   }




   ::windowing::window * window::window_get_owner()
   {

      ::oswindow oswindow = get_owner_oswindow();

      auto pacmewindowingwindow = win32_windowing()->window(oswindow);

      ::cast < ::windowing::window > pwindowingwindow = pacmewindowingwindow;

      return pwindowingwindow;

   }


   oswindow window::get_owner_oswindow()
   {

      if (!::IsWindow(get_hwnd()))
      {

         return nullptr;

      }

      if (get_hwnd() == nullptr)
      {

         return nullptr;

      }

      HWND hwndOwner = ::GetWindow(get_hwnd(), GW_OWNER);

      if (hwndOwner == nullptr)
      {

         return window_get_parent()->oswindow();

      }

      return as_oswindow(hwndOwner);

   }


   void window::set_owner(::windowing::window * pWndNewOwner)
   {

      auto hwnd = get_hwnd();

      HWND hwndOwner = nullptr;

      if (::is_set(pWndNewOwner))
      {

         hwndOwner = as_hwnd(pWndNewOwner->oswindow());

      }

      if (!::SetWindowLongPtr(hwnd, GWLP_HWNDPARENT, (LONG_PTR)hwndOwner))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      //return ::success;

   }



   //int window::get_window_long(int nIndex) const
   //{
   //   return ::GetWindowLong(get_hwnd(), nIndex);
   //}

   //int window::set_window_long(int nIndex, int lValue)
   //{
   //   return ::SetWindowLong(get_hwnd(), nIndex, lValue);
   //}


   //iptr window::get_window_long_ptr(int nIndex) const
   //{

   //   return ::GetWindowLongPtr(get_hwnd(), nIndex);

   //}


   //iptr window::set_window_long_ptr(int nIndex, iptr lValue)
   //{

   //   return ::SetWindowLongPtr(get_hwnd(), nIndex, lValue);

   //}


   // window
      /* window::operator hwnd() const
      { return this == nullptr ? nullptr : get_hwnd(); }*/
      //bool window::operator==(const window & wnd) const
      //{

      //   return (((window *)&wnd)->get_hwnd()) == ((window *)this)->get_hwnd();

      //}


      //bool window::operator!=(const window & wnd) const
      //{

      //   return (((window *)&wnd)->get_hwnd()) != ((window *)this)->get_hwnd();

      //}


      //unsigned int window::GetStyle() const
      //{

      //   if (!::IsWindow(get_hwnd()))
      //      return 0;

      //   return (unsigned int)::GetWindowLong(get_hwnd(), GWL_STYLE);

      //}


   void window::default_message_handler(::message::message * pmessage)
   {

      HWND hwnd = as_hwnd(pmessage->m_oswindow);

      UINT message = pmessage->m_emessage;

      WPARAM wparam = pmessage->m_wparam;

      LPARAM lparam = pmessage->m_lparam;

      LRESULT lresult = ::DefWindowProcW(hwnd, message, wparam, lparam);

      pmessage->m_lresult = lresult;

   }


   iptr window::_get_style() const
   {

      return _get_window_long_ptr(GWL_STYLE);

   }


   iptr window::_get_ex_style() const
   {

      return _get_window_long_ptr(GWL_EXSTYLE);

   }


   bool window::_set_style(iptr iStyle)
   {

      return _set_window_long_ptr(GWL_STYLE, iStyle);

   }


   bool window::_set_ex_style(iptr iExStyle)
   {

      return _set_window_long_ptr(GWL_EXSTYLE, iExStyle);

   }


   bool window::_modify_style(iptr dwRemove, iptr dwAdd, unsigned int nFlags)
   {

      auto nStyleOld = _get_style();

      auto nStyleNew = nStyleOld & ~dwRemove;

      nStyleNew |= dwAdd;

      if (nStyleNew != nStyleOld)
      {

         _set_style(nStyleNew);

         if (nFlags)
         {

            ::SetWindowPos(get_hwnd(), 
               0, 0, 0, 0, 0,
               SWP_NOSIZE 
               | SWP_NOZORDER
               | SWP_NOMOVE
               | SWP_NOACTIVATE
               | nFlags);

         }

      }

      return true;

   }


   bool window::_modify_ex_style(iptr dwRemove, iptr dwAdd, unsigned int nFlags)
   {

      auto nExStyleOld = _get_ex_style();

      auto nExStyleNew = nExStyleOld & ~dwRemove;

      nExStyleNew |= dwAdd;

      if (nExStyleNew != nExStyleOld)
      {

         _set_ex_style(nExStyleNew);

         if (nFlags)
         {

            ::SetWindowPos(get_hwnd(), 
               0, 0, 0, 0, 0,
               SWP_NOSIZE
               | SWP_NOZORDER
               | SWP_NOMOVE
               | SWP_NOACTIVATE
               | nFlags);

         }

      }

      return true;

   }


   //bool window::ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   if (!::IsWindow(get_hwnd()))
   //      return false;

   //   return ModifyStyleEx(get_hwnd(), dwRemove, dwAdd, nFlags);

   //}


   lresult window::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      return ::SendMessage(get_hwnd(), emessage, wparam, lparam);

   }


   void window::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      HWND hwnd = get_hwnd();

      BOOL bOk = ::PostMessage(hwnd, emessage, wparam, lparam);

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   //bool window::DragDetect(const ::int_point & point) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::DragDetect(((window *)this)->get_hwnd(), int_point) != false;

   //}


   void window::set_window_text(const ::scoped_string & scopedstr)
   {

      DWORD_PTR lresult = 0;

      auto puserinteraction = user_interaction();

      puserinteraction->m_strWindowText2 = scopedstr;

      wstring wstrText(puserinteraction->m_strWindowText2);

      const unichar * pwszText = wstrText;

      if (!::SendMessageTimeoutW(get_hwnd(), WM_SETTEXT, 0, (LONG_PTR)pwszText, SMTO_ABORTIFHUNG, 500, &lresult))
      {

         return;

      }

      //string str;

      //get_window_text(str);

   }


   //::string window::get_window_text()
   //{

   //   string str;

   //   get_window_text(str);

   //   ansi_count_copy(pszString, str, (size_t)minimum(nMaxCount, str.length()));

   //   return str.length();

   //}


   ::string window::get_window_text()
   {

      DWORD_PTR lresult = 0;

      if (!::SendMessageTimeoutW(get_hwnd(), WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG, 90, &lresult))
      {

         return {};

      }

      wstring wstr;

      auto p = wstr.get_buffer(lresult);

      if (!::SendMessageTimeoutW(get_hwnd(), WM_GETTEXT, (lparam)p, lresult + 1, SMTO_ABORTIFHUNG, 90, &lresult))
      {

         return {};

      }

      wstr.release_buffer();

      return wstr;

   }


   //character_count window::get_window_text_length()
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::GetWindowTextLength(get_hwnd());

   //}


   //void window::DragAcceptFiles(bool bAccept)
   //{
   //   ASSERT(::IsWindow(get_hwnd()));
   //   ::DragAcceptFiles(get_hwnd(), bAccept);
   //}


   unsigned int window::ArrangeIconicWindows()
   {

      ASSERT(::IsWindow(get_hwnd()));
      return ::ArrangeIconicWindows(get_hwnd());

   }


   //int window::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{

   //   //ASSERT(::IsWindow(get_hwnd())); return ::SetWindowRgn(get_hwnd(),hRgn,bRedraw);

   //}


   //int window::GetWindowRgn(HRGN hRgn)
   //{

   //   //ASSERT(::IsWindow(get_hwnd()) && hRgn != nullptr); return ::GetWindowRgn(get_hwnd(),hRgn);

   //}


      //void window::bring_to_top(::e_display edisplay)
      //{

      //   if (get_parent() == nullptr)
      //   {

      //      // place the window on top except for certain nCmdShow

      //      if (is_visible(edisplay)
      //         && edisplay_command(edisplay) != e_display_iconic &&
      //         !no_activate(edisplay))
      //      {

      //         HWND hwnd = get_hwnd();

      //         hwnd = ::GetLastActivePopup(hwnd);

      //         ::user::interaction * puserinteraction = psystem->ui_from_handle(hwnd);

      //         if (puserinteraction == nullptr)
      //            BringWindowToTop();
      //         else
      //            puserinteraction->BringWindowToTop();

      //      }

      //   }

      //}

      // MSDN
      // Brings the specified window to the top of the Z order.
      // If the window is a top-level window, it is activated.
      // If the window is a child window, the top-level parent
      // window associated with the child window is activated.
      //
      // Use the BringWindowToTop function to uncover any window
      // that is partially or completely obscured by other windows.
      // Calling this function is similar to calling the set_window_position
      // function to change a window's position in the Z order.
      // BringWindowToTop does not make a window a top-level window.

      //bool window::BringWindowToTop()
      //{

      //   bool bOk = ::BringWindowToTop(get_hwnd()) != false;


      //   if (GetExStyle() & WS_EX_LAYERED)
      //   {

      //      if (!(GetExStyle() & WS_EX_TOPMOST))
      //      {

      //         ::set_window_position(get_hwnd(), (HWND)e_zorder_top, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

      //         //::set_window_position(get_hwnd(),(HWND)e_zorder_top,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

      //         //::set_window_position(get_hwnd(),(HWND)e_zorder_top_most,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

      //         //::set_window_position(get_hwnd(),(HWND)e_zorder_top,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

      //      }

      //   }

      //   return bOk;

      //}


   //void window::MapWindowPoints(::user::window * puserinteractionTo, ::int_point * pPoint, unsigned int nCount)
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   ::MapWindowPoints(get_hwnd(), puserinteractionTo->get_hwnd(), pPoint, nCount);

   //}


   //void window::MapWindowPoints(::user::window * puserinteractionTo, ::int_rectangle * prectangle)

   //{
   //   ASSERT(::IsWindow(get_hwnd()));
   //   ::MapWindowPoints(get_hwnd(), puserinteractionTo->get_hwnd(), (::int_point *)prectangle, 2);

   //}



   void window::UpdateWindow()
   {
      ::UpdateWindow(get_hwnd());
   }

   void window::SetRedraw(bool bRedraw)
   {
      ASSERT(::IsWindow(get_hwnd()));
      ::SendMessage(get_hwnd(), WM_SETREDRAW, bRedraw, 0);
   }

   bool window::GetUpdateRect(::int_rectangle * prectangle, bool bErase)
   {

      ASSERT(::IsWindow(get_hwnd()));
      RECT r;
      auto bOk = ::GetUpdateRect(get_hwnd(), &r, bErase) != false;

      *prectangle = r;

      return bOk;

   }


   int window::GetUpdateRgn(::draw2d::region * pRgn, bool bErase)
   {

      //ASSERT(::IsWindow(get_hwnd()));
      //return ::GetUpdateRgn(get_hwnd(), (HRGN)pRgn->get_os_data(), bErase);

      return 0;

   }


   void window::Invalidate(bool bErase)
   {
      ASSERT(::IsWindow(get_hwnd()));
      ::InvalidateRect(get_hwnd(), nullptr, bErase);
   }

   void window::InvalidateRect(const ::int_rectangle * rectangle, bool bErase)

   {
      ASSERT(::IsWindow(get_hwnd()));
      ::InvalidateRect(get_hwnd(), (RECT *)rectangle, bErase);

   }


   void window::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   {

      //ASSERT(::IsWindow(get_hwnd()));
      //::InvalidateRgn(get_hwnd(), (HRGN)pRgn->get_os_data(), bErase);

   }


   void window::ValidateRect(const ::int_rectangle * rectangle)

   {

      ASSERT(::IsWindow(get_hwnd()));

      ::ValidateRect(get_hwnd(), (RECT *)rectangle);


   }


   void window::ValidateRgn(::draw2d::region * pRgn)
   {

      ASSERT(::IsWindow(get_hwnd()));

      //::ValidateRgn(get_hwnd(), (HRGN)pRgn->get_os_data());

   }


   void window::_on_configure_notify_unlocked(const ::int_rectangle & rectangle)
   {

      if (has_finishing_flag() || has_destroying_flag())
      {

         return;

      }

      //auto p = rectangle.origin();

      //::pointer < buffer > pbuffer = m_pgraphicsgraphics;

      //if (!pbuffer)
      //{

      //   return;

      //}

      //{

      //   auto pitem = pbuffer->get_buffer_item();

      //   if (pitem)
      //   {

      //      pitem->m_pointBufferItemWindow = p;

      //   }

      //}

      //{

      //   auto pitem = pbuffer->get_screen_item();

      //   if (pitem)
      //   {

      //      pitem->m_pointBufferItemWindow = p;

      //   }

      //}

      ::windowing::window::_on_configure_notify_unlocked(rectangle);

   }


   void window::ShowOwnedPopups(bool bShow)
   {

      ASSERT(::IsWindow(get_hwnd()));

      ::ShowOwnedPopups(get_hwnd(), bShow);

   }




   ::pointer<::draw2d::graphics>window::GetDCEx(::draw2d::region * prgnClip, unsigned int flags)
   {

      ASSERT(::IsWindow(get_hwnd()));

      auto pgraphics = __øcreate < ::draw2d::graphics >();

      throw ::exception(todo);

      //pgraphics->attach(::GetDCEx(get_hwnd(), (HRGN)prgnClip->get_os_data(), flags));

      return pgraphics;


   }


   bool window::LockWindowUpdate()
   {

      ASSERT(::IsWindow(get_hwnd()));

      return ::LockWindowUpdate(get_hwnd()) != false;

   }

   void window::UnlockWindowUpdate()
   {

      ASSERT(::IsWindow(get_hwnd()));

      ::LockWindowUpdate(nullptr);

   }


   bool window::RedrawWindow(const ::int_rectangle & rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   {

      //if (m_bDestroyImplOnly)
      //{

      //   return false;

      //}

      auto puserinteraction = user_interaction();

      if (!puserinteraction->is_window_visible(::user::e_layout_sketch))
      {

         return true;

      }

      if (!(_get_ex_style() & WS_EX_LAYERED))
      {

         ::RedrawWindow(get_hwnd(), nullptr, nullptr, flags);

      }

      if (flags & RDW_UPDATENOW)
      {





         //if (GetExStyle() & WS_EX_LAYERED)
         {

            //_001UpdateWindow();

            //return true;

         }
         //else
         //{

         //   if (!is_window_visible() && !m_bShowFlags)
         //      return false;

         //   if (!is_window_visible())
         //   {

         //      if (m_iShowFlags & SWP_SHOWWINDOW)
         //      {

         //         display(e_display_normal);

         //      }

         //   }

         //   return ::set_need_redraw(get_hwnd(), pRectUpdate, prgnUpdate == nullptr ? nullptr : (HRGN)prgnUpdate->get_os_data(),

         //      flags | RDW_NOERASE | RDW_NOFRAME | RDW_INVALIDATE) != false;

         //}

      }
      else
      {

         puserinteraction->set_need_redraw();

      }

      return true;

   }





   bool window::EnableScrollBar(int nSBFlags, unsigned int nArrowFlags)
   {

      ASSERT(::IsWindow(get_hwnd()));

      return ::EnableScrollBar(get_hwnd(), nSBFlags, nArrowFlags) != false;

   }

   //bool window::DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo)

   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::DrawAnimatedRects(get_hwnd(), idAni, prcFrom, lprcTo) != false;


   //}

   bool window::DrawCaption(::draw2d::graphics_pointer & pgraphics, const int_rectangle & prc, unsigned int uFlags)

   {

      ASSERT(::IsWindow(get_hwnd()));

      throw ::interface_only();
      return false;
      //      return ::DrawCaption(get_hwnd(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_hwnd(), prc, uFlags) != false;


   }


   bool window::is_this_enabled()
   {

      return ::IsWindowEnabled(get_hwnd()) != false;

   }


   void window::enable_window(bool bEnable)
   {

      BOOL bStateOk = ::EnableWindow(get_hwnd(), bEnable);


      if (is_different(bStateOk, bEnable))
      {

         debugf("EnableWindow has change enabled state");

      }
      else
      {

         debugf("EnableWindow hasn't change enabled state");

      }

   }


   //void window::set_focus()
   //{

   //   HWND hwnd = get_hwnd();

   //   if (!::XXXSetFocus(hwnd))
   //   {

   //      return ::error_failed;
   //      
   //   }

   //   return ::success;

   //}




   //bool window::XXXSetFocus()
   //{

   //   if (!::IsWindow(get_hwnd()))
   //   {

   //      return false;

   //   }

   //   if (!::IsWindowVisible(get_hwnd()))
   //   {

   //      return false;

   //   }

   //   puserinteraction->post_procedure(__routine([this]()
   //      {

   //         HWND hwnd = ::XXXSetFocus(get_hwnd());

   //         ::output_debug_string("::windowing_win32::window::XXXSetFocus ::XXXSetFocus(" + ::hex::lower_from((iptr)hwnd) + ")");

   //         return ::success;

   //      }));

   //   return true;

   //}


   //::user::interaction * window::get_desktop_window()
   //{

   //   return psystem->ui_from_handle(::get_desktop_window());

   //}


   // helper for radio buttons
   //int window::GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)
   //{
   //   for (int nID = nIDFirstButton; nID <= nIDLastButton; nID++)
   //   {
   //      if (IsDlgButtonChecked(nID))
   //         return nID; // atom that matched
   //   }
   //   return 0; // invalid ID
   //}


   //void window::CheckDlgButton(int nIDButton, unsigned int nCheck)
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   ::CheckDlgButton(get_hwnd(), nIDButton, nCheck);

   //}


   //void window::CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   ::CheckRadioButton(get_hwnd(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   //}


   //int window::DlgDirList(TCHAR * pPathSpec, int nIDListBox, int nIDStaticPath, unsigned int nFileType)

   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::DlgDirList(get_hwnd(), pPathSpec, nIDListBox, nIDStaticPath, nFileType);


   //}


   //int window::DlgDirListComboBox(TCHAR * pPathSpec, int nIDComboBox, int nIDStaticPath, unsigned int nFileType)

   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::DlgDirListComboBox(get_hwnd(), pPathSpec, nIDComboBox, nIDStaticPath, nFileType);


   //}


   //bool window::DlgDirSelect(TCHAR * pString, int nSize, int nIDListBox)

   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::DlgDirSelectEx(get_hwnd(), pString, nSize, nIDListBox) != false;


   //}


   //bool window::DlgDirSelectComboBox(TCHAR * pString, int nSize, int nIDComboBox)

   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::DlgDirSelectComboBoxEx(get_hwnd(), pString, nSize, nIDComboBox) != false;


   //}


   //void window::get_child_by_id(atom atom, hwnd * poswindow_) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   ASSERT(poswindow_ != nullptr);

   //   *poswindow_ = ::GetDlgItem(((window *)this)->get_hwnd(), (int)atom);

   //}


   //unsigned int window::GetChildByIdInt(int nID, BOOL * pTrans, bool bSigned) const

   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::GetDlgItemInt(((window *)this)->get_hwnd(), nID, pTrans, bSigned);


   //}


   //int window::GetChildByIdText(int nID, TCHAR * pStr, int nMaxCount) const

   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::GetDlgItemText(((window *)this)->get_hwnd(), nID, pStr, nMaxCount);


   //}


   //::user::window * window::GetNextDlgGroupItem(::user::window * pWndCtl, bool bPrevious) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return psystem->ui_from_handle(::GetNextDlgGroupItem(((window *)this)->get_hwnd(), pWndCtl->get_hwnd(), bPrevious));

   //}


   //::user::window * window::GetNextDlgTabItem(::user::window * pWndCtl, bool bPrevious) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return psystem->ui_from_handle(::GetNextDlgTabItem(((window *)this)->get_hwnd(), pWndCtl->get_hwnd(), bPrevious));

   //}


   //unsigned int window::IsDlgButtonChecked(int nIDButton) const
   //{
   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));
   //   return ::IsDlgButtonChecked(((window *)this)->get_hwnd(), nIDButton);
   //}


   //lparam window::SendDlgItemMessage(int nID, unsigned int message, wparam wParam, lparam lParam)
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::SendDlgItemMessage(((window *)this)->get_hwnd(), message, message, wParam, lParam);

   //}


   //void window::SetDlgItemInt(int nID, unsigned int nValue, bool bSigned)
   //{
   //   ASSERT(::IsWindow(get_hwnd()));
   //   ::SetDlgItemInt(get_hwnd(), nID, nValue, bSigned);
   //}
   //void window::SetDlgItemText(int nID, const ::scoped_string & scopedstrString)

   //{
   //   ASSERT(::IsWindow(get_hwnd()));
   //   ::SetDlgItemTextW(get_hwnd(), nID, wstring(pszString));

   //}
   //int window::ScrollWindowEx(int dx, int dy,
   //   const ::int_rectangle * pRectScroll, const ::int_rectangle * lpRectClip,

   //   ::draw2d::region * prgnUpdate, ::int_rectangle * pRectUpdate, unsigned int flags)

   //{

   //   //ASSERT(::IsWindow(get_hwnd()));
   //   //return ::ScrollWindowEx(get_hwnd(), dx, dy, pRectScroll, lpRectClip,

   //   //                        (HRGN)prgnUpdate->get_os_data(), pRectUpdate, flags);

   //   return 0;


   //}

   //void window::ShowScrollBar(unsigned int nBar, bool bShow)
   //{
   //   ASSERT(::IsWindow(get_hwnd()));
   //   ::ShowScrollBar(get_hwnd(), nBar, bShow);
   //}
   //::user::interaction * window::ChildWindowFromPoint(const ::int_point & point)
   //{
   //   ASSERT(::IsWindow(get_hwnd()));

   //   return  psystem->ui_from_handle(::ChildWindowFromPoint(get_hwnd(), int_point));


   //}

   //::user::interaction * window::ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags)
   //{
   //   ASSERT(::IsWindow(get_hwnd()));

   //   return  psystem->ui_from_handle(::ChildWindowFromPointEx(get_hwnd(), point, nFlags));


   //}



   ::windowing::window * window::get_next_window(unsigned int nFlag)
   {

      HWND hwnd = get_hwnd();

      HWND hwndNext = ::GetNextWindow(hwnd, nFlag);

      auto pwin32windowing = win32_windowing();

      auto pwindowNext = pwin32windowing->_window(hwndNext);

      return pwindowNext;

   }


   ::windowing::window * window::get_top_window()
   {

      HWND hwnd = get_hwnd();

      HWND hwndTop = ::GetTopWindow(hwnd);

      auto pwin32windowing = win32_windowing();

      auto pwindowTop = pwin32windowing->_window(hwndTop);

      return pwindowTop;

   }


   ::windowing::window * window::get_window(unsigned int nCmd)
   {

      HWND hwnd = get_hwnd();

      HWND hwndGet = ::GetWindow(hwnd, nCmd);

      auto pwin32windowing = win32_windowing();

      auto pwindowGet = pwin32windowing->_window(hwndGet);

      return pwindowGet;

   }


   ::windowing::window * window::get_last_active_popup()
   {

      HWND hwnd = get_hwnd();

      HWND hwndLastActivePopup = ::GetLastActivePopup(hwnd);

      auto pwin32windowing = win32_windowing();

      auto pwindowLastActivePopup = pwin32windowing->_window(hwndLastActivePopup);

      return pwindowLastActivePopup;

   }


   //bool window::FlashWindow(bool bInvert)
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::FlashWindow(get_hwnd(), bInvert) != false;

   //}


   //bool window::ChangeClipboardChain(hwnd oswindow_Next)
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::ChangeClipboardChain(get_hwnd(), oswindow_Next) != false;

   //}


   //hwnd window::SetClipboardImpacter()
   //{

   //   ASSERT(::IsWindow(get_hwnd()));

   //   return ::SetClipboardImpacter(get_hwnd());

   //}


   //bool window::open_clipboard()
   //{

   //   if (m_bClipboardOpened)
   //   {

   //      return true;

   //   }

   //   if (!::OpenClipboard(get_hwnd()))
   //   {

   //      return false;

   //   }

   //   m_bClipboardOpened = true;

   //   return true;

   //}


   //bool window::close_clipboard()
   //{

   //   if (!m_bClipboardOpened)
   //   {

   //      return false;

   //   }

   //   if (!::CloseClipboard())
   //   {

   //      return false;

   //   }

   //   m_bClipboardOpened = false;

   //   return true;

   //}


   //::user::interaction * window::GetOpenClipboardWindow()
   //{

   //   return psystem->ui_from_handle(::GetOpenClipboardWindow());

   //}


   //::user::interaction * window::GetClipboardOwner()
   //{

   //   return psystem->ui_from_handle(::GetClipboardOwner());

   //}


   //::user::interaction * window::GetClipboardImpacter()
   //{

   //   return psystem->ui_from_handle(::GetClipboardImpacter());

   //}


   int_point window::GetCaretPos()
   {

      ::int_point point;

      ::GetCaretPos((POINT *)&point);

      return point;

   }


   void window::SetCaretPos(const ::int_point & point)
   {

      ::SetCaretPos(point.x(), point.y());

   }


   void window::HideCaret()
   {

      ::HideCaret(get_hwnd());

   }


   void window::ShowCaret()
   {

      ::ShowCaret(get_hwnd());

   }


   //hicon window::SetIcon(hicon hIcon, bool bBigIcon)
   //{

   //   return (hicon)send_message(WM_SETICON, bBigIcon, (lparam)hIcon);

   //}

   //hicon window::GetIcon(bool bBigIcon) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return (hicon)const_cast <::windowing_win32::window *> (this)->send_message(WM_GETICON, bBigIcon);

   //}

   //void window::Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   throw ::interface_only();
   //   //      const_cast < ::windowing_win32::window * > (this)->send_message(WM_PRINT, (wparam)(dynamic_cast<::windows::graphics * >(pgraphics))->get_hwnd(), (lparam) dwFlags);

   //}

   //void window::PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   throw ::interface_only();
   //   //const_cast < ::windowing_win32::window * > (this)->send_message(WM_PRINTCLIENT, (wparam)(dynamic_cast<::windows::graphics * >(pgraphics))->get_hwnd(), (lparam) dwFlags);

   //}

   //bool window::SetWindowContextHelpId(unsigned int dwContextHelpId)
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::SetWindowContextHelpId(((window *)this)->get_hwnd(), dwContextHelpId) != false;

   //}

   //unsigned int window::GetWindowContextHelpId() const
   //{

   //   ASSERT(::IsWindow(((window *)this)->get_hwnd()));

   //   return ::GetWindowContextHelpId(((window *)this)->get_hwnd());

   //}


   // Default message map implementations
      //void window::OnActivateApp(bool, unsigned int)
      //{
      //   Default();
      //}
      //void window::OnActivate(unsigned int, ::user::window *, bool)
      //{
      //   Default();
      //}
      //void window::OnCancelMode()
      //{
      //   Default();
      //}
      //void window::OnChildActivate()
      //{
      //   Default();
      //}
      //void window::OnClose()
      //{
      //   Default();
      //}
      //void window::OnContextMenu(::user::window *, int_point)
      //{
      //   Default();
      //}

      //bool window::OnCopyData(::user::window *, COPYDATASTRUCT*)
      //{

      //   return Default() != false;

      //}

      //void window::OnEnable(bool)
      //{
      //   Default();
      //}
      //void window::OnEndSession(bool)
      //{
      //   Default();
      //}

      //bool window::OnEraseBkgnd(::draw2d::graphics *)
      //{

      //   return Default() != false;

      //}

      //void window::OnGetMinMaxInfo(MINMAXINFO*)
      //{
      //   Default();
      //}
      //void window::OnIconEraseBkgnd(::draw2d::graphics *)
      //{
      //   Default();
      //}


   //void window::on_message_set_focus(::message::message * pmessage)
   //{

   //   //m_bFocusImpl = true;

   //   //if (!m_bSystemCaret)
   //   //{

   //   //   m_bSystemCaret = true;

   //   //}

   //}


   //void window::on_message_kill_focus(::message::message * pmessage)
   //{

   //   //m_bFocusImpl = false;

   //   //if (m_bSystemCaret)
   //   //{

   //   //   m_bSystemCaret = false;

   //   //   ::DestroyCaret();

   //   //}

   //}


   //lresult window::OnMenuChar(unsigned int, unsigned int, ::user::menu*)
   //{

   //   return Default();

   //}


   //void window::OnMenuSelect(unsigned int, unsigned int, HMENU)
   //{

   //   Default();

   //}


   //void window::OnMove(int, int)
   //{

   //   Default();

   //}


   //hcursor window::OnQueryDragIcon()
   //{

   //   return (hcursor)Default();

   //}

   //bool window::OnQueryEndSession()
   //{

   //   return Default() != false;

   //}

   //bool window::OnQueryNewPalette()
   //{

   //   return Default() != false;

   //}

   //bool window::OnQueryOpen()
   //{

   //   return Default() != false;

   //}

   //void window::on_message_set_cursor(::message::message * pmessage)
   //{

   //   if (m_pcursor != nullptr)
   //   {

   //      set_cursor(m_pcursor);

   //      pmessage->m_lresult = TRUE;

   //      pmessage->m_bRet = true;

   //   }

   //}


   //void window::OnShowWindow(bool, unsigned int)
   //{

   //   Default();

   //}


   //void window::OnSize(unsigned int, int, int)
   //{

   //   Default();

   //}


   //void window::OnTCard(unsigned int, unsigned int)
   //{

   //   Default();

   //}


   void window::_001OnWindowPosChanging(::message::message * pmessage)
   {

      return;


   }


   void window::_001OnWindowPosChanged(::message::message * pmessage)
   {

      WINDOWPOS * pwindowpos = (WINDOWPOS *)pmessage->m_lparam.m_lparam;

      output_debug_string("\ninteraction_impl::_001OnWindowPosChanged");

      if (::IsIconic(get_hwnd()))
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction->const_layout().sketch().display() != ::e_display_iconic)
         {

            output_debug_string(" IsIconic or not IsIconic, thats the question window::_001OnWindowPosChanged");

         }

      }
      else if (::IsZoomed(get_hwnd()))
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction->const_layout().window().display() != ::e_display_zoomed)
         {

            output_debug_string(" IsZoomed or not IsZoomed, thats the question window::_001OnWindowPosChanged");

         }

      }


      //if (m_bDestroyImplOnly)
      //{

      //   return;

      //}

      auto puserinteraction = user_interaction();

      if (puserinteraction->layout().m_eflag)
      {

         return;

      }

      ::int_point point(pwindowpos->x, pwindowpos->y);

      bool bMove = false;

      if (puserinteraction->const_layout().sketch().origin() != point)
      {

         if (puserinteraction->const_layout().is_moving())
         {

            information() << "Window is Moving :: on_message_move";

         }

         puserinteraction->const_layout().sketch().origin() = point;

         bMove = true;

      }

      ::int_size size(pwindowpos->cx, pwindowpos->cy);

      bool bSize = false;

      if (puserinteraction->const_layout().sketch().size() != size)
      {

         puserinteraction->const_layout().sketch().size() = size;

         bSize = true;

      }

      if (bMove)
      {

         puserinteraction->set_reposition();

         puserinteraction->set_need_redraw();

      }

      if (bSize)
      {

         puserinteraction->set_need_layout();

      }

      if (bMove || bSize)
      {

         puserinteraction->set_need_redraw();

      }


      pmessage->m_bRet = true;

   }


   //void window::_001OnGetMinMaxInfo(::message::message * pmessage)
   //{

   //   ::pointer<::message::message>pmessage(pmessage);

   //}

   //   void window::OnDropFiles(HDROP)
   //   {
   //      Default();
   //   }
   //   void window::OnPaletteIsChanging(::user::window *)
   //   {
   //      Default();
   //   }
   //
   //   bool window::OnNcActivate(bool)
   //   {
   //
   //      return Default() != false;
   //
   //   }
   //
   //   void window::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   //   {
   //      Default();
   //   }
   //
   //   bool window::OnNcCreate(::user::system *)
   //   {
   //
   //      return Default() != false;
   //
   //   }
   //
   //   lresult window::OnNcHitTest(const int_point & )
   //   {
   //      return Default();
   //   }
   //   void window::OnNcLButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcLButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcLButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcMButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcMButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcMButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcMouseMove(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcPaint()
   //   {
   //      Default();
   //   }
   //   void window::OnNcRButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcRButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnNcRButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnSysChar(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnSysCommand(unsigned int, lparam)
   //   {
   //      Default();
   //   }
   //   void window::OnSysDeadChar(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnSysKeyDown(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnSysKeyUp(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnCompacting(unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnFontChange()
   //   {
   //      Default();
   //   }
   //   void window::OnPaletteChanged(::user::window *)
   //   {
   //      Default();
   //   }
   //   void window::OnSpoolerStatus(unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnTimeChange()
   //   {
   //      Default();
   //   }
   //   void window::OnChar(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnDeadChar(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnKeyDown(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnKeyUp(unsigned int, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnLButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnLButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnLButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnMButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnMButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnMButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   int window::OnMouseActivate(::user::window *, unsigned int, unsigned int)
   //   {
   //      return (int)Default();
   //   }
   //   void window::OnMouseMove(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //
   //   bool window::OnMouseWheel(unsigned int, short, const int_point&)
   //   {
   //
   //      return Default() != false;
   //
   //   }
   //
   //   lresult window::OnRegisteredMouseWheel(wparam, lparam)
   //   {
   //      return Default();
   //   }
   //   void window::OnRButtonDblClk(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnRButtonDown(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnRButtonUp(unsigned int, const int_point&)
   //   {
   //      Default();
   //   }
   //   void window::OnTimer(uptr)
   //   {
   //      Default();
   //   }
   //   void window::OnInitMenu(::user::menu*)
   //   {
   //      Default();
   //   }
   //   void window::OnInitMenuPopup(::user::menu*, unsigned int, bool)
   //   {
   //      Default();
   //   }
   //   void window::OnAskCbFormatName(__in unsigned int nMaxCount, __out_ecount_z(nMaxCount) char * lpszName)
   //   {
   //      (nMaxCount);
   //      if (nMaxCount > 0)
   //      {
   //         /* defwindow proc should do this for us, but to be safe, we'hi do it here too */
   //         lpszName[0] = '\0';
   //      }
   //      Default();
   //   }
   //   void window::OnChangeCbChain(hwnd, hwnd)
   //   {
   //      Default();
   //   }
   //   void window::OnDestroyClipboard()
   //   {
   //      Default();
   //   }
   //   void window::OnDrawClipboard()
   //   {
   //      Default();
   //   }
   //   void window::OnHScrollClipboard(::user::window *, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnPaintClipboard(::user::window *, HGLOBAL)
   //   {
   //      Default();
   //   }
   //   void window::OnRenderAllFormats()
   //   {
   //      Default();
   //   }
   //   void window::OnRenderFormat(unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnSizeClipboard(::user::window *, HGLOBAL)
   //   {
   //      Default();
   //   }
   //   void window::OnVScrollClipboard(::user::window *, unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   unsigned int window::OnGetDlgCode()
   //   {
   //      return (unsigned int)Default();
   //   }
   //   void window::OnMDIActivate(bool, ::user::window *, ::user::window *)
   //   {
   //      Default();
   //   }
   //   void window::OnEnterMenuLoop(bool)
   //   {
   //      Default();
   //   }
   //   void window::OnExitMenuLoop(bool)
   //   {
   //      Default();
   //   }
   //// Win4 support
   //   void window::OnStyleChanged(int, LPSTYLESTRUCT)
   //   {
   //      Default();
   //   }
   //   void window::OnStyleChanging(int, LPSTYLESTRUCT)
   //   {
   //      Default();
   //   }
   //   void window::OnSizing(unsigned int, ::int_rectangle *)
   //   {
   //      Default();
   //   }
   //   void window::OnMoving(unsigned int, ::int_rectangle *)
   //   {
   //      Default();
   //   }
   //   void window::OnCaptureChanged(::user::window *)
   //   {
   //      Default();
   //   }
   //
   //   bool window::OnDeviceChange(unsigned int, uptr)
   //   {
   //
   //      return Default() != false;
   //
   //   }
   //
   //   void window::OnWinIniChange(const ::string &)
   //   {
   //      Default();
   //   }
   //   void window::OnChangeUIState(unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   void window::OnUpdateUIState(unsigned int, unsigned int)
   //   {
   //      Default();
   //   }
   //   unsigned int window::OnQueryUIState()
   //   {
   //      return (unsigned int)Default();
   //   }

   // window dialog data support
   //    void window::do_data_exchange(CDataExchange*)
   //   { } // default does nothing

   // window modality support

   void window::BeginModalState()
   {

      ::EnableWindow(get_hwnd(), false);

   }

   void window::EndModalState()
   {

      ::EnableWindow(get_hwnd(), true);

   }

   // frame_window
      /*    void frame_window::DelayUpdateFrameTitle()
      { m_nIdleFlags |= idleTitle; }
      void frame_window::DelayRecalcLayout(bool bNotify)
      { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
      bool frame_window::InModalState() const
      { return m_cModalStack != 0; }
      void frame_window::set_title(const ::scoped_string & scopedstrTitle)

      { m_strTitle = pszTitle; }

      string frame_window::get_title() const
      { return m_strTitle; }
      */



   void window::CloseWindow()
   {
      ASSERT(::IsWindow(get_hwnd()));
      ::CloseWindow(get_hwnd());
   }

   bool window::OpenIcon()
   {

      ASSERT(::IsWindow(get_hwnd()));

      return ::OpenIcon(get_hwnd()) != false;

   }


   //////////////////////////////////////////////////////////////////////////////
   //// UI related window functions


   //hwnd window::get_safe_owner(hwnd hParent, hwnd * pWndTop)
   //{
   //   // get window to start with
   //   HWND hwnd = hParent;
   //   if (hwnd == nullptr)
   //   {
   //      /* trans      ::pointer<::user::frame_window>pFrame = channel::GetRoutingFrame_();
   //      if (pFrame != nullptr)
   //      hwnd = pFrame->get_hwnd();
   //      else
   //      hwnd = psystem->m_puiMain->get_hwnd();*/
   //   }

   //   // a popup window cannot be owned by a child window
   //   while (hwnd != nullptr && (::GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD))
   //   {

   //      hwnd = ::GetParent(hwnd);

   //   }

   //   // determine toplevel window to disable as well
   //   ::hwnd oswindow_Top = hwnd;
   //   ::hwnd oswindow_Temp = hwnd;
   //   for (;;)
   //   {
   //      if (oswindow_Temp == nullptr)
   //         break;
   //      else
   //         oswindow_Top = oswindow_Temp;
   //      oswindow_Temp = ::GetParent(oswindow_Top);
   //   }

   //   // get last active popup of first non-child that was found
   //   if (hParent == nullptr && hwnd != nullptr)
   //      hwnd = ::GetLastActivePopup(hwnd);

   //   // disable and store top level parent window if specified
   //   if (pWndTop != nullptr)
   //   {
   //      if (oswindow_Top != nullptr && ::IsWindowEnabled(oswindow_Top) && oswindow_Top != hwnd)
   //      {
   //         *pWndTop = oswindow_Top;
   //         ::EnableWindow(oswindow_Top, false);
   //      }
   //      else
   //         *pWndTop = nullptr;
   //   }

   //   return hwnd;    // return the owner as hwnd
   //}


   //lresult CALLBACK __cbt_filter_hook(int code, wparam wParam, lparam lParam)
   //{

   //   if (code != HCBT_CREATEWND)
   //   {

   //      goto call_next_hook;

   //   }

   //   ASSERT(lParam != 0);

   //   ::user::system * pcs = (::user::system *) ((LPCBT_CREATEWND)lParam)->lpcs;

   //   ASSERT(pcs != nullptr);

   //   ::windowing_win32::window * puserinteraction = thread_set("wnd_init");

   //   if (puserinteraction != nullptr || (!(pcs->style & WS_CHILD)))
   //   {

   //      thread_set("wnd_init") = nullptr;

   //      // Note: special check to avoid subclassing the IME window
   //      //if (gen_DBCS)
   //      {
   //         // check for cheap CS_IME style first...
   //         if (GetClassLongW((hwnd)wParam, GCL_STYLE) & CS_IME)
   //         {

   //            goto call_next_hook;

   //         }

   //         const wchar_t * pszClassName;

   //         wchar_t szClassName[128] = {};

   //         if(uptr(pcs->lpszClass) > 0xffff)
   //         {

   //            pszClassName = pcs->lpszClass;

   //         }
   //         else
   //         {

   //            ::GlobalGetAtomNameW((ATOM)(uptr)pcs->lpszClass, szClassName, _countof(szClassName));

   //            pszClassName = szClassName;

   //         }

   //         // a little more expensive to test this way, but necessary...
   //         if (wide_find_string_case_insensitive(pszClassName, L"ime") != 0)
   //         {
   //          
   //            goto call_next_hook;

   //         }

   //      }

   //      ASSERT(wParam != 0);

   //      ::HWND hwnd = (::hwnd) wParam;

   //      if (puserinteraction != nullptr)
   //      {

   //         ASSERT(oswindow_get(hwnd) == nullptr);

   //         puserinteraction->puserinteraction->m_pwindow = puserinteraction;

   //         puserinteraction->attach(hwnd);

   //         puserinteraction->pre_subclass_window();

   //         WNDPROC * ppuserinteractionprocSuper = puserinteraction->GetSuperWndProcAddr();

   //         ASSERT(ppuserinteractionprocSuper != nullptr);

   //         WNDPROC puserinteractionprocOld = (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (uptr)get_window_procedure();

   //         ASSERT(puserinteractionprocOld != nullptr);

   //         if (puserinteractionprocOld != get_window_procedure())
   //         {

   //            *ppuserinteractionprocSuper = puserinteractionprocOld;

   //         }

   //      }

   //   }

   //call_next_hook:

   //   lresult lResult = CallNextHookEx(t_hHookOldCbtFilter, code, wParam, lParam);

   //   return lResult;

   //}


   // void window::_001OnEraseBkgnd(::message::message * pmessage)
   // {
   //    ::pointer<::message::erase_bkgnd>perasebkgnd(pmessage);
   //    perasebkgnd->m_bRet = true;
   //    perasebkgnd->set_result(true);
   // }


   void window::on_message_get_icon(::message::message * pmessage)
   {

      if (pmessage->m_wparam == ICON_BIG)
      {

         if (m_picon)
         {

            ::int_size size;

            size.cx() = GetSystemMetrics(SM_CXICON);
            size.cy() = GetSystemMetrics(SM_CYICON);

            HICON hicon = (HICON)m_picon->get_os_data(size);

            pmessage->m_lresult = (LRESULT)hicon;

            pmessage->m_bRet = true;

         }

      }
      else if (pmessage->m_wparam == ICON_SMALL
         || pmessage->m_wparam == ICON_SMALL2)
      {

         if (m_picon)
         {

            ::int_size size;

            size.cx() = GetSystemMetrics(SM_CXSMICON);
            size.cy() = GetSystemMetrics(SM_CYSMICON);

            HICON hicon = (HICON)m_picon->get_os_data(size);

            pmessage->m_lresult = (LRESULT)hicon;

            pmessage->m_bRet = true;

         }

      }

   }


   void window::track_mouse_hover()
   {

      if (m_bTransparentMouseEvents)
      {

         m_bTrackMouseLeave = true;

         return;

      }

      TRACKMOUSEEVENT tme = { sizeof(tme) };
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = get_hwnd();
      TrackMouseEvent(&tme);

      track_mouse_leave();

   }


   //void window::set_origin(::draw2d::graphics_pointer & pgraphics)
   //{

   //   // graphics will be already set its impact port to the window for linux - cairo with xlib

   //   pgraphics->set_origin(::int_point());

   //}


   void window::on_set_parent(::user::interaction * puserinteraction) {

      throw ::interface_only();
   }

   bool window::get_rect_normal(::int_rectangle * prectangle) {

      throw ::interface_only();
      return false;
   }

   //// virtual void register_drop_target();
   //void window::show_task(bool bShow)
   //{

   //   throw ::interface_only();

   //}
   //


   void window::_window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation)
   {

      throw ::interface_only();

   }



   /*

/*   void window::_001DeferPaintLayeredWindowBackground(::image::image * pimage)
   {


   }

   */



   //bool window::get_rect_normal(::int_rectangle * prectangle)

   //{

   //   WINDOWPLACEMENT wp;

   //   zero(wp);

   //   if (!GetWindowPlacement(&wp))
   //      return false;

   //   *prectangle = wp.rcNormalPosition;


   //   return true;

   //}


   //DWORD WINAPI drop_target(LPVOID int_point)
   //{

   //   window * pimpl = (window *)int_point;

   //   HRESULT hr = OleInitialize(nullptr);

   //   hr = ::RegisterDragDrop(get_hwnd(), pimpl);

   //   if (SUCCEEDED(CoCreateInstance(CLSID_DragDropHelper, nullptr,
   //      CLSCTX_INPROC_SERVER,
   //      IID_IDropTargetHelper,
   //      (void **)&m_piDropHelper)))
   //   {
   //      m_bUseDnDHelper = true;
   //   }

   //   MSG msg;

   //   while (::GetMessage(&msg, nullptr, 0, 0xffffffffu))
   //   {

   //      TranslateMessage(&msg);

   //      DispatchMessage(&msg);

   //   }

   //   return 0;

   //}


   //void window::register_drop_target()
   //{
   //   m_bUseDnDHelper = false;

   //   ::CreateThread(nullptr, 0, drop_target, this, 0, nullptr);


   //}


   void window::show_task(bool bShowTaskBar)
   {

      synchronous_lock synchronouslock(synchronization());

      // https://www.daniweb.com/programming/software-development/threads/457564/mfc-application-disablehide-taskbar-icon

      set_tool_window(!bShowTaskBar);

      node()->defer_co_initialize_ex(false);

      comptr < ITaskbarList>                     tasklist;

      HRESULT hr = tasklist.CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER);

      if (SUCCEEDED(hr) && SUCCEEDED(hr = tasklist->HrInit()))
      {

         if (bShowTaskBar)
         {

            hr = tasklist->AddTab(get_hwnd());

            informationf("result = %d", hr);

         }
         else
         {

            tasklist->DeleteTab(get_hwnd());

         }

      }

   }



   /*bool window::set_window_position(class ::user::zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
   {

      if (!::user::window::set_window_position(zorder, x, y, cx, cy, nFlags))
      {

         return false;

      }

      if (!(GetExStyle() & WS_EX_LAYERED))
      {


         if (!::set_window_position(get_hwnd(), zorder, x, y, cx, cy, nFlags))
         {

            return false;

         }

      }

      return true;

   }
*/


//void window::window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation)
//{

//   ::user::window::window_show_change_visibility(edisplay, useractivation);

//}


   void window::_001OnActivate(::message::message * pmessage)
   {

      BOOL enabled = false;

      DwmIsCompositionEnabled(&enabled);

      //data->composition_enabled = enabled;

      if (enabled)
      {

         /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */

         MARGINS m = { 0,0,0,0 };

         unsigned int  dw = DWMNCRP_ENABLED;

         HWND hwnd = get_hwnd();

         DwmExtendFrameIntoClientArea(hwnd, &m);

         DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dw, sizeof(unsigned int));

      }
      else
      {

      }

   }


   void window::_001OnDwmNcRenderingChanged(::message::message * pmessage)
   {

      //#ifdef WINDOWS_DESKTOP

      wparam wparam;

      lparam lparam;

      wparam = pmessage->m_wparam;

      lparam = pmessage->m_lparam;

      //return Default();

      BOOL enabled = false;

      DwmIsCompositionEnabled(&enabled);

      //data->composition_enabled = enabled;

      if (enabled)
      {

         /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */

         MARGINS m = { 0,0,0,0 };

         unsigned int  dw = DWMNCRP_ENABLED;

         HWND hwnd = get_hwnd();

         DwmExtendFrameIntoClientArea(hwnd, &m);

         DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dw, sizeof(unsigned int));

      }
      else
      {

      }

      //update_region(data);
      //      long dwEx = ::GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
      //      dwEx &= ~(WS_EX_LAYERED);
      //      ::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,dwEx);
      //      ::InvalidateRect(GetSafeHwnd(),nullptr,true);
      //      ::UpdateWindow(GetSafeHwnd());
      //      //MoveAnchorsImmediatelly(hwndDlg);
      pmessage->m_bRet = true;

      pmessage->m_lresult = 0;

      //#endif

   }


   void window::on_message_non_client_calculate_size(::message::message * pmessage)
   {

      ::pointer<::message::nc_calc_size>pcalcsize(pmessage);

      BOOL bCalcValidRects = pcalcsize->GetCalcValidRects();

      NCCALCSIZE_PARAMS * pncsp = (NCCALCSIZE_PARAMS *)pcalcsize->m_pNCCALCSIZE_PARAMS;

      // TODO: Add your message handler code here and/or call default
      //if(bCalcValidRects)
      //{
      //   informationf("1");
      //   pncsp->rgrc[0].left() = lpncsp->lppos->x + 1;

      //   pncsp->rgrc[0].right() = lpncsp->lppos->x + lpncsp->lppos->cx - 1;

      //   pncsp->rgrc[0].top() = lpncsp->lppos->y + 32;

      //   pncsp->rgrc[0].bottom() = lpncsp->lppos->y + lpncsp->lppos->cy - 1;

      //}
      //else
      //{
      //   CRect * prectangle = (CRect *) pncsp;

      //   prectangle->top() += 32;
      //   prectangle->left()++;
      //   prectangle->bottom()--;
      //   prectangle->right()--;

      //   informationf("2");
      //}
      const int_rectangle & nonclient = pncsp->rgrc[0];

      //CMiniFrameWnd::OnNcCalcSize(bCalcValidRects, pncsp);

      const int_rectangle & client = pncsp->rgrc[0];

      if (is_zoomed())
      {

         WINDOWINFO wi = {};
         wi.cbSize = sizeof(wi);

         HWND hwnd = get_hwnd();

         ::GetWindowInfo(hwnd, &wi);

         /* Maximized windows always have a non-client border that hangs over
         the edge of the screen, so the int_size proposed by e_message_non_client_calc_size is
         fine. Just adjust the top border to erase the u title. */
         pncsp->rgrc[0].left = client.left();

         pncsp->rgrc[0].top = nonclient.top() + wi.cyWindowBorders;

         pncsp->rgrc[0].right = client.right();

         pncsp->rgrc[0].bottom = client.bottom();


         HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
         MONITORINFO mi = {};
         mi.cbSize = sizeof(mi);
         GetMonitorInfoW(mon, &mi);

         /* If the client int_rectangle is the same as the monitor's rectangle,
         the shell assumes that the u has gone fullscreen, so it erases
         the topmost attribute from any auto-hide appbars, making them
         inaccessible. To avoid this, reduce the int_size of the client area by
         one pixel on a certain edge. The edge is chosen based on which side
         of the monitor is likely to contain an auto-hide appbar, so the
         missing client area is covered by it. */
         if (EqualRect(&pncsp->rgrc[0], &mi.rcMonitor))

         {
            if (has_autohide_appbar(ABE_BOTTOM, mi.rcMonitor))
               pncsp->rgrc[0].bottom--;

            else if (has_autohide_appbar(ABE_LEFT, mi.rcMonitor))
               pncsp->rgrc[0].left++;

            else if (has_autohide_appbar(ABE_TOP, mi.rcMonitor))
               pncsp->rgrc[0].top++;

            else if (has_autohide_appbar(ABE_RIGHT, mi.rcMonitor))
               pncsp->rgrc[0].right--;

         }
      }
      else
      {

         /* For the non-maximized case, set the output const int_rectangle & to what it was
         before e_message_non_client_calc_size modified it. This will make the client int_size the
         same as the non-client size. */
         ::copy(&pncsp->rgrc[0], &nonclient);

      }

      pcalcsize->m_lresult = 0;

      pcalcsize->m_bRet = true;

   }


   //void window::default_message_handler(::message::message * pmessage)
   //{

   //   if (get_hwnd() == nullptr)
   //   {

   //      return;

   //   }

   //   WNDPROC pfnWndProc = *GetSuperWndProcAddr();

   //   lresult lresult = 0;

   //   if (pfnWndProc == nullptr)
   //   {

   //      lresult = ::DefWindowProcW(m_oswindow, (unsigned int)pmessage->m_emessage.long_long(), pmessage->m_wparam, pmessage->m_lparam);

   //   }
   //   else
   //   {

   //      lresult = ::CallWindowProc(pfnWndProc, m_oswindow, (unsigned int)pmessage->m_emessage.long_long(), pmessage->m_wparam, pmessage->m_lparam);

   //   }

   //   pmessage->m_lresult = lresult;

   //}


   void window::set_icon(::windowing::icon * picon)
   {

      //auto estatus = 

      ::windowing::window::set_icon(picon);

      //if (!estatus)
      //{

      //   //return estatus;

      //   throw ::exception(error_failed);

      //}

      if (::is_null(picon))
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      ::int_size sizeSmall;

      //sizeSmall.cx() = GetSystemMetrics(SM_CXSMICON);
      //sizeSmall.cy() = GetSystemMetrics(SM_CYSMICON);
      sizeSmall.cx() = 24;
      sizeSmall.cy() = 24;

      HICON hiconSmall = (HICON)picon->get_os_data(sizeSmall);

      ::int_size sizeBig;

      //sizeBig.cx() = GetSystemMetrics(SM_CXICON);
      //sizeBig.cy() = GetSystemMetrics(SM_CYICON);
      sizeBig.cx() = 32;
      sizeBig.cy() = 32;

      HICON hiconBig = (HICON)picon->get_os_data(sizeBig);

      HWND hwnd = get_hwnd();

      if (hiconSmall)
      {

         {
            //HWND hwnd = get_hwnd();
            user_interaction()->post_message((::enum_message) WM_SETICON, ICON_SMALL, (LPARAM)hiconSmall);
            //DWORD dwLastError = ::GetLastError();
            //information() << "ICON_BIT_SMALLER" << dwLastError;
         }

         ::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hiconSmall);

      }

      if (hiconBig)
      {

         //SetLastError(0);
         {
            // HWND hwnd = get_hwnd();
            //user_interaction()->post_message(WM_SETICON, ICON_BIG, (LPARAM)hiconBig);
            //::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
            //DWORD dwLastError = ::GetLastError();

            //information() << "ICON_LARGER" << dwLastError;
         }
         ::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hiconBig);

      }

      //return ::success;

   }


   //   void window::message_handler(::message::message * pmessage)
   //   {
   //
   //      if (::is_set(puserinteraction))
   //      {
   //
   //         puserinteraction->pre_translate_message(pmessage);
   //
   //      }
   //
   //      if (pmessage->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      unsigned int message;
   //
   //      message = pmessage->m_emessage.umessage();
   //
   //      m_uiMessage = message;
   //
   //      m_wparam = pmessage->m_wparam;
   //
   //      m_lparam = pmessage->m_lparam;
   //
   //      if (message == WM_IME_SETCONTEXT)
   //      {
   //
   //         if (m_wparam == 1)
   //         {
   //
   //            m_lparam &= ~ISC_SHOWUICOMPOSITIONWINDOW;
   //
   //         }
   //
   //         pmessage->m_lresult = ::DefWindowProcW(m_oswindow, m_uiMessage, m_wparam, m_lparam);
   //
   //         pmessage->m_bRet = true;
   //
   //         return;
   //
   //      }
   //
   //      bool bUserElementalOk = !m_bDestroyImplOnly && puserinteraction && puserinteraction->m_bUserElementOk;
   //
   //      if (message == e_message_key_down ||
   //         message == e_message_key_up ||
   //         message == e_message_char ||
   //         message == e_message_sys_key_down ||
   //         message == e_message_sys_key_up ||
   //         message == e_message_sys_char ||
   //         message == WM_IME_KEYDOWN ||
   //         message == WM_IME_SETCONTEXT ||
   //         message == WM_IME_SELECT ||
   //         message == WM_IME_KEYUP ||
   //         message == WM_IME_CHAR ||
   //         message == WM_IME_STARTCOMPOSITION ||
   //         message == WM_IME_COMPOSITION ||
   //         message == WM_IME_COMPOSITIONFULL ||
   //         message == WM_IME_NOTIFY ||
   //         message == WM_IME_ENDCOMPOSITION)
   //      {
   //
   //         auto pkey = pmessage->m_pkey;
   //
   //         if (message == e_message_key_down)
   //         {
   //
   //            output_debug_string("\n Key Down Event ");
   //
   //         }
   //
   //         
   //
   //         if (message == e_message_key_down || message == e_message_sys_key_down)
   //         {
   //            try
   //            {
   //               psession->set_key_pressed(pkey->m_ekey, true);
   //            }
   //            catch (...)
   //            {
   //            }
   //         }
   //         else if (message == e_message_key_up || message == e_message_sys_key_up)
   //         {
   //
   //            try
   //            {
   //
   //               psession->set_key_pressed(pkey->m_ekey, false);
   //
   //            }
   //            catch (...)
   //            {
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      if (message == e_message_timer)
   //      {
   //         //         puserinteraction->get_application()->step_timer();
   //      }
   //      else if (message == e_message_left_button_down)
   //      {
   //         ::int_rectangle rectangleX;
   //         ::GetClientRect(get_hwnd(), rectangleX);
   //         ::int_rectangle rectangleWindow;
   //         ::GetWindowRect(get_hwnd(), rectangleWindow);
   //         ::int_rectangle rectangleRegion;
   //         HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
   //         int regionType = ::GetWindowRgn(get_hwnd(), hrgn);
   //         if (regionType != ERROR)
   //         {
   //            ::GetRgnBox(hrgn, rectangleRegion);
   //         }
   //         ::DeleteObject(hrgn); /* finished with region */
   //         WINDOWPLACEMENT wp;
   //         zero(wp);
   //         wp.length = sizeof(WINDOWPLACEMENT);
   //         ::GetWindowPlacement(get_hwnd(), &wp);
   //         bool bZoomed = ::IsZoomed(get_hwnd()) != false;
   //         bool bIconic = ::IsIconic(get_hwnd()) != false;
   //      }
   //      else if (message == e_message_set_cursor
   //         || message == e_message_non_client_mouse_move)
   //      {
   //         //output_debug_string(".");
   //      }
   //      else
   //      {
   //
   //#ifdef _DEBUG
   //
   //         if (0)
   //         {
   //            switch (message)
   //            {
   //            case e_message_create:
   //               informationf("e_message_create wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_window_position_changing:
   //               informationf("e_message_window_position_changing wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_window_position_changed:
   //               informationf("e_message_window_position_changed wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_activate:
   //               informationf("e_message_activate wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case WM_ACTIVATEAPP:
   //               informationf("WM_ACTIVATEAPP wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_mouse_activate:
   //               informationf("e_message_mouse_activate wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_non_client_activate:
   //               informationf("e_message_non_client_activate wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_set_focus:
   //               informationf("e_message_set_focus wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_kill_focus:
   //               informationf("e_message_kill_focus wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_move:
   //               informationf("e_message_move wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            case e_message_size:
   //               informationf("e_message_size wparam=%08x lparam=%08x", pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            default:
   //               informationf("MESSAGE %08x wparam=%08x lparam=%08x", message, pmessage->m_wparam, pmessage->m_lparam);
   //
   //               break;
   //            }
   //
   //         }
   //
   //#endif //__DEBUG
   //
   //      }
   //
   //      //
   //
   //
   //
   //      /*      else if(message == CA2M_BERGEDGE)
   //      {
   //      if(pmessage->m_wparam == BERGEDGE_GETAPP)
   //      {
   //      ::pointer<::aura::application> ppapp= (::pointer<::aura::application> pmessage->m_lparam;
   //      *ppapp = get_application();
   //      pmessage->m_bRet = true;
   //      return;
   //      }
   //      }*/
   //      //pmessage->set_lresult(0);
   //
   //      if (message == e_message_mouse_leave)
   //      {
   //
   //         auto papexsession = get_session();
   //
   //         ::aura::session * psession = nullptr;
   //
   //         if (papexsession)
   //         {
   //
   //            psession = papexsession;
   //
   //         }
   //
   //         if (psession && psession->m_puiCapture)
   //         {
   //
   //            psession->m_puiCapture->_000OnMouseLeave(pmessage);
   //
   //         }
   //         else if (puserinteraction)
   //         {
   //
   //            puserinteraction->_000OnMouseLeave(pmessage);
   //
   //         }
   //
   //         return;
   //
   //      }
   //
   //      if (message == e_message_left_button_down ||
   //         message == e_message_left_button_up ||
   //         message == e_message_middle_button_down ||
   //         message == e_message_middle_button_up ||
   //         message == e_message_right_button_down ||
   //         message == e_message_right_button_up ||
   //         message == e_message_left_button_double_click ||
   //         message == e_message_mouse_move ||
   //         message == e_message_non_client_mouse_move ||
   //         message == e_message_mouse_wheel)
   //      {
   //
   //         message::mouse * pmouse = dynamic_cast <::message::mouse *> (pmessage);
   //
   //         if (message >= WM_MOUSEFIRST
   //            && message <= WM_MOUSELAST
   //            && m_bTranslateMouseMessageCursor
   //            && !pmouse->m_bTranslated)
   //         {
   //
   //            pmouse->m_bTranslated = true;
   //
   //            ::ClientToScreen(get_hwnd(), &pmouse->m_point);
   //
   //         }
   //
   //         if (message == e_message_left_button_down)
   //         {
   //
   //            informationf("e_message_left_button_down");
   //
   //            string strType = ::str().demangle(puserinteraction->type_name());
   //
   //            if (strType.case_insensitive_contains("list_box"))
   //            {
   //
   //               ::output_debug_string("list_box e_message_left_button_down");
   //
   //            }
   //
   //         }
   //         else if (message == e_message_left_button_up)
   //         {
   //
   //            informationf("e_message_left_button_up");
   //
   //         }
   //         else if (message == e_message_non_client_left_button_up)
   //         {
   //
   //            informationf("e_message_non_client_left_button_up");
   //
   //         }
   //         else if (message == e_message_non_client_left_button_down)
   //         {
   //
   //            informationf("e_message_non_client_left_button_down");
   //
   //            string strType;
   //
   //            if (strType.case_insensitive_contains("list_box"))
   //            {
   //
   //               ::output_debug_string("list_box e_message_non_client_left_button_down");
   //
   //            }
   //
   //         }
   //
   //         auto papexsession = get_session();
   //
   //         ::aura::session * psession = nullptr;
   //
   //         if (papexsession)
   //         {
   //
   //            psession = papexsession;
   //
   //         }
   //
   //         if (psession)
   //         {
   //
   //            psession->on_ui_mouse_message(pmouse);
   //
   //         }
   //
   //         if (message == e_message_mouse_move)
   //         {
   //            // We are at the message handler procedure.
   //            // mouse messages originated from message handler and that are mouse move happenings should end up with the correct cursor.
   //            // So the procedure starts by setting to the default cursor,
   //            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
   //            // handler has set it to another one.
   //            pmouse->m_ecursor = cursor_default;
   //
   //            //information() << "windows::e_message_mouse_move(%d,%d)", pmouse->m_point.x(), pmouse->m_point.y();
   //
   //            string strType;
   //
   //            if (puserinteraction)
   //            {
   //
   //               strType = ::str().demangle(puserinteraction->type_name());
   //
   //               if (strType.case_insensitive_contains("list_box"))
   //               {
   //
   //                  //::output_debug_string("list_box e_message_mouse_move");
   //
   //               }
   //
   //            }
   //
   //         }
   //         else if (message == e_message_non_client_mouse_move)
   //         {
   //            // We are at the message handler procedure.
   //            // mouse messages originated from message handler and that are mouse move happenings should end up with the correct cursor.
   //            // So the procedure starts by setting to the default cursor,
   //            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
   //            // handler has set it to another one.
   //            pmouse->m_ecursor = cursor_default;
   //         }
   //
   //         if (psession)
   //         {
   //
   //            auto puiCapture = psession->m_puiCapture;
   //
   //            if (::is_set(puiCapture))
   //            {
   //
   //               puiCapture->_000OnMouse(pmouse);
   //
   //               return;
   //
   //            }
   //
   //         }
   //
   //         _008OnMouse(pmouse);
   //
   //         return;
   //
   //      }
   //
   //      if (message == MESSAGE_OLE_DRAGENTER ||
   //         message == MESSAGE_OLE_DRAGOVER ||
   //         message == MESSAGE_OLE_DRAGLEAVE ||
   //         message == MESSAGE_OLE_DRAGDROP)
   //      {
   //
   //         message::drag_and_drop * pdrag = (::message::drag_and_drop *)pmessage;
   //
   //         auto puserinteraction = pdrag->userinteraction();
   //
   //         //hwnd_array hwnda;
   //         //user::interaction_pointer_array wnda;
   //         //wnda = *psystem->m_puiptraFrame;
   //         //hwnda = wnda.get_hwnda();
   //         //user::window_util::SortByZOrder(hwnda);
   //         //for (int i = 0; i < hwnda.get_size(); i++)
   //         //{
   //         //   ::pointer<::user::interaction>puserinteraction = wnda.find_first(hwnda[i]);
   //         //   if (puserinteraction != nullptr)
   //         //   {
   //
   //         if (puserinteraction)
   //         {
   //            puserinteraction->_000OnDrag(pdrag);
   //            if (pdrag->m_bRet)
   //               return;
   //
   //         }
   //         /*        }
   //              }*/
   //         return;
   //      }
   //      if (message == e_message_key_down ||
   //         message == e_message_key_up ||
   //         message == e_message_char ||
   //         message == e_message_sys_key_down ||
   //         message == e_message_sys_key_up ||
   //         message == e_message_sys_char ||
   //         message == WM_IME_KEYDOWN ||
   //         message == WM_IME_KEYUP ||
   //         message == WM_IME_CHAR ||
   //         message == WM_IME_SELECT ||
   //         message == WM_IME_SETCONTEXT ||
   //         message == WM_IME_STARTCOMPOSITION ||
   //         message == WM_IME_COMPOSITION ||
   //         message == WM_IME_COMPOSITIONFULL ||
   //         message == WM_IME_NOTIFY ||
   //         message == WM_IME_ENDCOMPOSITION ||
   //         message == WM_INPUTLANGCHANGE)
   //      {
   //
   //
   //         message::key * pkey = (::message::key *)pmessage;
   //
   //         ::pointer<::user::interaction>puiFocus;
   //
   //         auto papexsession = get_session();
   //
   //         ::aura::session * psession = nullptr;
   //
   //         if (papexsession)
   //         {
   //
   //            psession = papexsession;
   //
   //         }
   //
   //         if (psession)
   //         {
   //
   //            puiFocus = puserinteraction->get_keyboard_focus();
   //
   //         }
   //
   //         if (puiFocus && puiFocus->IsWindow() && puiFocus != puserinteraction)
   //         {
   //
   //            puiFocus->send(pkey);
   //
   //            if (pmessage->m_bRet)
   //            {
   //
   //               return;
   //
   //            }
   //
   //         }
   //         else if (!pkey->m_bRet)
   //         {
   //
   //            if (puserinteraction != nullptr)
   //            {
   //
   //               puserinteraction->_000OnKey(pkey);
   //
   //               if (pmessage->m_bRet)
   //               {
   //
   //                  return;
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //         //m_wparam-
   //
   //         //m_lparam = pmessage->m_lparam;
   //
   //         //pmessage->set_lresult(::default_window_procedure(message, pmessage->m_wparam, pmessage->m_lparam));
   //
   //         //return;
   //
   //      }
   //
   //      if (message == e_message_event)
   //      {
   //
   //         puserinteraction->handle_event(pmessage);
   //
   //         return;
   //
   //      }
   //
   //      ::user::window::message_handler(pmessage);
   //
   //      //if(pmessage->m_bRet && !pmessage->m_bDoSystemDefault)
   //
   //      if (pmessage->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      if (message == WM_IME_STARTCOMPOSITION ||
   //         message == WM_IME_COMPOSITION ||
   //         message == WM_IME_COMPOSITIONFULL ||
   //         message == WM_IME_NOTIFY ||
   //         message == WM_IME_ENDCOMPOSITION ||
   //         message == WM_IME_SELECT ||
   //         message == WM_IME_SETCONTEXT)
   //      {
   //
   //         //return;
   //
   //      }
   //
   //      //if (bUserElementalOk && pmessage->m_bWindowProc)
   //      //{
   //      //   
   //      //   if (puserinteraction != nullptr)
   //      //   {
   //      //      
   //      //      puserinteraction->default_window_procedure(pmessage);
   //
   //      //   }
   //      //   else
   //      //   {
   //      //      
   //      //      pmessage->set_lresult(::DefWindowProcW(m_oswindow, pmessage->m_emessage, pmessage->m_wparam, pmessage->m_lparam));
   //
   //      //   }
   //
   //      //}
   //
   //   }


   bool window::window_rectangle(::int_rectangle * prectangle)
   {

      RECT rectangle;

      if (!::GetWindowRect(get_hwnd(), &rectangle))
      {

         return false;

      }

      *prectangle = rectangle;

      return true;

   }


   WNDPROC * window::GetSuperWndProcAddr()
   {

      // Note: it is no longer necessary to override GetSuperWndProcAddr
      //  for each control class with a different WNDCLASS.
      //  This implementation now uses instance data, such that the previous
      //  WNDPROC can be anything.

      return &m_pfnSuper;

   }


   bool window::rectangle(::int_rectangle * prectangle)
   {

      RECT rectangle;

      if (!::GetClientRect(get_hwnd(), &rectangle))
      {

         return false;

      }

      *prectangle = rectangle;

      return true;

   }


   void window::non_top_most_upper_window_rects(::int_rectangle_array & recta)
   {

      /// from top to bottom
      top_level_enum toplevelenum;

      auto phwnda = toplevelenum.m_phwnda;

      HWND hwnd = get_hwnd();

      ::collection::index iFind = phwnda->find_first(hwnd);

      if (iFind < 0)
      {

         return;

      }

      ::int_rectangle rHigher;

      for (iFind--; iFind >= 0; iFind--)
      {

         hwnd = phwnda->element_at(iFind);

         int iExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

         if ((iExStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST)
         {

            continue;

         }

         if (::GetWindowRect(hwnd, (RECT *)&rHigher))
         {

            recta.add(rHigher);

         }

      }

   }


   void window::set_finish()
   {

      //auto estatus = 

      ::windowing::window::set_finish();

      //return estatus;

   }


   void window::set_tool_window(bool bSet)
   {

      if (bSet)
      {

         _modify_ex_style(0, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);

      }
      else
      {

         _modify_ex_style(WS_EX_TOOLWINDOW, 0, SWP_FRAMECHANGED);

      }

      //return ::success;

   }


   bool window::is_tool_window()
   {

      return _get_ex_style() & WS_EX_TOOLWINDOW;

   }


   void window::_task_transparent_mouse_event()
   {

      informationf("start window::_task_transparent_mouse_event");

      auto ptask = ::get_task();

      ::int_point pointCursor;

      ::int_point pointMouseMove;

      //auto pimpl = m_pwindow;

      auto pwindowing = windowing();

      auto itask = user_interaction()->user_thread()->m_itask;

      HWND hwnd = get_hwnd();

      lparam lparam;

      ::int_rectangle rectangleX;

      while (ptask->task_get_run())
      {

         if (m_timeLastMouseMove.elapsed() < 20_ms)
         {

            ::preempt(30_ms);

            continue;

         }

         auto hwndCapture = windows::get_mouse_capture(itask);

         if (hwndCapture != nullptr)
         {

            //output_debug_string("a mouse capture");

         }

         if (hwndCapture == hwnd)
         {

            ::preempt(50_ms);

            continue;

         }

         ::GetCursorPos((POINT *)&pointCursor);

         pointMouseMove = pointCursor;

         ::ScreenToClient(hwnd, (POINT *)&pointMouseMove);

         if (m_pointMouseMove == pointMouseMove)
         {

            ::preempt(30_ms);

            continue;

         }

         ::GetClientRect(hwnd, (RECT *)&rectangleX);

         if (!rectangleX.contains(pointMouseMove))
         {

            if (m_bTrackMouseLeave)
            {

               user_interaction()->post_message(e_message_mouse_leave);

            }

            ::preempt(100_ms);

            continue;

         }

         lparam = MAKELPARAM(pointMouseMove.x(), pointMouseMove.y());

         m_timeLastMouseMove.Now();

         //user_interaction()->post_message(e_message_mouse_move, 0, lparam);

         user_interaction()->send_message(e_message_mouse_move, 0, lparam);

         //::SendMessage(hwnd, e_message_mouse_move, 0, lparam);

         ::preempt(5_ms);

      }

      informationf("end window::_task_transparent_mouse_event");

   }


   void window::on_message_paint(::message::message * pmessage)
   {

      //PAINTSTRUCT ps;
      //HDC hdc = BeginPaint(m_hwnd, &ps);
      //RECT rc{100, 100, 200, 200};
      //auto hbr = ::CreateSolidBrush(RGB(100, 160, 220));
      //FillRect(hdc, &rc, hbr);
      //::GetWindowRect(m_hwnd, &rc);
      //::DeleteObject(hbr);
      ////display();                                              // OpenGL -> DIB
      ////BitBlt(hdc, 0, 0, width(rc), height(rc), m_hdcProto, 0, 0, SRCCOPY); // DIB -> hDC// можно и так:// 

      ////BITMAPINFOHEADER BIH;            // и заголовок// …// создаем DIB section// создаем структуру BITMAPINFOHEADER, описывающую наш DIBint iSize = sizeof(BITMAPINFOHEADER);  // размер
      ////memset(&BIH, 0, iSize);

      ////BIH.biSize = iSize;        // размер структуры
      ////BIH.biWidth = cxDIB;       // геометрия
      ////BIH.biHeight = cyDIB;      // битмапа
      ////BIH.biPlanes = 1;          // один план
      ////BIH.biBitCount = 24;       // 24 bits per pixel
      ////BIH.biCompression = BI_RGB;// без сжатия// создаем новый DC в памяти
      //BITMAPINFO bmp_info;
      //memset(&bmp_info, 0x0, sizeof(bmp_info));
      //bmp_info.bmiHeader=m_bitmapinfoheaderProto;
      //SetDIBitsToDevice(hdc, 0, 0, width(rc), height(rc),
      //   0, 0, 0, height(rc), &m_pbitsProto, &bmp_info, DIB_RGB_COLORS);
      //EndPaint(m_hwnd, &ps);

   }


   void window::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void window::on_message_non_client_destroy(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //destroy();

   }


   void window::_001OnCreate(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);


      {

         /*          DEVMODE dm;

                  if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm))
                  {

                     set_config_per_second(dm.dmDisplayFrequency);

                  }*/

      }

      //         default_message_handler(pmessage);

      auto puserinteraction = user_interaction();

      if (puserinteraction)
      {

         if (puserinteraction->is_message_only_window() || puserinteraction->cast <::windowing_win32::system_interaction >())
         {

            informationf("good : opt out!");

         }

         if (user_interaction()->m_bUserElementOk)
         {

            pcreate->m_lresult = 0;

         }

      }

   }


   float window::get_dpi_for_window()
   {

      ::oswindow oswindow = this->oswindow();

      return (float) ::get_dpi_for_window(oswindow);

   }


   float window::point_dpi(float points)
   {

      float fDpi = get_dpi_for_window();

      return points * fDpi / 72.f;

   }


   float window::dpiy(float y)
   {

      float fDpi = get_dpi_for_window();

      return y * fDpi / 96.f;

   }


   float window::dpix(float x)
   {

      float fDpi = get_dpi_for_window();

      return x * fDpi / 96.f;

   }


   float window::y_dpi(float y)
   {

      float fDpi = get_dpi_for_window();

      return y / fDpi;

   }


   float window::x_dpi(float x)
   {

      float fDpi = get_dpi_for_window();

      return x / fDpi;

   }


   //void window::_window_request_presentation_locked()
   //{

   //   auto puserinteraction = user_interaction();

   //   puserinteraction->_window_request_presentation_unlocked();

   //   //auto pprodevian = m_pprodevian;

   //   //puserinteraction->interaction_post(pprodevian->m_procedureWindowShow);

   //}


   void window::__update_graphics_buffer()
   {

      m_pgraphicsgraphics->update_screen();

      /*auto puserinteraction = user_interaction();

      if (!puserinteraction)
      {

         return;

      }

      auto pprodevian = m_pprodevian;

      if (!pprodevian)
      {

         return;

      }

      if(m_bUpdateScreenSynchronously)
      {

         pprodevian->m_procedureUpdateScreen();

      }
      else
      {

         pprodevian->post_procedure(pprodevian->m_procedureUpdateScreen);

      }*/

   }


   void window::on_redraw_window(unsigned int flags)
   {

      if (!(_get_ex_style() & WS_EX_LAYERED))
      {

         ::RedrawWindow(get_hwnd(), nullptr, nullptr, flags);

      }

   }



   //   defer_co_initialize_ex(false);

   //   comptr < ITaskbarList>                     tasklist;

   //   HRESULT hr = tasklist.CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER);

   //   if (SUCCEEDED(hr) && SUCCEEDED(hr = tasklist->HrInit()))
   //   {

   //      if (bShow)
   //      {

   //         hr = tasklist->AddTab((HWND)get_oswindow());

   //         informationf("result = %d", hr);

   //      }
   //      else
   //      {

   //         tasklist->DeleteTab((HWND)get_oswindow());

   //      }

   //   }

   //}


   //void window::get_cursor_position(::int_point * ppointCursor)
   //{

   //   ::GetCursorPos((POINT *)&m_pointCursor);

   //   *ppointCursor = m_pointCursor;

   //}


   //void window::set_cursor_position(const ::int_point & pointCursor)
   //{

   //   ::SetCursorPos(pointCursor.x(), pointCursor.y());

   //}


   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      //::pointer < ::windows::micro::user >pnanouserWindows = system()->acme_windowing();

      //auto hwnd = m_hwnd;

      //pnanouserWindows->_defer_show_system_menu(hwnd, &m_hmenuSystem, pointAbsolute);

      _defer_show_system_menu(pmouse);

   }


   LRESULT window::window_procedure(unsigned int message, wparam wparam, lparam lparam)
   {

      if (message == WM_PAINT)
      {

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            return ::DefWindowProc(m_hwnd, message, wparam, lparam);

         }

      }
      else if (message == WM_ERASEBKGND)
      {

         return TRUE;

      }

      auto pwin32windowing = win32_windowing();

      auto emessageTaskbarCreated = pwin32windowing->m_emessageWindowsTaskbarCreatedMessage;

      if (message == emessageTaskbarCreated)
      {

         output_debug_string("TaskbarCreateMessage");

      }

      if (message == WM_USER + 1297)
      {

         ::procedure procedure(lparam);

         procedure();

         return 0;

      }

      if (message == WM_USER + 123)
      {

         output_debug_string("let's see");

      }

      lresult lresult = 0;

      //if (hwnd == m_hwnd && on_window_procedure(lresult, message, wparam, lparam))
      //{

      //   return lresult;

      //}

      //if (message == WM_WINDOWPOSCHANGED)
      //{

      //   //if (m_bSizeMoveMode)
      //   {

      //      auto pwindowpos = (WINDOWPOS *)lparam;

      //      //::GetWindowRect(m_hwnd, &r);

      //      auto pointLparam = lparam_as_point(lparam);

      //      //auto xPos = (int)(short)LOWORD(lparam);   // horizontal position 
      //      //auto yPos = (int)(short)HIWORD(lparam);   // vertical position 
      //      auto xPos = pwindowpos->x;
      //      auto yPos = pwindowpos->y;

      //      //::int_point p(r.left, r.top);

      //      ::int_point p(xPos, yPos);

      //      m_pointWindow = p;

      //      //::SetWindowPos(m_hwnd, nullptr, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      //      user_interaction()->layout().m_statea[::user::e_layout_sketch].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_lading].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_layout].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_design].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_output].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_window].m_point2 = p;
      //      user_interaction()->layout().m_statea[::user::e_layout_normal].m_point2 = p;

      //      ::pointer < buffer > pbuffer  = m_pgraphicsgraphics;

      //      {

      //         auto pitem = pbuffer->get_buffer_item();

      //         if (pitem)
      //         {

      //            pitem->m_point = p;

      //         }

      //      }

      //      {

      //         auto pitem = pbuffer->get_screen_item();

      //         if (pitem)
      //         {

      //            pitem->m_point = p;

      //         }

      //      }

      //      return 0;

      //   }

      //}

      if (message == WM_SYSCOMMAND)
      {

         informationf("WM_SYSCOMMAND");

      }
      else if (message == WM_CHAR)
      {

         informationf("WM_CHAR");

      }
      else if (message == WM_KEYDOWN)
      {

         informationf("WM_KEYDOWN");

      }
      else if (message == WM_SYSKEYDOWN)
      {

         informationf("WM_SYSKEYDOWN");

      }
      else if (message == WM_SYSKEYUP)
      {

         informationf("WM_SYSKEYUP");

      }
      else if (message == e_message_show_window)
      {

         informationf("e_message_show_window");

      }
      else if (message == e_message_left_button_double_click)
      {

         information() << "e_message_left_button_double_click";

      }
      else if (message == e_message_activate)
      {

         if (wparam > 0)
         {

            information() << "activation window " << (iptr)m_hwnd;

            information() << "GetCapture " << (iptr)::GetCapture();

         }
         else
         {

            information() << "(2) activation window " << (iptr)m_hwnd;

            information() << "(2) GetCapture " << (iptr)::GetCapture();

         }

         information() << "e_message_activate wparam : " << wparam.m_number;

      }

      //if (is_registered_windows_message(message))
      //{

      //   lresult = ::DefWindowProcW(m_hwnd, message, wparam, lparam);

      //   return lresult;

      //}

      //auto pimpl = m_pwindow;

      //if (pimpl)
      {

         if (__windows_message_bypass(m_hwnd, message, wparam, (iptr)lparam, lresult))
         {

            return lresult;

         }

      }
      if (message == WM_SYSCOMMAND)
      {

         if(wparam == SC_KEYMENU)
         {
      //}
      //if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN)
      //{

      //   if (wparam == VK_SPACE)
      //   {

      //      if (0x8000 & GetAsyncKeyState(VK_RMENU)
      //         || 0x8000 & GetAsyncKeyState(VK_LMENU))
      //      {

               RECT r;

               GetWindowRect(m_hwnd, &r);

               auto pmouse = __create_new < ::message::mouse >();

               pmouse->m_pointAbsolute.x() = r.left;
               pmouse->m_pointAbsolute.y() = r.top;

               defer_show_system_menu(pmouse);

               return 0;

            //}

         }

      }

      //if (message == WM_INITMENU)
      //{

      //   ::pointer < ::windows::micro::user > pnanouser = system()->acme_windowing();

      //   LRESULT lresult = 0;

      //   if (pnanouser->_on_default_system_menu_init_menu(lresult, m_hwnd, m_hmenuSystem, wparam))
      //   {

      //      return lresult;

      //   }

      //}

      //return ::DefWindowProcW(hwnd, message, wparam, lparam);

      //auto psystem = system();

      //if (pimpl)
      {

         m_uiMessage = message;

         m_wparam = wparam;

         m_lparam = lparam;

         auto puserinteraction = user_interaction();

         if (message == e_message_activate)
         {

            puserinteraction->informationf("__window_procedure e_message_activate");

         }
         else if (message == e_message_create)
         {

            puserinteraction->informationf("e_message_create");

         }

         if (message == e_message_left_button_down)
         {

            puserinteraction->informationf("e_message_left_button_down");

         }
         else if (message == e_message_left_button_up)
         {

            puserinteraction->informationf("e_message_left_button_up");

         }
         else if (message == e_message_right_button_up)
         {

         }
         else if (message == 33815)
         {

            string strType = ::type(puserinteraction).name();

            if (strType.contains("list_box"))
            {

               puserinteraction->informationf("list_box");

            }

         }

         if (message == e_message_mouse_move)
         {

            if (lparam.m_lparam == m_lparamLastMouseMove.m_lparam)
            {

               return 0;

            }

            m_lparamLastMouseMove = lparam;

            ::int_point pointMouseMove(lparam_int_x(lparam), lparam_int_y(lparam));

            if (m_pointMouseMove == pointMouseMove)
            {

               return 0;

            }

            m_pointMouseMove = pointMouseMove;

            //if (m_pointMouseMove == pointMouseMove)
            //{

            //   return 0;

            //}

            m_pointMouseMove = pointMouseMove;

            m_timeLastMouseMove.Now();

         }
         else if (message == e_message_timer)
         {

            //if (wparam == e_timer_transparent_mouse_event)
            //{

            //   if (m_pointMouseMove == pointMouseMove)
            //   {

            //      return 0;

            //   }

            //   m_pointCursor = pointCursor;

            //   lparam = MAKELPARAM(pointCursor.x(), pointCursor.y());

            //   call_message_handler(e_message_mouse_move, 0, lparam);

            //}
            //else
            //{

            //   // ignoring Timer Event

            //   output_debug_string("iTE\n");

            //}

            return 0;

         }

         if (m_bDestroyImplOnly || ::is_null(puserinteraction))
         {

            auto pmessage = get_message((enum_message)message, wparam, (iptr)lparam);

            try
            {

               message_handler(pmessage);

            }
            catch (...)
            {

            }

            if (!pmessage->m_bRet)
            {

               default_message_handler(pmessage);

            }

            lresult = pmessage->m_lresult;

         }
         else if (::is_set(puserinteraction))
         {

            if (message == WM_GETTEXT)
            {

               return ::DefWindowProcW(m_hwnd, message, wparam, lparam);

            }
            else if (message == WM_GETTEXTLENGTH)
            {

               return ::DefWindowProcW(m_hwnd, message, wparam, lparam);

            }
            else if (message == WM_SETTEXT)
            {

               return ::DefWindowProcW(m_hwnd, message, wparam, lparam);

            }
            if (message == 34831)
            {

               //output_debug_string("message34381");
            }
            auto pmessage = get_message((enum_message)message, wparam, (iptr)lparam);

            try
            {

               if (message == WM_LBUTTONDOWN
                  || message == WM_LBUTTONUP
                  || message == WM_RBUTTONDOWN
                  || message == WM_RBUTTONUP
                  || message == WM_MBUTTONDOWN
                  || message == WM_MBUTTONUP)
               {

                  pmessage->m_actioncontext.m_puseractivationtoken = __allocate::win32::acme::windowing::activation_token(::get_task());

               }

               puserinteraction->message_handler(pmessage);
               //message_handler(pmessage);

            }
            catch (::exception & e)
            {

               get_task()->handle_exception(e);

               ::pointer < ::exception > pexception = e.clone();

               if (pexception)
               {

                  ::string str;

                  str.formatf("Exception while handling message %d", message);

                  pexception->m_strMessage += ", " + str;

                  m_exceptiona.add(pexception);

               }

               if (message == WM_CREATE)
               {

                  return -1;

               }

            }
            catch (...)
            {

               ::string str;

               str.formatf("Exception while handling message %d", message);

               m_exceptiona.add(__allocate::exception(error_catch_all_exception, str));

               if (message == WM_CREATE)
               {

                  return -1;

               }

            }

            if (!pmessage->m_bRet)
            {

               puserinteraction->default_message_handler(pmessage);

            }

            lresult = pmessage->m_lresult;

         }
         else
         {

            lresult = ::DefWindowProcW(m_hwnd, message, wparam, lparam);

         }

      }

      return lresult;

   }


   void window::on_message_window_position_changed(::message::message * pmessage)
   {

      auto pwindowpos = (WINDOWPOS*) (void *) pmessage->m_lparam.m_lparam;

      if (pwindowpos)
      {

         auto r = ::int_rectangle_dimension(
            pwindowpos->x, pwindowpos->y,
            pwindowpos->cx, pwindowpos->cy
         );

         _on_configure_notify_unlocked(r);

      }

   }

   void window::set_opacity(double dOpacity)
   {

      m_uOpacity = (unsigned char) (minimum_maximum(dOpacity, 0., 1.) * 255.0);

   }


   void window::_user_send(const ::procedure & procedure)
   {

      //if (m_hwnd)
      //{

      //   ::SendMessage(m_hwnd, WM_USER + 1297, 0, (lparam)(::uptr)(::subparticle *)procedure.m_pbase.m_p);

      //}
      //else
      if (m_puserthread)
      {

         m_puserthread->_send(procedure);

      }
      else
      {

         ::win32::acme::windowing::window::_user_send(procedure);

      }

   }


   void window::_user_post(const ::procedure & procedure)
   {

      auto puserinteraction = user_interaction();

      if (!puserinteraction)
      {

         ::windowing::window::_user_post(procedure);

         return;

      }

      user_interaction()->_user_post(procedure);

   }


   void window::_main_send(const ::procedure & procedure)
   {

      _user_send(procedure);

   }


   void window::_main_post(const ::procedure & procedure)
   {

      _user_post(procedure);

   }


   void window::_raw_client_to_screen(::int_point & point)
   {

      ::ClientToScreen(get_hwnd(),(POINT *)&point);

   }


   void window::_raw_screen_to_client(::int_point & point)
   {

      ::ScreenToClient(get_hwnd(),(POINT *)&point);

   }


} // namespace windowing_win32
