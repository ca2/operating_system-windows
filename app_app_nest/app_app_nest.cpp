#include "framework.h"



HANDLE g_hinstancePluginbase = nullptr;
void * g_pvoidPluginSystem = nullptr;
HANDLE g_hmutex = nullptr;


u32 plugin_container_app(const ::string & strChannel)
{

   ::plugin::system * psystem = new ::plugin::system(nullptr, nullptr);

   psystem->m_hinstance = ::GetModuleHandle(nullptr);

   ::set_thread(psystem);

   try
   {

      if(!psystem->pre_run())
      {

         return psystem->m_result.status();

      }

   }
   catch(...)
   {

      return -1;

   }

   //__start_core_system_main(psystem);

   psystem->begin();

   ::ca2plugin_container::application * papp = new ::ca2plugin_container::application(psystem, strChannel);

   papp->m_psession = psystem->m_psession;

   papp->m_psession = psystem->m_psession;

   papp->m_psession = psystem->m_psession;

   papp->get_application() = psystem->get_application();

   papp->get_application() = psystem;

   papp->system() = psystem;

   papp->system() = psystem;

   papp->m_hinstance = psystem->m_hinstance;

   papp->m_psession->m_psession = psystem->get_platform(0, nullptr);

   papp->create_host();

   try
   {

      if(!papp->pre_run())
      {

         return papp->m_result.status();

      }

   }
   catch(...)
   {

      return -61;

   }

   papp->main();

   auto estatus = papp->m_result.status();

   ExitProcess((unsigned int) estatus);

   return estatus;

}


i32 __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow)
{

   __UNREFERENCED_PARAMETER(lpCmdLine);

   if(!defer_core_init())
   {

      return -6;

   }


   //if(acmefile()->exists("C:\\ca2\\config\\plugin\\npca2_beg_debug_box.txt"))
   //{

   //   debug_box("app_app_nest boxmain NP_Initialize","app_app_nest box",MB_OK);

   //}

   i32 nReturnCode = 0;

   string strChannel(get_command_line_parameter(string(::GetCommandLineW()), "channel"));

   g_hmutex = ::CreateMutexW(nullptr, false, wstring("Global\\::ca2::fontopus::app_app_nest::" + strChannel));

   if (::GetLastError() == ERROR_ALREADY_EXISTS)
   {

      return -1;

   }

   if (acmefile()->exists("C:\\ca2\\config\\system\\beg_debug_box.txt"))
   {

      debug_box("app_app_nest", "app_app_nest", MB_OK);

   }

   nReturnCode = plugin_container_app(strChannel);

   try
   {

      defer_core_term();

   }
   catch (...)
   {

   }


   return nReturnCode;

}


extern "C" i32 WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow)
{

   return __win_main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

}














