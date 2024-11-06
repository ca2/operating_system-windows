#pragma once
/*-------------------------------------
|   itemidlist class for operate     |
| ITEMIDLIST data type and more       |
| functions.                          |
|           Version:2.0               |
|                                     |
|     Written by kim-ryo,2002.9(1.0)  |
|        Updated in 2002.11(2.0)	  |
|									  |
|  If you have any suggestion, please |
|mail to kim-ryo@netease.com,greate   |
|Thanks                               |
--------------------------------------*/

#include "acme/prototype/prototype/particle.h"
#include "acme_windows_common/comptr.h"
#include "acme/_operating_system.h"
#include <Shlobj.h>
#include <shellapi.h>


class CLASS_DECL_ACME_WINDOWS itemidlist :
   virtual public ::particle
{
public:


   LPITEMIDLIST m_pidl;


   itemidlist();
   itemidlist(const ::string & strPath);
   itemidlist(LPCITEMIDLIST pidl, bool bAttach = true);
   itemidlist(const itemidlist & iidl);
   itemidlist(itemidlist && iidl);
   ~itemidlist();

   //comptr < IShellFolder> _017GetParentShellFolder(LPITEMIDLIST piidlChild);

   //comptr < IShellFolder> _017GetShellFolder(const ::string & str, LPITEMIDLIST piidlChild);

   comptr < IShellFolder> get_shell_folder() const;

   comptr < IShellItem> get_shell_item() const;


   HRESULT GetUIObjectOf(REFIID riid, LPVOID* ppOut, HWND hWnd = nullptr);
   //Get relative pidl and the corresponding ShellFolder interface.
   void split(IShellFolder ** psf, itemidlist & ciid);

   //get last relative pidl.
   itemidlist last() const;
   string tooltip_info() const;
   void attach(LPITEMIDLIST pidl);
   itemidlist last_item_id_removed() const;
   itemidlist & remove_last_item_id() ;
   LPITEMIDLIST detach();
   int icon_index(int uFlags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON) const;
   string display_name(unsigned int dwFlags = SHGDN_NORMAL) const;//Retrieve pidl's dislpay name.
   //Copy a pidl due to the count number.
   //nCount=-1 indicate copy all pidl.
   itemidlist left(int nCount = -1) const;
   bool is_empty() const;
   bool is_unitary() const;
   bool is_empty_or_unitary() const;
   bool has_child() const; // has count >= 2
   itemidlist at(int nIndex) const;//Return a relative pidl at specified index.
   bool copy(LPCITEMIDLIST pidlf);
   inline int count() const;
   inline int len() const;
   inline void free();
   string path() const;//Retrieve full path.(only available for full-quality pidl)
   bool parse(const ::string & strPath);

   itemidlist operator/(const itemidlist & piidl) const ;//Concat two pidls.
   inline operator LPITEMIDLIST() const { return m_pidl; }
   inline operator LPCITEMIDLIST() const { return (LPCITEMIDLIST)m_pidl; }
   inline operator LPITEMIDLIST*() { return &m_pidl; }
   inline operator LPCITEMIDLIST*() { return (LPCITEMIDLIST*)&m_pidl; }
   itemidlist & operator=(const ::string & strPath);
   itemidlist & operator=(const itemidlist & pidl);
   itemidlist & operator=(LPCITEMIDLIST pidl);
   itemidlist & operator/=(const itemidlist & ciidl);//Add a ___new pidl to tail.
   itemidlist & operator-=(int i);//erase i Count items from tail.
   itemidlist operator -(int i) const;//erase i Count items from tail.
   bool operator==(const itemidlist & ciidl) const;
   itemidlist operator[](int nIndex) const;//Return a relative pidl at specified index.



   static int _icon_index(LPCITEMIDLIST pidlf, int uFlags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
   static void _split(IShellFolder ** psf, LPITEMIDLIST& pidl, LPITEMIDLIST pidlf);

   static string _tooltip_info(IShellFolder * psf, LPCITEMIDLIST pidl);

   //static LPITEMIDLIST _create(int nSize);
   static LPITEMIDLIST _cat(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);//Concat two pidl.
   //Create a relative pidl through a full-quality pidl at specified index.
   static LPITEMIDLIST _create_relative(LPCITEMIDLIST pidlf, int Index);
   static int _count(LPCITEMIDLIST pidl);
   static bool _is_empty(LPCITEMIDLIST pidl);
   static bool _is_unitary(LPCITEMIDLIST pidl);
   static bool __is_unitary(LPCITEMIDLIST pidl);
   static bool _is_empty_or_unitary(LPCITEMIDLIST pidl);
   static bool _has_child(LPCITEMIDLIST pidl); // has count >= 2
   static int _len(LPCITEMIDLIST pidl);
   static int _len(LPCITEMIDLIST pidl, int nCount);//Get pidl size_i32 throught the specified count.
   static void _free(LPITEMIDLIST& pidl);
   static LPITEMIDLIST _full(IShellFolder * psf, LPCITEMIDLIST lpi);

   static string _display_name(IShellFolder * psf, LPCITEMIDLIST lpi, unsigned int dwFlags);

   static HRESULT _GetUIObjectOf(REFIID riid, LPVOID* ppOut, LPITEMIDLIST pidlf, HWND hWnd);
   static LPITEMIDLIST _copy(LPCITEMIDLIST pidlOrg, int nCount);
   static int _order(LPCITEMIDLIST pidlf1, LPCITEMIDLIST pidlf2, IShellFolder * psfFolder = nullptr, LPARAM lParam = 0);//return zero means same,non-zero means different.
   //static HRESULT _parse(itemidlist & idl, const ::string & strPath, IShellFolder * psfFolder);
   static HRESULT _parse(itemidlist & idl, const ::string & strPath);
   static HRESULT get_item_in_known_folder(itemidlist & idl, const string & strPath);
   static bool get_refid_for_known_folder(KNOWNFOLDERID & refid, const ::string & strKnownFolder);
   static int _overlay_icon_index(IShellFolder * psfFolder, LPCITEMIDLIST pidl);

   static string _display_name(STRRET& str, LPCITEMIDLIST pidl);
   static string _path(LPCITEMIDLIST pidl);

   

   inline static LPCITEMIDLIST _next(LPCITEMIDLIST pidl)
   {

      unsigned char * pMem = (unsigned char *)pidl;

      pMem += pidl->mkid.cb;

      return (LPITEMIDLIST)pMem;

   }


   inline static LPITEMIDLIST _next(LPITEMIDLIST pidl)
   {

      return (LPITEMIDLIST)_next((LPCITEMIDLIST)pidl);

   }


};



