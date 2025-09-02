#include "framework.h"
#include "aura/inline/_app.inl"
#include <Shlobj.h>
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include <string.h>

#include <psapi.h>

#define WINDOWS
#include <tlhelp32.h>

void reg_delete_tree_dup(HKEY hkey, const ::scoped_string & scopedstrName);

class removal :
   public ::aura::application
{
public:


   HANDLE                     m_hmutex_app_removal;

   char *                     m_modpath;
   char *                     m_pszDllEnds;
   UINT *                     m_dwaProcess;
   INT                        m_iSizeProcess;
   HMODULE *                  m_hmodulea;
   INT                        m_iSizeModule;
   bool                       m_bInstallerInstalling;
   HINSTANCE                  m_hinstance;

   removal(::particle * pparticle);

   virtual ~removal();

   bool is_user_using(const ::scoped_string & scopedstrDll);

   INT cube_run(const ::scoped_string & scopedstr);

   bool are_there_user_files_in_use();

   bool is_user_using(UINT processid, const ::scoped_string & scopedstrDll);

   virtual void     run() override;

   virtual bool destroy();


   virtual void system(const ::scoped_string & scopedstrCmd);

   virtual ::file::path get_known_folder_dir(const KNOWNFOLDERID & rfid, const ::scoped_string & scopedstr);


   virtual void rmdir(const ::scoped_string & scopedstrDir);

   virtual void rmdir_n_v(const ::scoped_string & scopedstrDir);

   virtual void g_n_rmdir_n_v(const KNOWNFOLDERID & rfid, const ::scoped_string & scopedstrDir);

};


//// if MSVC CRT is used
//extern "C" int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
//{
//
//   __UNREFERENCED_PARAMETER(lpCmdLine);
//
//   if(!defer_aura_init())
//   {
//
//      return -1;
//
//   }
//
//   removal * premoval = ___new removal();
//
//   int iRet = ::app_main(premoval, hInstance,hPrevInstance,lpCmdLine,nCmdShow);
//
//   defer_aura_term();
//
//   return iRet;
//
//
//
//}


::aura::application * get_acid_app(::particle * pparticle)
{

   return ___new removal(pobject);

}


removal::removal(::particle * pparticle) :
   ::object(pobject),
   ::thread(pobject),
   ::aura::application(pobject)
{
   m_hinstance             = ::GetModuleHandleA(nullptr);
   m_hmutex_app_removal  = nullptr;
   m_modpath               = nullptr;
   m_pszDllEnds            = nullptr;
   m_dwaProcess            = nullptr;
   m_iSizeProcess          = 0;
   m_hmodulea              = nullptr;
   m_iSizeModule           = 0;
   m_bInstallerInstalling  = false;
   //g_pstraTrace            = nullptr;
}

removal::~removal()
{
}


::file::path removal::get_known_folder_dir(const KNOWNFOLDERID & rfid, const ::scoped_string & scopedstr)
{

   wchar_t * buf = nullptr;

   SHGetKnownFolderPath(rfid, 0, nullptr, &buf);

   ::file::path str(buf);

   CoTaskMemFree(buf);

   return str /lpcsz;

}




void removal::system(const ::scoped_string & scopedstrCmd)
{

   psystem->process().synch(pszCmd);


   /*STARTUPINFO si;
   PROCESS_INFORMATION pi;

   ZeroMemory(&si, sizeof(si));
   si.cb = sizeof(si);
   ZeroMemory(&pi, sizeof(pi));

   si.dwFlags |= STARTF_USESHOWWINDOW;
   si.wShowWindow = SW_HIDE;

   if (CreateProcess(nullptr, (char *) pszCmd, nullptr, nullptr, false, CREATE_NO_WINDOW | CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
   {
       WaitForSingleObject(pi.hProcess, INFINITE);
       CloseHandle(pi.hProcess);
       CloseHandle(pi.hthread);
   }*/

}


void removal::rmdir(const ::scoped_string & scopedstrDir)
{

   system(("cmd.exe /C rmdir /S /Q \"" + string(pszDir) + "\"").c_str());

}


void removal::rmdir_n_v(const ::scoped_string & scopedstrDir)
{

   string str(pszDir);
   rmdir(str.c_str());

   str.replace(":", "");

   string str2 = get_known_folder_dir(FOLDERID_LocalAppData, "Microsoft\\Windows\\Temporary Internet Files\\Virtualized")/  str;
   rmdir(str2.c_str());


   str2 = get_known_folder_dir(FOLDERID_LocalAppData,"Microsoft\\Windows\\INetCache\\Virtualized") / str;
   rmdir(str2.c_str());

}


void removal::g_n_rmdir_n_v(const KNOWNFOLDERID & rfid, const ::scoped_string & scopedstrDir)
{

   string strDir = get_known_folder_dir(rfid,pszDir);

   rmdir_n_v(strDir.c_str());

}




void     removal::run()
{


   m_hmutex_app_removal = ::CreateMutexW(nullptr, false, wstring("Global\\::ca2::fontopus::ccca2_spa_app_removal::7807e510-5579-11dd-ae16-0800200c7784"));
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      os_message_box(nullptr, "ca2 app.removal.exe is already running.\n\nPlease wait for app.removal to finish or close it - using Task Manager - Ctrl+Shift+ESC - to continue.", "app_app_admin.exe is running!", ::user::e_message_box_icon_exclamation);
      m_result.add(error_failed);
      return error_failed;
   }

   wchar_t szFile[MAX_PATH * 8];

   ::GetModuleFileName(nullptr, szFile, sizeof(szFile) / sizeof(szFile[0]));

   ::file::path strTargetDir = get_known_folder_dir(FOLDERID_ProgramFilesX86,"ca2.app.removal");

   dir().create(strTargetDir.c_str());

   wstring wstrTarget = strTargetDir / "app.removal.exe";

   if(::CopyFileW(szFile,wstrTarget.c_str(),true))
   {
      INT i = ::MessageBox(nullptr,wstring("Do you want to place a shortcut to ca2 app.removal in Desktop?\n\nProgram has already been copied to Program Files Folder."),wstring("app.removal installation"),MB_ICONQUESTION | MB_YESNOCANCEL);

      if (i == IDCANCEL)
      {
         m_result.add(error_failed);
         return error_failed;
      }

      if(i == IDYES)
      {
         string strLink= get_known_folder_dir(FOLDERID_Desktop,"ca2 app.removal Tool.lnk");
         wstring wstrLink(strLink);
         // create shortcurt;
         os_create_link(wstrTarget.c_str(), wstrLink.c_str(), L"ca2 app.removal Tool", wstrTarget.c_str(), 0);
      }
   }


   system("taskkill /F /IM app.exe");
   system("taskkill /F /IM app_app_admin.exe");
   system("taskkill /F /IM app_app_nest.exe");

   if(file_system()->exists("C:\\ca2\\config\\app-removal\\kill_browsers.txt") || file_system()->exists("C:\\ca2\\config\\app-removal\\kill_plugin_container.txt"))
   {

      system("taskkill /F /IM plugin-container.exe");

   }

   if(file_system()->exists("C:\\ca2\\config\\app-removal\\kill_browsers.txt") || file_system()->exists("C:\\ca2\\config\\app-removal\\kill_ie.txt"))
   {

      system("taskkill /F /IM iexplore.exe");

   }

   if(file_system()->exists("C:\\ca2\\config\\app-removal\\kill_browsers.txt") || file_system()->exists("C:\\ca2\\config\\app-removal\\kill_firefox.txt"))
   {

      system("taskkill /F /IM firefox.exe");

   }

   string strOnlyDrives = file_system()->as_string("C:\\ca2\\config\\app-removal\\only_drives.txt");
   string_array_base straDrives;
   if(strOnlyDrives.has_character())
   {
      straDrives.explode(",",strOnlyDrives);
   }

   g_n_rmdir_n_v(FOLDERID_ProgramFilesX86, "ca2");
   g_n_rmdir_n_v(FOLDERID_ProgramFiles,"ca2");

   if(straDrives.has_elements())
   {
      for(::collection::index i = 0; i < straDrives.get_count(); i++)
      {
         g_n_rmdir_n_v(FOLDERID_ProgramData,"ca2\\_" + straDrives[i]);
      }
   }
   else
   {
      g_n_rmdir_n_v(FOLDERID_ProgramData,"ca2");
   }

   g_n_rmdir_n_v(FOLDERID_LocalAppData, "VirtualStore\\Program Files (x86)\\ca2");
   g_n_rmdir_n_v(FOLDERID_LocalAppData,"VirtualStore\\Program Files\\ca2");
   if(straDrives.has_elements())
   {
      for(::collection::index i = 0; i < straDrives.get_count(); i++)
      {
         g_n_rmdir_n_v(FOLDERID_LocalAppData,"VirtualStore\\ProgramData\\ca2\\_" + straDrives[i]);
      }
   }
   else
   {
      g_n_rmdir_n_v(FOLDERID_LocalAppData,"VirtualStore\\ProgramData\\ca2");
   }

   if(straDrives.has_elements())
   {
      for(::collection::index i = 0; i < straDrives.get_count(); i++)
      {

         string strCa2 = "ca2\\_" + straDrives[i];

         g_n_rmdir_n_v(FOLDERID_Profile,strCa2);
         g_n_rmdir_n_v(FOLDERID_LocalAppDataLow,strCa2);
         g_n_rmdir_n_v(FOLDERID_RoamingAppData,strCa2);
         g_n_rmdir_n_v(FOLDERID_LocalAppData,strCa2);

         string strCore = "aura\\_" + straDrives[i];

         g_n_rmdir_n_v(FOLDERID_LocalAppDataLow,strCore);
         g_n_rmdir_n_v(FOLDERID_Profile,strCore);
         g_n_rmdir_n_v(FOLDERID_RoamingAppData,strCore);
         g_n_rmdir_n_v(FOLDERID_RoamingAppData,strCore);
      }
   }
   else
   {
      g_n_rmdir_n_v(FOLDERID_Profile,"ca2");
      g_n_rmdir_n_v(FOLDERID_LocalAppDataLow,"ca2");
      g_n_rmdir_n_v(FOLDERID_RoamingAppData,"ca2");
      g_n_rmdir_n_v(FOLDERID_LocalAppData,"ca2");

      g_n_rmdir_n_v(FOLDERID_LocalAppDataLow,"aura");
      g_n_rmdir_n_v(FOLDERID_Profile,"aura");
      g_n_rmdir_n_v(FOLDERID_RoamingAppData,"aura");
      g_n_rmdir_n_v(FOLDERID_RoamingAppData,"aura");
   }

   ::DeleteFileW(L"C:\\Windows\\Downloaded Program Files\\iexca2.dll");
   ::DeleteFileW(L"C:\\Windows\\Downloaded Program Files\\iexca2.inf");
   ::DeleteFileW(L"C:\\Windows\\Downloaded Program Files\\app_app_admin.exe");

   ::reg_delete_tree_dup(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\MozillaPlugins\\@ca2.cc/npca2");
   ::reg_delete_tree_dup(HKEY_CLASSES_ROOT, "Wow6432Node\\CLSID\\{CA212000-2000-2000-A861-F8AA2A7AEE4B}");
   ::reg_delete_tree_dup(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins\\@ca2.cc/npca2");
   ::reg_delete_tree_dup(HKEY_CLASSES_ROOT, "CLSID\\{CA212000-2000-2000-A861-F8AA2A7AEE4B}");

   ::reg_delete_tree_dup(HKEY_CLASSES_ROOT, "ca2os.ca2.fontopus.iexca2");
   ::reg_delete_tree_dup(HKEY_CLASSES_ROOT, "ca2os.ca2.fontopus.iexca2.2");
   ::reg_delete_tree_dup(HKEY_CLASSES_ROOT, "ca2_installer_file");

   //message_box(nullptr, "Hope Helped!", "Hope Helped!", ::user::e_message_box_icon_information);


   os_message_box(nullptr, "app-removal has finished cleaning ca2 directories.", "ca2 app-removal",::user::e_message_box_icon_information);


   return ::success;

}


// non-thread safe
bool removal::is_user_using(UINT processid, const ::scoped_string & scopedstrDll)
{

   HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
   MODULEENTRY32 me32;
   bool bFound = false;

   hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, processid );
   if( hModuleSnap == INVALID_HANDLE_VALUE )
   {
      return false;
   }

   me32.dwSize = sizeof(MODULEENTRY32);

   if(!Module32First(hModuleSnap, &me32))
   {
      ::CloseHandle(hModuleSnap);
      return false;
   }

   strcpy(m_pszDllEnds, "\\");
   ansi_concatenate(m_pszDllEnds, pszDll);

   do
   {
      if(ansi_ends_ci(string(me32.szModule), m_pszDllEnds) || _stricmp(string(me32.szModule), pszDll) == 0)
      {
         bFound = true;
         break;
      }

   }
   while(Module32Next(hModuleSnap, &me32));

   ::CloseHandle( hModuleSnap );
   return bFound;

}

// non-thread safe
bool removal::is_user_using(const ::scoped_string & scopedstrDll)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
   if(hProcessSnap == INVALID_HANDLE_VALUE)
   {
      return false;
   }

   pe32.dwSize = sizeof(PROCESSENTRY32);

   if(!Process32First(hProcessSnap, &pe32))
   {
      ::CloseHandle(hProcessSnap);
      return false;
   }

   bool bUsing = false;
   do
   {
      if(is_user_using(pe32.th32ProcessID, pszDll))
      {
         bUsing = true;
         break;
      }
   }
   while(Process32Next(hProcessSnap, &pe32));

   ::CloseHandle(hProcessSnap);

   return bUsing;

}




bool removal::are_there_user_files_in_use()
{
#ifdef X86
   if(is_user_using(dir().install()/"stage\\x86\\msvcp110d.dll"))
      return true;
   if(is_user_using(dir().install()/"stage\\x86\\msvcr110d.dll"))
      return true;
   if(is_user_using(dir().install()/"stage\\x86\\ca.dll"))
      return true;
   if(is_user_using(dir().install()/"stage\\x86\\ca2.dll"))
      return true;
   if(is_user_using(dir().install()/"stage\\x86\\ca2.dll"))
      return true;
#else
   if(is_user_using(dir().install() / "stage\\x64\\msvcp110d.dll"))
      return true;
   if(is_user_using(dir().install() / "stage\\x64\\msvcr110d.dll"))
      return true;
   if(is_user_using(dir().install() / "stage\\x64\\ca.dll"))
      return true;
   if(is_user_using(dir().install() / "stage\\x64\\ca2.dll"))
      return true;
   if(is_user_using(dir().install() / "stage\\x64\\ca2.dll"))
      return true;
#endif
   return false;
}


bool removal::destroy()
{

   return true;

}





