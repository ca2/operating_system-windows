#pragma once

#include "CustomMiniDockFrameWnd.h"

// CLibraryFrame frame

class CLibraryFrame :
   public CMiniFrameWnd,
   public IFolderFilter
{
public:
   ULONG    m_ulRef;
   bool        m_bOpenLibrary;
   CString        m_strNewPath;
   CString        m_strSelPath;
   
	CLibraryFrame();           
	virtual ~CLibraryFrame();
   CToolBar    m_toolbar;
   CFrameWnd *    m_pMainFrame;
   bool m_bTracking;
   virtual void NotifyFloatingWindows(DWORD dwFlags);
   virtual BOOL LoadFrame(UINT nIDResource,DWORD dwDefaultStyle, CWnd* pParentWnd,CCreateContext* pContext);
   BOOL Create(CWnd* pParent,DWORD dwBarStyle, PVOID p);
protected:
	()
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
   BOOL OnNcCreate(LPCREATESTRUCT lpcs);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   void OnActivate(UINT nState,CWnd* pWndOther,BOOL bMinimized);
   BOOL OnNcActivate(BOOL bActive);
   void OnNcLButtonDblClk(UINT nHitTest,CPoint int_point);
   void OnNcLButtonDown(UINT nHitTest,CPoint int_point);
   void OnNcLButtonUp(UINT nHitTest,CPoint int_point);
   void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
   void OnFileNewlibrary();
   void OnFileOpenlibrary();
   bool ValidateNewName(const ::string & psz, CString & strCandidateNewPath);
   virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID &,void **);
   virtual ULONG STDMETHODCALLTYPE AddRef();
   virtual ULONG STDMETHODCALLTYPE Release();
   virtual HRESULT STDMETHODCALLTYPE GetEnumFlags(IShellFolder * psf,PCIDLIST_ABSOLUTE pidlFolder,HWND * phwnd,DWORD * pgrfFlags);
   virtual HRESULT STDMETHODCALLTYPE ShouldShow(IShellFolder * psf,PCIDLIST_ABSOLUTE pidlFolder,PCUITEMID_CHILD pidlItem);
};


