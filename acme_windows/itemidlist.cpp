#include "framework.h"
#include "itemidlist.h"
#include "known_folder_struct.h"
#include "acme/exception/exception.h"
#include "acme_windows_common/cotaskptr.h"


itemidlist::itemidlist() :
   m_pidl(nullptr)
{

}


itemidlist::itemidlist(const itemidlist & iidl) :
   m_pidl(nullptr)
{

   m_pidl = ILCloneFull(iidl);

}


itemidlist::itemidlist(itemidlist && iidl)
{

   m_pidl = iidl.m_pidl;

   iidl.m_pidl = nullptr;

}


itemidlist::itemidlist(const ::string & pszPath) :
   m_pidl(nullptr)
{

   parse(pszPath);

}


itemidlist::itemidlist(LPCITEMIDLIST pidl, bool bAttach) :
   m_pidl(nullptr)
{

   if (bAttach)
   {

      attach((LPITEMIDLIST) pidl);

   }
   else
   {

      copy(pidl);

   }

}


itemidlist::~itemidlist()
{

   free();

}


void itemidlist::_free(LPITEMIDLIST & pidl)
{

   if (!pidl)
   {

      return;

   }

   ILFree(pidl);

   pidl = nullptr;

}


int itemidlist::count() const
{

   return _count(m_pidl); //Get pidl count.

}


bool itemidlist::is_empty() const
{

   return _is_empty(m_pidl); 

}


bool itemidlist::is_unitary() const
{

   return _is_unitary(m_pidl);

}


bool itemidlist::is_empty_or_unitary() const
{

   return _is_empty_or_unitary(m_pidl);

}


bool itemidlist::has_child() const
{

   return _has_child(m_pidl);

}

int itemidlist::len() const
{

   return _len(m_pidl);

}


void itemidlist::free()
{

   _free(m_pidl);

}



bool itemidlist::parse(const ::string & pszPath)
{

   free();

   if(FAILED(_parse(*this, pszPath)))
   {

      return false;

   }

   return true;

}


//LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidl)
//{
//
//   if (!pidl)
//   {
//
//      return nullptr;
//
//   }
//
//   return ILCloneFull(pidl);
//
//}


bool itemidlist::_is_empty(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return true;

   }

   if (ILIsEmpty(pidl))
   {

      return true;

   }

   return false;

}


int itemidlist::_count(LPCITEMIDLIST pidl)
{

   if (_is_empty(pidl))
   {

      return 0;

   }

   int nCount = 0;

   while (pidl)
   {

      nCount++;

      pidl = ILGetNext(pidl);

   }

   return nCount - 1;

}



bool itemidlist::__is_unitary(LPCITEMIDLIST pidl)
{

   int nCount = 0;

   while (pidl && nCount <= 1)
   {

      nCount++;

      pidl = ILGetNext(pidl);

   }

   return nCount == 1;

}


bool itemidlist::_is_unitary(LPCITEMIDLIST pidl)
{

   if (_is_empty(pidl))
   {

      return 0;

   }

   int nCount = 0;

   while (pidl && nCount <= 1)
   {

      nCount++;

      pidl = ILGetNext(pidl);

   }

   return nCount == 1;

}


bool itemidlist::_is_empty_or_unitary(LPCITEMIDLIST pidl)
{

   if (_is_empty(pidl))
   {

      return true;

   }

   return __is_unitary(pidl);

}


bool itemidlist::_has_child(LPCITEMIDLIST pidl)
{

   if (_is_empty(pidl))
   {

      return false;

   }

   if (__is_unitary(pidl))
   {

      return false;

   }

   return true;

}

int itemidlist::_len(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return 0;

   }

   return ILGetSize(pidl);

}


itemidlist itemidlist::operator/(const itemidlist & piidl) const
{

   return ILCombine(m_pidl, piidl);

}


itemidlist & itemidlist::operator=(const ::string & pszPath)
{

   if (!parse(pszPath))
   {

      throw ::exception(error_resource, "Failed to parse the path " + string (pszPath));

   }

   return *this;

}


itemidlist & itemidlist::operator=(const itemidlist & piidl)
{

   copy(piidl);

   return *this;

}

LPITEMIDLIST itemidlist::_cat(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
   
   LPITEMIDLIST pidlNew = ILCombine(pidl1, pidl2);

   return pidlNew;

}


//LPITEMIDLIST itemidlist::_create(int nSize)
//{
//
//   comptr < IMalloc > pmalloc;
//
//   LPITEMIDLIST pidl = nullptr;
//
//   if (FAILED(SHGetMalloc(&pmalloc)))
//   {
//
//      throw ::exception(error_no_memory);
//
//      return nullptr;
//
//   }
//
//   pidl = (LPITEMIDLIST)pmalloc->Alloc(nSize);
//
//   if (pidl == nullptr)
//   {
//
//      throw ::exception(error_no_memory);
//
//      return nullptr;
//
//   }
//
//   ::zero(pidl, nSize);
//
//   return pidl;
//
//}


itemidlist & itemidlist::operator=(LPCITEMIDLIST pidl)
{

   copy(pidl);

   return *this;

}

bool itemidlist::copy(LPCITEMIDLIST pidlf)
{

   free();

   m_pidl = ILCloneFull(pidlf);

   return true;

}


itemidlist & itemidlist::operator/=(const itemidlist & pidl)
{

   LPITEMIDLIST pidlp = m_pidl;

   m_pidl = _cat(m_pidl, pidl);

   _free(pidlp);

   return *this;

}


itemidlist & itemidlist::operator-=(int i)
{

   while (i > 0)
   {

      if (!ILRemoveLastID(m_pidl))
      {

         break;

      }

      i--;

   }

   return *this;

}

itemidlist itemidlist::operator-(int i) const
{

   auto pidl = ILCloneFull(m_pidl);

   while (i > 0)
   {

      if (!ILRemoveLastID(pidl))
      {

         break;

      }

      i--;

   }

   return pidl;

}


itemidlist & itemidlist::remove_last_item_id()
{

   if (is_empty_or_unitary())
   {

      free();

   }
   else
   {

      ILRemoveLastID(m_pidl);

   }

   return *this;

}


itemidlist itemidlist::last_item_id_removed() const
{

   if (is_empty_or_unitary())
   {

      return nullptr;

   }

   itemidlist itemidlist(m_pidl, false);

   itemidlist.remove_last_item_id();

   return itemidlist;

}

itemidlist itemidlist::at(int nIndex) const
{

   return _create_relative(m_pidl, nIndex);

}


itemidlist itemidlist::operator[](int nIndex) const
{

   return at(nIndex);

}


LPITEMIDLIST itemidlist::_create_relative(LPCITEMIDLIST pidlf, int iIndex)
{

   if (iIndex < 0)
   {

      return nullptr;

   }

   LPCITEMIDLIST p = pidlf;

   while (iIndex > 0)
   {

      p = ILGetNext(p);

      iIndex--;

   }

   if (p && iIndex == 0)
   {

      return ILClone(p);

   }

   return nullptr;

}


bool itemidlist::operator==(const itemidlist & pidl) const
{


   return ILIsEqual(m_pidl, pidl);


}


itemidlist itemidlist::left(int nCount) const
{

   auto pitem = _copy(m_pidl, nCount);

   return pitem;

}


int itemidlist::_len(LPCITEMIDLIST pidl, int nCount)
{

   int iCount = _count(pidl);

   if (nCount >= iCount)
   {

      return _len(pidl);

   }

   int cbTotal = 0;

   if (pidl)
   {

      while (nCount--)
      {

         cbTotal += pidl->mkid.cb;

         pidl = _next(pidl);

      }

   }

   return cbTotal;

}


string itemidlist::display_name(::u32 dwFlags) const
{

   comptr < IShellFolder > psf;


   comptr < IShellFolder > psfDesktop;


   HRESULT hr;

   itemidlist pidl;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))

   {

      return "";

   }

   int nCount = count();

   if (nCount > 1)
   {
      pidl = left(nCount - 1);

      hr = psfDesktop->BindToObject(pidl, 0, IID_IShellFolder, (LPVOID*)&psf);


      if (FAILED(hr))
      {

         return "";

      }

   }
   else
   {

      psf = psfDesktop;


   }

   pidl = at(nCount - 1);

   return _display_name(psf, pidl, dwFlags);


}


string itemidlist::path() const
{

   return _path(m_pidl);

}


int itemidlist::icon_index(int uFlags) const
{

   return _icon_index(m_pidl, uFlags);

}


void itemidlist::attach(LPITEMIDLIST pidl)
{

   free();

   m_pidl = pidl;

}


LPITEMIDLIST itemidlist::detach()
{

   LPITEMIDLIST pidl = m_pidl;

   m_pidl = nullptr;

   return pidl;

}


string itemidlist::tooltip_info() const
{

   comptr < IShellFolder > psfDesktop;

   comptr < IShellFolder > psf;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return "";

   }

   int iCount = count();

   itemidlist item = left(iCount - 1);

   HRESULT hr = psfDesktop->BindToObject(item, 0, IID_IShellFolder, (LPVOID*)&psf);

   if (FAILED(hr))
   {

      return "";

   }

   item = at(iCount - 1);

   return _tooltip_info(psf, item);

}


string itemidlist::_tooltip_info(IShellFolder * psf, LPCITEMIDLIST pidl)

{

   if (!psf)

   {

      return "";

   }

   comptr < IQueryInfo > pinfo;

   psf->GetUIObjectOf(nullptr, 1, (LPCITEMIDLIST*)&(pidl), IID_IQueryInfo, 0, (LPVOID*)&pinfo);


   if (pinfo.is_null())
   {

      return "";

   }

   cotaskptr < LPWSTR > pwsz;


   pinfo->GetInfoTip(0, &pwsz);


   return pwsz.m_p;


}


LPITEMIDLIST itemidlist::_full(IShellFolder * psf, LPCITEMIDLIST lpi)

{

   //   OLECHAR szOleChar[MAX_PATH + 1];

   comptr < IShellFolder > psfDeskTop;

   LPITEMIDLIST pifq;

   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   string str = _display_name(psf, lpi, SHGDN_FORPARSING);


   if (str.is_empty())
   {

      return nullptr;

   }

   hr = SHGetDesktopFolder(&psfDeskTop);


   if (FAILED(hr))
   {

      return nullptr;

   }

   wstring wstr(str);

   auto pwsz = wstr.get_string_buffer();

   hr = psfDeskTop->ParseDisplayName(nullptr, nullptr, pwsz, &ulEaten, &pifq, &ulAttribs);


   if (FAILED(hr))
   {

      return nullptr;

   }

   return pifq;


}


HRESULT itemidlist::_GetUIObjectOf(REFIID riid, LPVOID* ppOut, LPITEMIDLIST pidlf, HWND hWnd)
{

   comptr < IShellFolder > psf;


   HRESULT hr = S_OK;

   itemidlist ciidf(pidlf), pidl;

   ciidf.split(&psf, pidl);


   if (psf.is_null())

   {

      return E_FAIL;

   }

   hr = psf->GetUIObjectOf(hWnd, 1, pidl, riid, nullptr, ppOut);


   return hr;

}


HRESULT itemidlist::GetUIObjectOf(REFIID riid, LPVOID* ppOut, HWND hWnd)
{

   return _GetUIObjectOf(riid, ppOut, m_pidl, hWnd);

}


//Get relative pidl and the corresponding ShellFolder interface.
void itemidlist::split(IShellFolder ** psf, itemidlist & pidl)
{

   _split(psf, pidl.m_pidl, m_pidl);

}


itemidlist itemidlist::last() const
{

   int nCount = count();

   return at(nCount - 1);

}


void itemidlist::_split(IShellFolder ** psf, LPITEMIDLIST &pidl, LPITEMIDLIST pidlf)
{

   pidl = nullptr;

   *psf = nullptr;

   if (!pidlf)
   {

      SHGetDesktopFolder(psf);

      return;

   }

   comptr < IShellFolder > psfDesktop ;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return;

   }

   auto pidlFolder = ILClone(pidlf);

   ILRemoveLastID(pidlFolder);

   if (pidlFolder)
   {

      psfDesktop->BindToObject(pidlFolder, nullptr, IID_IShellFolder, (LPVOID*)psf);

      pidl = pidlFolder;

   }
   else
   {

      *psf = psfDesktop;

      (*psf)->AddRef();

   }

}


LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidlOrg, int nCount)
{

   if (nCount < 1)
   {

      return nullptr;

   }

   int iToRemove = _count(pidlOrg) - nCount;

   if (iToRemove <= 0)
   {

      return nullptr;

   }

   LPITEMIDLIST pidlRes = ILClone(pidlOrg);

   while (iToRemove > 0)
   {

      ILRemoveLastID(pidlRes);

      iToRemove--;

   }

   return pidlRes;

}


int itemidlist::_compare(LPCITEMIDLIST pidlf1, LPCITEMIDLIST pidlf2,
                         IShellFolder * psfFolder, LPARAM lParam)
{

   comptr < IShellFolder > psfDesktop = psfFolder;

   if (psfDesktop.is_null())
   {

      SHGetDesktopFolder(&psfDesktop);

      if (psfDesktop.is_null())
      {

         return 0;

      }

   }
   else
   {

      psfDesktop->AddRef();

   }

   HRESULT hr = psfDesktop->CompareIDs(lParam, pidlf1, pidlf2);

   return int(HRESULT_CODE(hr));

}


bool itemidlist::get_refid_for_known_folder(KNOWNFOLDERID & refid, const ::string & strKnownFolder)
{

   auto pknownfolderstruct = get_known_folder_struct(strKnownFolder);

   if(::is_set(pknownfolderstruct))
   {

      refid = pknownfolderstruct->m_knownfolderid;

      return true;

   }

   return false;

}


HRESULT itemidlist::get_item_in_known_folder(itemidlist & idl, const string & strPathParam)
{

   string strPath(strPathParam);

   HRESULT hr = E_FAIL;

   auto pknownfolder = get_known_folder_struct(strPathParam);

   if (pknownfolder)
   {

      while (pknownfolder->m_strKnownFolder.has_char())
      {

         const string & strKnownFolder = pknownfolder->m_strKnownFolder;

         if (strPath.begins_eat_ci(strKnownFolder))
         {

            wstring wstrPath(strPath);

            HANDLE handleToken = NULL;

            ITEMIDLIST * pidl = nullptr;

            hr = SHGetKnownFolderIDList(
               pknownfolder->m_knownfolderid,
               0,
               handleToken,
               &pidl);

            if (SUCCEEDED(hr))
            {

               if (strPath.has_char())
               {

                  itemidlist itemidlistRelative(strPath);

                  itemidlist itemidlist(pidl);

                  idl = itemidlist / itemidlistRelative;

               }
               else
               {

                  idl.m_pidl = pidl;

               }

            }

            return hr;

         }

         pknownfolder++;

      }

   }

   return hr;

}


HRESULT itemidlist::_parse(itemidlist & idl, const ::string & strPath)
{

   HRESULT hr = get_item_in_known_folder(idl, strPath);

   if(SUCCEEDED(hr))
   {

      return hr;

   }

   wstring wstrPath(strPath);

   comptr < IShellFolder > pshellfolderDesktop;

   if (FAILED(SHGetDesktopFolder(&pshellfolderDesktop)))
   {

      return E_FAIL;

   }

   ULONG chEaten = 0;

   hr = pshellfolderDesktop->ParseDisplayName(nullptr, nullptr, wstrPath, &chEaten, &idl.m_pidl, nullptr);

   return hr;

}


//HRESULT itemidlist::_parse(itemidlist & idl, const ::string & pcszPath)
//{
//
//   return _parse(idl, pcszPath, psfDesktop);
//
//}


int itemidlist::_icon_index(LPCITEMIDLIST pidlf, int uFlags)
{

   SHFILEINFO sfi;

   SHGetFileInfo((LPCTSTR)pidlf, 0, &sfi, sizeof(SHFILEINFO), uFlags);

   return sfi.iIcon;

}


int itemidlist::_overlay_icon_index(IShellFolder * psfFolder, LPCITEMIDLIST pidl)
{

   if (!psfFolder || !pidl)

   {

      return -1;

   }

   comptr < IShellIcon > psiIcon;


   comptr < IShellIconOverlay >  psiIconOl;


   int index = -1;

   psfFolder->QueryInterface(IID_IShellIcon, (LPVOID*)&psiIcon);


   if (psiIcon.is_null())

   {

      return -1;

   }

   psiIcon->QueryInterface(IID_IShellIconOverlay, (LPVOID*)&psiIconOl);


   if (psiIconOl.is_null())

   {

      return -1;

   }

   if (psiIconOl->GetOverlayIndex(pidl, &index) != S_OK)

   {

      index = -1;

   }

   return index;

}


string itemidlist::_display_name(STRRET & strret, LPCITEMIDLIST pidl)
{

   string str;

   switch (strret.uType)
   {
   case STRRET_WSTR:
   {
      str = (WCHAR *)strret.pOleStr;
   }
   break;
   case STRRET_OFFSET:
   {
      str = (char *)pidl + strret.uOffset;
   }
   break;
   case STRRET_CSTR:
   {
      str = (char *)strret.cStr;
      break;
   }
   default:
      break;
   }

   return str;

}


string itemidlist::_display_name(IShellFolder * psf, LPCITEMIDLIST pi, ::u32 dwFlags)
{

   string str;

   STRRET strret;

   if (NOERROR == psf->GetDisplayNameOf(pi, dwFlags, &strret))
   {

      str = _display_name(strret, pi);

   }

   return str;

}


string itemidlist::_path(LPCITEMIDLIST pidl)
{

   wstring wstr;

   auto pwsz = wstr.get_string_buffer(2048);

   SHGetPathFromIDListEx(pidl, pwsz, 2048, 0);

   wstr.release_string_buffer();

   return wstr;

}



comptr < IShellFolder > itemidlist::get_shell_folder() const
{

   comptr < IShellFolder > pfolder;

   HRESULT hr = SHCreateItemFromIDList(
      m_pidl,
      IID_IShellFolder,
      (void **)&pfolder
      );

   if (FAILED(hr))
   {

      return nullptr;

   }

   return pfolder;

}


comptr < IShellItem > itemidlist::get_shell_item() const
{

   comptr < IShellItem > pitem;

   HRESULT hr = SHCreateItemFromIDList(
      m_pidl,
      IID_IShellItem,
      (void **)&pitem
   );

   if (FAILED(hr))
   {

      return nullptr;

   }

   return pitem;

}
