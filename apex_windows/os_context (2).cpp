#include "framework.h"
#include "apex/operating_system.h"
#include "acme/os/windows_common/_file_c.h"
#include "acme/os/windows_common/cotaskptr.h"
#include "acme/os/windows_common/file.h"
#include <wincred.h>
#include <wtsapi32.h>
#include <shobjidl.h>
#include "acme/constant/id.h"
#include "_node_windows_private.h"
#include "acme/os/windows/_windows.h"
#include <ShellApi.h>


void hresult_to_estatus(HRESULT hresult)
{

   if (SUCCEEDED(hresult))
   {

      return ::success;

   }
   else
   {

      return ::error_failed;

   }

}



CREDUIAPI
BOOL
WINAPI
CredPackAuthenticationBufferWfoo(
_In_ unsigned int                                      dwFlags,
_In_ LPWSTR                                     pszUserName,
_In_ LPWSTR                                     pszPassword,
_Out_writes_bytes_opt_(*pcbPackedCredentials) PBYTE   pPackedCredentials,
_Inout_ unsigned int*                                  pcbPackedCredentials
);


//#include <Wtsapi32.h>
//#include <Psapi.h>
//#include <WinCred.h>

CLASS_DECL_APEX_WINDOWS HBITMAP get_icon_hbitmap(HICON hICON);

namespace windows
{


   os_context::os_context()
   {
   }


   os_context::~os_context()
   {
   }


   string os_context::get_command_line()
   {

      return GetCommandLineW();

   }


   bool os_context::shutdown(bool bIfPowerOff)
   {
      bool retval = true;
      HANDLE hToken;
      TOKEN_PRIVILEGES tokenprivileges;
      if (!OpenProcessToken(GetCurrentProcess(),
                            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid);
      tokenprivileges.PrivilegeCount = 1;
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      if (bIfPowerOff)
         retval = ExitWindowsEx(EWX_POWEROFF, 0) != false;
      else
         retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != false;

      //reset the previlages
      tokenprivileges.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      return retval;
   }

   bool os_context::reboot()
   {
      HANDLE hToken;
      TOKEN_PRIVILEGES tokenprivileges;
      if (!OpenProcessToken(GetCurrentProcess(),
                            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      if(!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tokenprivileges.PrivilegeCount = 1;
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }
      if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tokenprivileges.PrivilegeCount = 1;
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }

      if(!LIBCALL(wtsapi32,WTSShutdownSystem)(WTS_CURRENT_SERVER_HANDLE,WTS_WSD_REBOOT))
      {
         TRACELASTERROR();
         return false;
      }
      /*if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
      SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      {
      unsigned int dwLastError = ::GetLastError();
      return false;
      }*/
      //reset the previlages
      tokenprivileges.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      return true;
   }

   void os_context::terminate_processes_by_title(const ::scoped_string & scopedstrName)
   {

      unsigned int uPid;

      while(get_pid_by_title(lpszName, uPid))
      {

         HANDLE hProcess = ::OpenProcess( PROCESS_QUERY_INFORMATION |
                                          PROCESS_VM_READ,
                                          false, uPid);
         TerminateProcess(hProcess, (unsigned int) -1);
         CloseHandle(hProcess);
         /*::EnumWindows((WNDENUMPROC)
         CKillProcessHelper::TerminateAppEnum,
         (LPARAM) dwId);
         // Wait on the handle. If it signals, great.

         //If it times out, then you kill it.

         if(WaitForSingleObject(hProcess, 5000)
         !=WAIT_OBJECT_0)
         bResult = TerminateProcess(hProcess,0);
         else
         bResult = true;
         CloseHandle(hProcess);
         return bResult == true;*/

      }
   }

   bool os_context::get_pid_by_path(const ::scoped_string & scopedstrName, unsigned int & dwPid)
   {
      unsigned_int_array dwa;
      get_all_processes(dwa);
      for(int i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).case_insensitive_order(lpszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   bool os_context::get_pid_by_title(const ::scoped_string & scopedstrName, unsigned int & dwPid)
   {
      unsigned_int_array dwa;
      get_all_processes(dwa);
      for(int i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).title().case_insensitive_order(lpszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }


   int os_context::get_pid()
   {

      return (int) ::get_current_process_id();

   }




   ::file::path os_context::get_process_path(unsigned int dwPid)
   {
      string strName = ":<unknown>";
      // get a handle to the process.
      HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                     PROCESS_VM_READ,
                                     false, dwPid );

      // get the process name.

      if (nullptr != hProcess )
      {
         
         HMODULE hMod;

         DWORD cbNeeded;

         if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
         {
            
            strName = ::path::module(hMod);

         }

      }

      CloseHandle( hProcess );

      return strName;

   }


   void os_context::get_all_processes(unsigned_int_array & ua)
   {

      ASSERT(sizeof(unsigned int) == sizeof(unsigned int));

      ua.allocate(0);

      DWORD cbNeeded = 0;

      while(cbNeeded == natural(ua.get_count()))
      {

         ua.allocate(ua.get_count() + 1024);

         if(!EnumProcesses((DWORD *) ua.get_data(), (DWORD) (ua.get_count() * sizeof(unsigned int)), &cbNeeded))
         {

            return;

         }

         ua.allocate(cbNeeded / sizeof(unsigned int));

      }

   }


   //::file::path os_context::get_module_path(HMODULE hmodule)
   //{
   //   
   //   wstring wstrPath;
   //   
   //   unsigned int dwSize = 1;

   //   while(natural(wstrPath.get_length() + 1) == dwSize)
   //   {

   //      dwSize = ::GetModuleFileNameW(
   //               hmodule,
   //               wstrPath.get_buffer(dwSize + 1024),
   //               (dwSize + 1024));

   //      wstrPath.release_buffer();

   //   }

   //   return unicode_to_utf8(wstrPath);

   //}


   ::payload os_context::connection_settings_get_auto_detect()
   {

      try
      {

         registry::key key1(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

         memory mem;

         key1.get("DefaultConnectionSettings", mem);

         bool bAutoDetect = (((unsigned char*)mem.get_data())[8] & 0x08) != 0;

         if (!bAutoDetect)
         {

            return ::error_false;

         }

      }
      catch (const ::e_status & estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::payload os_context::connection_settings_get_auto_config_url()
   {

      string strUrl;
      
      try
      {

         registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

         key.get("AutoConfigURL", strUrl);

      }
      catch (const ::e_status & estatus)
      {

         return estatus;
   
      }

      return ::success;

   }


   bool os_context::local_machine_set_run(const ::string & pszKey, const ::string & pszCommand, bool bSet)
   {

      try
      {

         registry::key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);

         
         if (bSet)
         {

            keyKar.set(pszKey, string(pszCommand));

         }
         else
         {

            keyKar.delete_value(pszKey);

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool os_context::local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand, bool bSet)
   {

      try
      {

      registry::key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);

      if (bSet)
      {

         keyKar.set(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.delete_value(pszKey);

      }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool os_context::current_user_set_run(const ::string & pszKey, const ::string & pszCommand, bool bSet)
   {

      try
      {

            registry::key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);

 
            if (bSet)
            {

               keyKar.set(pszKey, string(pszCommand));

            }
            else
            {

               keyKar.delete_value(pszKey);

            }


      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool os_context::current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand, bool bSet)
   {

      try
      {

      registry::key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);

      if (bSet)
      {

         keyKar.set(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.delete_value(pszKey);

      }

      }
      catch (...)
      {

         return false;

      }

      return true;
   }


   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {

      try
      {

         registry::key key;

         key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true);

         key.open(key, "@ca2.cc/npca2", true);

         key.set("Description", "ca2 plugin for NPAPI");
         key.set("Path", get_context()->dir().ca2module() /"npca2.dll");
         key.set("ProductName", "ca2 plugin for NPAPI");
         key.set("Vendor", "ca2 Desenvolvimento de Software Ltda.");
         key.set("Version", get_context()->file().as_string(get_context()->dir().install()/"appdata/x86/ca2_build.txt"));

         key.open(key, "application/apex", true);

         key.set("Description", "apex Document");

      }
      catch (...)
      {

         return false;

      }

      return true;
   }

   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension)
   {

      try
      {

         string strExt;

         strExt = ".";
         strExt += pszExtension;

         string strOpenWithKey;
         strOpenWithKey = strExt + "\\OpenWithList";

         registry::key key(HKEY_CLASSES_ROOT, strOpenWithKey, false);

         key.ls_key(straKey);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension)
   {

      string_array straKey;

      if (!file_extension_get_open_with_list_keys(straKey, pszExtension))
      {

         return false;

      }


      return true;

   }


   bool os_context::file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath)
   {

      try
      {

      string strExtensionNamingClass(pszExtensionNamingClass);

      registry::key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);

      keyLink3.set("DefaultIcon", pszIconPath);

      }
      catch (...)
      {

         return false;

      }

      return true;


   }


   bool os_context::file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass,  const scoped_string & strCommand, const ::string & pszParam)
   {

      ::e_status estatus = ::success;

      try
      {

         string strExt;

         strExt += pszExtension;

         string strExtensionNamingClass(pszExtensionNamingClass);

         registry::key key(HKEY_CLASSES_ROOT, strExt, true);

         auto estatusRegistry = key._set(nullptr, strExtensionNamingClass);

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

         registry::key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);

         estatusRegistry = keyLink3._set("", "open");

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

         registry::key keyLink2(keyLink3, "open", true);

         estatusRegistry = keyLink2._set("", "");

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

         registry::key keyLink1(keyLink2, "command", true);

         string strCommand(pszCommand);

         strCommand = solve_relative(strCommand);

         string strFormat;

         strFormat.Format("\"%s\" %s", strCommand.c_str(), pszParam);

         estatusRegistry = keyLink1._set("", strFormat);

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }
      catch (...)
      {

         return false;

      }

      if (!estatus)
      {

         return false;

      }

      return true;


   }


   bool os_context::file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      try
      {
      string strExt;

      strExt = ".";
      strExt += pszExtension;

      registry::key key(HKEY_CLASSES_ROOT, strExt, false);
      key.get(nullptr, strExtensionNamingClass);

      registry::key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

      string strFormat;
      keyLink.get(nullptr, strFormat);
      {

         const scoped_string & str = strFormat;

         try
         {

            strCommand = ::str().consume_quoted_value(psz);
            ::str().consume_spaces(psz);
            ::str().consume(psz, "\"%L\"");
            strParam = psz;

         }
         catch(...)
         {
         }


      }


      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool os_context::open_in_ie(const ::scoped_string & scopedstr)
   {

      try
      {

         registry reg;

         string str;

         string str2;

         string strCommand;

         registry::key key(HKEY_CLASSES_ROOT, ".html", false);
         
         if(key._open(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
         {

            if(key._get("", str2))
            {
               
               string strCommand(str2);

               strCommand.replace("%1", pcsz);

               WinExec(strCommand,e_display_normal);

            }

         }
         else if(key._open(HKEY_CLASSES_ROOT, str, false))
         {
               
            str += "\\shell\\opennew\\command";

            if(key._get("", str2))
            {
                     
               string strCommand(str2);
                     
               strCommand.replace("%1", pcsz);

               WinExec(strCommand,e_display_normal);

            }

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //------------------------------------------------------------------------
   // The following function retrieves the identity of the current user.
   // This is a helper function and is not part of the Windows Biometric
   // Framework API.
   //
   struct TOKEN_INFO
   {
      TOKEN_USER tokenUser;
      unsigned char buffer[SECURITY_MAX_SID_SIZE];
   };


   HRESULT GetCurrentUserIdentity(TOKEN_INFO & tokenInfo)
   {

      // Declare variables.
      bool bOk = true;

      HANDLE tokenHandle = nullptr;

      DWORD bytesReturned = 0;

      // Open the access token associated with the
      // current process
      if(!OpenProcessToken(
            GetCurrentProcess(),            // Process handle
            TOKEN_READ,                     // Read access only
            &tokenHandle))                  // Access token handle
      {
         unsigned int win32Status = GetLastError();
         debug_print("Cannot open token handle: %d\n",win32Status);
         bOk = false;
      }

      // Zero the tokenInfoBuffer structure.
      ZeroMemory(&tokenInfo,sizeof(tokenInfo));

      // Retrieve information about the access token. In this case,
      // retrieve a SID.
      if(!GetTokenInformation(
            tokenHandle,                    // Access token handle
            TokenUser,                      // User for the token
            &tokenInfo.tokenUser,     // Buffer to fill
            sizeof(tokenInfo),        // Size of the buffer
            &bytesReturned))                // Size needed
      {
         unsigned int win32Status = GetLastError();
         debug_print("Cannot query token information: %d\n",win32Status);
         bOk = false;
      }

      if(tokenHandle != nullptr)
      {
         CloseHandle(tokenHandle);
      }

      return bOk;
   }
   BOOL
   GetAccountSid(
   TCHAR * SystemName,
   TCHAR * AccountName,
   PSID *Sid
   )
   {
      LPTSTR ReferencedDomain=nullptr;
      DWORD cbSid=128;    // initial allocation attempt
      DWORD cchReferencedDomain=16; // initial allocation int_size
      SID_NAME_USE peUse;
      BOOL bSuccess=false; // assume this function will fail

      __try
      {

         //
         // initial memory allocations
         //
         if((*Sid=HeapAlloc(
                  GetProcessHeap(),
                  0,
                  cbSid
                  )) == nullptr) __leave;

         if((ReferencedDomain=(TCHAR *)HeapAlloc(
                              GetProcessHeap(),
                              0,
                              cchReferencedDomain * sizeof(TCHAR)
                              )) == nullptr) __leave;

         //
         // Obtain the SID of the specified account on the specified system.
         //
         while(!LookupAccountName(
               SystemName,         // machine to lookup account on
               AccountName,        // account to lookup
               *Sid,               // SID of interest
               &cbSid,             // int_size of SID
               ReferencedDomain,   // domain account was found on
               &cchReferencedDomain,
               &peUse
               ))
         {
            if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               //
               // reallocate memory
               //
               if((*Sid=HeapReAlloc(
                        GetProcessHeap(),
                        0,
                        *Sid,
                        cbSid
                        )) == nullptr) __leave;

               if((ReferencedDomain=(TCHAR *)HeapReAlloc(
                                    GetProcessHeap(),
                                    0,
                                    ReferencedDomain,
                                    cchReferencedDomain * sizeof(TCHAR)
                                    )) == nullptr) __leave;
            }
            else __leave;
         }

         //
         // Indicate success.
         //
         bSuccess=true;

      } // finally
      __finally
      {

         //
         // Cleanup and indicate failure, if appropriate.
         //

         HeapFree(GetProcessHeap(),0,ReferencedDomain);

         if(!bSuccess)
         {
            if(*Sid != nullptr)
            {
               HeapFree(GetProcessHeap(),0,*Sid);
               *Sid = nullptr;
            }
         }

      } // finally

      return bSuccess;
   }


   bool os_context::_getCredentialsForService(const ::scoped_string & scopedstrService,WCHAR * szUsername,WCHAR *szPassword)
   {

      HRESULT hr = S_OK;
      unsigned int   dwResult;
      sec_cotaskptr < PVOID > pvInAuthBlob;
      sec_cotaskptr < PVOID > pvAuthBlob;
      CREDUI_INFOW u;
      ULONG   ulAuthPackage = 0;
      BOOL    fSave = false;
      WCHAR szDomainAndUser[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR szDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
//      TOKEN_INFO ti;

      unsigned int maxLenName = CREDUI_MAX_USERNAME_LENGTH + 1;
      unsigned int maxLenPass = CREDUI_MAX_PASSWORD_LENGTH + 1;
      unsigned int maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      HICON hicon = nullptr;

      // Display a dialog box to request credentials.
      zero(u);
      u.cbSize = sizeof(u);
      u.hwndParent = nullptr;

      // Retrieve the user name and domain name.
      // SID_NAME_USE    SidUse;
      unsigned int           cchTmpUsername = CREDUI_MAX_USERNAME_LENGTH +1;
      unsigned int           cchTmpDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;
      unsigned int           cchDomainAndUser = CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      wstring wstrCaption("\"ca2 : " + strService + "\" Authentication");
      wstring wstrMessage("The Service \"ca2 : " + strService + "\" requires current user password for installing Windows Service.");

      unsigned int lenUserName = CREDUI_MAX_USERNAME_LENGTH + 1;

      //::GetUserNameW(szUsername,&lenUserName);

      unsigned int dwLastError = 0;

      bool bOk;

      //if(!GetCurrentUserIdentity(ti))
      //   return false;
      ////szDomain[0] ='.';
      ////         szDomain[1] ='\0';
      //if(!LookupAccountSidW(
      //   nullptr,             // Local computer
      //   ti.tokenUser.puser->Sid,             // Security identifier for user
      //   szUsername,       // User name
      //   &cchTmpUsername,  // Size of user name
      //   szDomain,         // Domain name
      //   &cchTmpDomain,    // Size of domain name
      //   &SidUse))         // Account type
      //{
      //   dwResult = GetLastError();
      //   debug_print("\n getCredentialsForService LookupAccountSidLocalW failed: win32 error = 0x%x\n",dwResult);
      //   return false;
      //}

      ULONG l = sizeof(szDomainAndUser) / sizeof(WCHAR);

      ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

      // Combine the domain and user names.
      /*swprintf_s(
         szDomainAndUser,
         cchDomainAndUser,
         L"%s\\%s",
         szDomain,
         szUsername);*/
      ::zero(szPassword,CREDUI_MAX_PASSWORD_LENGTH);

      // Call CredPackAuthenticationBufferW once to determine the size,
      // in bytes, of the authentication buffer.

      if(!LIBCALL(credui,CredPackAuthenticationBufferW)(
            0,                // Reserved
            szDomainAndUser,  // Domain\User name
            szPassword,       // User Password
            nullptr,             // Packed credentials
            &pvInAuthBlob.m_size)    // Size, in bytes, of credentials
            && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      {
         dwResult = GetLastError();
         debug_print("\n getCredentialsForService CredPackAuthenticationBufferW (1) failed: win32 error = 0x%x\n",dwResult);
         return false;
      }

      // Allocate memory for the input buffer.
      pvInAuthBlob.alloc();

      if(pvInAuthBlob.is_null())
      {

         debug_print("\n getCredentialsForService CoTaskMemAlloc() Out of memory.\n");

         return false;

      }

      // Call CredPackAuthenticationBufferW again to retrieve the
      // authentication buffer.
      if(!LIBCALL(credui,CredPackAuthenticationBufferW)(
            0,
            szDomainAndUser,
            szPassword,
            (PBYTE)pvInAuthBlob.m_p,
            &pvInAuthBlob.m_size))
      {
         dwResult = GetLastError();
         debug_print("\n CredPackAuthenticationBufferW (2) failed: win32 error = 0x%x\n",dwResult);
      }


      u.pszCaptionText = wstrCaption;
      u.pszMessageText = wstrMessage;
      hicon = (HICON) ::LoadImageW(::GetModuleHandle(nullptr),MAKEINTRESOURCEW(1),IMAGE_ICON,48,48,LR_DEFAULTCOLOR);


      if(hicon != nullptr)
      {

         u.hbmBanner = get_icon_hbitmap(hicon);

         ::DeleteObject(hicon);

      }

retry:

      dwResult = LIBCALL(credui,CredUIPromptForWindowsCredentialsW)(
                 &u,             // Customizing information
                 dwLastError,               // Error code to display
                 &ulAuthPackage,  // Authorization package
                 pvInAuthBlob,    // Credential unsigned char array
                 pvInAuthBlob.m_size,    // Size of credential input buffer
                 &pvAuthBlob,     // Output credential unsigned char array
                 &pvAuthBlob.m_size,     // Size of credential unsigned char array
                 &fSave,          // Select the save check box.
                 //CREDUIWIN_SECURE_PROMPT |
                 CREDUIWIN_IN_CRED_ONLY |
                 CREDUIWIN_ENUMERATE_CURRENT_USER
                 );


      if(dwResult == NO_ERROR)
      {

         DWORD lenName = maxLenName;
         DWORD lenDomain = maxLenDomain;
         DWORD lenPass = maxLenPass;

         bOk = LIBCALL(credui, CredUnPackAuthenticationBufferW)(CRED_PACK_PROTECTED_CREDENTIALS,
               pvAuthBlob,
               pvAuthBlob.m_size,
               szUsername,
               &lenName,
               szDomain,
               &lenDomain,
               szPassword,
               &lenPass) != false;


         if(!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         //wcscpy(szDomainAndUser,szUsername);

         ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

         bOk = LIBCALL(credui,CredUIParseUserNameW)(
               szDomainAndUser,
               szUsername,
               CREDUI_MAX_USERNAME_LENGTH,
               szDomain,
               CREDUI_MAX_DOMAIN_TARGET_LENGTH
               ) == NO_ERROR ;

         if(!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         HANDLE h;

         if(::LogonUserW(
               szUsername,
               szDomain,
               szPassword,
               LOGON32_LOGON_SERVICE,
               LOGON32_PROVIDER_DEFAULT,
               &h))
         {

            ::CloseHandle(h);

         }
         else
         {

            dwLastError = ::GetLastError();

            goto retry;

         }

         wcscpy(szUsername,szDomainAndUser);

      }
      else
      {

         if (dwResult != ERROR_CANCELLED)
         {

            goto retry;

         }

         hr = HRESULT_FROM_WIN32(dwResult);
         
         bOk = false;

      }

      if(u.hbmBanner != nullptr)
      {

         ::DeleteObject(u.hbmBanner);

      }

      return bOk;

   }


   string os_context::calc_service_name()
   {

      ::application * papp = get_application();

      if(get_application()->m_strAppName.is_empty()
            || get_application()->m_strAppName.case_insensitive_order("bergedge") == 0
            || !get_application()->is_serviceable())
         return "";

      string strServiceName = get_application()->m_strAppId;

      strServiceName.replace("/","-");

      strServiceName.replace("\\","-");

      return strServiceName;

   }


   void os_context::create_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         return false;

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_CREATE_SERVICE);

      if(hdlSCM == 0)
      {

         unsigned int dwLastError = ::GetLastError();

         return false;

      }

      string strDisplayName(strServiceName);

      strDisplayName.replace("-"," ");

      string strExe(strServiceName);

      strExe.replace("-","_");

      strExe += ".exe";

      string strCalling = get_context()->dir().module() / strExe + " : service";

      if(is_true("no_remote_simpledb"))
      {

         strCalling += " no_remote_simpledb";

      }

      WCHAR * pname = nullptr;
      WCHAR * ppass = nullptr;

      WCHAR lpszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      ::application * papp = get_application();

      if(get_application()->is_user_service())
      {

         if(_getCredentialsForService(get_application()->m_strAppId,lpszName,pszPass))
         {

            pname = lpszName;
            ppass = pszPass;

         }
         else
         {

            return false;

         }

      }

      return create_service(strServiceName,strDisplayName,strCalling,pname,ppass);

   }


   void os_context::remove_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         return false;

      }

      return remove_service(strServiceName);

   }


   void os_context::start_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         return false;

      }

      return start_service(strServiceName);

   }


   bool os_context::create_service(const ::scoped_string & scopedstrServiceName, const ::scoped_string & scopedstrDisplayName, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass)
   {

      if (strServiceName.is_empty())
      {

         return false;

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_CREATE_SERVICE);

      if(hdlSCM == 0)
      {
         //::GetLastError()
         return false;

      }

      WCHAR lpszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      wcscpy(lpszName,wstring(strUser));
      wcscpy(pszPass,wstring(strPass));

      SC_HANDLE hdlServ = ::CreateServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          wstring(strDisplayName),        // service name to display
                          STANDARD_RIGHTS_REQUIRED,  // desired access
                          SERVICE_WIN32_OWN_PROCESS, // service type
                          SERVICE_AUTO_START,      // start type
                          SERVICE_ERROR_NORMAL,      // error control type
                          wstring(strCommand),                   // service's binary Path name
                          0,                      // no load ordering group
                          0,                      // no tag identifier
                          0,                      // no dependencies
                          strUser.has_character() ? lpszName : nullptr,                      // LocalSystem account
                          strPass.has_character() ? pszPass : nullptr);                     // no password


      if(!hdlServ)
      {

         unsigned int Ret = ::GetLastError();

         TRACELASTERROR();

         CloseServiceHandle(hdlSCM);

         return false;

      }

      SecureZeroMemory(lpszName,sizeof(lpszName));
      SecureZeroMemory(pszPass,sizeof(pszPass));


      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return true;

   }


   bool os_context::remove_service(const ::scoped_string & scopedstrServiceName)
   {

      if (strServiceName.is_empty())
      {

         return false;

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          DELETE);

      if(!hdlServ)
      {
         unsigned int Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         if(Ret == 1060) // Service already doesn't exist.
            return true; // do self-healing
         return false;
      }

      if(!::DeleteService(hdlServ))
      {
         unsigned int Ret = ::GetLastError();
         CloseServiceHandle(hdlServ);
         CloseServiceHandle(hdlSCM);
         return false;
      }

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return true;

   }

   void  os_context::stop_service()
   {

      string strServiceName = calc_service_name();

      if(strServiceName.is_empty())
         return false;

      return stop_service(strServiceName);

   }


   bool os_context::start_service(const ::scoped_string & scopedstrServiceName)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          SERVICE_START);                     // no password


      if(!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::GetLastError();
         return false;
      }

      bool bOk = StartService(hdlServ,0,nullptr) != false;

      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return bOk != false;
   }

   bool os_context::stop_service(const ::scoped_string & scopedstrServiceName)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          SERVICE_STOP);                     // no password

      if(!hdlServ)
      {
         // Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SERVICE_STATUS ss;

      memory_set(&ss,0,sizeof(ss));

      bool bOk = ::ControlService(hdlServ,SERVICE_CONTROL_STOP,&ss) != false;

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return bOk != false;
   }


   DECLSPEC_NO_RETURN void os_context::raise_exception( unsigned int dwExceptionCode, unsigned int dwExceptionFlags)
   {
      RaiseException( dwExceptionCode, dwExceptionFlags, 0, nullptr );
   }

   bool os_context::is_remote_session()
   {

      return GetSystemMetrics(SM_REMOTESESSION) != false;

   }




   void os_context::set_file_status(const ::string & pszFileName, const ::file::file_status& status)

   {

      unsigned int wAttr;
      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME pCreationTime = nullptr;

      LPFILETIME pLastAccessTime = nullptr;

      LPFILETIME pLastWriteTime = nullptr;

      wstring wstr(pszFileName);

      if((wAttr = windows_get_file_attributes(pszFileName)) == (unsigned int)-1L)
      {

         ::file::throw_os_error( (int)GetLastError());

      }

      if ((unsigned int)status.m_attribute != wAttr && (wAttr & ::windows::file::readOnly))
      {

         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         if (!SetFileAttributesW(wstr, (unsigned int)status.m_attribute))
         {

            ::file::throw_os_error( (int)GetLastError());

         }

      }

      // last modification time
      if (status.m_mtime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_application(), status.m_mtime, &lastWriteTime);

         pLastWriteTime = &lastWriteTime;


      }

      // last access time
      if (status.m_atime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_application(),status.m_atime, &lastAccessTime);

         pLastAccessTime = &lastAccessTime;


      }

      // create time
      if (status.m_ctime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_application(),status.m_ctime, &creationTime);

         pCreationTime = &creationTime;


      }

      HANDLE hFile = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

      if(hFile == INVALID_HANDLE_VALUE)
      {

         ::file::throw_os_error( (int)::GetLastError());

      }

      if(!SetFileTime((HANDLE)hFile, pCreationTime, pLastAccessTime, pLastWriteTime))

      {

         ::file::throw_os_error( (int)::GetLastError());

      }

      if(!::CloseHandle(hFile))
      {

         ::file::throw_os_error( (int)::GetLastError());

      }

      if ((unsigned int)status.m_attribute != wAttr && !(wAttr & ::windows::file::readOnly))
      {

         if (!::SetFileAttributesW(wstr, (unsigned int)status.m_attribute))
         {

            ::file::throw_os_error( (int)GetLastError());

         }

      }

   }


   bool os_context::resolve_link(::file::path & path, const ::scoped_string & scopedstrSource, string * pstrDirectory, string * pstrParams)
   {

      if (::os_context::resolve_link(path, strSource, pstrDirectory, pstrParams))
      {

         return true;

      }

      if (strSource.case_insensitive_ends(".lnk"))
      {

         if (resolve_lnk_link(path, strSource, pstrDirectory, pstrParams))
         {

            return true;

         }

      }

      return false;

   }


   bool os_context::resolve_lnk_link(::file::path & path, const ::scoped_string & scopedstrSource, string * pstrDirectory, string * pstrParams)
   {

      ASSERT(strSource.case_insensitive_ends(".lnk"));

      if (strSource.contains("0318") && strSource.contains("removal"))
      {

         output_debug_string("app.removal.tool link?!");

      }

      wstring wstrFileIn = utf8_to_unicode(strSource);

      bool bNativeUnicode = is_windows_native_unicode() != false;

      SHFILEINFOW info;

      zero(info);

      defer_co_initialize_ex(false);

      DWORD_PTR dw = 0;

      auto pitemidlist = path.m_pmatterOsPath.cast < ::itemidlist>();

      if (pitemidlist)
      {

         dw = SHGetFileInfoW((const wchar_t *)pitemidlist->m_pidl, 0, &info, sizeof(info), SHGFI_ATTRIBUTES | SHGFI_PIDL);

      }
      else
      {

         dw = SHGetFileInfoW(wstrFileIn, 0, &info, sizeof(info), SHGFI_ATTRIBUTES);

      }

      if (dw == 0 || !(info.dwAttributes & SFGAO_LINK))
      {

         return false;

      }

      HRESULT hr;

      comptr < IShellLinkW > pshelllink;

      if (FAILED(hr = pshelllink.CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER)))
      {

         return false;

      }

      bool bOk = false;

      comptr < IPersistFile > ppersistfile;

      if (SUCCEEDED(hr = pshelllink.As(ppersistfile)))
      {

         if (SUCCEEDED(hr = ppersistfile->Load(wstrFileIn, STGM_READ)))
         {

            //HWND hwnd = pinteraction == nullptr ? nullptr : pinteraction->get_handle();

            HWND hwnd = nullptr;

            unsigned int fFlags = 0;

            //fFlags |= pinteraction == nullptr ? (SLR_NO_UI | (10 << 16)) : 0;
            fFlags |= SLR_NO_UI;

            fFlags |= SLR_NOUPDATE;

            fFlags |= SLR_NOSEARCH;

            fFlags |= SLR_NOTRACK;

            wstring wstr;

            auto pwsz = wstr.get_buffer(MAX_PATH * 8);

            if (SUCCEEDED(pshelllink->GetPath(pwsz, MAX_PATH * 8, nullptr, 0)))
            {

               bOk = true;

               wstr.release_buffer();

               string strLink = unicode_to_utf8((const ::wide_character *)wstr);

               if (strLink.is_empty() && pitemidlist)
               {

                  pshelllink->GetIDList(&pitemidlist->m_pidl);

               }
               else
               {

                  path = strLink;

               }

            }

            if (::is_set(pstrDirectory))
            {

               auto pwsz = wstr.get_buffer(MAX_PATH * 8);

               if (SUCCEEDED(pshelllink->GetWorkingDirectory(pwsz, MAX_PATH * 8)))
               {

                  wstr.release_buffer();

                  *pstrDirectory = unicode_to_utf8((const ::wide_character *)wstr);

               }

            }

            if (::is_set(pstrParams))
            {

               auto pwsz = wstr.get_buffer(MAX_PATH * 8);

               if (SUCCEEDED(pshelllink->GetArguments(pwsz, MAX_PATH * 8)))
               {

                  wstr.release_buffer();

                  *pstrParams = unicode_to_utf8((const ::wide_character *)wstr);

               }

            }

         }

      }

      return bOk;

   }


   bool os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      try
      {

         registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", false);

         string strProgId;

         string strHash;

         key._get("Hash", strHash);

         key._get("ProgId", strProgId);

         if (strProgId.begins("App") && strHash.has_character())
         {

            strId = "edge";

         }
         if (strProgId.case_insensitive_begins("IE."))
         {

            strId = "ie";

         }
         else if (strProgId.case_insensitive_begins("ChromeHTML"))
         {

            strId = "chrome";

         }
         else if (strProgId.case_insensitive_begins("FirefoxHTML"))
         {

            strId = "firefox";

         }
         else if (strProgId.case_insensitive_begins("Opera"))
         {

            strId = "opera";

         }
         else if (strProgId.case_insensitive_begins("VivaldiHTM."))
         {

            strId = "vivaldi";

         }
         else if (strProgId.case_insensitive_ends("app_core_commander"))
         {

            strId = "commander";

         }
         else
         {

            strId = "commander";

         }

         string strDefault;

         key._open(HKEY_CLASSES_ROOT, strProgId + "\\shell\\open\\command", false);

         key._get("", strDefault);

         if (strDefault.is_empty())
         {

            return false;

         }

         bool bQuote = strDefault.case_insensitive_begins_eat("\"");

         character_count iFind = strDefault.case_insensitive_find(".exe");

         if (iFind <= 0)
         {

            return false;

         }

         path = strDefault.left()(iFind);

         path += ".exe";

         //MessageBox(nullptr, path, "pathProgram", e_message_box_ok);

         strParam = strDefault.substr(iFind + 5);

         if (bQuote)
         {

            strParam.case_insensitive_begins_eat("\"");

         }

         return true;

      }
      catch (...)
      {

         return false;

      }

   }


   bool os_context::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         ::file::path pathFolder;

         ::windows::shell_get_special_folder_path(nullptr, pathFolder, CSIDL_WINDOWS, false);

         pathFolder /= "Web/Wallpaper";

         pfileset->add_search(pathFolder, true);

      }

      return true;

   }
//#elif defined(LINUX)
//   //string strDir;
//   //strDir = get_context()->dir().path(getenv("HOME"), "Pictures");
//   //imagefileset.add_search(strDir);
//   string strDir;
//   strDir = "/usr/share/backgrounds";
//   imagefileset.add_search(strDir, true);
//            }
//
//#elif defined(MACOS)
//   //string strDir;
//   //strDir = get_context()->dir().path(getenv("HOME"), "Pictures");
//   //imagefileset.add_search(strDir);
//   string strDir;
//   strDir = "/Library/Desktop Pictures";
//   imagefileset.add_search(strDir, true);
//            }
//
//#else


   bool os_context::file_open(::file::path path, string strParams, string strFolder)
   {

      path = get_context()->defer_process_path(path);

      fork([=]()
      {

         ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

         SHELLEXECUTEINFOW si;

         zero(si);

         PeekMessage(nullptr, nullptr, 0, 0, 0);

         wstring wstrTarget(path);

         wstring wstrFolder(strFolder);

         wstring wstrParams(strParams);

         const wchar_t * pwszParams = wstrParams.c_str();

         const wchar_t * pwszFolder = wstrFolder.c_str();

         si.cbSize = sizeof(si);

         si.fMask = SEE_MASK_ASYNCOK;

         si.hwnd = nullptr;

         si.lpVerb = L"open";

         auto pitemidlist = path.m_pmatterOsPath.cast < ::itemidlist >();

         if (wstrTarget.is_empty() && pitemidlist)
         {

            si.fMask |= SEE_MASK_IDLIST;

            si.lpIDList = pitemidlist->m_pidl;


         }
         else
         {

            si.lpFile = wstrTarget;


         }

         si.lpParameters = pwszParams;


         si.lpDirectory = pwszFolder;


         si.nShow = SW_SHOWDEFAULT;

         si.hInstApp = nullptr;

         ShellExecuteExW(&si);

         //unsigned int dwLastError = ::GetLastError();

         //int iResult = (int) si.hInstApp;

         //string str;

         //str.formatf("ShellExecuteExW %d GetLastError = %d", iResult, dwLastError);

         //output_debug_string(str);


         //thread_pump_sleep(60 * 1000);


         //int iRet = (int) (iptr) ::ShellExecuteW(nullptr, L"open", wstring(path), pwszParams, pwszFolder, SW_RESTORE);

         //if (iRet < 32)
         //{

         //   /*0
         //      The operating system is out of memory or resources.
         //      ERROR_FILE_NOT_FOUND
         //      The specified file was not found.
         //      ERROR_PATH_NOT_FOUND
         //      The specified path was not found.
         //      ERROR_BAD_FORMAT
         //      The.exe file is invalid(non - Win32.exe or error in.exe image).
         //      SE_ERR_ACCESSDENIED
         //      The operating system denied access to the specified file.
         //      SE_ERR_ASSOCINCOMPLETE
         //      The file name association is incomplete or invalid.
         //      SE_ERR_DDEBUSY
         //      The DDE transaction could not be completed because other DDE transactions were being processed.
         //      SE_ERR_DDEFAIL
         //      The DDE transaction failed.
         //      SE_ERR_DDETIMEOUT
         //      The DDE transaction could not be completed because the request timed out.
         //      SE_ERR_DLLNOTFOUND
         //      The specified DLL was not found.
         //      SE_ERR_FNF
         //      The specified file was not found.
         //      SE_ERR_NOASSOC
         //      There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
         //      SE_ERR_OOM
         //      There was not enough memory to complete the operation.
         //      SE_ERR_PNF
         //      The specified path was not found.
         //      SE_ERR_SHARE
         //      A sharing violation occurred.*/

         //   message_box(nullptr, "Error opening file \"" + path + "\"", "Could not open file", e_message_box_icon_exclamation);

         //}

      });

      return true;

   }


   bool os_context::register_user_auto_start(string strId, string strCommand, bool bRegister)
   {

      current_user_set_run(strId, strCommand, bRegister);

      return true;

   }


   bool os_context::is_user_auto_start(string strId)
   {

      registry::key keyKar;

      if (keyKar._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false))
      {

         string strValue;

         if (keyKar._get(strId, strValue))
         {

            if (strValue.has_character())
            {

               return true;

            }

         }

      }

      return false;

   }

   ::file::path os_context::get_app_path(const ::scoped_string & scopedstrApp)
   {

      string str(strApp);

      registry::key key;

      string strDefault;

repeat:

      if (key._open(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + str, false))
      {

         if (key._get("", strDefault))
         {

            if (strDefault.has_character())
            {

               return strDefault;

            }

         }

      }

      if (!str.case_insensitive_ends(".exe"))
      {

         str += ".exe";

         goto repeat;

      }

      return ::os_context::get_app_path(str);

   }


   bool os_context::set_default_browser()
   {


      ::application * papp = get_application();

      string strTargetProgId;
      string strModule = solve_relative(::file::app_module());

      strTargetProgId = get_application()->m_strAppName;

      strTargetProgId.replace("-", "_");
      strTargetProgId.replace("\\", "_");
      strTargetProgId.replace("/", "_");

      __prevent_bad_status_exception;
      
      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         regkey.set(strTargetProgId, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities");

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId, true);

         string strValue;

         regkey.set("", get_application()->find_string("ApplicationName"));

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities", true);

         string strValue;

         regkey.set("ApplicationDescription", get_application()->find_string("ApplicationDescription"));
         regkey.set("ApplicationIcon", get_application()->find_string("ApplicationIcon"));
         regkey.set("ApplicationName", get_application()->find_string("ApplicationName"));

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\FileAssociations", true);

         string strValue;

         regkey.set(".htm", strTargetProgId);
         regkey.set(".html", strTargetProgId);
         regkey.set(".pdf", strTargetProgId);
         regkey.set(".shtml", strTargetProgId);
         regkey.set(".svg", strTargetProgId);
         regkey.set(".webp", strTargetProgId);
         regkey.set(".xht", strTargetProgId);
         regkey.set(".xhtml", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

         string strValue;

         regkey.set("StartMen::u32ernet", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\URLAssociations", true);

         string strValue;

         regkey.set("ftp", strTargetProgId);
         regkey.set("http", strTargetProgId);
         regkey.set("https", strTargetProgId);
         regkey.set("irc", strTargetProgId);
         regkey.set("mailto", strTargetProgId);
         regkey.set("mms", strTargetProgId);
         regkey.set("news", strTargetProgId);
         regkey.set("nntp", strTargetProgId);
         regkey.set("sms", strTargetProgId);
         regkey.set("smsto", strTargetProgId);
         regkey.set("tel", strTargetProgId);
         regkey.set("urn", strTargetProgId);
         regkey.set("webcal", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\DefaultIcon", true);

         string strValue;

         regkey.set("", strModule + ",0");

      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\InstallInfo", true);

         string strValue;

         regkey.set("HideIconsCommand", "\""+strModule + "\" : hide_icons");
         regkey.set("IconsVisible", 1);
         regkey.set("ReinstallCommand", "\""+strModule + "\" : install");
         regkey.set("ShowIconsCommand", "\""+strModule + "\" : show_icons");

      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\shell\\open\\command", true);

         string strValue;

         regkey.set("", "\""+strModule + "\" : browser_weather=default");

      }


      {

         registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

         regkey.set("", strTargetProgId + " HTML Document");
         regkey.set("AppUserModelId", get_application()->find_string("AppUserModelId"));

      }
      {

         registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\papplication", true);

         regkey.set("ApplicationCompany", get_application()->find_string("ApplicationCompany"));
         regkey.set("ApplicationDescription", get_application()->find_string("ApplicationDescription"));
         regkey.set("ApplicationIcon", get_application()->find_string("ApplicationIcon"));
         regkey.set("ApplicationName", get_application()->find_string("ApplicationName"));
         regkey.set("AppUserModelId", get_application()->find_string("AppUserModelId"));

      }
      {

         registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         regkey.set("", get_application()->find_string("DefaultIcon"));

      }

      file_association_set_shell_open_command(strTargetProgId, strTargetProgId, strModule, "\"%1\"");
      {

         ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

         string strProgId;

         regkey.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.delete_value("Hash");

            regkey.set("ProgId", strTargetProgId);

         }

      }

      {

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

         string strProgId;

         key.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            string strHash;

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         registry::key key(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);

         string strProgId;

         key.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);

         string strProgId;

         key._get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         registry::key key(HKEY_CLASSES_ROOT, ".html\\OpenWithProgids", true);

         key._set(strTargetProgId, "");

      }

      {

         registry::key key(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

         key._set(strTargetProgId, "");

      }

      SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);

      sleep(1_s);

      return true;

   }


   bool os_context::add_default_program(string_array & straExtension, string_array & straMimeType)
   {

      string strTargetProgId;

      string strModule = solve_relative(::file::app_module());

      string strApplicationRegistryPath = find_string("ApplicationRegistryPath");

      ::file::path pathApplication;

      pathApplication = "Software";

      pathApplication /= strApplicationRegistryPath;

      pathApplication /= strTargetProgId;

      strTargetProgId = get_application()->m_strAppName;

      strTargetProgId.replace("-", "_");
      strTargetProgId.replace("\\", "_");
      strTargetProgId.replace("/", "_");

      ::e_status estatus = ::success;

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication, true);

         string strValue;

         auto estatusRegistry = regkey._set("", get_application()->find_string("ApplicationName"));

         if(!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }

      
      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "DefaultIcon", true);

         string strValue;

         auto estatusRegistry = regkey._set("", strModule + ",0");

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }


      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "InstallInfo", true);

         string strValue;

         auto estatusRegistry = regkey._set("HideIconsCommand", "\"" + strModule + "\" : hide_icons");

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("IconsVisible", 1);

         }

         if(estatusRegistry.succeeded())
         {
          
            estatusRegistry = regkey._set("ReinstallCommand", "\"" + strModule + "\" : install");

         }

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ShowIconsCommand", "\"" + strModule + "\" : show_icons");

         }

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "shell/open/command", true);

         string strValue;

         auto estatusRegistry = regkey._set("", "\"" + strModule + "\" \"%1\"");

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }


      ::file::path pathApplicationCapabilities;

      pathApplicationCapabilities = pathApplication / "Capabilities";

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         auto estatusRegistry = regkey._set(strTargetProgId, pathApplicationCapabilities);

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities, true);

         string strValue;

         auto estatusRegistry = regkey._set("ApplicationDescription", get_application()->find_string("ApplicationDescription"));

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ApplicationIcon", get_application()->find_string("ApplicationIcon"));

         }

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ApplicationName", get_application()->find_string("ApplicationName"));

         }

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }


      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         string strValue;

         auto estatusRegistry = regkey._set(".mp4", strTargetProgId);

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }

      //{

      //   ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

      //   string strValue;

      //   regkey.set("StartMen::u32ernet", strTargetProgId);

      //}

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         for (::collection::index i = 0; i < straMimeType.get_count(); i++)
         {

            string strExtension = straExtension[i];

            auto estatusRegistry = regkey._set("." + strExtension, strTargetProgId + "." + strExtension);

            if (!estatusRegistry)
            {

               estatus = estatusRegistry;

            }

         }

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "MimeAssociations", true);

         for (::collection::index i = 0; i < straMimeType.get_count(); i++)
         {

            string strMimeType = straMimeType[i];

            string strExtension = straExtension[i];

            auto estatusRegistry = regkey._set(strMimeType, strTargetProgId + "." + strExtension);

            if (!estatusRegistry)
            {

               estatus = estatusRegistry;

            }

         }

      }

      //{

      //   registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

      //   regkey.set("", strTargetProgId + " HTML Document");
      //   regkey.set("AppUserModelId", get_application()->prop("AppUserModelId"));

      //}
      {

         registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\papplication", true);

         auto estatusRegistry = regkey._set("ApplicationCompany", get_application()->find_string("ApplicationCompany"));

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ApplicationDescription", get_application()->find_string("ApplicationDescription"));

         }

         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ApplicationIcon", get_application()->find_string("ApplicationIcon"));

         }
         
         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("ApplicationName", get_application()->find_string("ApplicationName"));

         }
         
         if(estatusRegistry.succeeded())
         {

            estatusRegistry = regkey._set("AppUserModelId", get_application()->find_string("AppUserModelId"));

         }

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }
      {

         registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         auto estatusRegistry = regkey._set("", get_application()->find_string("DefaultIcon"));

         if (!estatusRegistry)
         {

            estatus = estatusRegistry;

         }

      }

      for (::collection::index i = 0; i < straExtension.get_count(); i++)
      {

         string strExtension = straExtension[i];

         if (!file_association_set_shell_open_command(strExtension, strTargetProgId + "." + strExtension, strModule, "\"%1\""))
         {

            estatus = ::error_failed;

         }

         {

            registry::key regkey(HKEY_CLASSES_ROOT, "." + strExtension + "\\OpenWithProgids", true);

            auto estatusRegistry = regkey._set(strTargetProgId, "");

            if(!estatusRegistry)
            {

               informationf("Failure to set ." + strExtension + "\\OpenWithProgids");

               estatus = estatusRegistry;

            }

         }

      }

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   registry::key regkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   registry::key regkey(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

      //   if(!regkey.set(strTargetProgId, ""))
      //   {

      //      informationf("Failure to set .htm/OpenWithProgids");

      //   }

      //}
      //file_association_set_shell_open_command(".htm", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command(".html", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("http", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("https", strTargetProgId, strModule, "\"%1\"");

      fork([this]()
         {

            if (defer_co_initialize_ex(false))
            {

               SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);

               sleep(3_s);

            }

         });


      if (!estatus)
      {

         return false;

      }

      return true;

   }


   bool os_context::browse_file_open(::property_set & set)
   {

      //::user::interaction* pinteraction = nullptr;
      //
      //if (::is_set(puiOwner))
      //{

      //   pinteraction = puiOwner->get_wnd();

      //}

      bool bOk = false;

      //try
      //{

      //   if (::is_set(pinteraction))
      //   {

      //      pinteraction->enable_window(false);

      //   }

      //}
      //catch (...)
      //{


      //}

      try
      {

         bool bDisableOleDDE = true;

         defer_co_initialize_ex(false, bDisableOleDDE);

         comptr < IFileOpenDialog > pfileopen;

         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            FILEOPENDIALOGOPTIONS options = 0;

            hr = pfileopen->GetOptions(&options);

            array < COMDLG_FILTERSPEC > rgSpec;

            array < wstring > wstraSpecs;

            ::generic::container::copy(wstraSpecs, set["file_filter_specs"].stra());

            array < wstring > wstraNames;

            ::generic::container::copy(wstraNames, set["file_filter_names"].stra());

            rgSpec.set_size(minimum(wstraSpecs.get_size(), wstraNames.get_size()));

            for (::collection::index i = 0; i < rgSpec.get_size(); i++)
            {

               rgSpec[i].pszName = wstraNames[i];

               rgSpec[i].pszSpec = wstraSpecs[i];

               //{ L"CSV files", L"*.csv" },
               //{ L"Text files", L"*.txt" },
               //{ L"All files", L"*.*" },

            }

            if (rgSpec.get_size() > 0)
            {

               pfileopen->SetFileTypes(unsigned int(rgSpec.get_size()), rgSpec.get_data());

            }

            if ((bool)set["allow_multi_select"])
            {

               options |= FOS_ALLOWMULTISELECT;

            }

            hr = pfileopen->SetOptions(options);

            if (set["default_file_extension"].get_length() > 0)
            {

               pfileopen->SetDefaultExtension(wstring(set["default_file_extension"]));

            }

            if (set["file_name"].get_length() > 0)
            {

               pfileopen->SetFileName(wstring(set["file_name"]));

            }

            if (set["folder"].get_length() > 0)
            {

               wstring wstr(set["folder"]);

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            //HWND hwndOwner = nullptr;

            //if (::is_set(pinteraction))
            //{

            //   hwndOwner = pinteraction->get_handle();

            //}

            // Show the Save dialog box.
            //hr = pfileopen->Show(hwndOwner);
            hr = pfileopen->Show(nullptr);

            if (SUCCEEDED(hr))
            {

               if (options & FOS_ALLOWMULTISELECT)
               {

                  comptr < IShellItemArray > pitema;

                  hr = pfileopen->GetResults(&pitema);

                  if (SUCCEEDED(hr))
                  {

                     DWORD dwNumItems = 0; // number of items in multiple selection

                     hr = pitema->GetCount(&dwNumItems);  // get number of selected items

                     // Loop through IShellItemArray and construct string for display
                     for (unsigned int i = 0; i < dwNumItems; i++)
                     {
                        comptr < IShellItem > pitem;

                        hr = pitema->GetItemAt(i, &pitem); // get a selected item from the IShellItemArray

                        if (SUCCEEDED(hr))
                        {

                           cotaskp(PWSTR) pwszFilePath;

                           hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                           // Display the file name to the user.
                           if (SUCCEEDED(hr))
                           {

                              set["file_name"].stra().add(string((PWSTR)pwszFilePath));

                              bOk = true;

                           }

                        }

                     }

                  }

               }
               else
               {

                  // Get the file name from the dialog box.
                  comptr < IShellItem > pitem;

                  hr = pfileopen->GetResult(&pitem);

                  if (SUCCEEDED(hr))
                  {

                     cotaskp(PWSTR) pwszFilePath;

                     hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                     // Display the file name to the user.
                     if (SUCCEEDED(hr))
                     {

                        set["file_name"] = string((PWSTR)pwszFilePath);

                        bOk = true;

                     }

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      //try
      //{

      //   if (::is_set(pinteraction))
      //   {

      //      pinteraction->enable_window();

      //      pinteraction->order_top();

      //      pinteraction->display(e_display_normal, XXXX_activation_set_foreground);

      //      pinteraction->set_need_redraw();

      //      pinteraction->post_redraw();

      //   }

      //}
      //catch (...)
      //{

      //}

      return bOk;

   }


   bool os_context::browse_file_save(::property_set & set)
   {

      //::user::interaction* pinteraction = puiOwner->get_wnd();

      bool bOk = false;

      //try
      //{

      //   pinteraction->enable_window(false);

      //}
      //catch (...)
      //{

      //}

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileSaveDialog > pfilesave;

         // Create the FileSaveDialog object.
         HRESULT hr = pfilesave.CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            //COMDLG_FILTERSPEC rgSpec[] =
            //{
            // { L"CSV files", L"*.csv" },
            // { L"Text files", L"*.txt" },
            // { L"All files", L"*.*" },
            //};

            //pFileSave->SetFileTypes(3, rgSpec);



            //pFileSave->SetFileName(L"Twitter Automator Export");

            array < COMDLG_FILTERSPEC > rgSpec;

            array < wstring > wstraSpecs;

            ::generic::container::copy(wstraSpecs, set["file_filter_specs"].stra());

            array < wstring > wstraNames;

            ::generic::container::copy(wstraNames, set["file_filter_names"].stra());

            rgSpec.set_size(minimum(wstraSpecs.get_size(), wstraNames.get_size()));

            for (::collection::index i = 0; i < rgSpec.get_size(); i++)
            {

               rgSpec[i].pszName = wstraNames[i];

               rgSpec[i].pszSpec = wstraSpecs[i];

               //{ L"CSV files", L"*.csv" },
               //{ L"Text files", L"*.txt" },
               //{ L"All files", L"*.*" },

            }

            if (rgSpec.get_size() > 0)
            {

               pfilesave->SetFileTypes(unsigned int (rgSpec.get_size()), rgSpec.get_data());

            }

            if (set["default_file_extension"].get_length() > 0)
            {

               pfilesave->SetDefaultExtension(wstring(set["default_file_extension"]));

            }

            if (set["file_name"].get_length() > 0)
            {

               pfilesave->SetFileName(wstring(set["file_name"]));

            }

            if (set["folder"].get_length() > 0)
            {

               wstring wstr(set["folder"]);

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfilesave->SetFolder(psi);

               }

            }

            // Show the Save dialog box.
            hr = pfilesave->Show(nullptr);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfilesave->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["file_name"] = string(pwszFilePath);

                      bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      //try
      //{

      //   pinteraction->enable_window();

      //   pinteraction->order_top();

      //   pinteraction->display(e_display_normal, eXXX_activation_set_foreground);

      //   pinteraction->set_need_redraw();

      //   pinteraction->post_redraw();

      //}
      //catch (...)
      //{

      //}

      return bOk;

   }



   bool os_context::browse_folder( ::property_set & set)
   {

      //::user::interaction* pinteraction = puiOwner->get_wnd();

      bool bOk = false;

      //try
      //{

      //   pinteraction->enable_window(false);

      //}
      //catch (...)
      //{


      //}

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileOpenDialog > pfileopen;

         // Create the FileOpenDialog object.
         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            if (set["folder"].get_length() > 0)
            {

               wstring wstr(set["folder"]);

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            pfileopen->SetOptions(FOS_PICKFOLDERS);

            // Show the Open dialog box.
            hr = pfileopen->Show(nullptr);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfileopen->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["folder"] = string((PWSTR) pwszFilePath);

                     bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      //try
      //{

      //   pinteraction->enable_window();

      //   pinteraction->order_top();

      //   pinteraction->display(e_display_normal, XXXXe_activation_set_foreground);

      //   pinteraction->set_need_redraw();

      //   pinteraction->post_redraw();


      //}
      //catch (...)
      //{


      //}

      return bOk;

   }

   bool os_context::browse_file_or_folder(::property_set & set)
   {

      //::user::interaction* pinteraction = puiOwner->get_wnd();

      bool bOk = false;

      //try
      //{

      //   pinteraction->enable_window(false);

      //}
      //catch (...)
      //{


      //}

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileOpenDialog > pfileopen;

         // Create the FileOpenDialog object.
         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            if (set["folder"].get_length() > 0)
            {

               wstring wstr(set["folder"]);

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            pfileopen->SetOptions(FOS_PATHMUSTEXIST | FOS_PICKFOLDERS);

            // Show the Open dialog box.
            hr = pfileopen->Show(nullptr);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfileopen->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["path"] = string((PWSTR)pwszFilePath);

                     bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      //try
      //{

      //   pinteraction->enable_window();

      //   pinteraction->order_top();

      //   pinteraction->display(e_display_normal, XXXXe_activation_set_foreground);

      //   pinteraction->set_need_redraw();

      //   pinteraction->post_redraw();

      //}
      //catch (...)
      //{


      //}

      return bOk;


   }


   void os_context::list_process(::file::path_array & patha, unsigned_int_array & uaPid)
   {

      ASSERT(sizeof(unsigned int) == sizeof(unsigned int));

      get_all_processes(uaPid);

      patha.set_size(uaPid.get_count());

      for(::collection::index i = 0; i < uaPid.get_count(); i++)
      {

         patha[i] = get_process_path(uaPid[i]);

      }

   }


} // namespace windows


// CreateLink - Uses the Shell's IShellLink and IPersistFile interfaces
//              to create and store a shortcut to the specified object.
//
// Returns the result of calling the member functions of the interfaces.
//
// Parameters:
// pszPathObj  - Address of a buffer that contains the path of the object,

//                including the file name.
// pszPathLink - Address of a buffer that contains the path where the

//                Shell link is to be stored, including the file name.
// pszDesc     - Address of a buffer that contains a description of the

//                Shell link, stored in the Comment field of the link
//                properties.


HRESULT win_create_link(const ::wide_character * pszPathObj, const ::wide_character * pszPathLink, const ::wide_character * pszDesc, const ::wide_character * pszIconPath, int iIcon)

{

   HRESULT hres;

   IShellLinkW* psl;

   defer_co_initialize_ex(false);

   // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
   // has already been called.
   hres = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
   if (SUCCEEDED(hres))
   {
      IPersistFile* ppf;

      // set the path to the shortcut target and add the description.
      psl->SetPath(pszPathObj);

      psl->SetDescription(pszDesc);

      if (pszIconPath != nullptr && *pszIconPath != L'\0')

      {
         psl->SetIconLocation(pszIconPath, iIcon);

      }

      // Query IShellLink for the IPersistFile interface, used for saving the
      // shortcut in persistent storage.
      hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

      if (SUCCEEDED(hres))
      {
         //WCHAR wsz[MAX_PATH];

         // Ensure that the string is Unicode.
         //            MultiByteToWideChar(CP_ACP, 0, pszPathLink, -1, wsz, MAX_PATH);


         // Add code here to check return value from MultiByteWideChar
         // for success.

         // Save the link by calling IPersistFile::Save.
         hres = ppf->Save(pszPathLink, true);

         ppf->Release();
      }
      psl->Release();
   }
   return hres;

}


CLASS_DECL_APEX_WINDOWS void os_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
{

   wstring wstrObj(pathObj);
   wstring wstrLnk(pathLnk);
   wstring wstrDsc(strDesc);
   wstring wstrIco(pathIco);

   return hresult_to_estatus(win_create_link(wstrObj, wstrLnk, wstrDsc, wstrIco, iIcon));

}
