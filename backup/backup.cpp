#include "framework.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, unsigned int dwReason, LPVOID lpReserved)
{


   __UNREFERENCED_PARAMETER(hInstance);
   __UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::OutputDebugStringW(L"::ca2:: backup.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::OutputDebugStringW(L"::ca2:: backup.dll :: terminating!\n");


   }


   return 1;   // ok


}


