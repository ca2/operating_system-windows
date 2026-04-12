#pragma once

//
//#define WH_SHSTDAPI(type) type
//
//
//namespace windows
//{
//
//
//   class CLASS_DECL_ACME shell  
//   {
//   public:
//
//
//      static shell theWindowsShell;
//
//
//      shell();
//      virtual ~shell();
//
//
//      static bool Initialize();
///*      static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//      static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      static BOOL WINAPI _MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      static unsigned int WINAPI _GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      static BOOL WINAPI _GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         unsigned int nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         unsigned int nFileSystemNameSize);         // length of file system name buffer
//      static uptr __stdcall _SHGetFileInfo(
//         const unichar * pszPath,
//         unsigned int dwFileAttributes,
//         SHFILEINFOW *psfi,
//         unsigned int cbFileInfo,
//         unsigned int uFlags);
//      static BOOL __stdcall _GetStringTypeEx(
//         LCID Locale,
//         unsigned int dwInfoType,
//         const unichar * pSrcStr,
//
//         int cchSrc,
//         LPWORD pCharType);
//
//      static unsigned int WINAPI  _GetTempPath(
//         unsigned int nBufferLength,
//         unichar * pBuffer);
//
//      static unsigned int WINAPI _GetTempFileName(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         unsigned int uUnique,
//         unichar * pTempFileName);
//
//      static HANDLE WINAPI _CreateFile(
//         const unichar * pFileName,
//
//         unsigned int dwDesiredAccess,
//         unsigned int dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         unsigned int dwCreationDisposition,
//         unsigned int dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//      static unsigned int WINAPI _GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         unsigned int nSize
//         );
//      static BOOL WINAPI _GetClassInfo(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW puserinteractionclass);
//
//      static ATOM WINAPI _RegisterClass(
//         const WNDCLASSW *puserinteractionclass);
//
//
//      static oswindow WINAPI _CreateWindowEx(
//         unsigned int dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         unsigned int dwStyle,
//         int x,
//         int y,
//         int nWidth,
//         int nHeight,
//         ::windowing::window * pwindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);*/
//
//
//      BOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
//      HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      BOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      BOOL (WINAPI * m_pfnMoveFile)(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      unsigned int (WINAPI * m_pfnGetFullPathName)(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      BOOL (WINAPI * m_pfnGetVolumeInformation)(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         unsigned int nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         unsigned int nFileSystemNameSize);         // length of file system name buffer
//
//      DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
//         const unichar * pszPath,
//         unsigned int dwFileAttributes,
//         SHFILEINFOW *psfi,
//         unsigned int cbFileInfo,
//         unsigned int uFlags);
//      BOOL (__stdcall * m_pfnGetStringTypeEx)(
//         LCID Locale,
//         unsigned int dwInfoType,
//         const unichar * pSrcStr,
//
//         int cchSrc,
//         LPWORD pCharType);
//
//      unsigned int (WINAPI * m_pfnGetTempPath)(
//         unsigned int nBufferLength,
//         unichar * pBuffer);
//
//      unsigned int (WINAPI * m_pfnGetTempFileName)(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         unsigned int uUnique,
//         unichar * pTempFileName);
//
//      HANDLE (WINAPI * m_pfnCreateFile)(
//         const unichar * pFileName,
//
//         unsigned int dwDesiredAccess,
//         unsigned int dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         unsigned int dwCreationDisposition,
//         unsigned int dwFlagsAndAttributes,
//         HANDLE hTemplateFile
//         );
//
//      unsigned int (WINAPI * m_pfnGetModuleFileName)(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         unsigned int nSize
//         );
//
//      BOOL (WINAPI * m_pfnGetClassInfo)(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW puserinteractionclass);
//
//
//      ATOM (WINAPI * m_pfnRegisterClass)(
//         const WNDCLASSW *puserinteractionclass);
//
//
//      oswindow (WINAPI * m_pfnCreateWindowEx)(
//         unsigned int dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         unsigned int dwStyle,
//         int x,
//         int y,
//         int nWidth,
//         int nHeight,
//         ::windowing::window * pwindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);
//
//      static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
//      static bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
//      static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata);
//
//      static bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata);
//
//      static bool MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName);
//
//      static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
//      static unsigned int GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
//
//      static bool GetVolumeInformation(
//         const unichar * pRootPathName,           // root directory
//
//         unichar * pVolumeNameBuffer,        // volume name buffer
//
//         unsigned int nVolumeNameSize,            // length of name buffer
//         LPDWORD pVolumeSerialNumber,     // volume serial number
//
//         LPDWORD pMaximumComponentLength, // maximum file name length
//
//         LPDWORD pFileSystemFlags,        // file system options
//
//         unichar * pFileSystemNameBuffer,    // file system name buffer
//
//         unsigned int nFileSystemNameSize);         // length of file system name buffer
//
//      static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
//         const unichar * pszPath,
//         unsigned int dwFileAttributes,
//         SHFILEINFOW *psfi,
//         unsigned int cbFileInfo,
//         unsigned int uFlags);
//
//      static bool  GetStringTypeEx(      
//         LCID Locale,
//         unsigned int dwInfoType,
//         const char * pSrcStr,
//
//         int cchSrc,
//         LPWORD pCharType);
//
//
//      static unsigned int GetTempPathW(
//         unsigned int nBufferLength,
//         unichar * pBuffer);
//
//
//      static unsigned int GetTempFileNameW(
//         const unichar * pszPath,
//
//         const unichar * pszPrefix,
//
//         unsigned int uUnique,
//         unichar * pTempFileName);
//
//
//      static HANDLE CreateFile(
//         const unichar * pFileName,
//
//         unsigned int dwDesiredAccess,
//         unsigned int dwShareMode,
//         LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//         unsigned int dwCreationDisposition,
//         unsigned int dwFlagsAndAttributes,
//         HANDLE hTemplateFile);
//
//      static unsigned int WINAPI GetModuleFileName(
//         HMODULE hModule,
//         unichar * pFilename,
//
//         unsigned int nSize
//         );
//
//      static bool WINAPI GetClassInfo(
//         HINSTANCE hInstance ,
//         const unichar * pClassName,
//
//         LPWNDCLASSW puserinteractionclass);
//
//
//      static ATOM WINAPI RegisterClass(
//         const WNDCLASSW *puserinteractionclass);
//
//
//      static oswindow WINAPI CreateWindowEx(
//         unsigned int dwExStyle,
//         const unichar * pClassName,
//
//         const unichar * pWindowName,
//
//         unsigned int dwStyle,
//         int x,
//         int y,
//         int nWidth,
//         int nHeight,
//         ::windowing::window * pwindow_Parent,
//         HMENU hMenu,
//         HINSTANCE hInstance,
//         LPVOID pParam);
//
//
//
//      static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
//         const scoped_string & strPath,
//         unsigned int dwFileAttributes,
//         SHFILEINFO *psfi,
//         unsigned int cbFileInfo,
//         unsigned int uFlags);
//
//      static unsigned int GetTempPath(string & str);
//
//      static unsigned int GetTempFileName(
//         const scoped_string & strPath,
//
//         const scoped_string & strPrefix,
//
//         unsigned int uUnique,
//         string & str);
//
//      static bool MoveFile(const char * pExistingFileName, const char * lpNewFileName);
//
//
//   };
//
//   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
//   {
//      unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//      if(!(*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
//      {
//         free(pwszPath);
//         return false;
//      }
//      unicode_to_utf8(str, pwszPath);
//      free(pwszPath);
//      return true;
//   }
//
//
//   inline bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
//   {
//      return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath) != false;
//   }
//
//   inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * pdata)
//
//   {
//      return (*theWindowsShell.m_pfnFindFirstFile)(pcsz, pdata);
//
//   }
//
//   inline bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * pdata)
//
//   {
//      return (*theWindowsShell.m_pfnFindNextFile)(handle, pdata) != false;
//
//   }
//
//   inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
//   {
//      return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
//   }
//
//   inline unsigned int shell::GetFullPathName(const unichar * pFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
//
//   {
//      return (*theWindowsShell.m_pfnGetFullPathName)(pFileName, nBufferLength, lpBuffer, lpFilePart);
//
//   }
//
//
//   inline bool shell::MoveFile(const unichar * pExistingFileName, const unichar * lpNewFileName)
//
//   {
//      return (*theWindowsShell.m_pfnMoveFile)(pExistingFileName, lpNewFileName) != false;
//
//   }
//
//   inline bool shell::GetVolumeInformation(
//      const unichar * pRootPathName,           // root directory
//
//      unichar * pVolumeNameBuffer,        // volume name buffer
//
//      unsigned int nVolumeNameSize,            // length of name buffer
//      LPDWORD pVolumeSerialNumber,     // volume serial number
//
//      LPDWORD pMaximumComponentLength, // maximum file name length
//
//      LPDWORD pFileSystemFlags,        // file system options
//
//      unichar * pFileSystemNameBuffer,    // file system name buffer
//
//      unsigned int nFileSystemNameSize)         // length of file system name buffer
//   {
//      return (*theWindowsShell.m_pfnGetVolumeInformation)(
//         pRootPathName,           // root directory
//
//         pVolumeNameBuffer,        // volume name buffer
//
//         nVolumeNameSize,            // length of name buffer
//         pVolumeSerialNumber,     // volume serial number
//
//         pMaximumComponentLength, // maximum file name length
//
//         pFileSystemFlags,        // file system options
//
//         pFileSystemNameBuffer,    // file system name buffer
//
//         nFileSystemNameSize) != false;         // length of file system name buffer
//   }
//
//   inline unsigned int shell::SHGetFileInfo(
//      const unichar * pszPath,
//      unsigned int dwFileAttributes,
//      SHFILEINFOW *psfi,
//      unsigned int cbFileInfo,
//      unsigned int uFlags)
//   {
//      return (unsigned int) (*theWindowsShell.m_pfnSHGetFileInfo)(
//         pszPath,
//         dwFileAttributes,
//         psfi,
//         cbFileInfo,
//         uFlags);
//   }
//
//   inline unsigned int shell::GetTempPathW(
//      unsigned int nBufferLength,
//      unichar * pBuffer)
//
//   {
//      return (*theWindowsShell.m_pfnGetTempPath)(
//         nBufferLength,
//         pBuffer);
//
//   }
//
//   inline unsigned int shell::GetTempFileNameW(
//      const unichar * pszPath,
//
//      const unichar * pszPrefix,
//
//      unsigned int uUnique,
//      unichar * pTempFileName)
//
//   {
//      return (*theWindowsShell.m_pfnGetTempFileName)(
//         pszPath,
//
//         pszPrefix,
//
//         uUnique,
//         pTempFileName);
//
//   }
//
//   inline HANDLE shell::CreateFile(
//      const unichar * pFileName,
//
//      unsigned int dwDesiredAccess,
//      unsigned int dwShareMode,
//      LPSECURITY_ATTRIBUTES pSecurityAttributes,
//
//      unsigned int dwCreationDisposition,
//      unsigned int dwFlagsAndAttributes,
//      HANDLE hTemplateFile)
//   {
//      return (*theWindowsShell.m_pfnCreateFile)(
//         pFileName,
//
//         dwDesiredAccess,
//         dwShareMode,
//         pSecurityAttributes,
//
//         dwCreationDisposition,
//         dwFlagsAndAttributes,
//         hTemplateFile);
//   }
//
//   inline unsigned int shell::GetModuleFileName(
//      HMODULE hModule,
//      unichar * pFilename,
//
//      unsigned int nSize
//      )
//   {
//      return (*theWindowsShell.m_pfnGetModuleFileName)(
//         hModule,
//         pFilename,
//
//         nSize);
//   }
//
//   inline bool shell::GetClassInfo(
//      HINSTANCE hInstance ,
//      const unichar * pClassName,
//
//      LPWNDCLASSW puserinteractionclass)
//
//   {
//      return (*theWindowsShell.m_pfnGetClassInfo)(hInstance, pClassName, puserinteractionclass) != false;
//
//   }
//
//   inline ATOM shell::RegisterClass(
//      const WNDCLASSW *puserinteractionclass)
//
//   {
//      return (*theWindowsShell.m_pfnRegisterClass)(
//         puserinteractionclass);
//
//   }
//
//   inline oswindow shell::CreateWindowEx(
//      unsigned int dwExStyle,
//      const unichar * pClassName,
//
//      const unichar * pWindowName,
//
//      unsigned int dwStyle,
//      int x,
//      int y,
//      int nWidth,
//      int nHeight,
//      ::windowing::window * pwindow_Parent,
//      HMENU hMenu,
//      HINSTANCE hInstance,
//      LPVOID pParam)
//
//   {
//      return (*theWindowsShell.m_pfnCreateWindowEx)(
//         dwExStyle,
//         pClassName,
//
//         pWindowName,
//
//         dwStyle,
//         x,
//         y,
//         nWidth,
//         nHeight,
//         oswindow_Parent,
//         hMenu,
//         hInstance,
//         pParam);
//
//
//   }
//
//   inline unsigned int shell::GetTempPath(string & str)
//   {
//      unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
//      unsigned int dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
//      unicode_to_utf8(str, pwsz);
//      free(pwsz);
//      return dwResult;
//   }
//
//   inline unsigned int shell::GetTempFileName(const scoped_string & strPath, const scoped_string & strPrefix, unsigned int uUnique, string & str)
//
//   {
//      wstring wstrPathName = utf8_to_unicode(pszPath);
//
//      wstring wstrPrefixString = utf8_to_unicode(pszPrefix);
//
//      wstring wstr;
//      wstr.get_buffer(MAX_PATH * 4);
//      unsigned int uResult = (*theWindowsShell.m_pfnGetTempFileName)(wstrPathName, wstrPrefixString, uUnique, wstr);
//      unicode_to_utf8(str, wstr);
//      return uiResult;
//   }
//
//   inline bool shell::MoveFile(const char * pExistingFileName, const char * lpNewFileName)
//
//   {
//      return MoveFile(utf8_to_unicode(pExistingFileName), utf8_to_unicode(lpNewFileName));
//
//   }
//
//
//} // namespace windows




