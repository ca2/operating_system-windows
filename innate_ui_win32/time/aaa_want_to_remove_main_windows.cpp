#include "framework.h"
#include "acme/platform/app_core.h"
#include "application.h"
#include "acme/os/_application.h"


//CLASS_DECL_ACME ::i32 main_windows(HINSTANCE hinstance, HINSTANCE hPrevInstance, ::i8 * pCmdLine, ::i32 nCmdShow)
//{
//
//   ::i32 iStatus = -1;
//
//   class aura_aura aura_aura;
//
//   {
//
////
////      ::i32 iResult = 0;
////
////#ifdef GET_COMMAND_LINE
////
////      ::i8* pszCommandLine = GET_COMMAND_LINE(argc, argv);
////
////#elif defined(MAIN_STRING)
////
////      ::i8* pszCommandLine = strdup(MAIN_STRING);
////
////#elif defined (_WIN32)
////
////      ::i8* pszCommandLine = _strdup("");
////
////#else
////
////      ::i8* pszCommandLine = strdup("");
////
////#endif
//
////#ifdef LINUX
////
////      br_init_set_symbol(br_init_get_symbol());
////
////#endif
//
////#ifdef ACID_APP
////
////      PFN_NEW_ACME_APPLICATION pfnNewAuraApplication = &get_acid_app;
////
////#else
////
////      PFN_NEW_ACME_APPLICATION pfnNewAuraApplication = (PFN_NEW_ACME_APPLICATION) ::GetProcAddress(hinstance, "new_aura_application");;
////
////#endif
//
////#ifdef ACID_LIBRARY
////
////      PFN_NEW_ACME_LIBRARY pfnNewLibrary = &get_acid_library;
////
////#else
////
////      PFN_NEW_ACME_LIBRARY pfnNewLibrary = nullptr;
////
////#endif
//
//      //if (pfnNewAuraApplication)
//      //{
//
//      //   pfnNewAuraApplication = 
//
//      //}
//
//      //if (!pauramain)
//      //{
//
//        // output_error_message("Please!!\n\nImplement entry function with the macro \n\n__main\n{\n\n\t<\"Main Body\">\n\n}\n\n." + e_message_box_icon_error);
//
//         //return -1;
//
//      //}
//
//      ::aura_main_struct mainstruct = {};
//
//      mainstruct.m_bConsole = false;
//      mainstruct.m_bDraw2d = true;
//      mainstruct.m_bUser = true;
//      mainstruct.m_bUserEx = true;
//      mainstruct.m_bShowApplicationInformation = false;
//
//      auto psystem = allocateø ::platform::system();
//
//      psystem->system_construct(&mainstruct, hinstance, hPrevInstance, pCmdLine, nCmdShow);
//
//      //pmaindata->m_pappcore = allocateø app_core(pmaindata);
//
//      if (!psystem->system_beg())
//      {
//
//         throw ::exception("The application didn't started.");
//
//      }
//
//      bool bOk = psystem->system_ini();
//
//      if (!bOk)
//      {
//
//         throw ::exception("The application didn't started. (2)");
//
//      }
//
//      psystem->system_start();
//
//      iStatus = psystem->system_run();
//
//      psystem->system_end();
//
//   }
//
//   return iStatus;
//
//}



