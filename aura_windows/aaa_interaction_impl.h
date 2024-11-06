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

      unsigned int                                       m_uiLastRedrawRequest;

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


      //virtual bool __windows_message_bypass(HWND oswindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult);

      void install_message_routing(::channel* pchannel) override;

      bool operator==(const interaction_impl& wnd) const;
      bool operator!=(const interaction_impl& wnd) const;

      //virtual unsigned int GetStyle() const;
      //virtual unsigned int GetExStyle() const;
      //virtual bool ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0);
      //virtual bool ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0);

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
      //bool SubclassDlgItem(unsigned int nID, ::windowing::window * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const ::string & pszResourceName);

      //bool ExecuteDlgInit(LPVOID pResource);


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, const ::string & pszClassName, const ::string & pszWindowName,unsigned int dwStyle,const ::rectangle_i32 & rectangle,::user::interaction * pParentWnd,atom atom, ::request * prequest = nullptr) override;


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
      //virtual void CalcWindowRect(::rectangle_i32 * pClientRect, unsigned int nAdjustType = adjustBorder);



      //// get immediate child with given ID
      //using ::windowing::window::get_child_by_id;
      //void get_child_by_id(atom atom, oswindow* poswindow_) const;

      virtual bool _is_window() override;

      //#if(WINVER >= 0x0500)
      //
      //      ::windowing::window * GetAncestor(unsigned int gaFlags) const;
      //
      //#endif   // WINVER >= 0x0500

      lresult send_message(const ::atom& atom, wparam wParam = 0, lparam lParam = {}, const ::point_i32& point = {}) override;

      void post_message(const ::atom& atom, wparam wParam = 0, lparam lParam = {}) override;


      //bool SendNotifyMessage(unsigned int message, wparam wParam, lparam lParam);

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


      //virtual bool set_window_position(iptr z, int x, int y, int cx, int cy, unsigned int nFlags = SWP_SHOWWINDOW);


      // Window size_i32 and position Functions
      virtual bool window_is_iconic() override;
      virtual bool window_is_zoomed() override;
      //int SetWindowRgn(HRGN hRgn,bool bRedraw);
      //int GetWindowRgn(HRGN hRgn);

      virtual unsigned int ArrangeIconicWindows();
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


      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::point_i32 * pPoint, unsigned int nCount);

      //virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::rectangle_i32 * prectangle);


      virtual void Print(::draw2d::graphics_pointer& pgraphics, unsigned int dwFlags);
      virtual void PrintClient(::draw2d::graphics_pointer& pgraphics, unsigned int dwFlags);

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      //virtual bool GetUpdateRect(::rectangle_i32 * prectangle, bool bErase = false);

      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
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

      //virtual ::pointer<::draw2d::graphics>GetDCEx(::draw2d::region* prgnClip, unsigned int flags);
      virtual void LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      void show_software_keyboard(::user::element* pelement) override;
      void hide_software_keyboard(::user::element* pelement) override;


      virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate =
         {},
         ::draw2d::region* prgnUpdate = nullptr,
         unsigned int flags = RDW_INVALIDATE | RDW_ERASE);

      //virtual bool EnableScrollBar(int nSBFlags, unsigned int nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo);

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & prc, unsigned int uFlags);


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
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, ::point_i32 *pptDst, SIZE_I32 *psize,
//                                       ::draw2d::graphics * pDCSrc, ::point_i32 *pptSrc, ::color::color crKey, BLENDFUNCTION *pblend, unsigned int dwFlags);
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
      virtual void enable_window(bool bEnable = true);


//      virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for ___new code
      //virtual void CloseWindow();
      //virtual bool OpenIcon();

      //// Dialog-Box Item Functions
      //// (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      //virtual void CheckDlgButton(int nIDButton, unsigned int nCheck);
      //virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton);
      //virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      //virtual int DlgDirList(__inout_z TCHAR * pPathSpec, __in int nIDListBox,

      //                       __in int nIDStaticPath, __in unsigned int nFileType);
      //virtual int DlgDirListComboBox(__inout_z TCHAR * pPathSpec, __in int nIDComboBox,

      //                               __in int nIDStaticPath, __in unsigned int nFileType);
      //virtual bool DlgDirSelect(__out_ecount_z(nSize) TCHAR * pString, __in int nSize, __in int nIDListBox);

      //virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) TCHAR * pString, __in int nSize, __in int nIDComboBox);


      //virtual unsigned int GetChildByIdInt(int nID, BOOL * pTrans = nullptr, bool bSigned = true) const;

      //virtual int GetChildByIdText(__in int nID, __out_ecount_part_z(nMaxCount, return +1) TCHAR * pStr, __in int nMaxCount) const;

      /////virtual int GetChildByIdText(int nID, string & rectangleString) const;
      ////virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      ////virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual unsigned int IsDlgButtonChecked(int nIDButton) const;
      //virtual lresult SendDlgItemMessage(int nID, unsigned int message, wparam wParam = 0, lparam lParam = 0);
      //virtual void SetDlgItemInt(int nID, unsigned int nValue, bool bSigned = true);
      //virtual void SetDlgItemText(int nID, const ::string & pszString);


      //virtual bool open_clipboard() override;
      //virtual bool close_clipboard() override;


      // Scrolling Functions
      //virtual int GetScrollPos(int nBar) const;
      //virtual void GetScrollRange(int nBar, LPINT pMinPos, LPINT lpMaxPos) const;

      //virtual void ScrollWindow(int xAmount, int yAmount,
      //   const ::rectangle_i32 * rectangle = nullptr,

      //   const ::rectangle_i32 * pClipRect = nullptr);

      //virtual int SetScrollPos(int nBar, int nPos, bool bRedraw = true);
      //virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
      //                            bool bRedraw = true);
      //virtual void ShowScrollBar(unsigned int nBar, bool bShow = true);
      //virtual void EnableScrollBarCtrl(int nBar, bool bEnable = true);

      //virtual int ScrollWindowEx(int dx, int dy,
      //   const ::rectangle_i32 * pRectScroll, const ::rectangle_i32 * lpRectClip,

      //                           ::draw2d::region* prgnUpdate, ::rectangle_i32 * pRectUpdate, unsigned int flags);

      //virtual bool SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo,

      //                           bool bRedraw = true);
      //virtual bool GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask = SIF_ALL);

      //virtual int GetScrollLimit(int nBar);

//#if(WINVER >= 0x0500)
//
//      virtual bool GetScrollBarInfo(int idObject, PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      // Window Access Functions
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point);
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point, unsigned int nFlags);
      ///      virtual ::windowing::window * FindWindow(const ::string & pszClassName, const ::string & pszWindowName);

      //   virtual ::windowing::window * FindWindowEx(::windowing::window * pwindowParent,::windowing::window * pwindowChildAfter, const ::string & lpszClass, const ::string & pszWindow);

      //virtual ::point_i64 _client_parent_top_left() override;
      //virtual ::point_i64 _client_screen_top_left() override;

      virtual ::user::interaction * get_next_window(unsigned int nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * get_top_window() const;

      virtual ::user::interaction * get_window(unsigned int nCmd) const;
      virtual ::user::interaction * get_last_active_popup() const;

      virtual ::user::interaction * get_parent() const;
      virtual ::user::interaction * set_parent(::user::interaction * pWndNewParent);
      //      virtual ::user::interaction * WindowFromPoint(const ::point_i32 & point);


      virtual ::user::interaction * set_owner(::user::interaction * pWndNewParent);
      virtual ::user::interaction * get_owner() const;

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
      //virtual bool OnCommand(::message::message * pmessage);
      //virtual bool OnNotify(::message::message * pmessage);

      //void OnActivate(unsigned int nState, ::windowing::window * pWndOther, bool bMinimized);
      //void OnActivateApp(bool bActive, unsigned int dwThreadID);
      //lresult OnActivateTopLevel(wparam, lparam);
      //void OnCancelMode();
      //void OnChildActivate();
      //void OnClose();
      //void OnContextMenu(::windowing::window * pwindow, point_i32 pos);
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

      //lresult OnNcHitTest(const ::point_i32 & point);
      //void OnNcLButtonDblClk(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcLButtonDown(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcLButtonUp(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDblClk(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDown(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcMButtonUp(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcMouseMove(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcPaint();
      //void OnNcRButtonDblClk(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcRButtonDown(unsigned int nHitTest, const ::point_i32 & point);
      //void OnNcRButtonUp(unsigned int nHitTest, const ::point_i32 & point);

      //// ::auraacmesystem() message handler member functions
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
      //void OnLButtonDblClk(unsigned int nFlags, const ::point_i32 & point);
      //void OnLButtonDown(unsigned int nFlags, const ::point_i32 & point);
      //void OnLButtonUp(unsigned int nFlags, const ::point_i32 & point);
      //void OnMButtonDblClk(unsigned int nFlags, const ::point_i32 & point);
      //void OnMButtonDown(unsigned int nFlags, const ::point_i32 & point);
      //void OnMButtonUp(unsigned int nFlags, const ::point_i32 & point);
      //int OnMouseActivate(::windowing::window * pDesktopWnd, unsigned int nHitTest, const ::atom & atom);
      //void OnMouseMove(unsigned int nFlags, const ::point_i32 & point);
      //bool OnMouseWheel(unsigned int nFlags, short zDelta, const ::point_i32 & point);
      //lresult OnRegisteredMouseWheel(wparam wParam, lparam lParam);
      //void OnRButtonDblClk(unsigned int nFlags, const ::point_i32 & point);
      //void OnRButtonDown(unsigned int nFlags, const ::point_i32 & point);
      //void OnRButtonUp(unsigned int nFlags, const ::point_i32 & point);
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

      //void OnSizing(unsigned int nSide, ::rectangle_i32 * prectangle);

      //void OnMoving(unsigned int nSide, ::rectangle_i32 * prectangle);

      //void OnCaptureChanged(::windowing::window * pwindow);
      //bool OnDeviceChange(unsigned int nEventType, uptr dwData);

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
      //virtual bool GrayCtlColor(HDC hDC, ::windowing::window * pwindow, unsigned int nCtlColor,
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
      //virtual oswindow get_safe_owner(::windowing::window * pwindow, ::oswindow * pWndTop);
      //void PrepareForHelp();


      virtual void set_tool_window(bool bSet);


      friend class frame_window;

      bool CreateDlg(const ::string & pszTemplateName, ::windowing::window * pParentWnd);



      //CLASS_DECL_AURA friend lresult CALLBACK __send_message_hook(int, wparam, lparam);
      //CLASS_DECL_AURA friend lresult CALLBACK __cbt_filter_hook(int, wparam, lparam);

      // standard message implementation
      //lresult OnNTCtlColor(wparam wParam, lparam lParam);
      //lresult OnDisplayChange(wparam, lparam);
      //lresult OnDragList(wparam, lparam);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual int get_window_long(int nIndex) const;
      //virtual int set_window_long(int nIndex, int lValue);
      //virtual iptr get_window_long_ptr(int nIndex) const;
      //virtual void set_window_long_ptr(int nIndex, iptr lValue);


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
