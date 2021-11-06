#include "framework.h"
#include "aura/node/windows/windows.h"


CLASS_DECL_AURA i32 __win_main(__pointer(::aura::system) psystem,::windows::command * pmaininitdata);

typedef bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;

extern "C" i32 app_common_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow, app_core & appcore)
{

   //MessageBox(nullptr, lpCmdLine, "msg", 0);

   __UNREFERENCED_PARAMETER(lpCmdLine);

   string strAppId = read_resource_as_string(nullptr, 2000, "APPID");

   if (strAppId.has_char())
   {

      string strLibrary = ::process::app_id_to_app_name(strAppId);

      HMODULE hmodule = ::LoadLibrary(strLibrary + ".dll");

      if (hmodule != nullptr)
      {


         PFN_DEFER_INIT defer_init = nullptr;



         if ((hmodule = ::GetModuleHandle("aura.dll")) != nullptr)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_core_init");

         }
         else if ((hmodule = ::GetModuleHandle("base.dll")) != nullptr)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_base_init");

         }
         else if ((hmodule = ::GetModuleHandle("axis.dll")) != nullptr)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_axis_init");

         }

         if (!defer_init())
         {

            return -3;

         }

      }

   }


   ::aura::system * psystem                     = g_pfn_create_system();

   // what could influence time before main?
   // cold start (never previously called program and its Dlls...)?
   psystem->m_dwMainStartTime                   = appcore.m_tickStart;

   ASSERT(hPrevInstance == nullptr);

   ::windows::command * pmaininitdata    = new ::windows::command;


   pmaininitdata->m_hInstance                   = hinstance;
   pmaininitdata->m_hPrevInstance               = hPrevInstance;
   pmaininitdata->m_strCommandLine              = lpCmdLine;
   pmaininitdata->m_nCmdShow                    = nCmdShow;


   i32 nReturnCode                          = __win_main(psystem, pmaininitdata);

   appcore.m_dwAfterApplicationFirstRequest     = psystem->m_dwAfterApplicationFirstRequest;

   try
   {

      delete psystem;

   }
   catch (...)
   {

   }

   psystem = nullptr;

 
   return nReturnCode;

}




