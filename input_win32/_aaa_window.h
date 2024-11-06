// created by Camilo 2021-01-31 04:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


#include "aura/windowing/window.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 window :
      virtual public ::windowing::window,
      virtual public IDropTarget
   {
   public:


      //HICON                                         m_hiconSmall;
      //HICON                                         m_hiconBig;
      bool                                            m_bTrackMouseLeave : 1;
      WNDPROC                                         m_pfnSuper;
      //UINT                                          m_uiMessage;
      //WPARAM                                        m_wparam;
      //LPARAM                                        m_lparam;
      ::pointer<::aura_windows::interaction_impl>    m_pimpl2;
      class ::time                                      m_timeLastMouseMove;
      ::int_point                                     m_pointMouseMove;
      unsigned int                                           m_uExtraFlagsSetWindowPos;


      window();
      ~window() override;


      //void assert_ok() const override;
      //void dump(dump_context & dumpcontext) const override;


      void install_message_routing(channel* pchannel) override;



      void create_window(::windowing::window* pimpl) override;


      inline HWND get_hwnd() const { return (HWND)oswindow(); }
      inline void set_hwnd(HWND hwnd) { set_oswindow(__oswindow(hwnd)); }


      bool operator== (const window& window) const
      {
         return oswindow() == window.oswindow();
      }

      bool operator!= (const window& window) const
      {
         return !operator==(window);
      }


      ::windowing_win32::windowing* windowing() const { return m_pwindowing.cast < ::windowing_win32::windowing >(); }


      //virtual void set_oswindow(oswindow oswindow) override;


      DECLARE_MESSAGE_HANDLER(_001OnMessage);
      DECLARE_MESSAGE_HANDLER(_001OnTaskbarCreated);


      //bool defer_set_icon() override;


      //bool has_capture() const override;
      //bool has_keyboard_focus() const override;


      //void send_client_event(Atom atom, unsigned int numArgs, ...);
      //int store_name(const ::string & psz);
      //int select_input(int iInput);
      //int select_all_input();

      //virtual int map_window();

      //virtual int unmap_window(bool bWithdraw) override;

      //virtual void set_wm_class(const ::string & psz) override;

      void exit_iconify() override;

      
      void full_screen(const::int_rectangle& rectangle = {}) override;
      

      void exit_full_screen() override;

      void exit_zoomed() override;

      void set_keyboard_focus() override;

      void set_active_window() override;

      void bring_to_front() override;

      void switch_to_this_window(bool b) override;

      void set_foreground_window() override;

      void _set_foreground_window_unlocked() override;

      void set_mouse_capture() override;



      bool has_mouse_capture() const override;
      bool has_keyboard_focus() const override;


      bool is_active_window() const override;




      void destroy_window() override;

      //void _set_foreground_window_unlocked() override;

      //virtual void set_user_interaction(::layered * pinteraction) override;

      void post_non_client_destroy() override;

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      ::int_point get_mouse_cursor_host_position() override;

      ::int_point get_mouse_cursor_absolute_position() override;

//      virtual bool is_child_of(const ::windowing::window * pwindowAscendantCandidate) const override;
      
      //virtual long get_state() override;

      bool is_iconic() override;

      virtual bool is_window() override;

      virtual bool is_window_visible() override;

      //bool :window_is_iconic()

      //virtual void show_window(const::e_display & edisplay, const::e_activation & eactivation) override;
      
      bool client_to_screen(::int_point * ppoint) override;

      bool screen_to_client(::int_point * ppoint) override;

      //bool on_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide) override;

      //bool set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide) override;

      bool _configure_window_unlocked(const class ::zorder & zorder, const ::e_activation & eactivation, bool bNoZorder, ::e_display edisplay) override;

      virtual bool __set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide, unsigned int nOverrideFlags = 0);

      bool _set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy, const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay) override;

      void window_do_update_screen() override;

      //bool strict_set_window_position_unlocked() override;

      bool is_destroying() override;

      //virtual bool bamf_set_icon() override;

      //virtual bool set_icon(::image::image * pimage) override;

      //int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

      //virtual int_bool set_mouse_cursor(oswindow window, hcursor hcursor);



      virtual bool __windows_message_bypass(HWND oswindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult);

      //void install_message_routing(::channel * pchannel) override;

      //bool operator==(const interaction_impl & wnd) const;
      //bool operator!=(const interaction_impl & wnd) const;

      virtual iptr _get_style() const;
      virtual iptr _get_ex_style() const;
      virtual bool _set_style(iptr iStyle);
      virtual bool _set_ex_style(iptr iExStyle);
      virtual bool _modify_style(iptr dwRemove, iptr dwAdd, unsigned int nFlags = 0);
      virtual bool _modify_ex_style(iptr dwRemove, iptr dwAdd, unsigned int nFlags = 0);
      virtual iptr _get_window_long_ptr(int iIndex) const;
      virtual bool _set_window_long_ptr(int iIndex, ::iptr iLong);

      //virtual ::user::interaction * get_owner();
      //virtual void set_owner(::user::interaction * pOwnerWnd);

      // void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      //void _002OnDraw(::image::image * pimage);

      //virtual void present();

      //virtual void defer_start_prodevian();

      virtual void set_icon(::windowing::icon * pwindow) override;

      virtual void on_visual_applied() override;




      //virtual void window_apply_visual(const ::user::window_state & windowstate) override;

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnCreate);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
      //DECLARE_MESSAGE_HANDLER(on_message_move);
      //DECLARE_MESSAGE_HANDLER(on_message_size);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnDwmNcRenderingChanged);
      DECLARE_MESSAGE_HANDLER(_001OnProdevianSynch);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanged);
      //DECLARE_MESSAGE_HANDLER(_001OnGetMinMaxInfo);
      DECLARE_MESSAGE_HANDLER(_001OnEnable);
      DECLARE_MESSAGE_HANDLER(on_message_get_icon);


      //virtual void win_update_graphics();

//#if(WINVER >= 0x0500)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      //      virtual ::user::interaction * from_os_data(void * pdata);
      //virtual void * get_os_data() const;


      virtual void set_finish() override;


      //      virtual ::user::interaction * from_handle(HWND hwnd);

      // subclassing/unsubclassing functions
      //virtual void pre_subclass_window();
      //bool subclass_window(HWND hwnd);
      //bool SubclassDlgItem(unsigned int nID, ::windowing::window * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const ::string & pszResourceName);

      //bool ExecuteDlgInit(LPVOID pResource);


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, const ::string & pszClassName, const ::string & pszWindowName,unsigned int dwStyle,const ::int_rectangle & rectangle,::user::interaction * pParentWnd,atom atom, ::request * prequest = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pusersystem, ::user::interaction * puiParent, atom atom) override;

      //virtual void native_create_host() override;



      //virtual bool destroy_impl_only() override;
      //virtual bool DestroyWindow() override;

      //virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(::int_rectangle * pClientRect, unsigned int nAdjustType = adjustBorder);


      void get_child_by_id(atom atom, ::oswindow * poswindow_) const;

      //virtual bool _is_window() const override;

      //#if(WINVER >= 0x0500)
      //
      //      ::windowing::window * GetAncestor(unsigned int gaFlags) const;
      //
      //#endif   // WINVER >= 0x0500

      virtual lresult send_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr) override;

      virtual bool post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr) override;


      //bool SendNotifyMessage(unsigned int message, wparam wParam, lparam lParam);

      //bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //bool DragDetect(const ::int_point & point) const;



      // Window Text Functions
      void set_window_text(const ::scoped_string & scopedstr) override;

      ::string get_window_text() override;

      //virtual void get_window_text(string & rectangleString) override;
      //virtual character_count get_window_text_length() override;

      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      //virtual void on_reposition() override;
      //virtual void on_show_window() override;
      //virtual void on_zorder() override;

      //virtual void clear_need_layout() override;
      //virtual void clear_need_translation() override;
      //virtual void clear_show_flags() override;
      //virtual void clear_need_zorder() override;


      //virtual bool set_window_position(iptr z, int x, int y, int cx, int cy, unsigned int nFlags = SWP_SHOWWINDOW);


      // Window int_size and position Functions
      //virtual bool window_is_iconic() override;
      //virtual bool window_is_zoomed() override;
      //int SetWindowRgn(HRGN hRgn,bool bRedraw);
      //int GetWindowRgn(HRGN hRgn);

      virtual unsigned int ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();
      //using ::windowing::window::window_rectangle;
      //virtual bool window_rectangle(::i64_rectangle * prectangle);

      //using ::windowing::window::this->rectangle;
      //virtual bool this->rectangle(::i64_rectangle * prectangle);


      //virtual void rects_from_os();
      virtual bool window_rectangle(::int_rectangle * prectangle);
      virtual bool rectangle(::int_rectangle * prectangle);



      //virtual double_point client_screen_top_left() override;


      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl);

      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * puserinteractionpl);


      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::int_point * pPoint, unsigned int nCount);

      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::int_rectangle * prectangle);


      //virtual void Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;

      virtual void on_redraw_window(unsigned int flags) override;

      virtual void show_task(bool bShowTask) override;

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      virtual bool GetUpdateRect(::int_rectangle * prectangle, bool bErase = false);

      virtual int GetUpdateRgn(::draw2d::region * pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const ::int_rectangle * rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region * pRgn, bool bErase = true);
      virtual void ValidateRect(const ::int_rectangle * int_rectangle);

      virtual void ValidateRgn(::draw2d::region * pRgn);
      //virtual bool display(::e_display edisplay);


      //virtual void sketch_prepare_window_minimize(::e_activation eactivation) override;
      //virtual void sketch_prepare_window_maximize() override;
      //virtual void sketch_prepare_window_full_screen(const ::int_rectangle & rectangleHint = nullptr) override;
      //virtual void sketch_prepare_window_restore(::e_display edisplay) override;


      //virtual bool _is_window_visible() override;
      virtual void ShowOwnedPopups(bool bShow = true);

      virtual ::pointer<::draw2d::graphics>GetDCEx(::draw2d::region * prgnClip, unsigned int flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      virtual bool RedrawWindow(const ::int_rectangle& rectangleUpdate = {},
         ::draw2d::region * prgnUpdate = nullptr,
         unsigned int flags = RDW_INVALIDATE | RDW_ERASE);

      virtual bool EnableScrollBar(int nSBFlags, unsigned int nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo);

      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const int_rectangle & prc, unsigned int uFlags);


      //#if(WINVER >= 0x0500)
      //
      //      virtual bool AnimateWindow(const class time & time, unsigned int dwFlags);
      //
      //#endif   // WINVER >= 0x0500
      //
      //#if(_WIN32_WINNT >= 0x0501)
      //
      //      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, unsigned int nFlags) const;
      //
      //#endif   // _WIN32_WINNT >= 0x0501
      //
            // Layered Window

      //#if(_WIN32_WINNT >= 0x0500)
      //
      //      virtual bool SetLayeredWindowAttributes(::color::color crKey, unsigned char bAlpha, unsigned int dwFlags);
      //      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, ::int_point *pptDst, INT_SIZE *psize,
      //                                       ::draw2d::graphics * pDCSrc, ::int_point *pptSrc, ::color::color crKey, BLENDFUNCTION *pblend, unsigned int dwFlags);
      //
      //#endif   // _WIN32_WINNT >= 0x0500

      //#if(_WIN32_WINNT >= 0x0501)
      //
      //      virtual bool GetLayeredWindowAttributes(::color::color *pcrKey, unsigned char *pbAlpha, unsigned int *pdwFlags) const;
      //
      //#endif   // _WIN32_WINNT >= 0x0501


            // timer Functions
      //      virtual bool SetTimer(uptr uEvent, unsigned int nElapse, PFN_TIMER pfnTimer);
            //    virtual bool KillTimer(uptr uEvent);

            // Window State Functions
      virtual bool is_this_enabled();
      virtual bool enable_window(bool bEnable = true);

      // the active interaction_impl applies only to top-level (frame windows)
      //virtual ::user::interaction * get_active_window();
      //virtual ::user::interaction * set_active_window();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      //virtual bool set_foreground_window();
      //virtual ::user::interaction * get_foreground_window();


      //virtual bool has_keyboard_focus() const override;
      

      //virtual ::user::interaction * GetFocus();

      //virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for ___new code
      virtual void CloseWindow();
      virtual bool OpenIcon();

      //// Dialog-Box Item Functions
      //// (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      //virtual void CheckDlgButton(int nIDButton, unsigned int nCheck);
      //virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton);
      //virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      //virtual int DlgDirList(__inout_z TCHAR * pPathSpec, __in int nIDListBox,

      //   __in int nIDStaticPath, __inunsigned int nFileType);
      //virtual int DlgDirListComboBox(__inout_z TCHAR * pPathSpec, __in int nIDComboBox,

      //   __in int nIDStaticPath, __inunsigned int nFileType);
      //virtual bool DlgDirSelect(__out_ecount_z(nSize) TCHAR * pString, __in int nSize, __in int nIDListBox);

      //virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) TCHAR * pString, __in int nSize, __in int nIDComboBox);


      //virtual unsigned int GetChildByIdInt(int nID, BOOL * pTrans = nullptr, bool bSigned = true) const;

      //virtual int GetChildByIdText(__in int nID, __out_ecount_part_z(nMaxCount, return +1) TCHAR * pStr, __in int nMaxCount) const;

      ///virtual int GetChildByIdText(int nID, string & rectangleString) const;
      //virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual unsigned int IsDlgButtonChecked(int nIDButton) const;
      //virtual lresult SendDlgItemMessage(int nID, unsigned int message, wparam wParam = 0, lparam lParam = 0);
      //virtual void SetDlgItemInt(int nID, unsigned int nValue, bool bSigned = true);
      //virtual void SetDlgItemText(int nID, const ::string & pszString);


      //virtual bool open_clipboard() override;
      //virtual bool close_clipboard() override;


      //// Scrolling Functions
      //virtual int GetScrollPos(int nBar) const;
      //virtual void GetScrollRange(int nBar, LPINT pMinPos, LPINT lpMaxPos) const;

      //virtual void ScrollWindow(int xAmount, int yAmount,
      //   const ::int_rectangle * rectangle = nullptr,

      //   const ::int_rectangle * pClipRect = nullptr);

      //virtual int SetScrollPos(int nBar, int nPos, bool bRedraw = true);
      //virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
      //   bool bRedraw = true);
      //virtual void ShowScrollBar(unsigned int nBar, bool bShow = true);
      //virtual void EnableScrollBarCtrl(int nBar, bool bEnable = true);

      //virtual int ScrollWindowEx(int dx, int dy,
      //   const ::int_rectangle * pRectScroll, const ::int_rectangle * lpRectClip,

      //   ::draw2d::region * prgnUpdate, ::int_rectangle * pRectUpdate, unsigned int flags);

      //virtual bool SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo,

      //   bool bRedraw = true);
      //virtual bool GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask = SIF_ALL);

      //virtual int GetScrollLimit(int nBar);

      //#if(WINVER >= 0x0500)
      //
      //      virtual bool GetScrollBarInfo(int idObject, PSCROLLBARINFO psbi) const;
      //
      //#endif   // WINVER >= 0x0500

            // Window Access Functions
      //virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point);
      //virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags);
      ///      virtual ::windowing::window * FindWindow(const ::string & pszClassName, const ::string & pszWindowName);

      //   virtual ::windowing::window * FindWindowEx(::windowing::window * pwindowParent,::windowing::window * pwindowChildAfter, const ::string & lpszClass, const ::string & pszWindow);

      //virtual ::huge_integer_point _client_parent_top_left() override;
      //virtual ::huge_integer_point _client_screen_top_left() override;


      virtual ::windowing::window * get_next_window(unsigned int nFlag = GW_HWNDNEXT);
      virtual ::windowing::window * get_top_window() const;


      virtual ::windowing::window * get_window(unsigned int nCmd) const;
      virtual ::windowing::window * get_last_active_popup() const;

      
      virtual ::windowing::window * get_parent() const override;
      virtual ::oswindow get_parent_oswindow() const override;
      virtual void set_parent(::windowing::window * pwindow) override;

      virtual ::windowing::window * get_owner() const override;
      virtual ::oswindow get_owner_oswindow() const override;
      virtual void set_owner(::windowing::window * pwindow) override;

      //virtual ::user::interaction * set_owner(::user::interaction * pWndNewParent);
      //virtual oswindow get_owner() const;

      // virtual bool FlashWindow(bool bInvert);

      //virtual void message_box(const ::string & pszText, const ::string & pszTitle = nullptr, unsigned int nType = e_message_box_ok, const function_arg & functionarg = function_arg());


//
//#if(WINVER >= 0x0500)
//
//      virtual bool FlashWindowEx(unsigned int dwFlags, unsigned int  uCount, class ::time tickTimeout);
//
//#endif   // WINVER >= 0x0500
//
      // Clipboard Functions
      //virtual bool ChangeClipboardChain(::windowing::window * pwindow_Next);
      //virtual ::oswindow  SetClipboardImpacter();
      ////virtual bool OpenClipboard();
      //virtual ::user::interaction * GetClipboardOwner();
      //virtual ::user::interaction * GetClipboardImpacter();
      //virtual ::user::interaction * GetOpenClipboardWindow();

      virtual int_point GetCaretPos();
      virtual void SetCaretPos(const ::int_point & point);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      //virtual void DragAcceptFiles(bool bAccept = true);

      // icon Functions
      //virtual hicon SetIcon(hicon hIcon, bool bBigIcon);
      //virtual hicon GetIcon(bool bBigIcon) const;

      // Context Help Functions
      //virtual bool SetWindowContextHelpId(unsigned int dwContextHelpId);
      //virtual unsigned int GetWindowContextHelpId() const;

       //support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      //// Help Command Handlers
      //void OnHelp();          // F1 (uses current action_context)
      //void OnHelpIndex();     // ID_HELP_INDEX
      //void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      //void OnHelpUsing();     // ID_HELP_USING
      //virtual void WinHelp(uptr dwData, unsigned int nCmd = HELP_CONTEXT);
      ////virtual void HtmlHelp(uptr dwData, unsigned int nCmd = 0x000F);
      //virtual void WinHelpInternal(uptr dwData, unsigned int nCmd = HELP_CONTEXT);


      // dialog support
      //void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      //void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      ////virtual atom   RunModalLoop(unsigned int dwFlags = 0,::object * pliveobject = nullptr);
      //virtual bool ContinueModal() override;
      //virtual void EndModalLoop(atom nResult) override;
      //virtual void EndAllModalLoops(atom nResult);

      // Window-Management message handler member functions
      //virtual bool OnCommand(::message::message * pusermessage);
      //virtual bool OnNotify(::message::message * pusermessage);

      //void OnActivate(unsigned int nState, ::windowing::window * pWndOther, bool bMinimized);
      //void OnActivateApp(bool bActive, unsigned int dwThreadID);
      //lresult OnActivateTopLevel(wparam, lparam);
      //void OnCancelMode();
      //void OnChildActivate();
      //void OnClose();
      //void OnContextMenu(::windowing::window * pwindow, int_point pos);
      //bool OnCopyData(::windowing::window * pwindow, COPYDATASTRUCT* pCopyDataStruct);

      //HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::windowing::window * pwindow, unsigned int nCtlColor);


      //void OnEnable(bool bEnable);
      //void OnEndSession(bool bEnding);
      //void OnEnterIdle(unsigned int nWhy, ::windowing::window * pWho);
      //bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //void OnGetMinMaxInfo(MINMAXINFO* pMMI);

      //bool OnHelpInfo(HELPINFO* pHelpInfo);

      //void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //lresult OnMenuChar(unsigned int nChar, unsigned int nFlags, ::user::menu* pMenu);
      //void OnMenuSelect(unsigned int nItemID, unsigned int nFlags, HMENU hSysMenu);
      //void OnMove(int x, int y);
      //void OnParentNotify(const ::atom & atom, lparam lParam);
      //hcursor OnQueryDragIcon();
      //bool OnQueryEndSession();
      //bool OnQueryNewPalette();
      //bool OnQueryOpen();
      //void OnShowWindow(bool bShow, unsigned int nStatus);
      //void OnSize(unsigned int nType, int cx, int cy);
      //void OnTCard(unsigned int idAction, unsigned int dwActionData);

      //void OnChangeUIState(unsigned int nAction, unsigned int nUIElement);
      //void OnUpdateUIState(unsigned int nAction, unsigned int nUIElement);
      //unsigned int OnQueryUIState();

      //// Nonclient-Area message handler member functions
      //bool OnNcActivate(bool bActive);
      //void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* pncsp);

      //bool OnNcCreate(::user::system * pCreateStruct);

      //lresult OnNcHitTest(const ::int_point & point);
      //void OnNcLButtonDblClk(unsigned int nHitTest, const ::int_point & point);
      //void OnNcLButtonDown(unsigned int nHitTest, const ::int_point & point);
      //void OnNcLButtonUp(unsigned int nHitTest, const ::int_point & point);
      //void OnNcMButtonDblClk(unsigned int nHitTest, const ::int_point & point);
      //void OnNcMButtonDown(unsigned int nHitTest, const ::int_point & point);
      //void OnNcMButtonUp(unsigned int nHitTest, const ::int_point & point);
      //void OnNcMouseMove(unsigned int nHitTest, const ::int_point & point);
      //void OnNcPaint();
      //void OnNcRButtonDblClk(unsigned int nHitTest, const ::int_point & point);
      //void OnNcRButtonDown(unsigned int nHitTest, const ::int_point & point);
      //void OnNcRButtonUp(unsigned int nHitTest, const ::int_point & point);

      //// System message handler member functions
      //void OnDropFiles(HDROP hDropInfo);
      //void OnPaletteIsChanging(::windowing::window * pRealizeWnd);
      //void OnSysChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnSysCommand(unsigned int nID, lparam lParam);
      //void OnSysDeadChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnSysKeyDown(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnSysKeyUp(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnCompacting(unsigned int nCpuTime);
      //void OnDevModeChange(__in_z char * pDeviceName);

      //void OnFontChange();
      //void OnPaletteChanged(::windowing::window * pFocusWnd);
      //void OnSpoolerStatus(unsigned int nStatus, unsigned int nJobs);
      //void OnSysColorChange();
      //void OnTimeChange();
      //void OnSettingChange(unsigned int uFlags, const ::string & pszSection);

      //void OnWinIniChange(const ::string & pszSection);


      //// Input message handler member functions
      //void OnChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnDeadChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      ////      void OnHScroll(unsigned int nSBCode, unsigned int nPos, CScrollBar* pScrollBar);
      ////    void OnVScroll(unsigned int nSBCode, unsigned int nPos, CScrollBar* pScrollBar);
      //void OnKeyDown(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnKeyUp(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
      //void OnLButtonDblClk(unsigned int nFlags, const ::int_point & point);
      //void OnLButtonDown(unsigned int nFlags, const ::int_point & point);
      //void OnLButtonUp(unsigned int nFlags, const ::int_point & point);
      //void OnMButtonDblClk(unsigned int nFlags, const ::int_point & point);
      //void OnMButtonDown(unsigned int nFlags, const ::int_point & point);
      //void OnMButtonUp(unsigned int nFlags, const ::int_point & point);
      //int OnMouseActivate(::windowing::window * pDesktopWnd, unsigned int nHitTest, const ::atom & atom);
      //void OnMouseMove(unsigned int nFlags, const ::int_point & point);
      //bool OnMouseWheel(unsigned int nFlags, short zDelta, const ::int_point & point);
      //lresult OnRegisteredMouseWheel(wparam wParam, lparam lParam);
      //void OnRButtonDblClk(unsigned int nFlags, const ::int_point & point);
      //void OnRButtonDown(unsigned int nFlags, const ::int_point & point);
      //void OnRButtonUp(unsigned int nFlags, const ::int_point & point);
      //void OnTimer(uptr uEvent);

      //// Initialization message handler member functions
      //void OnInitMenu(::user::menu* pMenu);
      //void OnInitMenuPopup(::user::menu* pPopupMenu, unsigned int nIndex, bool bSysMenu);

      //// Clipboard message handler member functions
      //void OnAskCbFormatName(__in unsigned int nMaxCount, __out_ecount_z(nMaxCount) char * pszString);

      //void OnChangeCbChain(::windowing::window * pwindow_Remove, ::windowing::window * pwindow_After);
      //void OnDestroyClipboard();
      //void OnDrawClipboard();
      //void OnHScrollClipboard(::windowing::window * pClipAppWnd, unsigned int nSBCode, unsigned int nPos);
      //void OnPaintClipboard(::windowing::window * pClipAppWnd, HGLOBAL hPaintStruct);
      //void OnRenderAllFormats();
      //void OnRenderFormat(unsigned int nFormat);
      //void OnSizeClipboard(::windowing::window * pClipAppWnd, HGLOBAL hRect);
      //void OnVScrollClipboard(::windowing::window * pClipAppWnd, unsigned int nSBCode, unsigned int nPos);

      //// control message handler member functions
      //int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct);

      //void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct);

      //void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct);

      //unsigned int OnGetDlgCode();

      // MDI message handler member functions
      //void OnMDIActivate(bool bActivate,
      //                   ::windowing::window * pActivateWnd, ::windowing::window * pDeactivateWnd);

      // menu loop notification messages
      //void OnEnterMenuLoop(bool bIstrack_popup_menu);
      //void OnExitMenuLoop(bool bIstrack_popup_menu);

      //// Win4 messages
      //void OnStyleChanged(int nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnStyleChanging(int nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnSizing(unsigned int nSide, ::int_rectangle * prectangle);

      //void OnMoving(unsigned int nSide, ::int_rectangle * prectangle);

      //void OnCaptureChanged(::windowing::window * pwindow);
      //bool OnDeviceChange(unsigned int nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      virtual WNDPROC * GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();

      // for translating Windows messages in Main message pump
      //virtual void pre_translate_message(::message::message * pmessage);


      //virtual void default_message_handler(::message::message * pusermessage) override;
      //virtual void message_handler(::message::message * pusermessage);


      //virtual bool OnWndMsg(const ::atom & atom, wparam wParam, lparam lParam, lresult* pResult);

      // for handling default processing
      //lresult Default();
      //virtual void default_window_procedure(::message::message * pmessage) override;


      //virtual void post_non_client_destroy();

      //// for notifications from parent
      //virtual bool OnChildNotify(::message::message * pusermessage);
      //// return true if parent should not process this message
      //virtual bool ReflectChildNotify(::message::message * pusermessage);
      //virtual bool ReflectMessage(::windowing::window * pwindow_Child, ::message::message * pusermessage);

      
      //virtual bool CheckAutoCenter();
      //virtual bool GrayCtlColor(HDC hDC, HWND hwnd, unsigned int nCtlColor,
      //                          HBRUSH hbrGray, ::color::color clrText);


      // helper routines for implementation
      //bool HandleFloatingSysCommand(unsigned int nID, lparam lParam);
      //bool IsTopParentActive();
      //void ActivateTopParent();
      //virtual void on_final_release();
      ///virtual bool ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags);
      //virtual bool ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags);
      //virtual void _FilterToolTipMessage(MSG* pMsg,::windowing::window * pwindow);
      //bool _EnableToolTips(bool bEnable, unsigned int nFlag);
      //virtual oswindow get_safe_owner(::HWND hwnd, ::oswindow * pWndTop);
      //void PrepareForHelp();


      virtual void set_tool_window(bool bSet);


      friend class frame_window;

      //bool CreateDlg(const ::string & pszTemplateName, ::windowing::window * pParentWnd);



      //CLASS_DECL_WINDOWING_WIN32 friend lresult CALLBACK __send_message_hook(int, wparam, lparam);
      //CLASS_DECL_WINDOWING_WIN32 friend lresult CALLBACK __cbt_filter_hook(int, wparam, lparam);

      // standard message implementation
      //lresult OnNTCtlColor(wparam wParam, lparam lParam);
      //lresult OnDisplayChange(wparam, lparam);
      //lresult OnDragList(wparam, lparam);



      //virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual int get_window_long(int nIndex) const;
      //virtual int set_window_long(int nIndex, int lValue);
      //virtual iptr get_window_long_ptr(int nIndex) const;
      //virtual iptr set_window_long_ptr(int nIndex, iptr lValue);


      virtual void _task_transparent_mouse_event() override;


      virtual void track_mouse_hover() override;

      void set_origin(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(::int_rectangle * prectangle);
      //virtual void register_drop_target();
      //virtual void show_task(bool bShow);
      void _window_show_change_visibility(::e_display edisplay, ::e_activation eactivation) override;


      virtual void non_top_most_upper_window_rects(::int_rectangle_array & recta) override;


      // virtual void activate_top_parent();

      //virtual bool is_same_window(const ::windowing::window * pwindow) const override;  

      // internal to windowing library


      virtual bool get_window_placement(WINDOWPLACEMENT * puserinteractionpl);
      virtual bool set_window_placement(const WINDOWPLACEMENT * puserinteractionpl);


      //virtual iptr get_window_long_ptr(int nIndex) const override;
      //virtual bool set_window_long_ptr(int nIndex, iptr l) override;



      virtual void default_message_handler(::message::message * pusermessage);

      virtual float get_dpi_for_window() override;

      virtual float point_dpi(float points) override;

      virtual float y_dpi(float y) override;
      virtual float x_dpi(float x) override;

      virtual float dpiy(float y) override;
      virtual float dpix(float x) override;

      //void _window_request_presentation_locked() override;
      void window_update_screen_buffer() override;

      void get_cursor_position(::int_point * ppointCursor) override;
      void set_cursor_position(const ::int_point & pointCursor) override;

      

      // IUnknown
      virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject);

      virtual ULONG STDMETHODCALLTYPE AddRef(void);

      virtual ULONG STDMETHODCALLTYPE Release(void);

      // IDropTarget
      virtual HRESULT STDMETHODCALLTYPE DragEnter(
         /* [unique][in] */ __RPC__in_opt IDataObject * pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL point,
         /* [out][in] */ __RPC__inout DWORD * pdwEffect);

      virtual HRESULT STDMETHODCALLTYPE DragOver(
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL point,
         /* [out][in] */ __RPC__inout DWORD * pdwEffect);

      virtual HRESULT STDMETHODCALLTYPE DragLeave(void);

      virtual HRESULT STDMETHODCALLTYPE Drop(
         /* [unique][in] */ __RPC__in_opt IDataObject * pDataObj,
         /* [in] */ DWORD grfKeyState,
         /* [in] */ POINTL point,
         /* [out][in] */ __RPC__inout DWORD * pdwEffect);

      //::pointer<::message::message> get_message(const ::atom & atom, wparam wparam, lparam lparam);

      //void default_set(::message::message * pmessage, const ::atom & atom, wparam wparam, lparam lparam);


   };


} // namespace windowing_win32


//inline ::windowing_win32::window * __window(::windowing::window * pwindow)
//{
//
//   auto pwindowWin32 = (::windowing_win32::window *)pwindow->layer(LAYERED_IMPL);
//
//   return pwindowWin32;
//
//}


//inline HWND __hwnd(::windowing::window * pwindow)
//{
//
//   auto pwindowWin32 = __window(pwindow);
//
//   if (::is_null(pwindowWin32))
//   {
//
//      return nullptr;
//
//   }
//
//   return pwindowWin32->get_hwnd();
//
//}

