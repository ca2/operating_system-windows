
#include "framework.h"

bool has_subdir(CString str)
{

   CFileFind find;

   if(find.FindFile(str + "\\*.*"))
   {

      while(find.FindNextFileA())
      {

         if(find.IsDots())
         {

            

         }
         else if(find.IsDirectory())
         {

            return true;

         }


      } 

   }


   return false;

}

CString get_utf8(LPCWSTR lpcwsz)
{

   CString str;

   int count = ::WideCharToMultiByte(CP_UTF8,0,lpcwsz,-1,nullptr,0,nullptr,0);

   if(count > 0)
   {
      char * lpDst = str.get_buffer_set_length(count + 1);
      memory_set(lpDst,0,count + 1);

      ::WideCharToMultiByte(CP_UTF8,0,lpcwsz,-1,lpDst,count,nullptr,0);
      str.ReleaseBuffer();
   }
   return str;


}

// CLibraryFrame

IMPLEMENT_DYNCREATE(CLibraryFrame,CMiniFrameWnd)

CLibraryFrame::CLibraryFrame()
{
   m_bTracking = false;
   m_ulRef = 1;
}

CLibraryFrame::~CLibraryFrame()
{
}



   ON_WM_CREATE()
   ON_WM_NCCREATE()
   ON_WM_ACTIVATE()
   ON_WM_NCACTIVATE()
   ON_WM_NCLBUTTONDBLCLK()
   ON_WM_NCLBUTTONDOWN()
   ON_WM_NCLBUTTONUP()
   ON_WM_GETMINMAXINFO()
   ON_COMMAND(ID_FILE_NEWLIBRARY,&CLibraryFrame::OnFileNewlibrary)
   ON_COMMAND(ID_FILE_OPENLIBRARY,&CLibraryFrame::OnFileOpenlibrary)


//void CLibraryFrame::RecalcLayout(BOOL bNotify)
//{
//   CMiniFrameWnd::RecalcLayout(bNotify);
//}
// CLibraryFrame message handlers


BOOL CLibraryFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: Add your specialized code here and/or call the base class
   if(!CMiniFrameWnd::PreCreateWindow(cs))
      return false;
   pusersystem->m_createstruct.dwExStyle &= ~WS_EX_TOOLWINDOW;
   pusersystem->m_createstruct.style |= MFS_SYNCACTIVE;
   pusersystem->m_createstruct.hwndParent = application()->m_pMainWnd->GetSafeHwnd();
   return true;

}
Gdiplus::Bitmap * LoadPNG(LPCTSTR pName,LPCTSTR pType,HMODULE hInst);

int CLibraryFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if(CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   ModifyStyle(0,MFS_SYNCACTIVE | WS_THICKFRAME);
   
   EnableDocking(CBRS_ALIGN_TOP);
   if(m_toolbar.CreateEx(this,TBSTYLE_FLAT | TBSTYLE_LIST,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
   {
      Gdiplus::Bitmap * p = LoadPNG(MAKEINTRESOURCEA(IDR_LIBRARY),"PNG",nullptr);
      if(p != nullptr)
      {
         HBITMAP h = nullptr;
         p->GetHBITMAP(Gdiplus::Color(0,0,0,0),& h);
         if(m_toolbar.SetBitmap(h))
         {

            UINT u[]=
            {
               ID_VIEW_LIBRARY,
               ID_VIEW_PHOTO_LIBRARY
            };

            m_toolbar.SetSizes(CSize(39,38),CSize(32,32));

            if(m_toolbar.SetButtons(u,sizeof(u) / sizeof(u[0])))
            {
               m_toolbar.SetButtonText(0,"Microspot Data");
               m_toolbar.SetButtonText(1,"Photos");

               m_toolbar.EnableDocking(CBRS_ALIGN_TOP);
               ShowControlBar(&m_toolbar,true,true);

            }

         }

         delete p;

      }

   }


   return 0;
}


void CLibraryFrame::OnActivate(UINT nState,CWnd* pWndOther,BOOL bMinimized)
{
   //CMiniFrameWnd::OnActivate(nState,pWndOther,bMinimized);
   CWnd::OnActivate(nState,pWndOther,bMinimized);

   // hide the menu bar
   if(nState == WA_INACTIVE && (m_dwMenuBarVisibility & WINDOWS_DEFINITION_MBV_KEEPVISIBLE) == 0)
   {
      SetMenuBarState(WINDOWS_DEFINITION_MBS_HIDDEN);
   }

   // get top level frame unless this is a child window
   // determine if window should be active or not
   CFrameWnd* pTopLevel = (GetStyle() & WS_CHILD) ? this : m_pMainFrame;
   ENSURE_VALID(pTopLevel);
   CWnd* pActive = (nState == WA_INACTIVE ? pWndOther : this);
   BOOL bStayActive = (pActive != nullptr) ?
      (pTopLevel == pActive ||
      (pTopLevel == m_pMainFrame &&
      (pActive == pTopLevel ||
      pActive->SendMessage(WM_FLOATSTATUS,FS_SYNCACTIVE) != 0)))
      : false;
   pTopLevel->m_nFlags &= ~WF_STAYACTIVE;
   if(bStayActive)
      pTopLevel->m_nFlags |= WF_STAYACTIVE;

   // synchronization_object floating windows to the ___new state
   NotifyFloatingWindows(bStayActive ? FS_ACTIVATE : FS_DEACTIVATE);

   // get active impact (use active frame if no active impact)
   //CView* pActiveView = get_active_impact();
   //if(pActiveView == nullptr)
   //   pActiveView = GetActiveFrame()->get_active_impact();

   //// when frame gets activated, re-activate current impact
   //if(pActiveView != nullptr)
   //{
   //   if(nState != WA_INACTIVE && !bMinimized)
   //      pActiveView->OnActivateView(true,pActiveView,pActiveView);

   //   // always notify the impact of frame activations
   //   pActiveView->OnActivateFrame(nState,this);
   //}

}


BOOL CLibraryFrame::OnNcActivate(BOOL bActive)
{
   // TODO: Add your message handler code here and/or call default
   //if(m_bTracking)
   //{
     // CFrameWnd::OnNcActivate(bActive);
//   }
   //else
   {
      return CMiniFrameWnd::OnNcActivate(bActive);

   }
}
BOOL CLibraryFrame::OnNcCreate(LPCREATESTRUCT lpcs)
{
   if(!CFrameWnd::OnNcCreate(lpcs))
      return false;

   if(GetStyle() & MFS_SYNCACTIVE)
   {
      // syncronize activation state with top level parent
      CWnd* pParentWnd = application()->m_pMainWnd;
      CWnd* pActiveWnd = GetForegroundWindow();
      BOOL bActive = (pParentWnd == pActiveWnd) ||
         (pParentWnd->GetLastActivePopup() == pActiveWnd &&
         pActiveWnd->SendMessage(WM_FLOATSTATUS,FS_SYNCACTIVE) != 0);

      // the WM_FLOATSTATUS does the actual work
      SendMessage(WM_FLOATSTATUS,bActive ? FS_ACTIVATE : FS_DEACTIVATE);
   }

   return true;
}


void CLibraryFrame::NotifyFloatingWindows(DWORD dwFlags)
{
   ASSERT_OK(this);
   ASSERT(m_hWnd != nullptr);

   // get top level parent frame window first unless this is a child window
   CFrameWnd* pParent = (GetStyle() & WS_CHILD) ? this : m_pMainFrame;
   ENSURE(pParent != nullptr);
   if(dwFlags & (FS_DEACTIVATE | FS_ACTIVATE))
   {
      // update parent window activation state
      BOOL bActivate = !(dwFlags & FS_DEACTIVATE);
      BOOL bEnabled = pParent->IsWindowEnabled();

      if(bActivate && bEnabled && pParent != this)
      {
         // Excel will try to Activate itself when it receives a
         // WM_NCACTIVATE so we need to keep it from doing that here.
         m_nFlags |= WF_KEEPMINIACTIVE;
         pParent->SendMessage(WM_NCACTIVATE,true);
         m_nFlags &= ~WF_KEEPMINIACTIVE;
      }
      else
      {
         pParent->SendMessage(WM_NCACTIVATE,false);
      }
   }

   // then update the state of all floating windows owned by the parent
   HWND hWnd = ::GetWindow(::GetDesktopWindow(),GW_CHILD);
   while(hWnd != nullptr)
   {
      if(::windows_definition::IsDescendant(pParent->m_hWnd,hWnd))
         ::SendMessage(hWnd,WM_FLOATSTATUS,dwFlags,0);
      hWnd = ::GetWindow(hWnd,GW_HWNDNEXT);
   }
}


void CLibraryFrame::OnNcLButtonDown(UINT nHitTest,CPoint int_point)
{
   //if(nHitTest == HTCAPTION)
   //{
   //   // special activation for floating toolbars
   //   ActivateTopParent();

   //   // initiate toolbar drag for non-CBRS_FLOAT_MULTI toolbars
   //   //if((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
   //   //{
   //   //   int nPos = 1;
   //   //   CControlBar* pBar = nullptr;
   //   //   while(pBar == nullptr && nPos < m_wndDockBar.m_arrBars.GetSize())
   //   //      pBar = m_wndDockBar.GetDockedControlBar(nPos++);

   //   //   ENSURE_VALID(pBar);
   //   //   ASSERT_KINDOF(CControlBar,pBar);
   //   //   ENSURE(pBar->m_pDockContext != nullptr);
   //   //   pBar->m_pDockContext->StartDrag(point);
   //   //   return;
   //   //}
   //}
   //else if(nHitTest >= HTSIZEFIRST && nHitTest <= HTSIZELAST)
   //{
   //   // special activation for floating toolbars
   //   ActivateTopParent();

   //   //int nPos = 1;
   //   //CControlBar* pBar = nullptr;
   //   //while(pBar == nullptr && nPos < m_wndDockBar.m_arrBars.GetSize())
   //   //   pBar = m_wndDockBar.GetDockedControlBar(nPos++);

   //   //ENSURE_VALID(pBar);
   //   //ASSERT_KINDOF(CControlBar,pBar);
   //   //ENSURE(pBar->m_pDockContext != nullptr);

   //   //// CBRS_SIZE_DYNAMIC toolbars cannot have the CBRS_FLOAT_MULTI style
   //   //ASSERT((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0);
   //   //pBar->m_pDockContext->StartResize(nHitTest,int_point);
   //   return;
   //}
   m_bTracking = true;
   CMiniFrameWnd::OnNcLButtonDown(nHitTest,int_point);

   //Default();
}

void CLibraryFrame::OnNcLButtonDblClk(UINT nHitTest,CPoint int_point)
{
   if(nHitTest == HTCAPTION)
   {
      // special activation for floating toolbars
      ActivateTopParent();

      // initiate toolbar toggle for non-CBRS_FLOAT_MULTI toolbars
      //if((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0)
      //{
      //   int nPos = 1;
      //   CControlBar* pBar = nullptr;
      //   while(pBar == nullptr && nPos < m_wndDockBar.m_arrBars.GetSize())
      //      pBar = m_wndDockBar.GetDockedControlBar(nPos++);

      //   ENSURE_VALID(pBar);
      //   ASSERT_KINDOF(CControlBar,pBar);
      //   ENSURE(pBar->m_pDockContext != nullptr);
      //   pBar->m_pDockContext->ToggleDocking();
      //   return;
      //}
   }
   CMiniFrameWnd::OnNcLButtonDblClk(nHitTest,int_point);
}

BOOL CLibraryFrame::Create(CWnd* pParent,DWORD dwBarStyle, PVOID p)
{
   // set m_bInRecalcLayout to avoid flashing during creation
   // RecalcLayout will be called once something is docked
   m_bInRecalcLayout = true;

   //DWORD dwStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU | MFS_MOVEFRAME |
   //   MFS_4THICKFRAME | MFS_SYNCACTIVE | MFS_BLOCKSYSMENU |
   //   FWS_SNAPTOBARS;
   DWORD dwStyle = WS_POPUP |  WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU |  MFS_SYNCACTIVE |
      WS_THICKFRAME;

   if(dwBarStyle & CBRS_SIZE_DYNAMIC)
      dwStyle &= ~MFS_MOVEFRAME;

   DWORD dwExStyle = 0;
   m_strCaption = "Library";

   CRect rectangle = rectangleDefault;
   if(!CWnd::CreateEx(dwExStyle,::windows_definition::RegisterWndClass(CS_DBLCLKS,::LoadCursor(nullptr,IDC_ARROW)),
      m_strCaption,dwStyle,rectangle.left(),rectangle.top(),rectangle.right() - rectangle.left(),
      rectangle.bottom() - rectangle.top(),pParent->GetSafeHwnd(),(HMENU)(UINT_PTR)0,p))
   {
      return false;
   }

   dwStyle = dwBarStyle & (CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT) ?
   CBRS_ALIGN_LEFT : CBRS_ALIGN_TOP;
   dwStyle |= dwBarStyle & CBRS_FLOAT_MULTI;

   //CMenu* pSysMenu = GetSystemMenu(false);
   //if(pSysMenu)
   //{
   //   pSysMenu->DeleteMenu(SC_SIZE,MF_BYCOMMAND);
   //   pSysMenu->DeleteMenu(SC_MINIMIZE,MF_BYCOMMAND);
   //   pSysMenu->DeleteMenu(SC_MAXIMIZE,MF_BYCOMMAND);
   //   pSysMenu->DeleteMenu(SC_RESTORE,MF_BYCOMMAND);

   //   CString strHide;
   //   if(strHide.LoadString(WINDOWS_DEFINITION_IDS_HIDE))
   //   {
   //      pSysMenu->DeleteMenu(SC_CLOSE,MF_BYCOMMAND);
   //      pSysMenu->AppendMenu(MF_STRING | MF_ENABLED,SC_CLOSE,strHide);
   //   }
   //}

   //// must initially create with parent frame as parent
   //if(!m_wndDockBar.Create(pParent,WS_CHILD | WS_VISIBLE | dwStyle,
   //   WINDOWS_DEFINITION_IDW_DOCKBAR_FLOAT))
   //{
   //   m_bInRecalcLayout = false;
   //   return false;
   //}

   //// set parent to CMiniDockFrameWnd
   //m_wndDockBar.SetParent(this);
   m_bInRecalcLayout = false;

   return true;
}

BOOL CLibraryFrame::LoadFrame(UINT nIDResource,DWORD dwDefaultStyle,
   CWnd* pParentWnd,CCreateContext* pContext)
{
   // only do this once
   ASSERT_VALID_IDR(nIDResource);
   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

   CString strFullString;
   if(strFullString.LoadString(nIDResource))
      ::windows_definition::ExtractSubString(m_strTitle,strFullString,0);    // first sub-string

//   VERIFY(::windows_definition::DeferRegisterClass(WINDOWS_DEFINITION_WNDFRAMEORVIEW_REG));

   // attempt to create the window
   LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle,nIDResource);
   CString strTitle = m_strTitle;
   if(!Create(application()->m_pMainWnd, 0, pContext))
   {
      return false;   // will self destruct on failure normally
   }

   // save the default menu handle
   ASSERT(m_hWnd != nullptr);
   m_hMenuDefault = m_dwMenuBarState == WINDOWS_DEFINITION_MBS_VISIBLE ? ::GetMenu(m_hWnd) : m_hMenu;

   // load accelerator resource
   LoadAccelTable(ATL_MAKEINTRESOURCE(nIDResource));

   if(pContext == nullptr)   // send initial update
      SendMessageToDescendants(WM_INITIALUPDATE,0,0,true,true);

   return true;
}


void CLibraryFrame::OnNcLButtonUp(UINT nHitTest,CPoint int_point)
{
   CMiniFrameWnd::OnNcLButtonUp(nHitTest,int_point);

   m_bTracking = false;
}


void CLibraryFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
   // TODO: Add your message handler code here and/or call default

   CMiniFrameWnd::OnGetMinMaxInfo(lpMMI);

   lpMMI->ptMinTrackSize.x() = 320;
   lpMMI->ptMinTrackSize.y() = 450;
}


int CALLBACK LibraryFrameBrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
   CLibraryFrame * pframe = (CLibraryFrame *)lpData;

   if(uMsg == BFFM_IUNKNOWN)
   {
      IUnknown * pUk = (IUnknown *) lParam;
      if(pUk != nullptr)
      {
         CComPtr<IFolderFilterSite> pfilter;

         pUk->QueryInterface(&pfilter);
         if(pfilter != nullptr)
         {
            IUnknown * pThis = (IUnknown *)pframe;
            pfilter->SetFilter(pThis);


         }

      }

   }
   else if(uMsg == BFFM_SELCHANGED)
   {
      LPITEMIDLIST pidl = (LPITEMIDLIST) lParam;
      // get the name of the folder
      TCHAR path[MAX_PATH];
      SHGetPathFromIDList(pidl,path);
      pframe->m_strSelPath =  path;

   }
   else if(uMsg == BFFM_VALIDATEFAILED)
   {
      LPCTSTR lpcwszNewName = (LPCTSTR)lParam;

      CString str;

      str = lpcwszNewName;

      CString strCandidateNewPath;

      if(!pframe->ValidateNewName(str, strCandidateNewPath))
      {
         show_a_message_box("A library with this name already exists at the specified location (" + strCandidateNewPath + "). Please choose another location or another name.",e_message_box_icon_information);
         return 1;
      }


   }
   return 0;

}

bool CLibraryFrame::ValidateNewName(const ::scoped_string & scopedstrNewName,CString & strCandidateNewPath)
{
   CString & strNewPath = strCandidateNewPath;

   strNewPath = m_strSelPath;

   strNewPath.TrimRight("/");
   strNewPath.TrimRight("\\");

   strNewPath += "\\" + CString(pszNewName);
   CString strExt = ".spotlibrary";
   if(strNewPath.right()(strExt.GetLength()).CompareNoCase(strExt) != 0)
   {

      strNewPath += ".spotlibrary";

   }

   if(PathIsDirectory(strNewPath))
   {
      return false;
   }
   if(PathFileExists(strNewPath))
   {
      return false;
   }
   m_strNewPath = strNewPath;

   return true;


}


HRESULT STDMETHODCALLTYPE CLibraryFrame::QueryInterface(const IID & iid,void ** p)
{

   if(iid == IID_IUnknown)
   {
      
      *p = (IUnknown *) this;
      return S_OK;
   }
   else if(iid == IID_IFolderFilter)
   {

      *p = (IFolderFilter *) this;
      return S_OK;
   }
   return E_FAIL;
}


ULONG STDMETHODCALLTYPE CLibraryFrame::AddRef()
{

   return ++m_ulRef;

}


ULONG STDMETHODCALLTYPE CLibraryFrame::Release()
{
   
   return --m_ulRef;

}


HRESULT CLibraryFrame::GetEnumFlags(IShellFolder * psf, PCIDLIST_ABSOLUTE pidlFolder, HWND * phwnd, DWORD * pgrfFlags)
{
   *pgrfFlags = SHCONTF_FOLDERS;
   
   return S_OK;
}


HRESULT CLibraryFrame::ShouldShow(IShellFolder * psf,PCIDLIST_ABSOLUTE pidlFolder,PCUITEMID_CHILD pidlItem)
{
   IShellItem *psi;

   HRESULT hr = SHCreateItemWithParent(nullptr,psf,pidlItem,IID_PPV_ARGS(&psi));
   if(SUCCEEDED(hr))
   {
      // Determine here whether the item should be shown. This determination
      // is application-dependent.
      LPWSTR lpwstr = nullptr;
      psi->GetDisplayName(SIGDN_FILESYSPATH,&lpwstr);
      CString str = get_utf8(lpwstr);
      CoTaskMemFree(lpwstr);

      if(m_bOpenLibrary)
      {

         CString strLo(str);

         strLo.MakeLower();

         const scoped_string & strFind = ".spotlibrary";

         int iLenFind = strlen(pszFind);

         int iFind = strLo.Find(pszFind);

         if(iFind >= 0 && strLo.GetLength() > iFind + iLenFind + 1)
         {
            return S_FALSE;

         }

         if(!has_subdir(str))
         {

            return S_FALSE;

         }

      }
      else
      {

      }

      
      psi->Release();
   }

   return S_OK;
}


void CLibraryFrame::OnFileNewlibrary()
{

   //CString strFilter;

   //strFilter.LoadString(IDS_LIBRARYSAVEFILTERS);

   //CFileDialog dlg(false,"spotlibrary","untitled library.spotlibrary",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "");

   //dlg.DoModal();
   m_bOpenLibrary = false;

   BROWSEINFO bi ={0};
   bi.hwndOwner = GetSafeHwnd();
   bi.lParam = (LPARAM) this;
   bi.ulFlags = BIF_USENEWUI | BIF_NONEWFOLDERBUTTON | BIF_VALIDATE;
   bi.lpfn = &LibraryFrameBrowseCallbackProc;
   LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
   if(pidl != 0)
   {
      // get the name of the folder
      TCHAR path[MAX_PATH];
      SHGetPathFromIDList(pidl,path);

      // free memory used
      IMalloc * imalloc = 0;
      if(SUCCEEDED(SHGetMalloc(&imalloc)))
      {
         imalloc->Free(pidl);
         imalloc->Release();
      }
   }
}


void CLibraryFrame::OnFileOpenlibrary()
{
   m_bOpenLibrary = true;
   BROWSEINFO bi ={0};
   bi.lParam = (LPARAM) this;
   bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_NONEWFOLDERBUTTON;
   bi.lpfn = &LibraryFrameBrowseCallbackProc;
   bi.lpszTitle = _T("Select Microspot Library");
   bi.hwndOwner = GetSafeHwnd();
   LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
   if(pidl != 0)
   {
      // get the name of the folder
      TCHAR path[MAX_PATH];
      SHGetPathFromIDList(pidl,path);

      // free memory used
      IMalloc * imalloc = 0;
      if(SUCCEEDED(SHGetMalloc(&imalloc)))
      {
         imalloc->Free(pidl);
         imalloc->Release();
      }
   }
}
