#include "framework.h"
#include "acme/operating_system.h"
#include "acme/os/windows_common/_file_c.h"
#include <stdio.h>
#include <share.h>
#include <io.h>
#include <fcntl.h>




int_bool read_resource_as_file(const scoped_string & strFile, HINSTANCE hinstance, DWORD nID, LPCTSTR pcszType)

{

   HRSRC hrsrc = FindResource(hinstance, MAKEINTRESOURCE(nID), pcszType);

   HGLOBAL hglobalResource;
   unsigned int dwResourseSize;
   int_bool bOk;
   DWORD * pResource;
   FILE * file;

   if(hrsrc == nullptr)
      return false;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if(hglobalResource == nullptr)
      return false;

   dwResourseSize = SizeofResource(hinstance, hrsrc);

   if(hglobalResource != nullptr)
   {

      bOk = false;

      pResource = (DWORD *) LockResource(hglobalResource);

         auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;


               auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->create(::file_path_folder(pszFile));

      file = FILE_open(pszFile, "wb", _SH_DENYNO);

      if(file != nullptr)
      {

         auto dwWritten = FILE_write(pResource, 1, dwResourseSize, file);

         FILE_close(file);

         bOk = dwWritten == dwResourseSize;

      }

      return bOk;

   }

   return false;

}


int_bool file_system()->exists(const char * path1)
{

   unsigned int dwFileAttributes = windows_get_file_attributes(path1);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
   {

      return false;

   }

   return true;

}


int_bool file_system()->put_contents(const char * path, const char * contents, memsize len)
{

            auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->create(::file_path_folder(path));

   wstring wstr(path);

   FILE * file = FILE_open(path, "w", _SH_DENYWR);

   if (file == nullptr)
   {

      return false;

   }

   count dwWrite;

   if(len < 0)
      dwWrite = ansi_length(contents);
   else
      dwWrite = len;

   auto dwWritten = fwrite(contents, 1, (unsigned int) dwWrite, file);

   int_bool bOk = dwWritten == dwWrite;

   fclose(file);

   return dwWrite == dwWritten && bOk != false;

}


filesize file_length_dup(const char * path)
{

   HANDLE hfile = CreateFileW(wstring(path), GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   DWORD dwHi = 0;

   huge_natural u = GetFileSize(hfile, &dwHi);

   u |= ((huge_natural)dwHi) << 32ULL;

   CloseHandle(hfile);

   return u;

}


int_bool file_is_equal_path_dup(const scoped_string & str1, const scoped_string & str2)
{

   const int iBufSize = MAX_PATH * 8;

   wstring pwsz1 = utf8_to_unicode(psz1);

   wstring pwsz2 = utf8_to_unicode(psz2);

   unichar * pwszFile1;

   unichar * pwszFile2;

   unichar * pwszPath1 = ___new unichar[iBufSize];

   unichar * pwszPath2 = ___new unichar[iBufSize];

   int iCmp = -1;
   
   if(GetFullPathNameW(pwsz1, iBufSize, pwszPath1, &pwszFile1))
   {
      
      if(GetFullPathNameW(pwsz2, iBufSize, pwszPath2, &pwszFile2))
      {
         
         string path1 = unicode_to_utf8(pwszPath1);
         
         string path2 = unicode_to_utf8(pwszPath2);
         
         iCmp = ansi_compare_ci(path1, path2);

      }

   }

   delete pwszPath1;

   delete pwszPath2;

   return iCmp == 0;

}







































//#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

struct PROCESS_INFO_t
{
   wstring csProcess;
   unsigned int dwImageListIndex;
};


//#if !defined(LINUX) && !defined(MACOS) && !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)
//
////#include <Tlhelp32.h>
////#include <Psapi.h>
//
//
////void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext );
////void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext, HANDLE hDriver, GetFinalPathNameByHandleDef pGetFinalPathNameByHandle );
//
//const const ::wide_character * DRV_DOS_NAME = L"\\\\.\\ListFileDrv";
//const const ::wide_character * DRV_NAME = L"ListOpenedFileDrv";
//const const ::wide_character * DRV_FILE_NAME = L"ListOpenedFileDrv.sys";
//
//#define DRIVER_FILE_NAME_32 L"\\ListOpenedFileDrv_32.sys"
//#define DRIVER_FILE_NAME_64 L"\\ListOpenedFileDrv_64.sys"
//
//
//// This Function install the driver and starts it
//HANDLE OnlyGetDrv()
//{
//
//
//   HMODULE hModule = GetModuleHandle(_T("acme.dll"));
//   if( !hModule )
//   {
//      output_debug_string( L"GetModuleHandle(_T(\"acme.dll\")); failed" );
//      return 0;
//   }
//   wstring csFilePath;
//   LPWSTR pPath = csFilePath.get_buffer( MAX_PATH );
//
//   GetModuleFileNameW( hModule,pPath, MAX_PATH );
//
//   LIBCALL(shlwapi,PathRemoveFileSpecW)(pPath);
//
//   csFilePath.release_buffer();
//   if(IsWow64())
//   {
//      csFilePath += DRIVER_FILE_NAME_64;
//   }
//   else
//   {
//      csFilePath += DRIVER_FILE_NAME_32;
//   }
//
//   if(!LIBCALL(shlwapi, PathFileExistsW)(csFilePath))
//   {
//      message_box(nullptr,"Cannot find driver " + string(csFilePath),"Cannot find driver " + string(csFilePath),e_message_box_ok);
//      return 0;
//   }
//
//
//
//   // Delete the temp file...
//   //DeleteFile( csPath );
//   HANDLE hFile = CreateFileW( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE,
//                              FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
//                              OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
//   return hFile;
//
//}
//
//
////extern "C" CLASS_DECL_ACME void GetOpenedFiles(const ::wide_character * pPath, OF_TYPE Filter, OF_CALLBACK CallBackProc, uptr pUserContext)
////
////{
////   string csPath = pPath;
////
////   csPath.make_lower();
////   EnableTokenPrivilege( SE_DEBUG_NAME );
////   if( Filter& MODULES_ONLY )
////   {
////      EnumerateLoadedModules( csPath, CallBackProc, pUserContext );
////   }
////
////   if( Filter& FILES_ONLY )
////   {
////
////
////      // Extract the driver from the resource and install it.
////      //HANDLE hDriver = ExtractAndInstallDrv();
////      //HANDLE hDriver = OnlyGetDrv();
////      HANDLE hDriver = nullptr;
////      GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = 0;
////      if(  !hDriver )
////      {
////         pGetFinalPathNameByHandle = (GetFinalPathNameByHandleDef)GetProcAddress( GetModuleHandle(_T("kernel32.dll")), "GetFinalPathNameByHandleW" );
////      }
////      // Now walk all handles
////      EnumerateOpenedFiles( csPath, CallBackProc, pUserContext, hDriver, pGetFinalPathNameByHandle );
////      //if( hDriver )
////      {
////         // Time to wind up
////         //StopAndUninstallDrv( hDriver );
////      }
////   }
////}
//
////#ifndef UNIVERSAL_WINDOWS
////
////typedef struct _SYSTEM_HANDLE_INFORMATION
////{
////   unsigned int         dwCount;
////   SYSTEM_HANDLE Handles[1];
////} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION, **PPSYSTEM_HANDLE_INFORMATION;
////
////typedef enum _SYSTEM_INFORMATION_CLASS2
////{
////   SystemHandleInformation = 0X10,
////} SYSTEM_INFORMATION_CLASS2;
////
////#endif
//
////typedef NTSTATUS ( WINAPI *PNtQuerySystemInformation)
////( IN SYSTEM_INFORMATION_CLASS2 SystemInformationClass,
////  OUT   PVOID              SystemInformation,
////  IN ULONG              SystemInformationLength,
////  OUT   PULONG                ReturnLength OPTIONAL );
//
////DWORD g_CurrentIndex = 0;
////struct THREAD_PARAMS
////{
////   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
////   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
////   LPWSTR pPath;
////
////   int nFileType;
////   HANDLE hStartEvent;
////   HANDLE hFinishedEvent;
////   bool bStatus;
////};
//
////DWORD WINAPI  ThreadProc(void * p)
////{
////
////   THREAD_PARAMS * pThreadParam = (THREAD_PARAMS *) p;
////
////   FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)___new unsigned char[MAX_PATH * 8];
////
////   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
////   for( g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;  )
////   {
////
////      WaitForSingleObject( pThreadParam->hStartEvent, U32_INFINITE_TIMEOUT );
////      ResetEvent( pThreadParam->hStartEvent );
////      pThreadParam->bStatus = false;
////      SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
////      g_CurrentIndex++;
////      HANDLE hDup = (HANDLE)sh.wValue;
////      HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE, false, sh.dwProcessId );
////      if( hProcess )
////      {
////         bool b = DuplicateHandle( hProcess, (HANDLE)sh.wValue, GetCurrentProcess(), &hDup, 0, false, DUPLICATE_SAME_ACCESS ) != false;
////         if( !b )
////         {
////            hDup = (HANDLE)sh.wValue;
////         }
////         CloseHandle( hProcess );
////      }
////      //unsigned int dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->pPath, MAX_PATH, 0 );
////
////      //unsigned int dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
////      unsigned int dwRet = GetFinalPathNameByHandleW( hDup, pThreadParam->pPath, MAX_PATH, 0 );
////
////      //wcsncpy(pThreadParam->pPath, pinfo->FileName, pinfo->FileNameLength);
////
////      if( hDup && (hDup != (HANDLE)sh.wValue))
////      {
////         CloseHandle( hDup );
////      }
////      if(dwRet)
////      {
////         pThreadParam->bStatus = true;
////      }
////      SetEvent( pThreadParam->hFinishedEvent );
////
////   }
////   delete[] (unsigned char *) pinfo;
////   return ::success;
////}
//
////void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext, HANDLE hDriver,
////                           GetFinalPathNameByHandleDef pGetFinalPathNameByHandle )
////{
////   int nFileType;
////
////   if(is_windows_vista_or_greater())
////   {
////      nFileType = VISTA_FILETYPE;
////   }
////   else
////   {
////      nFileType = XP_FILETYPE;
////   }
////
////   const char * pPath = csPath;
////
////   wstring csShortName;
////   GetShortPathNameW( wstring(csPath), csShortName.get_buffer( MAX_PATH), MAX_PATH );
////   csShortName.release_buffer();
////   string strShortName(csShortName);
////   strShortName.make_lower();
////   bool bShortPath = false;
////   const char * pShortPath = strShortName;
////
////   if(string( csShortName )!= csPath && false == csShortName.is_empty())
////   {
////      bShortPath = true;
////   }
////
////   HMODULE hModule = GetModuleHandleW(L"ntdll.dll");
////   PNtQuerySystemInformation NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress( hModule, "NtQuerySystemInformation" );
////   if( 0 == NtQuerySystemInformation )
////   {
////      output_debug_string( L"Getting proc of NtQuerySystemInformation failed" );
////      return;
////   }
////
////   // Get the list of all handles in the file_system
////   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = ___new SYSTEM_HANDLE_INFORMATION;
////   unsigned int size = sizeof(SYSTEM_HANDLE_INFORMATION);
////   DWORD needed = 0;
////   NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
////   if( !NT_SUCCESS(status))
////   {
////      if( 0 == needed )
////      {
////         return;// some other error
////      }
////      // The previously supplied buffer wasn't enough.
////      delete pSysHandleInformation;
////      size = needed + 1024;
////      pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)___new unsigned char[int_size];
////      status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
////      if( !NT_SUCCESS(status))
////      {
////         // some other error so quit.
////         delete pSysHandleInformation;
////         return;
////      }
////   }
////
////   if( pGetFinalPathNameByHandle )// there is no driver, we have do it ugly way
////   {
////      g_CurrentIndex = 0;
//////    TCHAR tcFileName[MAX_PATH+1];
////      THREAD_PARAMS ThreadParams;
////      wstring wstrFileName;
////
////      
////      ThreadParams.pPath = wstrFileName.get_buffer(MAX_PATH * 8);;
////
////      ThreadParams.nFileType = nFileType;
////      ThreadParams.pGetFinalPathNameByHandle = pGetFinalPathNameByHandle;
////      ThreadParams.pSysHandleInformation = pSysHandleInformation;
////      ThreadParams.hStartEvent = ::CreateEvent( 0, true, false, 0 );
////      ThreadParams.hFinishedEvent = ::CreateEvent( 0, true, false, 0 );
////      HANDLE ThreadHandle = 0;
////      while( g_CurrentIndex < pSysHandleInformation->dwCount )
////      {
////         if( !ThreadHandle )
////         {
////            ThreadHandle = CreateThread(NULL, 0, ThreadProc, &ThreadParams, 0, NULL);
////         }
////         ResetEvent( ThreadParams.hFinishedEvent );
////         SetEvent( ThreadParams.hStartEvent );
////         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadParams.hFinishedEvent, 100 ))
////         {
////            string csError;
////            csError.Format("Query hang for handle %d", (int)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue);
////            output_debug_string(csError );
////            TerminateThread( ThreadHandle, 0 );
////            CloseHandle( ThreadHandle );
////            ThreadHandle = 0;
////            continue;
////         }
////         if( !ThreadParams.bStatus )
////         {
////            continue;
////         }
////         int nCmpStart = 4;
////         string csFileName( unicode_to_utf8(&ThreadParams.pPath[nCmpStart]));
////
////         csFileName.make_lower();
////         if(csFileName.find("vs11_dp_ctp") >= 0)
////         {
////            continue;
////         }
////         else if( 0 != strcmp( pPath, csFileName))
////
////         {
////            continue;
////         }
////         OF_INFO_t stOFInfo;
////         stOFInfo.dwPID = pSysHandleInformation->Handles[g_CurrentIndex - 1].dwProcessId;
////         wstring wstrCallback;
////         wstrCallback = utf8_to_unicode(csFileName);
////         stOFInfo.pFile = wstrCallback;
////
////         stOFInfo.hFile  = (HANDLE)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue;
////         CallBackProc( stOFInfo, pUserContext );
////      }
////      if( ThreadHandle )
////      {
////         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadHandle, 1000 ))
////         {
////            TerminateThread( ThreadHandle, 0 );
////         }
////         CloseHandle( ThreadHandle );
////      }
////      CloseHandle( ThreadParams.hStartEvent );
////      CloseHandle( ThreadParams.hFinishedEvent );
////      return;
////   }
////
////   // Walk through the handle list
////   for ( unsigned int i = 0; i < pSysHandleInformation->dwCount; i++ )
////   {
////      SYSTEM_HANDLE& sh = pSysHandleInformation->Handles[i];
////      if( sh.bObjectType != nFileType )// Under windows XP file handle is of type 28
////      {
////         continue;
////      }
////
////      string csFileName;
////      string csDir;
////      if( hDriver )
////      {
////         HANDLE_INFO stHandle = {0};
////         ADDRESS_INFO stAddress;
////         stAddress.pAddress = sh.pAddress;
////         DWORD dwReturn = 0;
////         bool bSuccess = DeviceIoControl( hDriver, IOCTL_LISTDRV_BUFFERED_IO, &stAddress, sizeof(ADDRESS_INFO), &stHandle, sizeof(HANDLE_INFO), &dwReturn, nullptr ) != false;
////
////
////         if( bSuccess && stHandle.tcFileName[0] != 0 &&
////               stHandle.uType != FILE_DEVICE_SOUND &&
////               stHandle.uType != FILE_DEVICE_NAMED_PIPE )
////         {
////
////            if( stHandle.uType != FILE_DEVICE_NETWORK_FILE_SYSTEM  )
////            {
////               // Get the drive name from the dos device name
////               if( !GetDrive(string(stHandle.tcDeviceName), csFileName, true ))
////               {
////                  output_debug_string( "GetDrive failed" );
////               }
////               csFileName += stHandle.tcFileName;
////            }
////            else
////            {
////               csFileName = "\\";
////               csFileName += stHandle.tcFileName;
////            }
////         }
////         else
////         {
////            continue;
////         }
////      }
////      else
////      {
////         return;
////      }
////
////
////      csFileName.make_lower();
////      // Check whether the file belongs to the specified folder
//////       if( -1 == csFileName.Find( csPath ))
//////       {
//////          if( bShortPath )
//////          {
//////             // Some times the file name may be in short path form.
//////             if( -1 == csFileName.Find( csShortName ))
//////             {
//////                continue;
//////             }
//////          }
//////          else
//////          {
//////             continue;
//////          }
//////       }
////
////      if( 0 != strcmp( pPath, csFileName))
////
////      {
////         if( bShortPath )
////         {
////            // Some times the file name may be in short path form.
////            if( 0 != strcmp( pShortPath, csFileName))
////
////            {
////               continue;
////            }
////         }
////         else
////         {
////            continue;
////         }
////      }
////      OF_INFO_t stOFInfo;
////      stOFInfo.dwPID = sh.dwProcessId;
////      wstring wstrCallback;
////      wstrCallback = utf8_to_unicode(csFileName);
////      stOFInfo.pFile = wstrCallback;
////
////      stOFInfo.hFile  = (HANDLE)sh.wValue;
////      CallBackProc( stOFInfo, pUserContext );
////   }
////   delete pSysHandleInformation;
////
////}
//
//
////void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uptr pUserContext )
////{
////   wstring csShortName;
////   GetShortPathNameW(wstring( csPath), csShortName.get_buffer( MAX_PATH), MAX_PATH );
////   csShortName.release_buffer();
////   string strShortName(csShortName);
////   strShortName.make_lower();
////   bool bShortPath = false;
////   if(csPath !=  string(csShortName) && !csShortName.is_empty())
////   {
////      bShortPath = true;
////   }
////
////   unsigned int dwsize = 300;
////   PDWORD pDwId = (PDWORD)___new unsigned char[dwsize];
////   DWORD dwReturned = dwsize;
////   // Enum all the process first
////   while( 1 )
////   {
////      EnumProcesses( pDwId, dwsize, &dwReturned );
////      if( dwsize > dwReturned  )
////      {
////         break;
////      }
////      delete pDwId;
////      dwsize += 50;
////      pDwId = (PDWORD)___new unsigned char[dwsize];
////   }
////   int nCount = dwReturned / sizeof(unsigned int);
////   int nItemCount = -1;
////   // Enumerate modules of the above process
////   for( int nIdx = 0; nIdx < nCount; nIdx++ )
////   {
////      if( 0 != pDwId[nIdx] )
////      {
////         HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
////         MODULEENTRY32W me32;
////         // Take a snapshot of all modules in the specified process.
////         hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pDwId[nIdx] );
////         if( hModuleSnap == INVALID_HANDLE_VALUE )
////         {
////            continue;
////         }
////         me32.dwSize = sizeof( MODULEENTRY32W );
////         if( !Module32FirstW( hModuleSnap, &me32 ) )
////         {
////            CloseHandle( hModuleSnap );
////            continue;
////         }
////         bool bFirst = true;
////         PROCESS_INFO_t stInfo;
////         do
////         {
////            string csModule;
////            if( bFirst )
////            {
////               // First module is always the exe name
////               bFirst = false;
////               if(!LIBCALL(shlwapi,PathFileExistsW)(me32.szExePath))
////               {
////                  WCHAR tcFileName[MAX_PATH];
////                  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, true, pDwId[nIdx] );
////                  if( GetProcessImageFileNameW( hProcess, tcFileName, MAX_PATH ))
////                  {
////                     GetDrive( string(tcFileName), csModule, false );
////                  }
////                  CloseHandle( hProcess );
////               }
////               else
////               {
////                  csModule = me32.szExePath;
////               }
////               csModule.make_lower();
////            }
////            else
////            {
////               csModule = me32.szExePath;
////               csModule.make_lower();
////            }
////            if( -1 == csModule.find( csPath ))
////            {
////               if( bShortPath )
////               {
////                  if( -1 == csModule.find( string(csShortName)))
////                  {
////                     continue;
////                  }
////               }
////               else
////               {
////                  continue;
////               }
////            }
////            OF_INFO_t stOFInfo;
////            stOFInfo.dwPID = pDwId[nIdx];
////            wstring wstrCallback;
////
////            wstrCallback = utf8_to_unicode(csModule);
////
////            stOFInfo.pFile = wstrCallback;
////
////            CallBackProc( stOFInfo, pUserContext );
////         }
////         while( Module32NextW( hModuleSnap, &me32 ) );
////         CloseHandle( hModuleSnap );
////      }
////   }
////
////   delete pDwId;
////
////}
////
////
////
////#endif // LINUX
//




int ftruncate(int file, filesize len)
{
   return _chsize_s (file, len);
}





int_bool ensure_file_size_fd(int fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return 0;

   return 1;

}

int_bool FILE_set_size(FILE * file, size_t iSize)
{

   return ensure_file_size_fd(_fileno(file), iSize);

}

































int_bool file_set_length(const char * lpszName, size_t iSize)
{

   wstring wstr(lpszName);

   HANDLE h = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

   if(h == INVALID_HANDLE_VALUE)
      return false;

   if(!ensure_file_size_handle(h, iSize))
   {

      ::CloseHandle(h);

      return false;

   }

   ::CloseHandle(h);

   return true;

}


int_bool file_move(const scoped_string & strNewName, const scoped_string & strOldName)
{

   wstring wstrOldName(pszOldName);

   wstring wstrNewName(pszNewName);

   if (!::MoveFileW(wstrOldName, wstrNewName))
   {

      return false;

   }

   return true;

}


int_bool file_delete(const scoped_string & strFileName)
{

   wstring wstrFileName(pszFileName);

   if (!::DeleteFileW(wstrFileName))
   {

      return false;

   }

   return true;

}



char get_drive_letter(const char * pDevicePath)
{

   wchar_t d = 'A';

   while(d <= L'Z')
   {

      wchar_t szDeviceName[3] = {d,L':',L'\0'};

      wchar_t szTarget[512] = {0};

      if (QueryDosDeviceW(szDeviceName, szTarget, 511) != 0)
      {

         if (wcscmp(wstring(pDevicePath), szTarget) == 0)
         {

            return (char)d;

         }

      }

      d++;
   
   }

   return '\0';

}


memory file_as_memory(const char * path, memsize iReadAtMostByteCount)
{

   memory mem;

   if (iReadAtMostByteCount < 0)
   {

      file_as_memory(mem, path);

   }
   else
   {

      mem.set_size(iReadAtMostByteCount);

      memsize iRead = file_as_memory(path, mem.get_data(), mem.get_size());

      mem.set_size(iRead);

   }

   return mem;

}



//#include "framework.h"
//#include <Winsvc.h>

//const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
//const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
//const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

// Function resolves the fosedevice name to drive name
bool GetDrive(const scoped_string & strDosName, string& csDrive, bool bDriveLetterOnly)
{
   WCHAR tcDeviceName[50];
   WCHAR tcDrive[3] = L"A:";

   wstring wstrDosName(pszDosName);

   // Iterating through the drive letters
   for (WCHAR actDrive = L'A'; actDrive <= L'Z'; actDrive++)
   {
      tcDrive[0] = actDrive;
      // Query the device for the drive letter
      if (QueryDosDeviceW(tcDrive, tcDeviceName, 50) != 0)
      {
         // Is this the drive letter we are looking for?
         if (wcsnicmp(tcDeviceName, wstrDosName, wcslen(tcDeviceName)) == 0)
         {
            if (bDriveLetterOnly)
            {
               csDrive = tcDrive;
            }
            else
            {
               csDrive = pszDosName;
               csDrive.replace(string(tcDeviceName), string(tcDrive));
            }
            return true;
         }
      }
   }
   return false;
}

//#ifdef _M_IX86
//#define DRVIER_ID IDR_XPDRIVER32
//#else
//#define DRVIER_ID IDR_XPDRIVER64
//#endif

//#ifdef _M_IX86
//#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
//#else
//#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")
//#endif

// This Function install the driver and starts it
//HANDLE ExtractAndInstallDrv()
//{
//   SC_HANDLE hSCManager = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
//   SC_HANDLE hService = OpenServiceW(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
//   string csPath;
//   if (0 == hService)
//   {
//      //Service not installed. So install the service.
//
//      /*OSVERSIONINFO info = { 0 };
//      info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//      GetVersionEx(&info);
//      int nDriverId = IDR_VISTA_DRIVER;
//      if( info.dwMajorVersion == 5 )
//      {
//      nDriverId = IDR_XPDRIVER;
//      }*/
//
//
//      /*// First extract the resource
//      HINSTANCE hModule= __get_instance_handle();
//      HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(DRVIER_ID),_T("BINARY"));
//      HGLOBAL hDrvRsrc = LoadResource(hModule, hRsrc);
//      unsigned int dwDriverSize = SizeofResource(hModule, hRsrc);
//      LPVOID pvDriver = LockResource(hDrvRsrc);
//
//      CFile File;
//      if( !File.Open( DRV_FILE_NAME, CFile::modeCreate|CFile::modeWrite ))
//      {
//      return 0;
//      }
//      File.Write( pvDriver, dwDriverSize );
//
//      csPath = File.GetFilePath();
//      File.Close();*/
//
//
//      HMODULE hModule = GetModuleHandle(_T("acme.dll"));
//      if (!hModule)
//      {
//         output_debug_string(L"GetModuleHandle(_T(\"acme.dll\")); failed");
//         return 0;
//      }
//      wstring csFilePath;
//      LPWSTR pPath = csFilePath.get_buffer(MAX_PATH);
//
//      GetModuleFileNameW(hModule, pPath, MAX_PATH);
//
//      LIBCALL(shlwapi, PathRemoveFileSpecW)(pPath);
//
//      csFilePath.release_buffer();
//      if (IsWow64())
//      {
//         csFilePath += DRIVER_FILE_NAME_64;
//      }
//      else
//      {
//         csFilePath += DRIVER_FILE_NAME_32;
//      }
//
//      if (!LIBCALL(shlwapi, PathFileExistsW)(csFilePath))
//      {
//         message_box(nullptr, "Cannot find driver " + string(csFilePath), "Cannot find driver " + string(csFilePath), e_message_box_ok);
//         return 0;
//      }
//
//
//
//      hService = CreateServiceW(hSCManager, DRV_NAME, DRV_NAME, SERVICE_ALL_ACCESS,
//                               SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
//                               csFilePath, nullptr, nullptr, nullptr, nullptr, nullptr);
//
//      if (0 == hService)
//      {
//         output_debug_string(L"CreateService failed");
//         CloseServiceHandle(hSCManager);
//         return 0;
//      }
//   }
//
//   if (!StartService(hService, 0, nullptr))
//   {
//      unsigned int dwLastError = GetLastError();
//      if (dwLastError != ERROR_SERVICE_ALREADY_RUNNING)
//      {
//         DeleteService(hService);
//         CloseServiceHandle(hService);
//         CloseServiceHandle(hSCManager);
//         //DeleteFile( csPath );
//         output_debug_string(L"StartService failed");
//         return 0;
//      }
//
//   }
//   // Delete the temp file...
//   //DeleteFile( csPath );
//   HANDLE hFile = CreateFileW(DRV_DOS_NAME, GENERIC_READ | GENERIC_WRITE,
//                             FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
//                             OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
//   if (INVALID_HANDLE_VALUE == hFile)
//   {
//      hFile = 0;
//      SERVICE_STATUS  stSrvStatus = { 0 };
//      ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
//   }
//   CloseServiceHandle(hService);
//   CloseServiceHandle(hSCManager);
//   return hFile;
//}
//
//// Function stops the service and then deletes it.
//int_bool StopAndUninstallDrv(HANDLE hDrvHandle)
//{
//   CloseHandle(hDrvHandle);
//   SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
//   SC_HANDLE hService = OpenServiceW(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
//   SERVICE_STATUS  stSrvStatus = { 0 };
//   ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
//   int_bool bDeleted = DeleteService(hService);
//   CloseServiceHandle(hService);
//   CloseServiceHandle(hSCManager);
//   return bDeleted;
//}
//


















string get_volume_path(const scoped_string & str)
{
   WCHAR wsz[4096];
   if (!GetVolumePathNameW(utf8_to_unicode(psz), wsz, sizeof(wsz) / sizeof(wsz[0])))
   {
      return "";
   }
   return wsz;
}



namespace file
{

#ifdef WINDOWS


   //bool exception::get_error_message(string & str, unsigned int * pnHelpContext)
   //{

   //   // if (pnHelpContext != nullptr)
   //   //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

   //   string strMessage;

   //   string strFileName = m_path;

   //   if (strFileName.is_empty())
   //   {

   //      strFileName = "IDS_UNNAMED_FILE";

   //   }

   //   if (m_lOsError == ERROR_ACCESS_DENIED || m_lOsError == ERROR_SHARING_VIOLATION)
   //   {

   //      wstring wstr;

   //      wstr = utf8_to_unicode(m_path.name());

   //      // #ifdef WINDOWS_DESKTOP
   //      //          GetOpenedFiles(wstr, ALL_TYPES, &exception::CallBackFunc, (uptr)this);
   //      // #endif

   //      if (m_strAdd.has_character())
   //      {
   //         ((exception *)this)->m_strAdd = " Process Using the file = " + m_strAdd;
   //      }
   //      else
   //      {
   //         ((exception *)this)->m_strAdd = " Process Using the file Not Found ";
   //      }

   //   }


   //   string strExtra;

   //   strExtra = get_last_error_message(m_lOsError);

   //   strExtra += m_strAdd;

   //   strMessage.formatf("file error number: %d - %s - file: %s", m_estatus.m_estatus, strExtra.c_str(), strFileName.c_str());

   //   str = strMessage;

   //   return true;
   //}


#endif


} // namespace file






//
//
//int_bool file_exists_raw(const char * path1)
//{
//
//
//   unsigned int dwFileAttributes = GetFileAttributesA(path1);
//
//   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//
//}
