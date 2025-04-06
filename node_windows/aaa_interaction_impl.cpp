#include "framework.h"
#include "acme/operating_system.h"
#include "system_interaction.h"
//#include "aura/message.h"
#include "aura/user/interaction_thread.h"
#include "aura/os/windows/windowing.h"
//#include "aura/os/windows/imm_context.h"
//#include "aura/buffer.h"
#include "acme/const/timer.h"
#include "apex/platform/app_core.h"
#include "interaction_impl.h"


//const GUID CLSID_TaskbarList = { 0x56FDF344, 0xFD6D, 0x11D0,{ 0x95, 0x8A, 0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90 } };
//const GUID IID_ITaskbarList = { 0x56FDF342, 0xFD6D, 0x11D0,{ 0x95, 0x8A, 0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90 } };
//const GUID IID_ITaskbarList2 = { 0x602D4995, 0xB13A, 0x429b,{ 0xA6, 0x6E, 0x19, 0x35, 0xE4, 0x4F, 0x43, 0x17 } };
//const GUID IID_ITaskList3 = { 0xEA1AFB91, 0x9E28, 0x4B86,{ 0x90, 0xE9, 0x9E, 0x9F, 0x8A, 0x5E, 0xEF, 0xAF } };

CLASS_DECL_AURA_WINDOWS int g_iMouseDown = 0;

//CLASS_DECL_AURA_WINDOWS thread_iptr < DWORD_PTR > t_time1;
//CLASS_DECL_AURA_WINDOWS thread_iptr < DWORD_PTR > t_time2;


//extern CLASS_DECL_AURA_WINDOWS thread_int_ptr < DWORD_PTR > t_time1;

//thread_int_ptr < HHOOK > t_hHookOldCbtFilter;
//thread_pointer < ::windows::interaction_impl  > thread_set("wnd_init");

//lresult CALLBACK __activation_window_procedure(::windowing::window * pwindow,unsigned int nMsg,wparam wParam,lparam lParam);

const char * gen_OldWndProc = "::aura::OldWndProc423";

//CLASS_DECL_AURA_WINDOWS bool hook_window_create(::windows::interaction_impl * pwindow);


//#define __WNDCLASS(s)    L"ca2" L##s
//#define __WND             __WNDCLASS("Wnd")
//#define __WNDCONTROLBAR   __WNDCLASS("ControlBar")
//#define __WNDMDIFRAME     __WNDCLASS("MDIFrame")
//#define __WNDFRAMEORVIEW  __WNDCLASS("FrameOrView")
//#define __WNDOLECONTROL   __WNDCLASS("OleControl")



struct __CTLCOLOR
{
   ::windowing::window * pwindow;
   HDC hDC;
   unsigned int nCtlType;
};


const unichar gen_Wnd[] = L"windows_interaction_impl";


namespace windows
{


   interaction_impl::interaction_impl()
   {

      user_common_construct();

   }


   //void interaction_impl::construct(::windowing::window * pwindow)
   //{

   //   //set_handle(oswindow);

   //}


   void interaction_impl::user_common_construct()
   {

      m_bFocusImpl = false;

      m_bSystemCaret = false;

      m_uCodePage = CP_UTF8;

      m_iLangId = LANG_USER_DEFAULT;

      m_pfnSuper = nullptr;
      m_bUseDnDHelper = false;
      m_bUpdateGraphics = false;
      m_bIgnoreSizeEvent = false;
      m_bIgnoreMoveEvent = false;

      //set_handle(nullptr);

      zero(m_size);
      zero(m_point);

   }


   interaction_impl::~interaction_impl()
   {

      if (m_strDebug.case_insensitive_contains("main_frame"))
      {

         output_debug_string("main_frame");

      }

   }


   void * interaction_impl::get_os_data() const
   {

      return (void *)((::windows::interaction_impl *) this)->get_oswindow();

   }



   //bool interaction_impl::ModifyStyle(::windowing::window * pwindow, unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   m_pwindow->modify

   //   bool bOk = __modify_style(oswindow, GWL_STYLE, dwRemove, dwAdd, 0);

   //   if (nFlags != 0)
   //   {

   //      //m_iShowFlags = nFlags;



   //   }

   //   return bOk;

   //}


   //bool interaction_impl::ModifyStyleEx(::windowing::window * pwindow, unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   return __modify_style(oswindow, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);

   //}


   //lresult interaction_impl::Default()
   //{

   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   //void interaction_impl::pre_subclass_window()
   //{

   //}


   void interaction_impl::native_create_host()
   {

      auto estatus = __øconstruct(m_pwindow);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pwindow->create_window(this);

      if (!estatus)
      {

         return estatus;

      }

      return true;

   }


   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {

      return true;

   }


   // bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const ::string & lpszName)
   // {

   //    if (_is_window())
   //    {

   //       DestroyWindow();

   //    }

   //    ::user::system createstruct(0, nullptr, lpszName, WS_CHILD, nullptr);

   //    pusersystem->m_createstruct.hwndParent = HWND_MESSAGE;

   //    if (!native_create_window_ex(pinteraction, createstruct, HWND_MESSAGE))
   //    {

   //       return false;

   //    }

   //    return true;

   // }


   //void interaction_impl::install_message_routing(::channel * pchannel)
   //{

   //   last_install_message_routing(pchannel);
   //   
   //   ::windowing::window::install_message_routing(pchannel);

   //   if (!m_puserinteraction->m_bMessageWindow)
   //   {
   //      
   //      MESSAGE_LINK(e_message_paint, pchannel, this, &interaction_impl::_001OnPaint);
   //      MESSAGE_LINK(WM_PRINT, pchannel, this, &interaction_impl::_001OnPrint);

   //   }

   //   m_puserinteraction->install_message_routing(pchannel);
   //   MESSAGE_LINK(e_message_create, pchannel, this, &interaction_impl::on_message_create);
   //   if (!m_puserinteraction->m_bMessageWindow)
   //   {
   //      MESSAGE_LINK(e_message_set_cursor, pchannel, this, &interaction_impl::on_message_set_cursor);
   //      MESSAGE_LINK(e_message_erase_background, pchannel, this, &interaction_impl::_001OnEraseBkgnd);
   //      MESSAGE_LINK(e_message_non_client_calcsize, pchannel, this, &interaction_impl::on_message_non_client_calculate_size);
   //      MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::on_message_show_window);
   //      MESSAGE_LINK(e_message_activate, pchannel, this, &interaction_impl::_001OnActivate);
   //      MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &interaction_impl::_001OnDwmNcRenderingChanged);
   //      MESSAGE_LINK(e_message_move, pchannel, this, &interaction_impl::on_message_move);
   //      MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
   //      MESSAGE_LINK(e_message_window_position_changing,pchannel,this,&interaction_impl::_001OnWindowPosChanging);
   //      MESSAGE_LINK(e_message_window_position_changed,pchannel,this,&interaction_impl::_001OnWindowPosChanged);
   //      MESSAGE_LINK(WM_GETMINMAXINFO,pchannel,this,&interaction_impl::_001OnGetMinMaxInfo);


   //   }

   //   prio_install_message_routing(pchannel);

   //   MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_impl::on_message_destroy);
   //   MESSAGE_LINK(e_message_enable, pchannel, this, &interaction_impl::_001OnEnable);
   //   MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_message_set_focus);
   //   MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::on_message_kill_focus);



   //}


   //void interaction_impl::on_message_show_window(::message::message * pmessage)
   //{

   //   ::pointer<::message::show_window>pshowwindow(pmessage);

   //   if (pshowwindow->m_bShow)
   //   {

   //      output_debug_string("windows::interaction_impl::on_message_show_window bShow = true");

   //   }
   //   else
   //   {

   //      output_debug_string("windows::interaction_impl::on_message_show_window bShow = false");

   //   }


   //}




   //void interaction_impl::on_message_move(::message::message* pmessage)
   //{

   //   if (m_bDestroyImplOnly)
   //   {

   //      return;

   //   }

   //   if (m_puserinteraction->layout().m_eflag)
   //   {

   //      return;

   //   }

   //   ::pointer<::message::move>pmove(pmessage);

   //   if (m_puserinteraction->layout().sketch().origin() != pmove->m_point)
   //   {

   //      if (m_puserinteraction->layout().is_moving())
   //      {

   //         information() << "Window is Moving :: on_message_move";

   //      }

   //      m_puserinteraction->layout().sketch().origin()= pmove->m_point;

   //      if (m_puserinteraction->layout().sketch().display() != e_display_normal)
   //      {

   //         m_puserinteraction->display(e_display_normal);

   //      }

   //      m_puserinteraction->set_reposition();

   //      m_puserinteraction->set_need_redraw();

   //   }

   //}


   //void interaction_impl::on_message_size(::message::message * pmessage)
   //{

   //   if (m_bDestroyImplOnly)
   //   {

   //      return;

   //   }

   //   if (m_puserinteraction->layout().m_eflag)
   //   {

   //      return;

   //   }

   //   ::pointer<::message::size>psize(pmessage);

   //   if (m_puserinteraction->layout().sketch().size() != psize->m_size)
   //   {

   //      m_puserinteraction->layout().sketch().size() = psize->m_size;

   //      if (m_puserinteraction->layout().sketch().display() != e_display_normal)
   //      {

   //         m_puserinteraction->display(e_display_normal);

   //      }

   //      m_puserinteraction->set_need_layout();

   //      m_puserinteraction->set_need_redraw();

   //   }

   //}


   //void interaction_impl::_001OnEnable(::message::message * pmessage)
   //{

   //   ::pointer<::message::enable>penable(pmessage);

   //   if (penable != nullptr)
   //   {

   //      if (penable->get_enable())
   //      {

   //         output_debug_string("::window::interaction_impl _001OnEnable = true");

   //      }
   //      else
   //      {

   //         output_debug_string("::window::interaction_impl _001OnEnable = false");

   //      }

   //   }

   //}


   //void interaction_impl::on_message_destroy(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //   //__release(m_pthreadUserImpl REFERENCING_DEBUGGING_COMMA_THIS);

   //}


   void interaction_impl::post_nc_destroy()
   {

      m_pwindow->post_nc_destroy();


      ::windowing::window::post_non_client_destroy();

   }


   //void interaction_impl::on_final_release()
   //{

   //   if (get_handle() != nullptr)
   //   {

   //      DestroyWindow();    // will call post_non_client_destroy

   //   }
   //   else
   //   {

   //      post_non_client_destroy();

   //   }

   //}


   void interaction_impl::assert_ok() const
   {

      m_pwindow->assert_ok();
      
   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      ::windowing::window::install_message_routing(pchannel);

      //m_puserinteraction->install_message_routing(pchannel);

   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      
      object::dump(dumpcontext);


      m_pwindow->dump(dumpcontext);

   }


   void interaction_impl::on_set_parent(::user::interaction * pinteraction)
   {

   }


   bool interaction_impl::destroy_impl_only()
   {


      return ::windowing::window::destroy_impl_only();

   }


   bool interaction_impl::start_destroying_window()
   {

      return ::windowing::window::start_destroying_window();

   }


   void interaction_impl::destroy_window()
   {

      return ::windowing::window::destroy_window();

   }




   //WNDPROC* interaction_impl::GetSuperWndProcAddr()
   //{

   //   // Note: it is no longer necessary to override GetSuperWndProcAddr
   //   //  for each control class with a different WNDCLASS.
   //   //  This implementation now uses instance data, such that the previous
   //   //  WNDPROC can be anything.

   //   return &m_pfnSuper;

   //}


   //void interaction_impl::pre_translate_message(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //}


   //int interaction_impl::GetChildByIdText(int nID, string & rString) const
   //{

   //   ASSERT(::is_window(((::windows::interaction_impl *)this)->get_handle()));

   //   rString = "";    // is_empty without deallocating

   //   ::windowing::window * pwindow = ::GetDlgItem(((::windows::interaction_impl *)this)->get_handle(), nID);

   //   if (oswindow != nullptr)
   //   {

   //      int nLen = ::GetWindowTextLength(oswindow);
   //      wstring wstr;

   //      ::GetWindowTextW(oswindow, wstr.get_buffer(nLen), nLen + 1);

   //      wstr.release_buffer();

   //      rString = wstr;

   //   }

   //   return (int)rString.get_length();

   //}




   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl will delegate owner draw messages to self drawing controls

   //// Drawing: for all 4 control types
   //void interaction_impl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct)

   //{

   //   // reflect notification to child interaction_impl control
   //   //      if (ReflectMessage(pDrawItemStruct->hwndItem))

   //   //       return;     // eat it

   //   // not handled - do default
   //   // Default();
   //}

   //// Drawing: for all 4 control types
   //int interaction_impl::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct)

   //{
   //   // reflect notification to child interaction_impl control
   //   //      lresult lResult;
   //   //      if (ReflectLastMsg(pCompareItemStruct->hwndItem, &lResult))

   //   //       return (int)lResult;        // eat it

   //   // not handled - do default
   //   return (int)Default();
   //}

   //void interaction_impl::OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct)

   //{
   //   // reflect notification to child interaction_impl control
   //   //if (ReflectLastMsg(pDeleteItemStruct->hwndItem))

   //   // return;     // eat it
   //   // not handled - do default
   //   //Default();
   //}

   //bool interaction_impl::_EnableToolTips(bool bEnable, unsigned int nFlag)
   //{
   //   __UNREFERENCED_PARAMETER(bEnable);
   //   __UNREFERENCED_PARAMETER(nFlag);
   //   return false;
   //}



   //bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return ::GetWindowInfo(((interaction_impl *)this)->get_handle(), pwi) != false;
   //}

   //::windowing::window * interaction_impl::GetAncestor(unsigned int gaFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return  psystem->ui_from_handle(::GetAncestor(((interaction_impl *)this)->get_handle(), gaFlags));
   //}



   //bool interaction_impl::GetScrollBarInfo(int idObject, PSCROLLBARINFO psbi) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   ASSERT(psbi != nullptr);
   //   return ::GetScrollBarInfo(((interaction_impl *)this)->get_handle(), idObject, psbi) != false;
   //}

   //bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   ASSERT(pti != nullptr);
   //   return ::GetTitleBarInfo(((interaction_impl *)this)->get_handle(), pti) != false;
   //}

   //bool interaction_impl::AnimateWindow(::duration ::duration, unsigned int dwFlags)
   //{
   //   ASSERT(_is_window());
   //   return ::AnimateWindow(get_handle(), __os(::duration), dwFlags) != false;
   //}

   //bool interaction_impl::FlashWindowEx(unsigned int dwFlags, unsigned int  uCount, ::duration tickTimeout)
   //{
   //   ASSERT(_is_window());
   //   FLASHWINFO fwi;
   //   fwi.cbSize = sizeof(fwi);
   //   fwi.hwnd = get_handle();
   //   fwi.dwFlags = dwFlags;
   //   fwi.uCount = uCount;
   //   fwi.dwTimeout = __os(tickTimeout);

   //   return ::FlashWindowEx(&fwi) != false;
   //}



   //bool interaction_impl::SetLayeredWindowAttributes(color32_t crKey, unsigned char bAlpha, unsigned int dwFlags)
   //{
   //   ASSERT(_is_window());
   //   return ::SetLayeredWindowAttributes(get_handle(), crKey, bAlpha, dwFlags) != false;
   //}

   //bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst, ::int_point *pptDst, INT_SIZE *psize,
   //      ::draw2d::graphics * pDCSrc, ::int_point *pptSrc, color32_t crKey, BLENDFUNCTION *pblend, unsigned int dwFlags)
   //{
   //   ASSERT(_is_window());
   //   throw ::interface_only();
   //   return false;
   //   /*      return ::UpdateLayeredWindow(get_handle(), WIN_HDC(pDCDst), pptDst, psize,
   //   WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != false;*/
   //}


   //bool interaction_impl::GetLayeredWindowAttributes(color32_t *pcrKey, unsigned char *pbAlpha, unsigned int *pdwFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return ::GetLayeredWindowAttributes(((interaction_impl *)this)->get_handle(), pcrKey, pbAlpha, (LPDWORD)pdwFlags) != false;
   //}

   //bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics, unsigned int nFlags) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   throw ::interface_only();
   //   //      return ::PrintWindow(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), nFlags) != false;
   //   return false;
   //}


   //lresult interaction_impl::OnNTCtlColor(wparam wParam, lparam lParam)
   //{
   //   // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
   //   __CTLCOLOR ctl;
   //   ctl.hDC = (HDC)wParam;
   //   ctl.oswindow = (oswindow)lParam;
   //   return 0;
   //}

   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl extensions for help support

   //void interaction_impl::WinHelp(uptr dwData, unsigned int nCmd)
   //{
   //   __UNREFERENCED_PARAMETER(dwData);
   //   __UNREFERENCED_PARAMETER(nCmd);
   //   throw ::interface_only();

   //   /*      application* pApp = ::auraacmesystem();
   //   ASSERT_VALID(pApp);
   //   ASSERT(pApp->m_pszHelpFilePath != nullptr);
   //   ASSERT(pApp->m_eHelpType == ::windows_definition::WinHelp);

   //   wait_cursor wait(this);

   //   PrepareForHelp();

   //   // need to use top level parent (for the case where get_handle() is in DLL)
   //   ::pointer<::user::interaction>pwindow = EnsureTopLevelParent();

   //   information(trace_category_appmsg, e_trace_level_warning, "WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   //   // finally, run the Windows Help engine
   //   /* trans   if (!::WinHelp((pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   //   {
   //   // linux message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   //   output_error_message("Failed to launch help");
   //   }*/
   //}

   ////void interaction_impl::HtmlHelp(uptr dwData, unsigned int nCmd)
   ////{
   //// throw ::interface_only();
   ///*
   //application* pApp = ::auraacmesystem();
   //ASSERT_VALID(pApp);
   //ASSERT(pApp->m_pszHelpFilePath != nullptr);
   //// to call HtmlHelp the m_fUseHtmlHelp must be set in
   //// the application's constructor
   //ASSERT(pApp->m_eHelpType == ::windows_definition::HTMLHelp);

   //wait_cursor wait(this);

   //PrepareForHelp();

   //// need to use top level parent (for the case where get_handle() is in DLL)
   //::pointer<::user::interaction>pwindow = EnsureTopLevelParent();

   //information(trace_category_appmsg, e_trace_level_warning, "HtmlHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   //// run the HTML Help engine
   ///* trans   if (!::aura::HtmlHelp((pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   //{
   //// linux message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   //output_error_message("Failed to launch help");
   //}*/
   ////}

   //void interaction_impl::PrepareForHelp()
   //{

   //   ::pointer<::user::interaction>pFrameWnd = m_puserinteraction;

   //   if (pFrameWnd.is_set())
   //   {

   //      // frame_window windows should be allowed to exit help mode first

   //      pFrameWnd->ExitHelpMode();

   //   }

   //   // cancel any tracking modes
   //   send_message(WM_CANCELMODE);
   //   send_message_to_descendants(WM_CANCELMODE, 0, 0, true, true);

   //   // need to use top level parent (for the case where get_handle() is in DLL)
   //   ::pointer<::user::interaction>pwindow = EnsureTopLevel();
   //   (pwindow.m_p)->send_message(WM_CANCELMODE);
   //   (pwindow.m_p)->send_message_to_descendants(WM_CANCELMODE, 0, 0, true, true);

   //   // attempt to cancel capture
   //   ::windowing::window * pwindow_Capture = ::GetCapture();
   //   if (oswindow_Capture != nullptr)
   //      ::SendMessage(oswindow_Capture, WM_CANCELMODE, 0, 0);
   //}


   //void interaction_impl::WinHelpInternal(uptr dwData, unsigned int nCmd)
   //{
   //   __UNREFERENCED_PARAMETER(dwData);
   //   __UNREFERENCED_PARAMETER(nCmd);
   //   throw ::interface_only();
   //   /*
   //   application* pApp = ::auraacmesystem();
   //   ASSERT_VALID(pApp);
   //   if (pApp->m_eHelpType == ::windows_definition::HTMLHelp)
   //   {
   //   // translate from WinHelp commands and data to to HtmlHelp
   //   ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
   //   if (nCmd == HELP_CONTEXT)
   //   nCmd = HH_HELP_CONTEXT;
   //   else if (nCmd == HELP_CONTENTS)
   //   nCmd = HH_DISPLAY_TOC;
   //   else if (nCmd == HELP_FINDER)
   //   nCmd = HH_HELP_FINDER;
   //   HtmlHelp(dwData, nCmd);
   //   }
   //   else
   //   WinHelp(dwData, nCmd);*/
   //}



   void interaction_impl::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      channel::route_command(pcommand, bRouteToKeyDescendant);

   }




   //bool interaction_impl::OnCommand(::user::message * pusermessage)
   //{
   //   __UNREFERENCED_PARAMETER(pusermessage);
   //   return false;
   //}


   //bool interaction_impl::OnNotify(::user::message * pusermessage)
   //{

   //   ASSERT(pusermessage != nullptr);
   //   NMHDR* pNMHDR = pusermessage->m_lparam.cast < NMHDR>();
   //   ::windowing::window * pwindow_Ctrl = pNMHDR->hwndFrom;

   //   // get the child ID from the interaction_impl itself
   //   //      uptr nID = __get_dialog_control_id(oswindow_Ctrl);
   //   //      int nCode = pNMHDR->code;

   //   ASSERT(oswindow_Ctrl != nullptr);
   //   ASSERT(::is_window(oswindow_Ctrl));

   //   //      if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
   //   //       return true;        // locked out - ignore control notification

   //   // reflect notification to child interaction_impl control
   //   if (ReflectMessage(oswindow_Ctrl, pusermessage))
   //      return true;        // eaten by child

   //   //      __NOTIFY notify;
   //   //    notify.pResult = pResult;
   //   //  notify.pNMHDR = pNMHDR;
   //   //xxx   return _001OnCommand(pusermessage);
   //   return false;
   //}


   //bool interaction_impl::IsTopParentActive()
   //{
   //   
   //   ASSERT(get_handle() != nullptr);
   //   
   //   ASSERT_VALID(this);

   //   auto puserinteractionTopLevel = get_top_level();

   //   if (!puserinteractionTopLevel)
   //   {

   //      return false;

   //   }

   //   return interaction_impl::get_foreground_window() == puserinteractionTopLevel->GetLastActivePopup();

   //}


   void interaction_impl::activate_top_parent()
   {

      m_pwindow->activate_top_parent();

   }




   //bool interaction_impl::HandleFloatingSysCommand(unsigned int nID, lparam lParam)
   //{

   //   ::pointer<::user::interaction>pParent = get_top_level();

   //   switch (nID & 0xfff0)
   //   {
   //   case SC_PREVWINDOW:
   //   case SC_NEXTWINDOW:
   //      if (LOWORD(lParam) == VK_F6 && pParent)
   //      {
   //         pParent->XXXSetFocus();
   //         return true;
   //      }
   //      break;

   //   case SC_CLOSE:
   //   case SC_KEYMENU:
   //      // Check lParam.  If it is 0L, then the ::account::user may have done
   //      // an Alt+Tab, so just ignore it.  This breaks the ability to
   //      // just press the Alt-key and have the first menu selected,
   //      // but this is minor compared to what happens in the Alt+Tab
   //      // case.
   //      if ((nID & 0xfff0) == SC_CLOSE || lParam != 0L)
   //      {
   //         if (pParent)
   //         {
   //            // Sending the above WM_SYSCOMMAND may destroy the cast,
   //            // so we have to be careful about restoring activation
   //            // and focus after sending it.
   //            ::windowing::window * pwindow_Save = get_handle();
   //            ::windowing::window * pwindow_Focus = ::GetFocus();
   //            pParent->set_active_window();
   //            pParent->send_message(WM_SYSCOMMAND, nID, lParam);

   //            // be very careful here...
   //            if (::is_window(oswindow_Save))
   //               ::set_active_window(oswindow_Save);
   //            if (::is_window(oswindow_Focus))
   //               ::set_keyboard_focus(oswindow_Focus);
   //         }
   //      }
   //      return true;
   //   }
   //   return false;
   //}

   //bool interaction_impl::ReflectMessage(::windowing::window * pwindow_Child, ::user::message * pusermessage)
   //{

   //   // check if in permanent map, if it is reflect it (could be OLE control)
   //   auto pwindow = psystem->ui_from_handle(oswindow_Child);
   //   ASSERT(!pwindow || (pwindow)->get_handle() == oswindow_Child);
   //   if (!pwindow)
   //   {
   //      return false;
   //   }

   //   // only OLE controls and permanent windows will get reflected msgs
   //   ASSERT(pwindow);
   //   return (pwindow)->OnChildNotify(pusermessage);
   //}

   //bool interaction_impl::OnChildNotify(::user::message * pusermessage)
   //{

   //   return ReflectChildNotify(pusermessage);
   //}

   //bool interaction_impl::ReflectChildNotify(::user::message * pusermessage)
   //{

   //   // Note: reflected messages are send directly to interaction_impl::OnWndMsg
   //   //  and interaction_impl::_001OnCommand for speed and because these messages are not
   //   //  routed by normal _001OnCommand routing (they are only dispatched)

   //   unsigned int message;

   //   message = ::message::translate_to_os_message(pusermessage->id());

   //   switch (message)
   //   {
   //   // normal messages (just wParam, lParam through OnWndMsg)
   //   case e_message_scroll_x:
   //   case e_message_scroll_y:
   //   case WM_PARENTNOTIFY:
   //   case WM_DRAWITEM:
   //   case e_message_measure_item:
   //   case WM_DELETEITEM:
   //   case WM_VKEYTOITEM:
   //   case WM_CHARTOITEM:
   //   case WM_COMPAREITEM:
   //      // reflect the message through the message map as WM_REFLECT_BASE+uMsg
   //      //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wParam, lParam, pResult);
   //      return false;

   //   // special case for e_message_command
   //   case e_message_command:
   //   {
   //      // reflect the message through the message map as OCM_COMMAND
   //      __keep(pusermessage->m_bReflect, true);

   //      if (interaction_impl::OnCommand(pusermessage))
   //      {
   //         pusermessage->m_bRet = true;
   //         return true;
   //      }
   //   }
   //   break;

   //   // special case for WM_NOTIFY
   //   case WM_NOTIFY:
   //   {
   //      // reflect the message through the message map as OCM_NOTIFY
   //      NMHDR* pNMHDR = pusermessage->m_lparam.cast < NMHDR >();
   //      //            int nCode = pNMHDR->code;
   //      //            __NOTIFY notify;
   //      //          notify.pResult = pResult;
   //      //        notify.pNMHDR = pNMHDR;
   //      // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, nullptr);
   //   }

   //   // other special cases (WM_CTLCOLOR family)
   //   default:
   //      if (message >= WM_CTLCOLORMSGBOX && message <= WM_CTLCOLORSTATIC)
   //      {
   //         // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
   //         /*__CTLCOLOR ctl;
   //         ctl.hDC = (HDC)wParam;
   //         ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
   //         //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
   //         ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

   //         // reflect the message through the message map as OCM_CTLCOLOR
   //         bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (lparam)&ctl, pResult);
   //         if ((HBRUSH)*pResult == nullptr)
   //         bResult = false;
   //         return bResult;*/
   //         return false;
   //      }
   //      break;
   //   }

   //   return false;   // let the parent handle it
   //}

//   void interaction_impl::OnParentNotify(const ::atom & atom, lparam lParam)
//   {
//      if ((LOWORD(message) == e_message_create || LOWORD(message) == e_message_destroy))
//      {
//         //if (ReflectMessage((oswindow) lParam))
//         // return;     // eat it
//      }
//      // not handled - do default
//      //Default();
//   }
//
////void interaction_impl::on_message_set_focus(::message::message * pdetails)
////{
////
////   //bool bHandled;
//
////   //bHandled = false;
////   //if(!bHandled)
////   //{
////   //   Default();
////   //}
//
//
//
////}
//
//
//   lresult interaction_impl::OnActivateTopLevel(wparam wParam, lparam)
//   {
//
//      return 0;
//
//   }
//
//
//   void interaction_impl::OnSysColorChange()
//   {
//      throw ::interface_only();
//
//      /*      application* pApp = ::auraacmesystem();
//      if (pApp != nullptr && pApp->m_puiMain == this)
//      {
//      // recolor global brushes used by control bars
//      ::windows_definition::Data.UpdateSysColors();
//      }
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, true, true);
//
//      Default();*/
//   }
//
//   bool gen_GotScrollLines;
//
//   void interaction_impl::OnSettingChange(unsigned int uFlags, const ::string & pszSection)
//
//   {
//      UNUSED_ALWAYS(uFlags);
//      UNUSED_ALWAYS(pszSection);
//
//
//      // force refresh of settings that we cache
//      gen_GotScrollLines = false;
//
//
//      interaction_impl::OnDisplayChange(0, 0);    // to update system metrics, etc.
//   }
//
//   void interaction_impl::OnDevModeChange(__in char * pDeviceName)
//
//   {
//      __UNREFERENCED_PARAMETER(pDeviceName);
//
//      throw ::interface_only();
//      /*application* pApp = ::auraacmesystem();
//      if (pApp != nullptr && pApp->m_puiMain == this)
//      pApp->DevModeChange(pDeviceName);
//
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      {
//      const MSG* pMsg = GetCurrentMessage();
//      send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam,
//      true, true);
//      }*/
//   }
//
//   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
//   {
//      //return //Default() != 0;
//      return false;
//   }
//
//   lresult interaction_impl::OnDisplayChange(wparam wparam, lparam lparam)
//
//   {
//
//      // forward this message to all other child windows
//      if (!(GetStyle() & WS_CHILD))
//      {
//         //         const MSG* pMsg = GetCurrentMessage();
//         send_message_to_descendants(e_message_display_change, wparam, lparam, true, true);
//
//      }
//
//      return Default();
//   }
//
//   lresult interaction_impl::OnDragList(wparam, lparam lParam)
//   {
//      LPDRAGLISTINFO pInfo = (LPDRAGLISTINFO)lParam;
//
//      ASSERT(pInfo != nullptr);
//
//
//      //      lresult lResult;
//      //if (ReflectLastMsg(pInfo->hWnd, &lResult))
//
//      //   return (int)lResult;    // eat it
//
//      // not handled - do default
//      //return (int)Default();
//      return 0;
//   }
//
//
   //void interaction_impl::_002OnDraw(::image::image * pimage)
   //{

   //   throw ::interface_only();

   //}


   void interaction_impl::present()
   {

      _001UpdateWindow();

   }


   //void interaction_impl::defer_start_prodevian()
   //{


   //   ::windowing::window::defer_start_prodevian();


   //}


   //void interaction_impl::on_message_create(::message::message * pmessage)
   //{

   //   ::pointer<::message::create>pcreate(pmessage);


   //   {

   //      DEVMODE dm;

   //      if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm))
   //      {

   //         set_config_per_second(dm.dmDisplayFrequency);

   //      }

   //   }

   //   default_message_handler(pmessage);

   //   if (m_puserinteraction)
   //   {

   //      if (m_puserinteraction->is_message_only_window() || m_puserinteraction.cast <::user::system_interaction >())
   //      {

   //         informationf("good : opt out!");

   //      }

   //      if (m_puserinteraction->m_bUserElementOk)
   //      {

   //         pcreate->m_lresult = 0;

   //      }

   //   }

   //}


   //BOOL CALLBACK GetAppsEnumWindowsProc(::windowing::window * pwindow, lparam lParam);




   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

   }


   //void interaction_impl::_001OnProdevianSynch(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}




   //void interaction_impl::_001OnPrint(::message::message * pmessage)
   //{

   //}



//   bool interaction_impl::subclass_window(::windowing::window * pwindow)
//   {
//
//      if (!attach(oswindow))
//         return false;
//
//      // allow any other subclassing to occur
//      pre_subclass_window();
//
//      m_pfnSuper = (WNDPROC)::GetWindowLongPtr(oswindow, GWLP_WNDPROC);
//
//      WNDPROC * plpfn = GetSuperWndProcAddr();
//
//      WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(oswindow, GWLP_WNDPROC, (iptr)windows_user_interaction_impl_get_window_procedure());
//
//      ASSERT(oldWndProc != windows_user_interaction_impl_get_window_procedure());
//
//      if (*plpfn == nullptr)
//      {
//
//         *plpfn = oldWndProc;   // the first control of that type created
//
//      }
//
//
//#ifdef _DEBUG
//
//      else if (*plpfn != oldWndProc)
//      {
//
//         information(trace_category_appmsg, e_trace_level_warning, "int_point: Trying to use subclass_window with incorrect interaction_impl\n");
//         information(trace_category_appmsg, e_trace_level_warning, "\tderived class.\n");
//         information(trace_category_appmsg, e_trace_level_warning, "\toswindow_ = $%08X (nIDC=$%08X) is not a %hs.\n", (unsigned int)(uptr)oswindow, __get_dialog_control_id(oswindow), typeid(*this).name());
//
//         ASSERT(false);
//
//         // undo the subclassing if continuing after assert
//
//         ::SetWindowLongPtr(oswindow, GWLP_WNDPROC, (iptr)oldWndProc);
//
//      }
//
//#endif //__DEBUG
//
//      message::size size;
//
//      on_message_size(&size);
//
//      return true;
//
//   }


   //bool interaction_impl::SubclassDlgItem(unsigned int nID, ::windowing::window * pParent)
   //{

   //   ASSERT(pParent);

   //   ASSERT(::is_window((pParent)->get_handle()));

   //   // check for normal dialog control first
   //   ::windowing::window * pwindow_Control = ::GetDlgItem((pParent)->get_handle(), nID);
   //   if (oswindow_Control != nullptr)
   //      return subclass_window(oswindow_Control);


   //   return false;   // control not found
   //}


   //oswindow interaction_impl::unsubclass_window()
   //{
   //   //ASSERT(_is_window());

   //   if (!_is_window())
   //      return nullptr;

   //   // set WNDPROC back to original value
   //   WNDPROC* plpfn = GetSuperWndProcAddr();

   //   ::SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (iptr)*plpfn);

   //   *plpfn = nullptr;


   //   // and detach the oswindow from the interaction_impl object
   //   return detach();
   //}


   /*

   bool interaction_impl::IsChild(const ::user::interaction * pwindow) const
   {

   ASSERT(_is_window());

   if(pwindow->get_handle() == nullptr)
   {
   return ::user::primitive::IsChild(pwindow);
   }
   else
   {
   return ::IsChild(get_handle(),pwindow->get_handle()) != false;
   }

   }

   */


   bool interaction_impl::_is_window() const
   {

      if (!m_bUserElementOk)
      {

         return false;

      }

      if (m_puserinteraction == nullptr)
      {

         return false;

      }

      if (!m_pwindow)
      {

         return false;

      }

      if (!m_pwindow->is_window())
      {

         return false;

      }

      //if (!_is_window())
      //{

      //   return false;

      //}

      return true;

   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void interaction_impl::rects_from_os()
   {

      //::int_rectangle rectangleX;

      //::GetClientRect(m_oswindow, rectangleX);

      //::int_rectangle rectangleScreen;

      //::GetWindowRect(m_oswindow, rectangleScreen);

      //if (::IsIconic(m_oswindow))
      //{

      //   information() << "interaction_impl::rects_from_os window is iconic";

      //}
      //else
      //{

      //   m_puserinteraction->m_pointScreen = rectangleScreen.origin();

      //   m_puserinteraction->m_size = rectangleScreen.size();

      //}

      //if (rectangleX.size() != m_puserinteraction->m_size)
      //{

      //   informationf("ATTENTION!! Client Size <> Window Size");

      //}


      ////m_puserinteraction->m_sizeScreen = rectangleScreen.size();

      ////m_puserinteraction->m_pointScreenClient.x() = 0;

      ////m_puserinteraction->m_pointScreenClient.y() = 0;

      ////::ScreenToClient(m_oswindow, m_puserinteraction->m_pointScreenClient);

      ////HWND hwndParent = ::get_parent(m_oswindow);

      ////if (hwndParent != NULL)
      ////{

      ////   m_puserinteraction->m_pointParentClient.x() = 0;

      ////   m_puserinteraction->m_pointParentClient.y() = 0;

      ////   ::ClientToScreen(m_oswindow, m_puserinteraction->m_pointParentClient);

      ////   ::ScreenToClient(hwndParent, m_puserinteraction->m_pointParentClient);

      ////}
      ////else
      ////{

      ////   m_puserinteraction->m_pointParentClient = m_puserinteraction.m_pointScreenWindow;

      ////}

      ////m_puserinteraction->m_pointClient = m_puserinteraction.m_pointScreenWindow;

      ////m_puserinteraction->m_pointClient -= m_puserinteraction.m_pointScreenClient;

   }


   //double_point interaction_impl::client_screen_top_left()
   //{

   //   ::int_point point;

   //   ::ClientToScreen(m_oswindow, &point);

   //   return double_point(point.x(), point.y());

   //}


   bool interaction_impl::window_rect_from_os(::int_rectangle * prectangle)
   {

      if (!_is_window())
      {

         return false;

      }

      ::int_rectangle rectangleWindow;

      //if (!(GetExStyle() & WS_EX_LAYERED))
      //{

      //   ::GetWindowRect(m_oswindow, rectangleWindow);

      //   m_puserinteraction->m_pointParentClientRequest = rectangleWindow.origin();

      //   m_puserinteraction->m_sizeClientRequest = rectangleWindow.size();

      //}
      //else
      //{

      //   ::set_rect_point_size(&rectangleWindow, m_puserinteraction->m_pointParentClientRequest, m_puserinteraction.m_sizeClientRequest);

      //}

      //*prectangle = rectangleWindow;

      //if (get_parent() != nullptr)
      //{

      //   get_parent()->_001ClientToScreen(prectangle);

      //}

      return true;

   }


   bool interaction_impl::client_rect_from_os(::int_rectangle * prectangle)
   {

      //oswindow handle = get_handle();

      //if (!_is_window())
      //{

      //   return false;

      //}

      //::int_rectangle rect32;

      //if (!(GetExStyle() & WS_EX_LAYERED))
      //{

      //   if (!::GetWindowRect(get_handle(), rect32))
      //   {

      //      return false;

      //   }

      //   if (get_parent() != nullptr)
      //   {

      //      get_parent()->_001ScreenToClient(rect32);

      //   }

      //   //::copy(m_puserinteraction->m_rectangleParentClient, rect32);

      //}

      //rect32 = m_puserinteraction->m_rectangleParentClient;

      //rect32.offset(-rect32.top_left());

      //::copy(prectangle, rect32);

      return true;

   }


   void interaction_impl::sketch_prepare_window_minimize(const ::user::activation & useractivation)
   {

      primitive_impl::sketch_prepare_window_minimize(useractivation);

   }


   void interaction_impl::sketch_prepare_window_maximize()
   {

      primitive_impl::sketch_prepare_window_maximize();

   }


   void interaction_impl::sketch_prepare_window_full_screen(const ::int_rectangle & rectangleHint)
   {

      primitive_impl::sketch_prepare_window_full_screen(rectangleHint);

   }


   void interaction_impl::sketch_prepare_window_restore(edisplay edisplay)
   {

      primitive_impl::sketch_prepare_window_restore(edisplay);

   }


   bool interaction_impl::display(::e_display edisplay)
   {

      if (!_is_window())
      {

         return false;

      }

      return true;

   }


   bool interaction_impl::window_is_iconic()
   {

      return m_pwindow->is_iconic();

   }


   bool interaction_impl::window_is_zoomed()
   {

      return ::windowing::window::window_is_zoomed();

   }


   ::user::interaction * interaction_impl::get_parent() const
   {
      
      //return m_pwindow->get_parent();
      return nullptr;

   }


   ::user::interaction * interaction_impl::set_parent(::user::interaction * pWndNewParent)
   {

      //ASSERT(_is_window());

      //return psystem->ui_from_handle(::SetParent(get_handle(), pWndNewParent->get_handle()));

      return nullptr;

   }


   ::user::interaction * interaction_impl::get_owner() const
   {

      //if (!_is_window())
      //   return nullptr;

      //if (get_handle() == nullptr)
      //   return nullptr;

      //HWND hwndParent = ::GetWindow(get_handle(), GW_OWNER);

      //if (hwndParent == nullptr)
      //   return get_parent();

      //return psystem->ui_from_handle(hwndParent);
      return nullptr;

   }

   ::user::interaction * interaction_impl::set_owner(::user::interaction * pWndNewParent)
   {

      return nullptr;

   }



   //int interaction_impl::get_window_long(int nIndex) const
   //{
   //   return ::GetWindowLong(get_handle(), nIndex);
   //}

   //int interaction_impl::set_window_long(int nIndex, int lValue)
   //{
   //   return ::SetWindowLong(get_handle(), nIndex, lValue);
   //}


   //iptr interaction_impl::get_window_long_ptr(int nIndex) const
   //{

   //   return m_pwindow->get_window_long_ptr(nIndex);

   //}


   //void interaction_impl::set_window_long_ptr(int nIndex, iptr lValue)
   //{

   //   return m_pwindow->set_window_long_ptr(nIndex, lValue);

   //}


// interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {

      return (((interaction_impl *)&wnd)->get_oswindow()) == ((interaction_impl *)this)->get_oswindow();

   }


   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {

      return (((interaction_impl *)&wnd)->get_oswindow()) != ((interaction_impl *)this)->get_oswindow();

   }


   //unsigned int interaction_impl::GetStyle() const
   //{

   //   if (!_is_window())
   //      return 0;

   //   return (unsigned int)::GetWindowLong(get_handle(), GWL_STYLE);

   //}


   //unsigned int interaction_impl::GetExStyle() const
   //{

   //   if (!_is_window())
   //      return 0;

   //   return (unsigned int)::GetWindowLong(get_handle(), GWL_EXSTYLE);

   //}


   //bool interaction_impl::ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   if (!_is_window())
   //      return false;

   //   return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);

   //}


   //bool interaction_impl::ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   if (!_is_window())
   //      return false;

   //   return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);

   //}


   lresult interaction_impl::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      auto pwindow = m_pwindow;

      unsigned int message = atom.umessage();

      return m_pwindow->send_message(message,  wparam, lparam);

   }


   bool interaction_impl::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      auto pwindow = m_pwindow;

      unsigned int message = atom.umessage();

      return m_pwindow->post_message(message, wparam, lparam);

   }


   //bool interaction_impl::DragDetect(const ::int_point & point) const
   //{

   //   return m_pwindow->DragDetect(point);

   //   //ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   //return ::DragDetect(((interaction_impl *)this)->get_handle(), int_point) != false;

   //}


   void interaction_impl::set_window_text(const ::string & pszString)
   {

      m_pwindow->set_window_text(pszString);

      //DWORD_PTR lresult = 0;

      //m_puserinteraction->m_strWindowText = pszString;

      //wstring wstrText(m_puserinteraction->m_strWindowText);

      //const unichar * pwszText = wstrText;

      //if (!::SendMessageTimeoutW(get_handle(), WM_SETTEXT, 0, (lparam)pwszText, SMTO_ABORTIFHUNG, 500, &lresult))
      //{

      //   return;

      //}

      //string str;

      //get_window_text(str);

   }



   character_count interaction_impl::get_window_text(char * pszString, character_count nMaxCount)

   {

      string str;

      get_window_text(str);

      ansi_count_copy(pszString, str, (size_t) minimum(nMaxCount, str.length()));


      return str.length();

   }

   
   void interaction_impl::get_window_text(string & str)
   {

      m_pwindow->set_window_text(str);

   }


   character_count interaction_impl::get_window_text_length()
   {

      return m_pwindow->get_window_text_length();

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      m_pwindow->DragAcceptFiles(bAccept);

   }


   unsigned int interaction_impl::ArrangeIconicWindows()
   {

      return m_pwindow->ArrangeIconicWindows();

   }


   //void interaction_impl::MapWindowPoints(::windowing::window * puserinteractionTo, ::int_point * pPoint, unsigned int nCount)

   //{
   //   ASSERT(_is_window());
   //   ::MapWindowPoints(get_handle(), puserinteractionTo->get_handle(), pPoint, nCount);

   //}

   //void interaction_impl::MapWindowPoints(::windowing::window * puserinteractionTo, ::int_rectangle * prectangle)

   //{
   //   ASSERT(_is_window());
   //   ::MapWindowPoints(get_handle(), puserinteractionTo->get_handle(), (::int_point *)prectangle, 2);

   //}



   void interaction_impl::UpdateWindow()
   {
      
      m_pwindow->UpdateWindow();

   }


   void interaction_impl::SetRedraw(bool bRedraw)
   {
      
      m_pwindow->SetRedraw(bRedraw);
      
   }

   
   void interaction_impl::on_visual_applied()
   {

      ::windowing::window::on_visual_applied();

   }


   // void interaction_impl::window_apply_visual(const ::user::window_state & windowstate)
   // {

   //    return ::windowing::window::window_apply_visual(windowstate);

   // }


   //bool interaction_impl::_is_window_visible()
   //{

   //   try
   //   {

   //      if (!::IsWindowVisible(get_handle()))
   //      {

   //         return false;

   //      }

   //      return true;

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //}


   //void interaction_impl::ShowOwnedPopups(bool bShow)
   //{

   //   ASSERT(_is_window());

   //   ::ShowOwnedPopups(get_handle(), bShow);

   //}




   //::pointer<::draw2d::graphics>interaction_impl::GetDCEx(::draw2d::region* prgnClip, unsigned int flags)
   //{

   //   ASSERT(_is_window());

   //   auto pgraphics = __øcreate < ::draw2d::graphics > ();

   //   throw ::exception(todo);

   //   //pgraphics->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_os_data(), flags));

   //   return pgraphics;


   //}


   bool interaction_impl::LockWindowUpdate()
   {

      return m_pwindow->LockWindowUpdate();

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      return m_pwindow->UnlockWindowUpdate();

   }


   bool interaction_impl::RedrawWindow(const ::int_rectangle& rectangleUpdate, ::draw2d::region* prgnUpdate, unsigned int flags)
   {

      if (m_bDestroyImplOnly)
      {

         return false;

      }

      if (!m_puserinteraction->is_window_visible(::user::e_layout_sketch))
      {

         return true;

      }

     m_pwindow->on_redraw_window(flags);

      if (flags & RDW_UPDATENOW)
      {





         //if (GetExStyle() & WS_EX_LAYERED)
         {

            _001UpdateWindow();

            return true;

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

         //   return ::set_need_redraw(get_handle(), pRectUpdate, prgnUpdate == nullptr ? nullptr : (HRGN)prgnUpdate->get_os_data(),

         //      flags | RDW_NOERASE | RDW_NOFRAME | RDW_INVALIDATE) != false;

         //}

      }
      else
      {

         m_puserinteraction->set_need_redraw();

      }

      return true;

   }





   //bool interaction_impl::EnableScrollBar(int nSBFlags, unsigned int nArrowFlags)
   //{

   //   ASSERT(_is_window());

   //   return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != false;

   //}

   //bool interaction_impl::DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo)

   //{

   //   ASSERT(_is_window());

   //   return ::DrawAnimatedRects(get_handle(), idAni, prcFrom, lprcTo) != false;


   //}

   //bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics, const int_rectangle & prc, unsigned int uFlags)

   //{

   //   ASSERT(_is_window());

   //   throw ::interface_only();
   //   return false;
   //   //      return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), prc, uFlags) != false;


   //}


   bool interaction_impl::is_this_enabled()
   {

      return m_pwindow->is_this_enabled();

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      return m_pwindow->enable_window(bEnable);

   }



   //::user::interaction * interaction_impl::get_keyboard_focus() const
   //{

   //   if (!has_keyboard_focus())
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionFocus;

   //}


   //bool interaction_impl::has_keyboard_focus()
   //{

   //   au

   //   return m_pwindow->has_keyboard_focus();

   //}


   //bool interaction_impl::is_active()
   //{

   //   return m_pwindow->is_active();

   //}


   //bool interaction_impl::XXXSetFocus()
   //{

   //   return m_pwindow->XXXSetFocus();

   //}


   //::user::interaction *  interaction_impl::get_desktop_window()
   //{

   //   return m_pwindow->get_desktop_window();

   //}


   //int interaction_impl::GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)
   //{
   //   for (int nID = nIDFirstButton; nID <= nIDLastButton; nID++)
   //   {
   //      if (IsDlgButtonChecked(nID))
   //         return nID; // atom that matched
   //   }
   //   return 0; // invalid ID
   //}


   //void interaction_impl::CheckDlgButton(int nIDButton, unsigned int nCheck)
   //{

   //   ASSERT(_is_window());

   //   ::CheckDlgButton(get_handle(), nIDButton, nCheck);

   //}


   //void interaction_impl::CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
   //{

   //   ASSERT(_is_window());

   //   ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);

   //}


   //int interaction_impl::DlgDirList(TCHAR * pPathSpec, int nIDListBox, int nIDStaticPath, unsigned int nFileType)

   //{

   //   ASSERT(_is_window());

   //   return ::DlgDirList(get_handle(), pPathSpec, nIDListBox, nIDStaticPath, nFileType);


   //}


   //int interaction_impl::DlgDirListComboBox(TCHAR * pPathSpec, int nIDComboBox, int nIDStaticPath, unsigned int nFileType)

   //{

   //   ASSERT(_is_window());

   //   return ::DlgDirListComboBox(get_handle(), pPathSpec, nIDComboBox, nIDStaticPath, nFileType);


   //}


   //bool interaction_impl::DlgDirSelect(TCHAR * pString, int nSize, int nIDListBox)

   //{

   //   ASSERT(_is_window());

   //   return ::DlgDirSelectEx(get_handle(), pString, nSize, nIDListBox) != false;


   //}


   //bool interaction_impl::DlgDirSelectComboBox(TCHAR * pString, int nSize, int nIDComboBox)

   //{

   //   ASSERT(_is_window());

   //   return ::DlgDirSelectComboBoxEx(get_handle(), pString, nSize, nIDComboBox) != false;


   //}


   //void interaction_impl::get_child_by_id(atom atom, oswindow* poswindow_) const
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   ASSERT(poswindow_ != nullptr);

   //   *poswindow_ = ::GetDlgItem(((interaction_impl *)this)->get_handle(), (int)atom);

   //}


   //unsigned int interaction_impl::GetChildByIdInt(int nID, BOOL * pTrans, bool bSigned) const

   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return ::GetDlgItemInt(((interaction_impl *)this)->get_handle(), nID, pTrans, bSigned);


   //}


   //int interaction_impl::GetChildByIdText(int nID, TCHAR * pStr, int nMaxCount) const

   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return ::GetDlgItemText(((interaction_impl *)this)->get_handle(), nID, pStr, nMaxCount);


   //}


   ////::windowing::window * interaction_impl::GetNextDlgGroupItem(::windowing::window * pWndCtl, bool bPrevious) const
   ////{

   ////   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   ////   return psystem->ui_from_handle(::GetNextDlgGroupItem(((interaction_impl *)this)->get_handle(), pWndCtl->get_handle(), bPrevious));

   ////}


   ////::windowing::window * interaction_impl::GetNextDlgTabItem(::windowing::window * pWndCtl, bool bPrevious) const
   ////{

   ////   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   ////   return psystem->ui_from_handle(::GetNextDlgTabItem(((interaction_impl *)this)->get_handle(), pWndCtl->get_handle(), bPrevious));

   ////}


   //unsigned int interaction_impl::IsDlgButtonChecked(int nIDButton) const
   //{
   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));
   //   return ::IsDlgButtonChecked(((interaction_impl *)this)->get_handle(), nIDButton);
   //}


   //lparam interaction_impl::SendDlgItemMessage(int nID, unsigned int message, wparam wParam, lparam lParam)
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return ::SendDlgItemMessage(((interaction_impl *)this)->get_handle(), message, message, wParam, lParam);

   //}


   //void interaction_impl::SetDlgItemInt(int nID, unsigned int nValue, bool bSigned)
   //{
   //   ASSERT(_is_window());
   //   ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);
   //}
   //void interaction_impl::SetDlgItemText(int nID, const ::string & pszString)

   //{
   //   ASSERT(_is_window());
   //   ::SetDlgItemTextW(get_handle(), nID, wstring(pszString));

   //}
   //int interaction_impl::ScrollWindowEx(int dx, int dy,
   //   const ::int_rectangle * pRectScroll, const ::int_rectangle * lpRectClip,

   //                                     ::draw2d::region* prgnUpdate, ::int_rectangle * pRectUpdate, unsigned int flags)

   //{

   //   //ASSERT(_is_window());
   //   //return ::ScrollWindowEx(get_handle(), dx, dy, pRectScroll, lpRectClip,

   //   //                        (HRGN)prgnUpdate->get_os_data(), pRectUpdate, flags);

   //   return 0;


   //}

   //void interaction_impl::ShowScrollBar(unsigned int nBar, bool bShow)
   //{
   //   ASSERT(_is_window());
   //   ::ShowScrollBar(get_handle(), nBar, bShow);
   //}
   //::user::interaction * interaction_impl::ChildWindowFromPoint(const ::int_point & point)
   //{
   //   ASSERT(_is_window());

   //   return  psystem->ui_from_handle(::ChildWindowFromPoint(get_handle(), int_point));


   //}

   //::user::interaction * interaction_impl::ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags)
   //{
   //   ASSERT(_is_window());

   //   return  psystem->ui_from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));


   //}



   ::user::interaction * interaction_impl::get_next_window(unsigned int nFlag)
   {

      auto pwindow = m_pwindow->get_next_window(nFlag);

      auto puserinteraction = __user_interaction(pwindow);

      return puserinteraction;
      
      //if (!_is_window())
      //   return nullptr;

      //return  psystem->ui_from_handle(::GetNextWindow(get_handle(), nFlag));

   }


   ::user::interaction * interaction_impl::get_top_window() const
   {

      auto pwindow = m_pwindow->get_top_window();

      auto puserinteraction = __user_interaction(pwindow);

      return puserinteraction;

   }


   ::user::interaction * interaction_impl::get_window(unsigned int nCmd) const
   {

      auto pwindow = m_pwindow->get_window(nCmd);

      auto puserinteraction = __user_interaction(pwindow);

      return puserinteraction;

   }


   ::user::interaction * interaction_impl::get_last_active_popup() const
   {

      /*ASSERT(_is_window());

      return psystem->ui_from_handle(::GetLastActivePopup(get_handle()));*/

      return nullptr;

   }



   //bool interaction_impl::FlashWindow(bool bInvert)
   //{

   //   ASSERT(_is_window());

   //   return ::FlashWindow(get_handle(), bInvert) != false;

   //}

   //bool interaction_impl::ChangeClipboardChain(::windowing::window * pwindow_Next)
   //{

   //   ASSERT(_is_window());

   //   return ::ChangeClipboardChain(get_handle(), oswindow_Next) != false;

   //}

   //oswindow interaction_impl::SetClipboardViewer()
   //{

   //   ASSERT(_is_window());

   //   return ::SetClipboardViewer(get_handle());

   //}

   //
   //bool interaction_impl::open_clipboard()
   //{

   //   if (m_bClipboardOpened)
   //   {

   //      return true;

   //   }

   //   if (!::OpenClipboard(get_handle()))
   //   {

   //      return false;

   //   }

   //   m_bClipboardOpened = true;

   //   return true;

   //}



   //bool interaction_impl::close_clipboard()
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


   //::user::interaction * interaction_impl::GetOpenClipboardWindow()
   //{

   //   return psystem->ui_from_handle(::GetOpenClipboardWindow());

   //}

   //::user::interaction * interaction_impl::GetClipboardOwner()
   //{

   //   return psystem->ui_from_handle(::GetClipboardOwner());

   //}

   //::user::interaction * interaction_impl::GetClipboardViewer()
   //{

   //   return psystem->ui_from_handle(::GetClipboardViewer());

   //}



   int_point interaction_impl::GetCaretPos()
   {

      return m_pwindow->GetCaretPos();

   }

   //   ::int_point point;

   //   ::GetCaretPos((::int_point *)&point);

   //   return point;

   //}


   void interaction_impl::SetCaretPos(const ::int_point & point)
   {

      m_pwindow->SetCaretPos(point);

   }


   void interaction_impl::HideCaret()
   {

      m_pwindow->HideCaret();

   }


   void interaction_impl::ShowCaret()
   {

      m_pwindow->ShowCaret();

   }


   //bool interaction_impl::set_foreground_window()
   //{

   //   return m_pwindow->set_foreground_window();

   //}


   //::user::interaction * interaction_impl::get_foreground_window()
   //{

   //   return m_pwindow->get_foreground_window();

   //}


   //bool interaction_impl::SendNotifyMessage(unsigned int message, wparam wParam, lparam lParam)
   //{

   //   return ::SendNotifyMessage(get_handle(), message, wParam, lParam) != false;

   //}


   void interaction_impl::set_icon(::windowing::icon * picon)
   {

      return m_pwindow->set_icon(picon);

   }


   ::pointer<::windowing::icon>interaction_impl::get_icon() const
   {

      return m_pwindow->get_icon();

   }




   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
   {

      ASSERT(_is_window());

      throw ::interface_only();
      //      const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINT, (wparam)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (lparam) dwFlags);

   }


   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const
   {

      ASSERT(_is_window());

      throw ::interface_only();
      //const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (wparam)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (lparam) dwFlags);

   }

   //bool interaction_impl::SetWindowContextHelpId(unsigned int dwContextHelpId)
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return ::SetWindowContextHelpId(((interaction_impl *)this)->get_handle(), dwContextHelpId) != false;

   //}

   //unsigned int interaction_impl::GetWindowContextHelpId() const
   //{

   //   ASSERT(::is_window(((interaction_impl *)this)->get_handle()));

   //   return ::GetWindowContextHelpId(((interaction_impl *)this)->get_handle());

   //}


// Default message map implementations
   //void interaction_impl::OnActivateApp(bool, unsigned int)
   //{
   //   Default();
   //}
   //void interaction_impl::OnActivate(unsigned int, ::windowing::window *, bool)
   //{
   //   Default();
   //}
   //void interaction_impl::OnCancelMode()
   //{
   //   Default();
   //}
   //void interaction_impl::OnChildActivate()
   //{
   //   Default();
   //}
   //void interaction_impl::OnClose()
   //{
   //   Default();
   //}
   //void interaction_impl::OnContextMenu(::windowing::window *, int_point)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnCopyData(::windowing::window *, COPYDATASTRUCT*)
   //{

   //   return Default() != false;

   //}

   //void interaction_impl::OnEnable(bool)
   //{
   //   Default();
   //}
   //void interaction_impl::OnEndSession(bool)
   //{
   //   Default();
   //}

   //bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   //{

   //   return Default() != false;

   //}

   //void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   //{
   //   Default();
   //}
   //void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   //{
   //   Default();
   //}


   //void interaction_impl::on_message_set_focus(::message::message * pusermessage)
   //{

   //   m_bFocusImpl = true;

   //   if (!m_bSystemCaret)
   //   {

   //      m_bSystemCaret = true;

   //      //::CreateCaret(m_oswindow, nullptr, 1, 1);

   //   }

   //}


   //void interaction_impl::on_message_kill_focus(::message::message * pmessage)
   //{

   //   m_bFocusImpl = false;

   //   if (m_bSystemCaret)
   //   {

   //      m_bSystemCaret = false;

   //      ::DestroyCaret();

   //   }

   //}


   //lresult interaction_impl::OnMenuChar(unsigned int, unsigned int, ::user::menu*)
   //{

   //   return Default();

   //}


   //void interaction_impl::OnMenuSelect(unsigned int, unsigned int, HMENU)
   //{

   //   Default();

   //}


   //void interaction_impl::OnMove(int, int)
   //{

   //   Default();

   //}


   //hcursor interaction_impl::OnQueryDragIcon()
   //{

   //   return (hcursor)Default();

   //}

   //bool interaction_impl::OnQueryEndSession()
   //{

   //   return Default() != false;

   //}

   //bool interaction_impl::OnQueryNewPalette()
   //{

   //   return Default() != false;

   //}

   //bool interaction_impl::OnQueryOpen()
   //{

   //   return Default() != false;

   //}


   //void interaction_impl::on_message_set_cursor(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   

   //   auto pcursor = psession->get_cursor();

   //   if (pcursor != nullptr && pcursor->m_ecursor != cursor_system)
   //   {

   //      pcursor->set_current(m_puserinteraction, psession);

   //   }

   //   pusermessage->m_lresult = 1;

   //   pusermessage->m_bRet = true;

   //}


   //void interaction_impl::OnShowWindow(bool, unsigned int)
   //{

   //   Default();

   //}


   //void interaction_impl::OnSize(unsigned int, int, int)
   //{

   //   Default();

   //}


   //void interaction_impl::OnTCard(unsigned int, unsigned int)
   //{

   //   Default();

   //}


   //void interaction_impl::_001OnWindowPosChanging(::message::message * pmessage)
   //{

   //   return;

   //}


   //void interaction_impl::_001OnWindowPosChanged(::message::message * pmessage)
   //{

   //   WINDOWPOS * pwindowpos = (WINDOWPOS *) pmessage->m_lparam.m_lparam;

   //   output_debug_string("\ninteraction_impl::_001OnWindowPosChanged");

   //   if (::is_ok(m_pwindow))
   //   {

   //      if (m_puserinteraction->layout().sketch().display() != ::e_display_iconic)
   //      {

   //         output_debug_string(" IsIconic or not IsIconic, thats the question interaction_impl::_001OnWindowPosChanged");

   //      }

   //   }
   //   else if (::IsZoomed(get_handle()))
   //   {

   //      if (m_puserinteraction->layout().window().display() != ::e_display_zoomed)
   //      {

   //         output_debug_string(" IsZoomed or not IsZoomed, thats the question interaction_impl::_001OnWindowPosChanged");

   //      }

   //   }

   //   
   //   if (m_bDestroyImplOnly)
   //   {

   //      return;

   //   }

   //   if (m_puserinteraction->layout().m_eflag)
   //   {

   //      return;

   //   }

   //   ::int_point point(pwindowpos->x, pwindowpos->y);

   //   bool bMove = false;

   //   if (m_puserinteraction->layout().sketch().origin() != int_point)
   //   {

   //      if (m_puserinteraction->layout().is_moving())
   //      {

   //         information() << "Window is Moving :: on_message_move";

   //      }

   //      m_puserinteraction->layout().sketch().origin() = point;

   //      bMove = true;

   //   }

   //   ::int_size size(pwindowpos->cx, pwindowpos->cy);

   //   bool bSize = false;

   //   if (m_puserinteraction->layout().sketch().size() != int_size)
   //   {

   //      m_puserinteraction->layout().sketch().size() = size;

   //      bSize = true;

   //   }

   //   if (bMove)
   //   {

   //      m_puserinteraction->set_reposition();

   //      m_puserinteraction->set_need_redraw();

   //   }

   //   if (bSize)
   //   {

   //      m_puserinteraction->set_need_layout();

   //   }

   //   if (bMove || bSize)
   //   {

   //      m_puserinteraction->set_need_redraw();

   //   }


   //   pmessage->m_bRet = true;

   //}


   //void interaction_impl::_001OnGetMinMaxInfo(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //}

//   void interaction_impl::OnDropFiles(HDROP)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteIsChanging(::windowing::window *)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnNcActivate(bool)
//   {
//
//      return Default() != false;
//
//   }
//
//   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnNcCreate(::user::system *)
//   {
//
//      return Default() != false;
//
//   }
//
//   lresult interaction_impl::OnNcHitTest(const int_point & )
//   {
//      return Default();
//   }
//   void interaction_impl::OnNcLButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcLButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcMouseMove(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcPaint()
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnNcRButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysChar(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysCommand(unsigned int, lparam)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysDeadChar(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyDown(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnSysKeyUp(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnCompacting(unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnFontChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnPaletteChanged(::windowing::window *)
//   {
//      Default();
//   }
//   void interaction_impl::OnSpoolerStatus(unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnTimeChange()
//   {
//      Default();
//   }
//   void interaction_impl::OnChar(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnDeadChar(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyDown(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnKeyUp(unsigned int, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnLButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnMButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   int interaction_impl::OnMouseActivate(::windowing::window *, unsigned int, unsigned int)
//   {
//      return (int)Default();
//   }
//   void interaction_impl::OnMouseMove(unsigned int, const int_point&)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnMouseWheel(unsigned int, short, const int_point&)
//   {
//
//      return Default() != false;
//
//   }
//
//   lresult interaction_impl::OnRegisteredMouseWheel(wparam, lparam)
//   {
//      return Default();
//   }
//   void interaction_impl::OnRButtonDblClk(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonDown(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnRButtonUp(unsigned int, const int_point&)
//   {
//      Default();
//   }
//   void interaction_impl::OnTimer(uptr)
//   {
//      Default();
//   }
//   void interaction_impl::OnInitMenu(::user::menu*)
//   {
//      Default();
//   }
//   void interaction_impl::OnInitMenuPopup(::user::menu*, unsigned int, bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnAskCbFormatName(__in unsigned int nMaxCount, __out_ecount_z(nMaxCount) char * lpszName)
//   {
//      (nMaxCount);
//      if (nMaxCount > 0)
//      {
//         /* defwindow proc should do this for us, but to be safe, we'hi do it here too */
//         lpszName[0] = '\0';
//      }
//      Default();
//   }
//   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
//   {
//      Default();
//   }
//   void interaction_impl::OnDestroyClipboard()
//   {
//      Default();
//   }
//   void interaction_impl::OnDrawClipboard()
//   {
//      Default();
//   }
//   void interaction_impl::OnHScrollClipboard(::windowing::window *, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnPaintClipboard(::windowing::window *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderAllFormats()
//   {
//      Default();
//   }
//   void interaction_impl::OnRenderFormat(unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnSizeClipboard(::windowing::window *, HGLOBAL)
//   {
//      Default();
//   }
//   void interaction_impl::OnVScrollClipboard(::windowing::window *, unsigned int, unsigned int)
//   {
//      Default();
//   }
//   unsigned int interaction_impl::OnGetDlgCode()
//   {
//      return (unsigned int)Default();
//   }
//   void interaction_impl::OnMDIActivate(bool, ::windowing::window *, ::windowing::window *)
//   {
//      Default();
//   }
//   void interaction_impl::OnEnterMenuLoop(bool)
//   {
//      Default();
//   }
//   void interaction_impl::OnExitMenuLoop(bool)
//   {
//      Default();
//   }
//// Win4 support
//   void interaction_impl::OnStyleChanged(int, LPSTYLESTRUCT)
//   {
//      Default();
//   }
//   void interaction_impl::OnStyleChanging(int, LPSTYLESTRUCT)
//   {
//      Default();
//   }
//   void interaction_impl::OnSizing(unsigned int, ::int_rectangle *)
//   {
//      Default();
//   }
//   void interaction_impl::OnMoving(unsigned int, ::int_rectangle *)
//   {
//      Default();
//   }
//   void interaction_impl::OnCaptureChanged(::windowing::window *)
//   {
//      Default();
//   }
//
//   bool interaction_impl::OnDeviceChange(unsigned int, uptr)
//   {
//
//      return Default() != false;
//
//   }
//
//   void interaction_impl::OnWinIniChange(const ::string &)
//   {
//      Default();
//   }
//   void interaction_impl::OnChangeUIState(unsigned int, unsigned int)
//   {
//      Default();
//   }
//   void interaction_impl::OnUpdateUIState(unsigned int, unsigned int)
//   {
//      Default();
//   }
//   unsigned int interaction_impl::OnQueryUIState()
//   {
//      return (unsigned int)Default();
//   }

// interaction_impl dialog data support
//    void interaction_impl::do_data_exchange(CDataExchange*)
//   { } // default does nothing

// interaction_impl modality support

   //void interaction_impl::BeginModalState()
   //{

   //   ::EnableWindow(get_handle(), false);

   //}

   //void interaction_impl::EndModalState()
   //{

   //   ::EnableWindow(get_handle(), true);

   //}

// frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
   { m_nIdleFlags |= idleTitle; }
   void frame_window::DelayRecalcLayout(bool bNotify)
   { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
   bool frame_window::InModalState() const
   { return m_cModalStack != 0; }
   void frame_window::set_title(const ::string & pszTitle)

   { m_strTitle = pszTitle; }

   string frame_window::get_title() const
   { return m_strTitle; }
   */



   //void interaction_impl::CloseWindow()
   //{
   //   ASSERT(_is_window());
   //   ::CloseWindow(get_handle());
   //}

   //bool interaction_impl::OpenIcon()
   //{

   //   ASSERT(_is_window());

   //   return ::OpenIcon(get_handle()) != false;

   //}

////////////////////////////////////////////////////////////////////////////
// UI related interaction_impl functions

   //oswindow interaction_impl::get_safe_owner(oswindow hParent, oswindow* pWndTop)
   //{
   //   // get interaction_impl to start with
   //   ::windowing::window * pwindow = hParent;
   //   if (oswindow == nullptr)
   //   {
   //      /* trans      ::pointer<::user::frame_window>pFrame = channel::GetRoutingFrame_();
   //      if (pFrame != nullptr)
   //      oswindow = pFrame->get_handle();
   //      else
   //      oswindow = psystem->m_puiMain->get_handle();*/
   //   }

   //   // a popup interaction_impl cannot be owned by a child interaction_impl
   //   while (oswindow != nullptr && (::GetWindowLong(oswindow, GWL_STYLE) & WS_CHILD))
   //   {

   //      oswindow = ::GetParent(oswindow);

   //   }

   //   // determine toplevel interaction_impl to disable as well
   //   ::windowing::window * pwindow_Top = oswindow;
   //   ::windowing::window * pwindow_Temp = oswindow;
   //   for (;;)
   //   {
   //      if (oswindow_Temp == nullptr)
   //         break;
   //      else
   //         oswindow_Top = oswindow_Temp;
   //      oswindow_Temp = ::GetParent(oswindow_Top);
   //   }

   //   // get last active popup of first non-child that was found
   //   if (hParent == nullptr && oswindow != nullptr)
   //      oswindow = ::GetLastActivePopup(oswindow);

   //   // disable and store top level parent interaction_impl if specified
   //   if (pWndTop != nullptr)
   //   {
   //      if (oswindow_Top != nullptr && ::IsWindowEnabled(oswindow_Top) && oswindow_Top != oswindow)
   //      {
   //         *pWndTop = oswindow_Top;
   //         ::EnableWindow(oswindow_Top, false);
   //      }
   //      else
   //         *pWndTop = nullptr;
   //   }

   //   return oswindow;    // return the owner as oswindow
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

   //   ::windows::interaction_impl * puserinteraction = thread_set("wnd_init");

   //   if (puserinteraction != nullptr || (!(pcs->style & WS_CHILD)))
   //   {

   //      thread_set("wnd_init") = nullptr;

   //      // Note: special check to avoid subclassing the IME interaction_impl
   //      //if (gen_DBCS)
   //      {
   //         // check for cheap CS_IME style first...
   //         if (GetClassLongW((oswindow)wParam, GCL_STYLE) & CS_IME)
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

   //      ::windowing::window * pwindow = (::oswindow) wParam;

   //      if (puserinteraction != nullptr)
   //      {

   //         ASSERT(oswindow_get(oswindow) == nullptr);

   //         puserinteraction->m_puserinteraction->m_pimpl = puserinteraction;

   //         puserinteraction->attach(oswindow);

   //         puserinteraction->pre_subclass_window();

   //         WNDPROC * ppuserinteractionprocSuper = puserinteraction->GetSuperWndProcAddr();

   //         ASSERT(ppuserinteractionprocSuper != nullptr);

   //         WNDPROC puserinteractionprocOld = (WNDPROC)SetWindowLongPtrW(oswindow, GWLP_WNDPROC, (uptr)get_window_procedure();

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


   //void interaction_impl::_001OnEraseBkgnd(::message::message * pmessage)
   //{
   //   ::pointer<::message::erase_bkgnd>perasebkgnd(pmessage);
   //   perasebkgnd->m_bRet = true;
   //   perasebkgnd->set_result(true);
   //}



   void interaction_impl::_001OnTriggerMouseInside()
   {

      ::windowing::window::_001OnTriggerMouseInside();

      //TRACKMOUSEEVENT tme = { sizeof(tme) };
      //tme.dwFlags = TME_LEAVE;
      //tme.hwndTrack = get_handle();
      //TrackMouseEvent(&tme);

   }



   void interaction_impl::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      // graphics will be already set its impact port to the interaction_impl for linux - cairo with xlib

      pgraphics->SetViewportOrg(::int_point());

   }


   /*

/*   void interaction_impl::_001DeferPaintLayeredWindowBackground(::image::image * pimage)
   {


   }

   */



   bool interaction_impl::get_rect_normal(::int_rectangle * prectangle)

   {

      return false;
      //WINDOWPLACEMENT wp;

      //zero(wp);

      //if (!GetWindowPlacement(&wp))
      //{

      //   return false;

      //}

      //*prectangle = wp.rcNormalPosition;

      //return true;

   }


   void interaction_impl::register_drop_target()
   {

      //m_bUseDnDHelper = false;

      //::CreateThread(nullptr, 0, drop_target, this, 0, nullptr);

   }


   void interaction_impl::show_task(bool bShow)
   {

      synchronous_lock synchronouslock(mutex());

      // https://www.daniweb.com/programming/software-development/threads/457564/mfc-application-disablehide-taskbar-icon

      m_pwindow->show_task(bShow);


   }


   /*bool interaction_impl::set_window_position(class ::user::zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
   {

      if (!::windowing::window::set_window_position(zorder, x, y, cx, cy, nFlags))
      {

         return false;

      }

      if (!(GetExStyle() & WS_EX_LAYERED))
      {


         if (!::set_window_position(get_handle(), zorder, x, y, cx, cy, nFlags))
         {

            return false;

         }

      }

      return true;

   }
*/


   void interaction_impl::window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation)
   {

      ::windowing::window::window_show_change_visibility(edisplay, useractivation);

   }


   //void interaction_impl::_001OnActivate(::message::message* pmessage)
   //{

   //   BOOL enabled = false;

   //   DwmIsCompositionEnabled(&enabled);

   //   //data->composition_enabled = enabled;

   //   if (enabled)
   //   {

   //      /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */

   //      MARGINS m = { 0,0,0,0 };

   //      unsigned int  dw = DWMNCRP_ENABLED;

   //      DwmExtendFrameIntoClientArea(get_safe_handle(), &m);

   //      DwmSetWindowAttribute(get_safe_handle(), DWMWA_NCRENDERING_POLICY, &dw, sizeof(unsigned int));

   //   }
   //   else
   //   {

   //   }

   //}


//   void interaction_impl::_001OnDwmNcRenderingChanged(::message::message* pmessage)
//   {
//
////#ifdef WINDOWS_DESKTOP
//
//      ::pointer<::user::message>pusermessage(pmessage);
//
//      wparam wparam;
//
//      lparam lparam;
//
//      wparam = pusermessage->m_wparam;
//
//      lparam = pusermessage->m_lparam;
//
//      //return Default();
//
//      BOOL enabled = false;
//
//      DwmIsCompositionEnabled(&enabled);
//
//      //data->composition_enabled = enabled;
//
//      if (enabled)
//      {
//
//         /* The u needs a frame to show a shadow, so give it the smallest amount of frame possible */
//
//         MARGINS m = { 0,0,0,0 };
//
//         unsigned int  dw = DWMNCRP_ENABLED;
//
//         DwmExtendFrameIntoClientArea(get_safe_handle(), &m);
//
//         HWND hwnd = get_safe_handle();
//
//         DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &dw, sizeof(unsigned int));
//
//      }
//      else
//      {
//
//      }
//
//      //update_region(data);
//      //      long dwEx = ::GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
//      //      dwEx &= ~(WS_EX_LAYERED);
//      //      ::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,dwEx);
//      //      ::InvalidateRect(GetSafeHwnd(),nullptr,true);
//      //      ::UpdateWindow(GetSafeHwnd());
//      //      //MoveAnchorsImmediatelly(hwndDlg);
//      pusermessage->m_bRet = true;
//
//      pusermessage->m_lresult = 0;
//
////#endif
//
//   }


//   void interaction_impl::on_message_non_client_calculate_size(::message::message* pmessage)
//   {
//
////#ifdef WINDOWS_DESKTOP
//
//      ::pointer<::message::nc_calc_size>pcalcsize(pmessage);
//
//      BOOL bCalcValidRects = pcalcsize->GetCalcValidRects();
//      NCCALCSIZE_PARAMS* pncsp = pcalcsize->m_pparams;
//
//
//      // TODO: Add your message handler code here and/or call default
//      //if(bCalcValidRects)
//      //{
//      //   informationf("1");
//      //   pncsp->rgrc[0].left() = lpncsp->lppos->x + 1;
//
//      //   pncsp->rgrc[0].right() = lpncsp->lppos->x + lpncsp->lppos->cx - 1;
//
//      //   pncsp->rgrc[0].top() = lpncsp->lppos->y + 32;
//
//      //   pncsp->rgrc[0].bottom() = lpncsp->lppos->y + lpncsp->lppos->cy - 1;
//
//      //}
//      //else
//      //{
//      //   CRect * prectangle = (CRect *) pncsp;
//
//      //   prectangle->top() += 32;
//      //   prectangle->left()++;
//      //   prectangle->bottom()--;
//      //   prectangle->right()--;
//
//      //   informationf("2");
//      //}
//      const int_rectangle& nonclient = pncsp->rgrc[0];
//
//      //CMiniFrameWnd::OnNcCalcSize(bCalcValidRects, pncsp);
//
//      const int_rectangle& client = pncsp->rgrc[0];
//
//      if (node_is_zoomed())
//      {
//         WINDOWINFO wi = {};
//         wi.cbSize = sizeof(wi);
//         ::GetWindowInfo(get_safe_handle(), &wi);
//
//         /* Maximized windows always have a non-client border that hangs over
//         the edge of the screen, so the int_size proposed by e_message_non_client_calcsize is
//         fine. Just adjust the top border to erase the u title. */
//         pncsp->rgrc[0].left() = client.left();
//
//         pncsp->rgrc[0].top() = nonclient.top() + wi.cyWindowBorders;
//
//         pncsp->rgrc[0].right() = client.right();
//
//         pncsp->rgrc[0].bottom() = client.bottom();
//
//
//         HMONITOR mon = MonitorFromWindow(get_safe_handle(), MONITOR_DEFAULTTOPRIMARY);
//         MONITORINFO mi = {};
//         mi.cbSize = sizeof(mi);
//         GetMonitorInfoW(mon, &mi);
//
//         /* If the client int_rectangle is the same as the monitor's rectangle,
//         the shell assumes that the u has gone fullscreen, so it erases
//         the topmost attribute from any auto-hide appbars, making them
//         inaccessible. To avoid this, reduce the int_size of the client area by
//         one pixel on a certain edge. The edge is chosen based on which side
//         of the monitor is likely to contain an auto-hide appbar, so the
//         missing client area is covered by it. */
//         if (EqualRect(&pncsp->rgrc[0], &mi.rcMonitor))
//
//         {
//            if (has_autohide_appbar(ABE_BOTTOM, mi.rcMonitor))
//               pncsp->rgrc[0].bottom()--;
//
//            else if (has_autohide_appbar(ABE_LEFT, mi.rcMonitor))
//               pncsp->rgrc[0].left()++;
//
//            else if (has_autohide_appbar(ABE_TOP, mi.rcMonitor))
//               pncsp->rgrc[0].top()++;
//
//            else if (has_autohide_appbar(ABE_RIGHT, mi.rcMonitor))
//               pncsp->rgrc[0].right()--;
//
//         }
//      }
//      else
//      {
//         /* For the non-maximized case, set the output const int_rectangle & to what it was
//         before e_message_non_client_calcsize modified it. This will make the client int_size the
//         same as the non-client size. */
//         pncsp->rgrc[0] = nonclient;
//
//
//      }
//
//
//      //::pointer<::user::message>pusermessage(pmessage);
//
//      pcalcsize->m_lresult = 0;
//
//      pcalcsize->m_bRet = true;
//
////#endif
//
//   }


void interaction_impl::set_tool_window(bool bSet)
{

   return m_pwindow->set_tool_window(bSet);


}

} // namespace windows

//
//
//bool is_registered_windows_message(unsigned int message)
//{
//
//   return message >= 0xc000 && message <= 0xffff;
//
//}
//
//
//lresult CALLBACK WndProc(HWND oswindow, unsigned int message, wparam wparam, lparam lparam);
//
//int g_iCol = 0;
//
//lresult CALLBACK __window_procedure(HWND oswindow, unsigned int message, wparam wparam, lparam lparam)
//{
//
//   ::windowing::window * pimpl = oswindow_interaction_impl(oswindow);
//
//   lresult lresult = 0;
//
//   if (is_registered_windows_message(message))
//   {
//
//      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);
//
//      return lresult;
//
//   }
//
//   if (pimpl)
//   {
//
//      if (pimpl->__windows_message_bypass(oswindow, message, wparam, lparam, lresult))
//      {
//
//         return lresult;
//
//      }
//
//   }
//
//   //return ::DefWindowProcW(oswindow, message, wparam, lparam);
//
//   if (::get_context_system() == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   if (::auraacmesystem() == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   pimpl->m_uiMessage = message;
//
//   pimpl->m_wparam = wparam;
//
//   pimpl->m_lparam = lparam;
//
//   ::user::interaction * pinteraction = pimpl->m_puserinteraction;
//
//   if (message == e_message_activate)
//   {
//
//      output_debug_string("test");
//
//   }
//
//   if (message == e_message_left_button_up)
//   {
//
//      ::output_debug_string("e_message_left_button_up");
//
//   }
//
//   if (message == e_message_mouse_move)
//   {
//
//      if (lparam == pimpl->m_lparamLastMouseMove)
//      {
//
//         return 0;
//
//      }
//
//      pimpl->m_lparamLastMouseMove = lparam;
//
//      ::int_point pointCursor;
//
//      ::GetCursorPos(pointCursor);
//
//      if (pimpl->m_pointCursor == pointCursor)
//      {
//
//         return 0;
//
//      }
//
//      pimpl->m_pointCursor = pointCursor;
//
//   }
//   else if (message == e_message_timer)
//   {
//
//      if (wparam == e_timer_transparent_mouse_event)
//      {
//
//         ::int_point pointCursor;
//
//         ::GetCursorPos(pointCursor);
//
//         if (pimpl->m_pointCursor == pointCursor)
//         {
//
//            return 0;
//
//         }
//
//         pimpl->m_pointCursor = pointCursor;
//
//         lparam lparam;
//
//         ::ScreenToClient(oswindow, pointCursor);
//
//         lparam = MAKELPARAM(pointCursor.x(), pointCursor.y());
//
//         pimpl->call_message_handler(e_message_mouse_move, 0, lparam);
//
//      }
//      else
//      {
//
//         // ignoring Timer Event
//
//         output_debug_string("iTE\n");
//
//      }
//
//      return 0;
//
//   }
//
//   if (pimpl->m_bDestroyImplOnly || ::is_null(pinteraction))
//   {
//
//      auto pusermessage = pimpl->get_message_base(oswindow, (enum_message) message, wparam, lparam);
//
//      try
//      {
//
//         pimpl->message_handler(pusermessage);
//
//      }
//      catch (...)
//      {
//
//      }
//      
//      if (!pusermessage->m_bRet)
//      {
//
//         pimpl->default_message_handler(pusermessage);
//
//      }
//
//      lresult = pusermessage->m_lresult;
//
//   }
//   else if (::is_set(pinteraction))
//   {
//
//      if (message == WM_GETTEXT)
//      {
//
//         return ::DefWindowProcW(oswindow, message, wparam, lparam);
//         
//      }
//      else if (message == WM_GETTEXTLENGTH)
//      {
//
//         return ::DefWindowProcW(oswindow, message, wparam, lparam);
//
//      }
//      else if (message == WM_SETTEXT)
//      {
//
//         return ::DefWindowProcW(oswindow, message, wparam, lparam);
//
//      }
//
//      auto pusermessage = pinteraction->get_message_base(oswindow,(enum_message) message, wparam, lparam);
//
//      try
//      {
//
//         pinteraction->message_handler(pusermessage);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      if (!pusermessage->m_bRet)
//      {
//
//         pinteraction->default_message_handler(pusermessage);
//
//      }
//
//      lresult = pusermessage->m_lresult;
//
//   }
//   else
//   {
//
//      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);
//
//   }
//
//   return lresult;
//
//}
//
//




//CLASS_DECL_AURA_WINDOWS bool hook_window_create(::windows::interaction_impl * pwindow)
//{
//
//   if (pwindow == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (pwindow->get_handle() != nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      t_hHookOldCbtFilter = ::SetWindowsHookExW(WH_CBT, windows::__cbt_filter_hook, nullptr, ::GetCurrentThreadId());
//
//      if (t_hHookOldCbtFilter == nullptr)
//      {
//
//         return false;
//
//      }
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      return false;
//
//   }
//
//   thread_set("wnd_init") = pwindow;
//
//   if (thread_set("wnd_init") == nullptr)   // hook not already in progress
//   {
//
//      return false;
//
//   }
//
//   if (thread_set("wnd_init") != pwindow)
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//CLASS_DECL_AURA_WINDOWS bool unhook_window_create()
//{
//
//   if (thread_set("wnd_init") != nullptr)
//   {
//
//      thread_set("wnd_init") = nullptr;
//
//      return false;   // was not successfully hooked
//
//   }
//
//   return true;
//
//}
//

//
//void CLASS_DECL_AURA_WINDOWS _handle_activate(::windowing::window * pwindow, wparam nState, ::windowing::window * pWndOther)
//{
//
//   ASSERT(pwindow);
//
//   // send WM_ACTIVATETOPLEVEL when top-level parents change
//   if (!((pwindow)->GetStyle() & WS_CHILD))
//   {
//      
//      ::pointer<::user::interaction>pTopLevel = pwindow->get_top_level();
//
//      if (pTopLevel && (!pWndOther || !::is_window((pWndOther)->get_handle()) || pTopLevel != (pWndOther)->get_top_level()))
//      {
//         // lParam points to interaction_impl getting the e_message_activate message and
//         //  oswindow_Other from the e_message_activate.
//         ::windowing::window * pwindow_2[2];
//         oswindow_2[0] = (pwindow)->get_handle();
//         if (!pWndOther)
//         {
//            oswindow_2[1] = nullptr;
//         }
//         else
//         {
//
//            oswindow_2[1] = (pWndOther)->get_handle();
//
//         }
//
//         // send it...
//         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (lparam)&oswindow_2[0]);
//
//      }
//
//   }
//
//}
//
//
//void __term_windowing()
//{
//
//   //if (t_hHookOldCbtFilter != nullptr)
//   //{
//
//   //   ::UnhookWindowsHookEx(t_hHookOldCbtFilter);
//
//   //   t_hHookOldCbtFilter = nullptr;
//
//   //}
//
//}
//





//
//namespace windows
//{
//
//
//   void interaction_impl::default_message_handler(::user::message * pusermessage)
//   {
//
//      if (get_handle() == nullptr)
//      {
//
//         return;
//
//      }
//
//      WNDPROC pfnWndProc = *GetSuperWndProcAddr();
//
//      lresult lresult = 0;
//
//      if (pfnWndProc == nullptr)
//      {
//
//         lresult = ::DefWindowProcW(m_oswindow, (unsigned int) pmessage->m_emessage.long_long(), pmessage->m_wparam, pmessage->m_lparam);
//
//      }
//      else
//      {
//
//         lresult = ::CallWindowProc(pfnWndProc, m_oswindow, (unsigned int) pmessage->m_emessage.long_long(), pmessage->m_wparam, pmessage->m_lparam);
//
//      }
//
//      pmessage->m_lresult = lresult;
//
//   }
//
//
//   bool interaction_impl::set_icon(::image::icon * picon, bool bSmall)
//   {
//
//      if (::is_null(picon))
//      {
//
//         return false;
//
//      }
//
//      hicon hicon = picon->get_os_data();
//
//      if(::is_null(hicon))
//      {	
//
//         return false;
//
//      }
//
//      if(bSmall)
//      {
// 
//         SendMessage(get_handle(), (unsigned int)WM_SETICON, ICON_SMALL, (lparam)hicon);
//
//      }
//      else
//      {
//
//         SendMessage(get_handle(), (unsigned int)WM_SETICON, ICON_BIG, (lparam)hicon);
//
//      }
//
//      return true;
//
//   }
//
//
//   void interaction_impl::message_handler(::user::message * pusermessage)
//   {
//
//      if (::is_set(m_puserinteraction))
//      {
//
//         m_puserinteraction->pre_translate_message(pusermessage);
//
//      }
//
//      if (pusermessage->m_bRet)
//      {
//
//         return;
//
//      }
//
//      unsigned int message;
//
//      message = pusermessage->id().umessage();
//
//      m_uiMessage = message;
//
//      m_wparam = pusermessage->m_wparam;
//
//      m_lparam = pusermessage->m_lparam;
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
//         pusermessage->m_lresult = ::DefWindowProcW(m_oswindow, m_uiMessage, m_wparam, m_lparam);
//
//         pusermessage->m_bRet = true;
//
//         return;
//
//      }
//
//      bool bUserElementalOk = !m_bDestroyImplOnly && m_puserinteraction && m_puserinteraction->m_bUserElementOk;
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
//         ::pointer<::message::key>pkey(pusermessage);
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
//         //         m_puserinteraction->get_application()->step_timer();
//      }
//      else if (message == e_message_left_button_down)
//      {
//         ::int_rectangle rectangleX;
//         ::GetClientRect(get_handle(), rectangleX);
//         ::int_rectangle rectangleWindow;
//         ::GetWindowRect(get_handle(), rectangleWindow);
//         ::int_rectangle rectangleRegion;
//         HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
//         int regionType = ::GetWindowRgn(get_handle(), hrgn);
//         if (regionType != ERROR)
//         {
//            ::GetRgnBox(hrgn, rectangleRegion);
//         }
//         ::DeleteObject(hrgn); /* finished with region */
//         WINDOWPLACEMENT wp;
//         zero(wp);
//         wp.length = sizeof(WINDOWPLACEMENT);
//         ::GetWindowPlacement(get_handle(), &wp);
//         bool bZoomed = ::IsZoomed(get_handle()) != false;
//         bool bIconic = ::IsIconic(get_handle()) != false;
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
//               informationf("e_message_create wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_window_position_changing:
//               informationf("e_message_window_position_changing wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_window_position_changed:
//               informationf("e_message_window_position_changed wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_activate:
//               informationf("e_message_activate wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case WM_ACTIVATEAPP:
//               informationf("WM_ACTIVATEAPP wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_mouse_activate:
//               informationf("e_message_mouse_activate wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_non_client_activate:
//               informationf("e_message_non_client_activate wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_set_focus:
//               informationf("e_message_set_focus wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_kill_focus:
//               informationf("e_message_kill_focus wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_move:
//               informationf("e_message_move wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            case e_message_size:
//               informationf("e_message_size wparam=%08x lparam=%08x", pusermessage->m_wparam, pusermessage->m_lparam);
//
//               break;
//            default:
//               informationf("MESSAGE %08x wparam=%08x lparam=%08x", message, pusermessage->m_wparam, pusermessage->m_lparam);
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
//      if(pusermessage->m_wparam == BERGEDGE_GETAPP)
//      {
//      ::pointer<::aura::application> ppapp= (::pointer<::aura::application> pusermessage->m_lparam;
//      *ppapp = get_application();
//      pusermessage->m_bRet = true;
//      return;
//      }
//      }*/
//      //pusermessage->set_lresult(0);
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
//            psession->m_puiCapture->_000OnMouseLeave(pusermessage);
//
//         }
//         else if (m_puserinteraction)
//         {
//
//            m_puserinteraction->_000OnMouseLeave(pusermessage);
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
//         message::mouse * pmouse = dynamic_cast <::message::mouse *> (pusermessage);
//
//         if (message >= WM_MOUSEFIRST
//            && message <= WM_MOUSELAST
//            && m_bTranslateMouseMessageCursor
//            && !pmouse->m_bTranslated)
//         {
//
//            pmouse->m_bTranslated = true;
//
//            ::ClientToScreen(get_handle(), &pmouse->m_point);
//
//         }
//
//         if (message == e_message_left_button_down)
//         {
//
//            informationf("e_message_left_button_down");
//
//            string strType = ::str().demangle(m_puserinteraction->type_name());
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
//            if (m_puserinteraction)
//            {
//
//               strType = ::str().demangle(m_puserinteraction->type_name());
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
//         message::drag_and_drop * pdrag = (::message::drag_and_drop *) pusermessage;
//
//         auto pinteraction = pdrag->userinteraction();
//
//         //user::oswindow_array oswindowa;
//         //user::interaction_pointer_array wnda;
//         //wnda = *psystem->m_puiptraFrame;
//         //oswindowa = wnda.get_hwnda();
//         //user::window_util::SortByZOrder(oswindowa);
//         //for (int i = 0; i < oswindowa.get_size(); i++)
//         //{
//         //   ::pointer<::user::interaction>pinteraction = wnda.find_first(oswindowa[i]);
//         //   if (pinteraction != nullptr)
//         //   {
//
//         if (pinteraction)
//         {
//            pinteraction->_000OnDrag(pdrag);
//            if (pdrag->m_bRet)
//               return;
//
//         }
//    /*        }
//         }*/
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
//         message::key * pkey = (::message::key *) pusermessage;
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
//            puiFocus = m_puserinteraction->get_keyboard_focus();
//
//         }
//
//         if (puiFocus && puiFocus->_is_window() && puiFocus != m_puserinteraction)
//         {
//
//            puiFocus->send(pkey);
//
//            if (pusermessage->m_bRet)
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
//            if (m_puserinteraction != nullptr)
//            {
//
//               m_puserinteraction->_000OnKey(pkey);
//
//               if (pusermessage->m_bRet)
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
//         //m_lparam = pusermessage->m_lparam;
//
//         //pusermessage->set_lresult(::default_window_procedure(message, pusermessage->m_wparam, pusermessage->m_lparam));
//
//         //return;
//
//      }
//
//      if (message == e_message_event)
//      {
//
//         m_puserinteraction->handle_event(pusermessage);
//
//         return;
//
//      }
//
//      ::windowing::window::message_handler(pusermessage);
//
//      //if(pmessage->m_bRet && !pusermessage->m_bDoSystemDefault)
//
//      if (pusermessage->m_bRet)
//      {
//
//         return;
//
//      }
//
//      if(message == WM_IME_STARTCOMPOSITION ||
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
//      //if (bUserElementalOk && pusermessage->m_bWindowProc)
//      //{
//      //   
//      //   if (m_puserinteraction != nullptr)
//      //   {
//      //      
//      //      m_puserinteraction->default_window_procedure(pusermessage);
//
//      //   }
//      //   else
//      //   {
//      //      
//      //      pusermessage->set_lresult(::DefWindowProcW(m_oswindow, pusermessage->id(), pusermessage->m_wparam, pusermessage->m_lparam));
//
//      //   }
//
//      //}
//
//   }
//
//
//   void interaction_impl::non_top_most_upper_window_rects(::int_rectangle_array& recta)
//   {
//
//      /// from top to bottom
//      top_level_enum toplevelenum;
//
//      auto poswindowa = toplevelenum.m_poswindowa;
//
//      ::windowing::window * pwindow = get_safe_handle();
//      
//      index iFind = poswindowa->find_first(oswindow);
//
//      if (iFind < 0)
//      {
//
//         return;
//
//      }
//
//      ::int_rectangle rHigher;
//
//      for (iFind--; iFind >= 0; iFind--)
//      {
//
//         oswindow = poswindowa->element_at(iFind);
//
//         int iExStyle = GetWindowLong(oswindow, GWL_EXSTYLE);
//
//         if ((iExStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST)
//         {
//
//            continue;
//
//         }
//
//         if (::GetWindowRect(oswindow, rHigher))
//         {
//
//            recta.add(rHigher);
//
//         }
//
//      }
//
//   }
//
//
//   void interaction_impl::finish(::object * pcontextobjectFinish)
//   {
//
//      auto estatus = set_finish(pcontextobjectFinish);
//
//      if (estatus == success)
//      {
//
//         on_finish();
//
//      }
//
//      return estatus;
//
//   }
//
//
//
//

//
//
//} // namespace windows
//



