#pragma once


//#include "aura/user/user/interaction_impl.h"


#include "acme/_operating_system.h"

#include <Shobjidl.h>
#include <Shellapi.h>



namespace aura_windows
{


   class CLASS_DECL_AURA_WINDOWS interaction_impl :
      virtual public ::windowing::window
   {
   public:


      //__creatable_from_base(interaction_impl, ::windowing::window);


      HWND                                      m_hwnd;
      bool                                      m_bClipboardOpened : 1;
      bool                                      m_bFocusImpl : 1;
      bool                                      m_bSystemCaret : 1;

      ::rectangle_i32                           m_rectangleLast;

      bool                                      m_bUpdateGraphics;

      size_i32                                  m_size;

      point_i32                                 m_point;

      ::user::interaction_base* m_pbasewnd;

      u32                                       m_uiLastRedrawRequest;

      IDropTargetHelper* m_piDropHelper;

      bool                                      m_bUseDnDHelper;

      WNDPROC                                   m_pfnSuper; // for subclassing of controls

      ::e_display                               m_edisplayLayout;
      rectangle_i64                             m_rectangleLastPos;
      class ::time                                m_timeLastPos;
      string                                    m_strDebug;

      ::point_i32                               m_pointCursor;


      interaction_impl();
      virtual ~interaction_impl();


      void user_common_construct();



      //virtual void construct(::windowing::window * pwindow);

      //void assert_ok() const override;
      //void dump(dump_context & dumpcontext) const override;


      //bool create_message_queue(::user::interaction * pinteraction, const ::string & lpszName);

      //virtual const MSG* GetCurrentMessage();

      //virtual void update_graphics_resources();

      //void native_create_host() override;


      //virtual bool __windows_message_bypass(HWND oswindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult);

      void install_message_routing(::channel* pchannel) override;

      bool operator==(const interaction_impl& wnd) const;
      bool operator!=(const interaction_impl& wnd) const;

      //virtual u32 GetStyle() const;
      //virtual u32 GetExStyle() const;
      //virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);
      //virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);

      //virtual ::user::interaction * get_owner();
      //virtual void set_owner(::user::interaction * pOwnerWnd);

      virtual void route_command(::message::command* pcommand, bool bRouteToKeyDescendant = false) override;

      //void _002OnDraw(::image::image * pimage);

      virtual void present();

      //virtual void defer_start_prodevian();

      //virtual bool set_icon(::image::icon * picon, bool bSmall) override;

      //void _on_configure_notify_unlocked(const ::rectangle_i32& rectangle) override;

      //virtual void window_apply_visual(const ::user::window_state & windowstate) override;

      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);
      DECLARE_MESSAGE_HANDLER(on_message_reposition);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      //DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      //DECLARE_MESSAGE_HANDLER(_001OnPaint);
      //DECLARE_MESSAGE_HANDLER(_001OnPrint);
      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      //DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      //DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
      //DECLARE_MESSAGE_HANDLER(on_message_move);
      //DECLARE_MESSAGE_HANDLER(on_message_size);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(_001OnActivate);
      //DECLARE_MESSAGE_HANDLER(_001OnDwmNcRenderingChanged);
      //DECLARE_MESSAGE_HANDLER(_001OnProdevianSynch);
      //DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      //DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanged);
      //DECLARE_MESSAGE_HANDLER(_001OnGetMinMaxInfo);
      //DECLARE_MESSAGE_HANDLER(_001OnEnable);


      //virtual void win_update_graphics();


#if(WINVER >= 0x0500)

      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      //      virtual ::user::interaction * from_os_data(void * pdata);
      virtual void* get_os_data() const;


      //virtual void finish(::object * pcontextobjectFinish) override;


      //      virtual ::user::interaction * from_handle(::windowing::window * pwindow);

      // subclassing/unsubclassing functions
      //virtual void pre_subclass_window();
      //bool subclass_window(::windowing::window * pwindow);
      //bool SubclassDlgItem(::u32 nID, ::windowing::window * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const ::string & pszResourceName);

      //bool ExecuteDlgInit(LPVOID pResource);


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, const ::string & pszClassName, const ::string & pszWindowName,u32 dwStyle,const ::rectangle_i32 & rectangle,::user::interaction * pParentWnd,atom atom, ::request * prequest = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pusersystem, ::user::interaction * puiParent, atom atom) override;

      //virtual void native_create_host() override;

      virtual void destroy_impl_only() override;
      virtual void start_destroying_window() override;

      virtual void destroy_window() override;

      // special pre-creation and interaction_impl rectangle_i32 adjustment hooks
      //virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(::rectangle_i32 * pClientRect, ::u32 nAdjustType = adjustBorder);



      //// get immediate child with given ID
      //using ::windowing::window::get_child_by_id;
      //void get_child_by_id(atom atom, oswindow* poswindow_) const;

      virtual bool _is_window() override;

      //#if(WINVER >= 0x0500)
      //
      //      ::windowing::window * GetAncestor(::u32 gaFlags) const;
      //
      //#endif   // WINVER >= 0x0500

      lresult send_message(const ::atom& atom, wparam wParam = 0, lparam lParam = {}, const ::point_i32& point = {}) override;

      void post_message(const ::atom& atom, wparam wParam = 0, lparam lParam = {}) override;


      //bool SendNotifyMessage(::u32 message, wparam wParam, lparam lParam);

      //bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //bool DragDetect(const ::point_i32 & point) const;



      // Window Text Functions
      //virtual void set_window_text(const ::string & pszString) override;

      //virtual strsize get_window_text(char * pszStringBuf, strsize nMaxCount) override;

      //virtual void get_window_text(string & rectangleString) override;
      //virtual strsize get_window_text_length() override;

      virtual void on_layout(::draw2d::graphics_pointer& pgraphics) override;
      //virtual void on_reposition() override;
      //virtual void on_show_window() override;
      //virtual void on_zorder() override;

      //virtual void clear_need_layout() override;
      //virtual void clear_need_translation() override;
      //virtual void clear_show_flags() override;
      //virtual void clear_need_zorder() override;


      //virtual bool set_window_position(iptr z, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags = SWP_SHOWWINDOW);


      // Window size_i32 and position Functions
      virtual bool window_is_iconic() override;
      virtual bool window_is_zoomed() override;
      //i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //i32 GetWindowRgn(HRGN hRgn);

      virtual ::u32 ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();
      //using ::windowing::window::window_rectangle;
      //virtual bool window_rectangle(::rectangle_i64 * prectangle);

      //using ::windowing::window::this->rectangle;
      //virtual bool this->rectangle(::rectangle_i64 * prectangle);


      virtual void rects_from_os();
      virtual bool window_rect_from_os(::rectangle_i32* prectangle);
      virtual bool client_rect_from_os(::rectangle_i32* prectangle);



      //virtual point_f64 client_screen_top_left() override;


      //virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);

      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);


      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::point_i32 * pPoint, ::u32 nCount);

      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::rectangle_i32 * prectangle);


      virtual void Print(::draw2d::graphics_pointer& pgraphics, u32 dwFlags);
      virtual void PrintClient(::draw2d::graphics_pointer& pgraphics, u32 dwFlags);

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      //virtual bool GetUpdateRect(::rectangle_i32 * prectangle, bool bErase = false);

      //virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      //virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const ::rectangle_i32 * rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::rectangle_i32 * rectangle_i32);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool display(::e_display edisplay);


      //virtual void design_window_minimize(::e_activation eactivation) override;
      //virtual void design_window_maximize() override;
      //virtual void design_window_full_screen(const ::rectangle_i32 & rectangleHint = nullptr) override;
      //virtual void design_window_normal(::e_display edisplay) override;


      //virtual bool _is_window_visible() override;
//      virtual void ShowOwnedPopups(bool bShow = true);

      //virtual ::pointer<::draw2d::graphics>GetDCEx(::draw2d::region* prgnClip, u32 flags);
      virtual void LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      void show_software_keyboard(::user::element* pelement) override;
      void hide_software_keyboard(::user::element* pelement) override;


      virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate =
         {},
         ::draw2d::region* prgnUpdate = nullptr,
         ::u32 flags = RDW_INVALIDATE | RDW_ERASE);

      //virtual bool EnableScrollBar(i32 nSBFlags, ::u32 nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(i32 idAni, const LPRECTprcFrom, const LPRECTlprcTo);

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & prc, ::u32 uFlags);


//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(const class time & time, u32 dwFlags);
//
//#endif   // WINVER >= 0x0500
//
//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, ::u32 nFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//
      // Layered Window

//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(::color::color crKey, ::u8 bAlpha, u32 dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, ::point_i32 *pptDst, SIZE_I32 *psize,
//                                       ::draw2d::graphics * pDCSrc, ::point_i32 *pptSrc, ::color::color crKey, BLENDFUNCTION *pblend, u32 dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(::color::color *pcrKey, ::u8 *pbAlpha, u32 *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501


      // timer Functions
//      virtual bool SetTimer(uptr uEvent, ::u32 nElapse, PFN_TIMER pfnTimer);
      //    virtual bool KillTimer(uptr uEvent);

      // Window State Functions
      virtual bool is_this_enabled();
      virtual void enable_window(bool bEnable = true);


//      virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for ___new code
      //virtual void CloseWindow();
      //virtual bool OpenIcon();

      //// Dialog-Box Item Functions
      //// (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      //virtual void CheckDlgButton(i32 nIDButton, ::u32 nCheck);
      //virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton);
      //virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton);
      //virtual i32 DlgDirList(__inout_z TCHAR * pPathSpec, __in i32 nIDListBox,

      //                       __in i32 nIDStaticPath, __in ::u32 nFileType);
      //virtual i32 DlgDirListComboBox(__inout_z TCHAR * pPathSpec, __in i32 nIDComboBox,

      //                               __in i32 nIDStaticPath, __in ::u32 nFileType);
      //virtual bool DlgDirSelect(__out_ecount_z(nSize) TCHAR * pString, __in i32 nSize, __in i32 nIDListBox);

      //virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) TCHAR * pString, __in i32 nSize, __in i32 nIDComboBox);


      //virtual ::u32 GetChildByIdInt(i32 nID, BOOL * pTrans = nullptr, bool bSigned = true) const;

      //virtual i32 GetChildByIdText(__in i32 nID, __out_ecount_part_z(nMaxCount, return +1) TCHAR * pStr, __in i32 nMaxCount) const;

      /////virtual i32 GetChildByIdText(i32 nID, string & rectangleString) const;
      ////virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      ////virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual ::u32 IsDlgButtonChecked(i32 nIDButton) const;
      //virtual lresult SendDlgItemMessage(i32 nID, ::u32 message, wparam wParam = 0, lparam lParam = 0);
      //virtual void SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned = true);
      //virtual void SetDlgItemText(i32 nID, const ::string & pszString);


      //virtual bool open_clipboard() override;
      //virtual bool close_clipboard() override;


      // Scrolling Functions
      //virtual i32 GetScrollPos(i32 nBar) const;
      //virtual void GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const;

      //virtual void ScrollWindow(i32 xAmount, i32 yAmount,
      //   const ::rectangle_i32 * rectangle = nullptr,

      //   const ::rectangle_i32 * pClipRect = nullptr);

      //virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = true);
      //virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
      //                            bool bRedraw = true);
      //virtual void ShowScrollBar(::u32 nBar, bool bShow = true);
      //virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = true);

      //virtual i32 ScrollWindowEx(i32 dx, i32 dy,
      //   const ::rectangle_i32 * pRectScroll, const ::rectangle_i32 * lpRectClip,

      //                           ::draw2d::region* prgnUpdate, ::rectangle_i32 * pRectUpdate, ::u32 flags);

      //virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo,

      //                           bool bRedraw = true);
      //virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, ::u32 nMask = SIF_ALL);

      //virtual i32 GetScrollLimit(i32 nBar);

//#if(WINVER >= 0x0500)
//
//      virtual bool GetScrollBarInfo(::i32 idObject, PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      // Window Access Functions
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point);
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags);
      ///      virtual ::windowing::window * FindWindow(const ::string & pszClassName, const ::string & pszWindowName);

      //   virtual ::windowing::window * FindWindowEx(::windowing::window * pwindowParent,::windowing::window * pwindowChildAfter, const ::string & lpszClass, const ::string & pszWindow);

      //virtual ::point_i64 _client_parent_top_left() override;
      //virtual ::point_i64 _client_screen_top_left() override;

      virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * get_top_window() const;

      virtual ::user::interaction * get_window(::u32 nCmd) const;
      virtual ::user::interaction * get_last_active_popup() const;

      virtual ::user::interaction * get_parent() const;
      virtual ::user::interaction * set_parent(::user::interaction * pWndNewParent);
      //      virtual ::user::interaction * WindowFromPoint(const ::point_i32 & point);


      virtual ::user::interaction * set_owner(::user::interaction * pWndNewParent);
      virtual ::user::interaction * get_owner() const;

      // virtual bool FlashWindow(bool bInvert);

      //virtual void message_box(const ::string & pszText, const ::string & pszTitle = nullptr, ::u32 nType = e_message_box_ok, const function_arg & functionarg = function_arg());


//
//#if(WINVER >= 0x0500)
//
//      virtual bool FlashWindowEx(u32 dwFlags, ::u32  uCount, class ::time tickTimeout);
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

      virtual point_i32 GetCaretPos();
      virtual void SetCaretPos(const ::point_i32 & point);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = true);

      // icon Functions
      virtual void set_icon(::windowing::icon * picon);
      virtual ::pointer<::windowing::icon>get_icon() const;

      // Context Help Functions
      //virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      //virtual u32 GetWindowContextHelpId() const;

       //support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      //// Help Command Handlers
      //void OnHelp();          // F1 (uses current action_context)
      //void OnHelpIndex();     // ID_HELP_INDEX
      //void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      //void OnHelpUsing();     // ID_HELP_USING
      //virtual void WinHelp(uptr dwData, ::u32 nCmd = HELP_CONTEXT);
      ////virtual void HtmlHelp(uptr dwData, ::u32 nCmd = 0x000F);
      //virtual void WinHelpInternal(uptr dwData, ::u32 nCmd = HELP_CONTEXT);


      // dialog support
      //void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      //void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      ////virtual atom   RunModalLoop(u32 dwFlags = 0,::object * pliveobject = nullptr);
      //virtual bool ContinueModal() override;
      //virtual void EndModalLoop(atom nResult) override;
      //virtual void EndAllModalLoops(atom nResult);

      // Window-Management message handler member functions
      //virtual bool OnCommand(::message::message * pmessage);
      //virtual bool OnNotify(::message::message * pmessage);

      //void OnActivate(::u32 nState, ::windowing::window * pWndOther, bool bMinimized);
      //void OnActivateApp(bool bActive, u32 dwThreadID);
      //lresult OnActivateTopLevel(wparam, lparam);
      //void OnCancelMode();
      //void OnChildActivate();
      //void OnClose();
      //void OnContextMenu(::windowing::window * pwindow, point_i32 pos);
      //bool OnCopyData(::windowing::window * pwindow, COPYDATASTRUCT* pCopyDataStruct);

      //HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::windowing::window * pwindow, ::u32 nCtlColor);


      //void OnEnable(bool bEnable);
      //void OnEndSession(bool bEnding);
      //void OnEnterIdle(::u32 nWhy, ::windowing::window * pWho);
      //bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //void OnGetMinMaxInfo(MINMAXINFO* pMMI);

      //bool OnHelpInfo(HELPINFO* pHelpInfo);

      //void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //lresult OnMenuChar(::u32 nChar, ::u32 nFlags, ::user::menu* pMenu);
      //void OnMenuSelect(::u32 nItemID, ::u32 nFlags, HMENU hSysMenu);
      //void OnMove(i32 x, i32 y);
      //void OnParentNotify(const ::atom & atom, lparam lParam);
      //hcursor OnQueryDragIcon();
      //bool OnQueryEndSession();
      //bool OnQueryNewPalette();
      //bool OnQueryOpen();
      //void OnShowWindow(bool bShow, ::u32 nStatus);
      //void OnSize(::u32 nType, i32 cx, i32 cy);
      //void OnTCard(::u32 idAction, u32 dwActionData);

      //void OnChangeUIState(::u32 nAction, ::u32 nUIElement);
      //void OnUpdateUIState(::u32 nAction, ::u32 nUIElement);
      //::u32 OnQueryUIState();

      //// Nonclient-Area message handler member functions
      //bool OnNcActivate(bool bActive);
      //void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* pncsp);

      //bool OnNcCreate(::user::system * pCreateStruct);

      //lresult OnNcHitTest(const ::point_i32 & point);
      //void OnNcLButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcLButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcLButtonUp(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonUp(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMouseMove(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcPaint();
      //void OnNcRButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcRButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcRButtonUp(::u32 nHitTest, const ::point_i32 & point);

      //// ::auraacmesystem() message handler member functions
      //void OnDropFiles(HDROP hDropInfo);
      //void OnPaletteIsChanging(::windowing::window * pRealizeWnd);
      //void OnSysChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysCommand(::u32 nID, lparam lParam);
      //void OnSysDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnCompacting(::u32 nCpuTime);
      //void OnDevModeChange(__in_z char * pDeviceName);

      //void OnFontChange();
      //void OnPaletteChanged(::windowing::window * pFocusWnd);
      //void OnSpoolerStatus(::u32 nStatus, ::u32 nJobs);
      //void OnSysColorChange();
      //void OnTimeChange();
      //void OnSettingChange(::u32 uFlags, const ::string & pszSection);

      //void OnWinIniChange(const ::string & pszSection);


      //// Input message handler member functions
      //void OnChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      ////      void OnHScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      ////    void OnVScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      //void OnKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnLButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnLButtonUp(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonUp(::u32 nFlags, const ::point_i32 & point);
      //i32 OnMouseActivate(::windowing::window * pDesktopWnd, ::u32 nHitTest, const ::atom & atom);
      //void OnMouseMove(::u32 nFlags, const ::point_i32 & point);
      //bool OnMouseWheel(::u32 nFlags, i16 zDelta, const ::point_i32 & point);
      //lresult OnRegisteredMouseWheel(wparam wParam, lparam lParam);
      //void OnRButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnRButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnRButtonUp(::u32 nFlags, const ::point_i32 & point);
      //void OnTimer(uptr uEvent);

      //// Initialization message handler member functions
      //void OnInitMenu(::user::menu* pMenu);
      //void OnInitMenuPopup(::user::menu* pPopupMenu, ::u32 nIndex, bool bSysMenu);

      //// Clipboard message handler member functions
      //void OnAskCbFormatName(__in ::u32 nMaxCount, __out_ecount_z(nMaxCount) char * pszString);

      //void OnChangeCbChain(::windowing::window * pwindow_Remove, ::windowing::window * pwindow_After);
      //void OnDestroyClipboard();
      //void OnDrawClipboard();
      //void OnHScrollClipboard(::windowing::window * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);
      //void OnPaintClipboard(::windowing::window * pClipAppWnd, HGLOBAL hPaintStruct);
      //void OnRenderAllFormats();
      //void OnRenderFormat(::u32 nFormat);
      //void OnSizeClipboard(::windowing::window * pClipAppWnd, HGLOBAL hRect);
      //void OnVScrollClipboard(::windowing::window * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);

      //// control message handler member functions
      //i32 OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct);

      //void OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct);

      //void OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct);

      //::u32 OnGetDlgCode();

      // MDI message handler member functions
      //void OnMDIActivate(bool bActivate,
      //                   ::windowing::window * pActivateWnd, ::windowing::window * pDeactivateWnd);

      // menu loop notification messages
      //void OnEnterMenuLoop(bool bIstrack_popup_menu);
      //void OnExitMenuLoop(bool bIstrack_popup_menu);

      //// Win4 messages
      //void OnStyleChanged(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnStyleChanging(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnSizing(::u32 nSide, ::rectangle_i32 * prectangle);

      //void OnMoving(::u32 nSide, ::rectangle_i32 * prectangle);

      //void OnCaptureChanged(::windowing::window * pwindow);
      //bool OnDeviceChange(::u32 nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      //virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      //virtual void BeginModalState();
      //virtual void EndModalState();

      // for translating Windows messages in Main message pump
      //virtual void pre_translate_message(::message::message * pmessage);


      bool on_mouse_message(::message::mouse * pmouse) override;


      virtual void message_handler(::message::message* pmessage) override;


      //virtual void default_message_handler(::message::message * pmessage) override;
      //virtual void message_handler(::message::message * pmessage);


      //virtual bool OnWndMsg(const ::atom & atom, wparam wParam, lparam lParam, lresult* pResult);

      // for handling default processing
      //lresult Default();
      //virtual void default_window_procedure(::message::message * pmessage) override;


      void post_non_client_destroy() override;

      // for notifications from parent
      //virtual bool OnChildNotify(::message::message * pmessage);
      // return true if parent should not process this message
      //virtual bool ReflectChildNotify(::message::message * pmessage);
      //virtual bool ReflectMessage(::windowing::window * pwindow_Child, ::message::message * pmessage);

      
      //virtual bool CheckAutoCenter();
      //virtual bool GrayCtlColor(HDC hDC, ::windowing::window * pwindow, ::u32 nCtlColor,
      //                          HBRUSH hbrGray, ::color::color clrText);


      // helper routines for implementation
      //bool HandleFloatingSysCommand(::u32 nID, lparam lParam);
      //bool IsTopParentActive();
      //void ActivateTopParent();
      //virtual void on_final_release();
      ///virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags);
      //virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags);
      //virtual void _FilterToolTipMessage(MSG* pMsg,::windowing::window * pwindow);
      //bool _EnableToolTips(bool bEnable, ::u32 nFlag);
      //virtual oswindow get_safe_owner(::windowing::window * pwindow, ::oswindow * pWndTop);
      //void PrepareForHelp();


      virtual void set_tool_window(bool bSet);


      friend class frame_window;

      bool CreateDlg(const ::string & pszTemplateName, ::windowing::window * pParentWnd);



      //CLASS_DECL_AURA friend lresult CALLBACK __send_message_hook(i32, wparam, lparam);
      //CLASS_DECL_AURA friend lresult CALLBACK __cbt_filter_hook(i32, wparam, lparam);

      // standard message implementation
      //lresult OnNTCtlColor(wparam wParam, lparam lParam);
      //lresult OnDisplayChange(wparam, lparam);
      //lresult OnDragList(wparam, lparam);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual ::i32 get_window_long(i32 nIndex) const;
      //virtual ::i32 set_window_long(i32 nIndex, ::i32 lValue);
      //virtual iptr get_window_long_ptr(i32 nIndex) const;
      //virtual void set_window_long_ptr(i32 nIndex, iptr lValue);


      //void _001OnTriggerMouseInside();

      void set_origin(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual void get_rect_normal(::rectangle_i32 * prectangle);
      virtual void register_drop_target();
      virtual void show_task(bool bShow);
      //void _window_show_change_visibility_unlocked(::e_display edisplay, ::e_activation eactivation) override;


      //virtual void non_top_most_upper_window_rects(::rectangle_i32_array& recta) override;


      virtual void activate_top_parent();


      void _raw_client_to_screen(::point_i32 & point) override;
      void _raw_screen_to_client(::point_i32 & point) override;


   };


} // namespace aura_windows


CLASS_DECL_AURA::user::interaction * __user_interaction(::windowing::window * pwindow);
