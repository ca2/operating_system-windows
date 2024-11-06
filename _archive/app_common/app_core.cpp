#include "framework.h"
#include "aura/node/windows/windows.h"


CLASS_DECL_AURA int __win_main(::pointer<::aura::system>psystem,::windows::command * pmaininitdata);


extern "C" int app_core_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow, app_core & appcore)
{

   //MessageBox(nullptr, lpCmdLine, "msg", 0);

   __UNREFERENCED_PARAMETER(lpCmdLine);

   ::aura::system * psystem                     = g_pfn_create_system();

   // what could influence time before main?
   // cold start (never previously called program and its Dlls...)?
   psystem->m_dwMainStartTime                   = appcore.m_tickStart;

   ASSERT(hPrevInstance == nullptr);

   ::windows::command * pmaininitdata    = ___new ::windows::command;


   pmaininitdata->m_hInstance                   = hinstance;
   pmaininitdata->m_hPrevInstance               = hPrevInstance;
   pmaininitdata->m_strCommandLine              = lpCmdLine;
   pmaininitdata->m_nCmdShow                    = nCmdShow;


   int nReturnCode                          = __win_main(psystem, pmaininitdata);

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




