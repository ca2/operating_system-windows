#include "../spalib/spalib.h"

HANDLE g_hmutexBoot = nullptr;
extern std::string g_strId;
extern std::string g_strVersion;
//stra g_straRestartCommandLine;
HWND g_hwndMessage = nullptr;
//MSG g_msg;

void parse_installer(const ::scoped_string & scopedstr);
bool parse_installer_start(const ::scoped_string & scopedstr);
SPALIB_API std::string read_resource_as_string(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);


int start();

ATOM installer_RegisterClass(HINSTANCE hInstance);

LRESULT CALLBACK installer_WndProc(HWND hWnd,::enum_message emessage, ::wparam wparam, ::lparam lparam);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   spa_set_admin(false);

   g_hmutexBoot = nullptr;
   SECURITY_ATTRIBUTES MutexAttributes;
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
   MutexAttributes.nLength = sizeof( MutexAttributes );
   MutexAttributes.bInheritHandle = false; // object uninheritable
   // declare and initialize a security descriptor
   SECURITY_DESCRIPTOR SD;
   BOOL bInitOk = InitializeSecurityDescriptor(
                     &SD,
                     SECURITY_DESCRIPTOR_REVISION );
   if ( bInitOk )
   {
      // give the security descriptor a Null Dacl
      // done using the  "true, (PACL)nullptr" here
      BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                            true,
                                            (PACL)nullptr,
                                            false );
      if ( bSetOk )
      {
         // Make the security attributes int_point
         // to the security descriptor
         MutexAttributes.lpSecurityDescriptor = &SD;
         g_hmutexBoot = ::CreateMutex(&MutexAttributes, false, "Global\\ca2::fontopus::ca2_spa_boot::7807e510-5579-11dd-ae16-0800200c7784");
         if(::GetLastError() == ERROR_ALREADY_EXISTS)
         {
            ::OutputDebugString("another instance of spa is already running");
            return -202;
         }
      }
      else
      {
         ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
         return -200;
      }
   }
   else
   {
      ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
      return -201;
   }

   prepare_small_bell();

   if(!installer_RegisterClass(hInstance))
      return -1;

   g_hwndMessage = ::CreateWindowExA(0, "TeDigoS", "ca2::fontopus::installer:callback_window", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);

   DWORD dw = GetLastError();
   if(g_hwndMessage == nullptr)
      return -1;

   wchar_t * lpwstr = ::GetCommandLineW();
   int numargs;
   int numchars;
   wparse_cmdline(
      lpwstr, 
      nullptr, 
      nullptr,
      &numargs,
      &numchars);

   wchar_t * pszCmdLine = ___new WCHAR[numchars];
   wchar_t ** argv = ___new WCHAR*[numargs];

   wparse_cmdline(
      lpwstr, 
      argv, 
      pszCmdLine,
      &numargs,
      &numchars);

   if(numargs >= 2)
   {
      std::string str(unsigned char(argv[1]));
      if(parse_installer_start(str.c_str()))
      {
         return start();
      }
   }

   std::string strDir = ::dir::app_app();
   std::string strSp = ::path::app_appadmin();
   std::string strSpDest;

//   STARTUPINFO si;
//   PROCESS_INFORMATION pi;
   SHELLEXECUTEINFO sei;
   memory_set(&sei, 0, sizeof(sei));
   sei.cbSize = sizeof(sei);
   sei.fMask = SEE_MASK_NOCLOSEPROCESS;
   sei.nShow = SW_HIDE;
   std::string strParameters;

   if(numargs >= 2)
   {
      std::string str(unsigned char(argv[1]));
      int i = str.find("starter_start=");
      if(i != std::string::npos)
      {
         int iStart = i + strlen("starter_start=");
         i = str.find(" ", i);
         if(i != std::string::npos)
         {
            g_strId = str.substr(iStart, i - iStart);
         }
         else
         {
            g_strId = str.substr(iStart);
         }
         strParameters = "starter_start=";
         strParameters += g_strId;
         strParameters += " background";
      }
      else
      {
         std::string str(unsigned char(argv[1]));
         strParameters = "\""+ str + "\"";
         parse_installer(str.c_str());
      }
   }
   
   sei.lpDirectory = strDir.c_str();
   sei.lpFile = strSp.c_str();
   sei.lpParameters =  strParameters.c_str();

   CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

   if(!::ShellExecuteEx(&sei))
   {
      return 1;
   }

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(sei.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(100);
      if(PeekMessage(&g_msg, nullptr, 0, 0xffffffffu, PM_REMOVE))
      {
   //		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
   //		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
   //		}
	   }

      i++;
   }
   std::string strInstall;

   /*std::string strUrl;
   std::string strApp;
   strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&atom=";
   strUrl += g_strId;
   strUrl += "&key=application";
   int iRetry = 0;
   while(true)
   {
      strApp = ms_get(strUrl.c_str());
      if(strApp.length() > 0)
         break;
      iRetry++;
      if(iRetry > 30)
         break;
      Sleep5000;
   }
   if(iRetry > 30)
   {
      return 1;
   }*/

   int iCount = 20;
   for(int i = 0; i < iCount; i++)
   {
	   if(PeekMessage(&g_msg, nullptr, 0, 0xffffffffu, PM_REMOVE))
	   {
   //		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
   //		{
		   TranslateMessage(&g_msg);
		   DispatchMessage(&g_msg);
   //		}
	   }
      Sleep(100);
   }

   return start();
}




bool file_system()->exists(const ::string & path1)
{
   DWORD dwFileAttributes = ::GetFileAttributes(path1);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;
}



//void parse_installer(XNode & node)
//{
//   if(node.name == "spa" && node.childs.size() > 0)
//   {
//      LPXNode lpnode = &node;
//      for(unsigned int u = 0; u < lpnode->childs.size(); u++)
//      {
//         if(lpnode->childs[u]->name == "index")
//         {
//            if(lpnode->childs[u]->GetAttr("start") != nullptr)
//            {
//               if(std::string(lpnode->childs[u]->GetAttrValue("start")).length() > 0)
//               {
//                  g_strId= std::string(lpnode->childs[u]->GetAttrValue("start"));
//               }
//            }
//         }
//      }
//   }
//}
//
//void parse_installer(const ::scoped_string & scopedstr)
//{
//   XNode node;
//   node.Load(file::get_contents(psz).c_str());
//   parse_installer(node);
//}
//
//bool parse_installer_start(XNode & node)
//{
//   int iOkCount = 0;
//   std::string strInstalledBuild;
//   std::string strRequestedBuild;
//   if(node.name == "spa" && node.childs.size() > 0)
//   {
//      LPXNode lpnode = &node;
//      for(unsigned int u = 0; u < lpnode->childs.size(); u++)
//      {
//         if(lpnode->childs[u]->name == "index")
//         {
//            if(lpnode->childs[u]->GetAttr("start") != nullptr)
//            {
//               if(std::string(lpnode->childs[u]->GetAttrValue("start")).length() > 0)
//               {
//                  g_strId = std::string(lpnode->childs[u]->GetAttrValue("start"));
//                  iOkCount++;
//               }
//               else
//               {
//                  return false;
//               }
//            }
//            else
//            {
//               return false;
//            }
//         }
//         else
//         {
//            return false;
//         }
//         if(lpnode->childs[u]->GetAttr("build") != nullptr)
//         {
//            if(std::string(lpnode->childs[u]->GetAttrValue("build")).length() > 0)
//            {
//               strInstalledBuild = file::get_contents("C:\\ca2\\stage\\app\\build.txt");
//               if(strInstalledBuild.length() <= 0)
//                  return false;
//               strRequestedBuild = std::string(lpnode->childs[u]->GetAttrValue("build")).c_str();
//               if(strRequestedBuild.length() <= 0)
//                  return false;
//               iOkCount++;
//            }
//            else
//            {
//               return false;
//            }
//         }
//         else
//         {
//            return false;
//         }
//      }
//   }
//   if(iOkCount < 3)
//      return false;
//   if(strRequestedBuild != strInstalledBuild)
//      return false;
//   if(!is_installed(g_strId.c_str()))
//      return false;
//   return true;
//}
//
//
//
//bool parse_installer_start(const ::scoped_string & scopedstr)
//{
//   XNode node;
//   node.Load(file::get_contents(psz).c_str());
//   return parse_installer_start(node);
//}
//
//void trace(const ::scoped_string & scopedstr)
//{
//   printf("%s", psz);
//}

//int start()
//{
//   STARTUPINFO si;
//   PROCESS_INFORMATION pi;
////   SHELLEXECUTEINFO sei;
//   std::string strInstall;
//   std::string strCommand = file_system()->as_string("C:\\ca2\\machine\\on_after_spaadmin.txt");
//
//   if(strCommand.length() > 0)
//   {
//      ::DeleteFileA("C:\\ca2\\machine\\on_after_spaadmin.txt");
//      int iStart = 0;
//      while(true)
//      {
//         int iFind = strCommand.find(';', iStart);
//         if(iFind < 0)
//            strInstall = strCommand.substr(iStart);
//         else
//            strInstall = strCommand.substr(iStart, iFind - iStart);
//         memory_set(&si, 0, sizeof(si));
//         memory_set(&pi, 0, sizeof(pi));
//         if(!::CreateProcess(nullptr, (LPSTR)  strInstall.c_str(),
//            nullptr, nullptr, false, 0, nullptr, nullptr,
//            &si, &pi))
//         {
//         }
//         if(iFind < 0)
//            break;
//         iStart = iFind + 1;
//      }
//   }
//   else if(g_strId == "_set_windesk")
//   {
//      strInstall = "C:\\ca2\\" + g_strVersion + "\\stage\\basis\\";
//      strInstall += "winservice_1app.exe";
//      memory_set(&si, 0, sizeof(si));
//      memory_set(&pi, 0, sizeof(pi));
//      if(!::CreateProcess(nullptr, (LPSTR)  strInstall.c_str(),
//         nullptr, nullptr, false, 0, nullptr, nullptr,
//         &si, &pi))
//      {
//         return 1;
//      }
//   }
//   else
//   {
//      strInstall = "C:\\ca2\\" + g_strVersion + "\\stage\\basis\\";
//      strInstall += "bergedgeapp.exe";
//      strInstall += " : ";
//      strInstall += "app=";
//      strInstall += g_strId;
//      memory_set(&si, 0, sizeof(si));
//      memory_set(&pi, 0, sizeof(pi));
//      if(!::CreateProcess(nullptr, (LPSTR)  strInstall.c_str(),
//         nullptr, nullptr, false, 0, nullptr, nullptr,
//         &si, &pi))
//      {
//         return 1;
//      }
//   }
//   for(unsigned int u = 0; u < g_straRestartCommandLine.size(); u++)
//   {
//      std::string & str = g_straRestartCommandLine.at(u);
//      memory_set(&si, 0, sizeof(si));
//      memory_set(&pi, 0, sizeof(pi));
//      if(!::CreateProcess(nullptr,(LPSTR)str.c_str(),nullptr,nullptr,false,0,nullptr,nullptr,&si,&pi))
//      {
//         trace(("failed to create process " + str).c_str());
//      }
//      else
//      {
//         trace(("successfully created process " + str).c_str());
//      }
//   }
//   defer_play_small_bell();
//   return 0;
//}




  //FUNCTION: MyRegisterClass()

  //PURPOSE: Registers the window class.

  //COMMENTS:

  //  This function and its usage are only necessary if you want this code
  //  to be compatible with Win32 systems prior to the 'RegisterClassEx'
  //  function that was added to Windows 95. It is important to call this function
  //  so that the application will get 'well formed' small icons associated
  //  with it.

ATOM installer_RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			   = 0;
	wcex.lpfnWndProc	   = installer_WndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance		   = hInstance;
	wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STORE_CA2_SPA));
	wcex.hCursor		   = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_STORE_CA2_SPA);
   wcex.lpszMenuName	   = nullptr;
	wcex.lpszClassName	= "TeDigoS";
	wcex.hIconSm		   = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  e_message_destroy	- post a quit message and return
//
//
LRESULT CALLBACK installer_WndProc(HWND hWnd, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
{
	switch (message)
	{
   case WM_COPYDATA:
      {
         COPYDATASTRUCT * pcds = (COPYDATASTRUCT *) lParam;
         if(pcds->dwData == 15112000)
         {
            std::string str((const ::string &) pcds->lpData, pcds->cbData);
            g_straRestartCommandLine.decode_v16(str.c_str());
         }
      }
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
	return 0;
}
