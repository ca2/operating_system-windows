#include "framework.h"
#include "acme/node/windows/_windows.h"


/***
*int _validdrive( unsigned int drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _validdrive (
unsigned int drive
)
{
   unsigned int retcode;
   wchar_t drvstr[4];

   if ( drive == 0 )
      return 1;

   drvstr[0] = (char) ('A' + drive - 1);
   drvstr[1] = ':';
   drvstr[2] = '\\';
   drvstr[3] = '\0';

   if ( ((retcode = GetDriveTypeW( drvstr )) == DRIVE_UNKNOWN) ||
         (retcode == DRIVE_NO_ROOT_DIR) )
      return 0;

   return 1;
}

/*WCHAR * __cdecl _wgetdcwd (
int drive,
WCHAR *pnbuf,
int maxlen
);

*/
/***
*_TSCHAR *_getcwd(pnbuf, maxlen) - get current working directory of default drive
*
*Purpose:
*       _getcwd gets the current working directory for the ::account::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then nullptr is returned.  If pnbuf = nullptr, maxlen is ignored.
*       An entry point "_getdcwd()" is defined with takes the above
*       parameters, plus a drive number.  "_getcwd()" is implemented
*       as a call to "_getcwd()" with the default drive (0).
*
*       If pnbuf = nullptr, maxlen is ignored, and a buffer is automatically
*       allocated using malloc() -- a pointer to which is returned by
*       _getcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       _TSCHAR *pnbuf = pointer to a buffer maintained by the ::account::user;
*       int maxlen = length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the ca.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/

/*WCHAR * __cdecl _wgetcwd (
WCHAR *pnbuf,
int maxlen
)
{
WCHAR *retval;


retval = _wgetdcwd(0, pnbuf, maxlen);

return retval;
}*/


/***
*_TSCHAR *_getdcwd(drive, pnbuf, maxlen) - get ca.w.d. for given drive
*
*Purpose:
*       _getdcwd gets the current working directory for the ::account::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then nullptr is returned.  If pnbuf = nullptr, maxlen is ignored,
*       and a buffer is automatically allocated using malloc() --
*       a pointer to which is returned by _getdcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       int drive   - number of the drive being inquired about
*                     0 = default, 1 = 'a:', 2 = 'b:', etc.
*       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::account::user;
*       int maxlen  - length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the ca.w.d. name
*       (same as pnbuf if non-nullptr; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/


/*WCHAR * __cdecl _wgetdcwd (
int drive,
WCHAR *pnbuf,
int maxlen
)
{
WCHAR *point;
WCHAR dirbuf[_MAX_PATH];
WCHAR drvstr[4];
int len;
WCHAR *pname; /* only used as argument to GetFullPathName */

/*
* GetCurrentDirectory only works for the default drive in Win32
*/
/*      if ( drive != 0 ) {
/*
* Not the default drive - make sure it's valid.
*/
/*        if ( !_validdrive(drive) ) {
_doserrno = ERROR_INVALID_DRIVE;
//                errno = EACCES;
return nullptr;
}

/*
* get the current directory string on that drive and its length
*/
/*      drvstr[0] = (char) ('A' - 1 + drive);
drvstr[1] = ':';
drvstr[2] = '.';
drvstr[3] = '\0';
len = shell::GetFullPathName( drvstr,
sizeof(dirbuf) / sizeof(_TSCHAR),
dirbuf,
&pname );

} else {

/*
* get the current directory string and its length
*/
/*            len = GetCurrentDirectory( sizeof(dirbuf) / sizeof(_TSCHAR),
(char *)dirbuf );
}

/* API call failed, or buffer not large enough */
/*      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
return nullptr;

/*
* set up the buffer.
*/
/*    if ( (point = pnbuf) == nullptr ) {
/*
* allocate a buffer for the ::account::user.
*/
/*      if ( (point = (WCHAR *)malloc(maximum(len, maxlen) * sizeof(WCHAR)))
== nullptr )
{
//                errno = ENOMEM;
return nullptr;
}
}
else if ( len > maxlen ) {
/*
* Won't fit in the ::account::user-supplied buffer!
*/
//            errno = ERANGE; /* Won't fit in ::account::user buffer */
/*    return nullptr;
}

/*
* Place the current directory string into the ::account::user buffer
*/
/*
return wcscpy(point, dirbuf);
}

/*#ifndef WPRFLAG

/***
*int _validdrive( unsigned int drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/

/*int __cdecl _validdrive (
unsigned int drive
)
{
unsigned int retcode;
char drvstr[4];

if ( drive == 0 )
return 1;

drvstr[0] = 'A' + drive - 1;
drvstr[1] = ':';
drvstr[2] = '\\';
drvstr[3] = '\0';

if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
(retcode == DRIVE_NO_ROOT_DIR) )
return 0;

return 1;
}*/

namespace windows
{

   shell shell::theWindowsShell;


   shell::shell()
   {

   }

   shell::~shell()
   {

   }

   bool shell::Initialize()
   {

      theWindowsShell.m_pfnSHGetPathFromIDList = ::SHGetPathFromIDListW;
      theWindowsShell.m_pfnFindFirstFile = ::FindFirstFileW;
      theWindowsShell.m_pfnFindNextFile = ::FindNextFileW;
      theWindowsShell.m_pfnMoveFile = ::MoveFileW;
      theWindowsShell.m_pfn_fullpath = ::_wfullpath;
      theWindowsShell.m_pfnGetFullPathName = ::GetFullPathNameW;
      theWindowsShell.m_pfnGetVolumeInformation = ::GetVolumeInformationW;
      theWindowsShell.m_pfnSHGetFileInfo = ::SHGetFileInfoW;
      theWindowsShell.m_pfnGetStringTypeEx = ::GetStringTypeExW;
      theWindowsShell.m_pfnGetTempPath = ::GetTempPathW;
      theWindowsShell.m_pfnGetTempFileName = ::GetTempFileNameW;
      theWindowsShell.m_pfnCreateFile = ::CreateFileW;
      theWindowsShell.m_pfnGetModuleFileName = ::GetModuleFileNameW;
      theWindowsShell.m_pfnGetClassInfo = ::GetClassInfoW;
      theWindowsShell.m_pfnRegisterClass = ::RegisterClassW;
      theWindowsShell.m_pfnCreateWindowEx = ::CreateWindowExW;
      return true;
   }

   /*   BOOL shell::_SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
      {
         char pszPathA[MAX_PATH * 2];
         if(!::SHGetPathFromIDListA(pidl, pszPathA))
            return false;
         return utf8_to_unicode(pszPath, MAX_PATH * 2, pszPathA) ? true : false;
      }

      BOOL shell::_MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)

      {
         string str1, str2;
         unicode_to_utf8(str1, pExistingFileName);

         unicode_to_utf8(str2, pNewFileName);

         return ::MoveFileA(str1, str2);
      }

      HANDLE shell::_FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata)

      {
         string
         unicode_to_utf8(pszPathA, MAX_PATH * 2, pcsz);

         WIN32_FIND_DATAA data;
         HANDLE handle = ::FindFirstFileA(pszPathA, &data);
         if(handle == INVALID_HANDLE_VALUE)
            return INVALID_HANDLE_VALUE;

         pdata->dwFileAttributes = data.dwFileAttributes;

         pdata->ftCreationTime = data.ftCreationTime;

         pdata->ftLastAccessTime = data.ftLastAccessTime;

         pdata->ftLastWriteTime = data.ftLastWriteTime;

         pdata->nFileSizeHigh = data.nFileSizeHigh;

         pdata->nFileSizeLow = data.nFileSizeLow;

         pdata->dwReserved0 = data.dwReserved0;

         pdata->dwReserved1 = data.dwReserved1;

         ACPToUnicode(pdata->cFileName, MAX_PATH, data.cFileName);

         ACPToUnicode(pdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);


         return handle;
      }


      BOOL shell::_FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)

      {
         WIN32_FIND_DATAA data;
         bool b = ::FindNextFileA(handle, &data) != false;
         if(b == false)
            return false;

         pdata->dwFileAttributes = data.dwFileAttributes;

         pdata->ftCreationTime = data.ftCreationTime;

         pdata->ftLastAccessTime = data.ftLastAccessTime;

         pdata->ftLastWriteTime = data.ftLastWriteTime;

         pdata->nFileSizeHigh = data.nFileSizeHigh;

         pdata->nFileSizeLow = data.nFileSizeLow;

         pdata->dwReserved0 = data.dwReserved0;

         pdata->dwReserved1 = data.dwReserved1;

         ACPToUnicode(pdata->cFileName, MAX_PATH, data.cFileName);

         ACPToUnicode(pdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);


         return b;
      }


      WCHAR * __cdecl shell::__fullpath (
         WCHAR *UserBuf,
         const WCHAR *path,
         size_t maxlen
         )
      {
         WCHAR *buf;
         WCHAR *pfname;
         unsigned long count;


         if ( !path || !*path )  /* no work to do */
   /*         return( _wgetcwd( UserBuf, (int) maxlen ) );

         /* allocate buffer if necessary */

   //   if ( !UserBuf )
   //      if ( !(buf = (WCHAR *) malloc(_MAX_PATH * sizeof(WCHAR))) ) {
   //         //                errno = ENOMEM;
   //         return( nullptr );
   //      }
   //      else
   //         maxlen = _MAX_PATH;
   //   else
   //      buf = UserBuf;

   //   count = GetFullPathName ( path,
   //      (int) maxlen,
   //      buf,
   //      &pfname );

   //   if ( count >= maxlen ) {
   //      if ( !UserBuf )
   //         free(buf);
   //      //errno = ERANGE;
   //      return( nullptr );
   //   }
   //   else if ( count == 0 ) {
   //      if ( !UserBuf )
   //         free(buf);
   //      //_dosmaperr( GetLastError() );
   //      return( nullptr );
   //   }

   //   return( buf );

   //}


   //unsigned int WINAPI shell::_GetFullPathName(
   //   const unichar * pFileName,

   //   unsigned int nBufferLength,
   //   unichar * pBuffer,

   //   unichar ** pFilePart)

   //{
   //   char pszPathA[MAX_PATH * 2];
   //   UnicodeToACP(pszPathA, MAX_PATH * 2, pFileName);

   //   string str;
   //   char * psz = str.GetBuffer(nBufferLength * 2);

   //   char * pszFilePart;

   //   unsigned int dw = ::GetFullPathName(pszPathA, nBufferLength, psz, &pszFilePart);

   //   str.ReleaseBuffer();
   //   ACPToUnicode(pBuffer, nBufferLength, str);

   //   *pFilePart = lpBuffer + ((int) (pszFilePart - psz));

   //   return dw;
   //}

   //BOOL WINAPI shell::_GetVolumeInformation(
   //   const unichar * pRootPathName,           // root directory

   //   unichar * pVolumeNameBuffer,        // volume name buffer

   //   unsigned int nVolumeNameSize,            // length of name buffer
   //   LPDWORD pVolumeSerialNumber,     // volume serial number

   //   LPDWORD pMaximumComponentLength, // maximum file name length

   //   LPDWORD pFileSystemFlags,        // file system options

   //   unichar * pFileSystemNameBuffer,    // file system name buffer

   //   unsigned int nFileSystemNameSize)         // length of file system name buffer
   //{
   //   string strRootPathName;
   //   string strVolumeNameBuffer;
   //   string strFileSystemNameBuffer;
   //   UnicodeToACP(strRootPathName, pRootPathName);

   //   bool b = ::GetVolumeInformation(
   //      strRootPathName,
   //      strVolumeNameBuffer.GetBuffer(nVolumeNameSize),
   //      nVolumeNameSize,
   //      pVolumeSerialNumber,

   //      pMaximumComponentLength,

   //      pFileSystemFlags,

   //      strFileSystemNameBuffer.GetBuffer(nFileSystemNameSize),
   //      nFileSystemNameSize) != false;

   //   strVolumeNameBuffer.ReleaseBuffer();
   //   strFileSystemNameBuffer.ReleaseBuffer();
   //   ACPToUnicode(
   //      pVolumeNameBuffer,

   //      nVolumeNameSize,
   //      strVolumeNameBuffer);
   //   ACPToUnicode(
   //      pFileSystemNameBuffer,

   //      nFileSystemNameSize,
   //      strFileSystemNameBuffer);
   //   return b;
   //}

   //uptr shell::_SHGetFileInfo(
   //   const unichar * pszPath,
   //   unsigned int dwFileAttributes,
   //   SHFILEINFOW *psfi,
   //   unsigned int cbFileInfo,
   //   unsigned int uFlags)
   //{
   //   __UNREFERENCED_PARAMETER(cbFileInfo);
   //   string strPath;
   //   UnicodeToACP(strPath, pszPath);
   //   SHFILEINFOA shia;
   //   if(!::SHGetFileInfoA(strPath, dwFileAttributes,
   //      &shia,
   //      sizeof(shia),
   //      uFlags))
   //      return false;
   //   ACPToUnicode(
   //      psfi->szDisplayName,
   //      sizeof(psfi->szDisplayName) / sizeof(WCHAR),
   //      shia.szDisplayName);
   //   ACPToUnicode(
   //      psfi->szTypeName,
   //      sizeof(psfi->szTypeName) / sizeof(WCHAR),
   //      shia.szTypeName);
   //   return true;
   //}


   //BOOL shell::_GetStringTypeEx(
   //   LCID uCodePage,
   //   unsigned int dwInfoType,
   //   const unichar * pSrcStr,

   //   int cchSrc,
   //   LPWORD pCharType)

   //{
   //   strsize iCount = cchSrc;
   //   if(iCount < 0)
   //      iCount = UnicodeToMultiByteCount(uCodePage, pSrcStr);

   //   string str;
   //   char * psz = str.GetBuffer(iCount);

   //   if(UnicodeToMultiByte(uCodePage, psz, iCount, lpSrcStr))

   //   {
   //      //str.ReleaseBuffer();
   //      //return true;
   //   }
   //   else
   //   {
   //      return false;
   //   }
   //   if(!GetStringTypeA(uCodePage, dwInfoType, psz, (int) iCount, lpCharType))

   //   {
   //      return false;
   //   }
   //   return true;
   //}


   //unsigned int shell::_GetTempPath(
   //   unsigned int nBufferLength,
   //   unichar * pBuffer)

   //{
   //   string str;
   //   unsigned int dw = ::GetTempPathA(nBufferLength, str.GetBuffer(nBufferLength * 2));
   //   str.ReleaseBuffer();
   //   ACPToUnicode(pBuffer, nBufferLength, str);

   //   return dw;
   //}

   //unsigned int shell::_GetTempFileName(
   //   const unichar * pszPath,

   //   const unichar * pszPrefix,

   //   unsigned int uUnique,
   //   unichar * pTempFileName)

   //{
   //   string strPathName;
   //   string strPrefixString;
   //   string strTempFileName;
   //   UnicodeToACP(strPathName, pszPath);

   //   UnicodeToACP(strPrefixString, pszPrefix);

   //   unsigned int user = ::GetTempFileNameA(
   //      strPathName,
   //      strPrefixString,
   //      uUnique,
   //      strTempFileName.GetBuffer(MAX_PATH));
   //   if(user == 0)
   //   {
   //      return 0;
   //   }
   //   strTempFileName.ReleaseBuffer();
   //   ACPToUnicode(
   //      pTempFileName,

   //      MAX_PATH,
   //      strTempFileName);
   //   return user;
   //}


   //HANDLE shell::_CreateFile(
   //   const unichar * pFileName,

   //   unsigned int dwDesiredAccess,
   //   unsigned int dwShareMode,
   //   LPSECURITY_ATTRIBUTES pSecurityAttributes,

   //   unsigned int dwCreationDisposition,
   //   unsigned int dwFlagsAndAttributes,
   //   HANDLE hTemplateFile
   //   )
   //{
   //   string strFileName;
   //   UnicodeToACP(strFileName, pFileName);

   //   HANDLE handle = ::CreateFileA(
   //      strFileName,
   //      dwDesiredAccess,
   //      dwShareMode,
   //      pSecurityAttributes,

   //      dwCreationDisposition,
   //      dwFlagsAndAttributes,
   //      hTemplateFile);
   //   return handle;
   //}


   //unsigned int shell::_GetModuleFileName(
   //   HMODULE hModule,
   //   unichar * pFilename,

   //   unsigned int nSize
   //   )
   //{
   //   string str;
   //   unsigned int dw = ::GetModuleFileNameA(hModule, str.GetBuffer(nSize * 2), nSize * 2);
   //   str.ReleaseBuffer();
   //   ACPToUnicode(pFilename, nSize, str);

   //   return dw;
   //}

   //BOOL shell::_GetClassInfo(HINSTANCE hInstance , const unichar * pClassName, LPWNDCLASSW puserinteractionclass)

   //{
   //   WNDCLASS wndclass;

   //   string strClassName;
   //   const scoped_string & strClassName;

   //   if(((unsigned int) pClassName) >> 16 == 0)

   //   {
   //      pszClassName = (const ::string &) lpClassName;

   //   }
   //   else
   //   {
   //      strClassName = pClassName;

   //      pszClassName = strClassName;

   //   }
   //   if(!::GetClassInfoA(hInstance, pszClassName, &wndclass))

   //      return false;

   //   puserinteractionclass->style = wndclass.style;

   //   puserinteractionclass->lpfnWndProc = wndclass.lpfnWndProc;

   //   puserinteractionclass->lpfnWndProc = wndclass.lpfnWndProc;

   //   puserinteractionclass->cbClsExtra = wndclass.cbClsExtra;

   //   puserinteractionclass->cbWndExtra = wndclass.cbWndExtra;

   //   puserinteractionclass->hInstance = wndclass.hInstance;

   //   puserinteractionclass->hIcon = wndclass.hIcon;

   //   puserinteractionclass->hCursor = wndclass.hCursor;

   //   puserinteractionclass->hbrBackground = wndclass.hbrBackground;


   //   /*   if(((unsigned int) wndclass) >> 16 == 0)
   //   {
   //   pszClassName = (const ::string &) lpClassName;

   //   }
   //   else
   //   {
   //   strClassName = pClassName;

   //   pszClassName = strClassName

   //   }
   //   string strMenuName;*/
   //   //strMenuName = wndclass->pszMenuName;

   //   puserinteractionclass->pszMenuName = (const unichar *) wndclass.pszMenuName;


   //   puserinteractionclass->pszClassName = (const unichar *) wndclass.pszClassName;


   //   return true;

   //}
   //ATOM shell::_RegisterClass(
   //   const WNDCLASSW *puserinteractionclass)

   //{
   //   WNDCLASS wndclass;

   //   wndclass.style = puserinteractionclass->style;

   //   wndclass.pfnWndProc = puserinteractionclass->lpfnWndProc;

   //   wndclass.pfnWndProc = puserinteractionclass->lpfnWndProc;

   //   wndclass.cbClsExtra = puserinteractionclass->cbClsExtra;

   //   wndclass.cbWndExtra = puserinteractionclass->cbWndExtra;

   //   wndclass.hInstance = puserinteractionclass->hInstance;

   //   wndclass.hIcon = puserinteractionclass->hIcon;

   //   wndclass.hCursor = puserinteractionclass->hCursor;

   //   wndclass.hbrBackground = puserinteractionclass->hbrBackground;


   //   string strMenuName;
   //   strMenuName = puserinteractionclass->pszMenuName;

   //   wndclass.pszMenuName = strMenuName;


   //   string strClassName;
   //   strClassName = puserinteractionclass->pszClassName;

   //   wndclass.pszClassName = strClassName;


   //   return ::RegisterClassA(&wndclass);
   //}


   //oswindow shell::_CreateWindowEx(
   //   unsigned int dwExStyle,
   //   const unichar * pClassName,

   //   const unichar * pWindowName,

   //   unsigned int dwStyle,
   //   int x,
   //   int y,
   //   int nWidth,
   //   int nHeight,
   //   oswindow oswindow_Parent,
   //   HMENU hMenu,
   //   HINSTANCE hInstance,
   //   LPVOID pParam)

   //{
   //   string strClassName;
   //   const scoped_string & strClassName;

   //   if(((unsigned int) pClassName) >> 16 == 0)

   //   {
   //      pszClassName = (const ::string &) lpClassName;

   //   }
   //   else
   //   {
   //      strClassName = pClassName;

   //      pszClassName = strClassName;

   //   }

   //   string strWindowName;
   //   strWindowName = pWindowName;


   //   return ::CreateWindowExA(
   //      dwExStyle,
   //      pszClassName,

   //      strWindowName,
   //      dwStyle,
   //      x,
   //      y,
   //      nWidth,
   //      nHeight,
   //      oswindow_Parent,
   //      hMenu,
   //      hInstance,
   //      pParam);


   //}
   //*/

} // namespace windows


