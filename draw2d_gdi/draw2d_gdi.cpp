#include "framework.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, u32 dwReason, LPVOID lpReserved)
{

   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::OutputDebugStringW(L"::aura:: draw2d_gdi.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::OutputDebugStringW(L"::aura:: draw2d_gdi.dll :: terminating!\n");

   }

   return 1;   // ok

}







static ::mutex * s_pmutex = nullptr;

::mutex & draw2d_gdi_mutex()
{

   return *s_pmutex;

}


void init_draw2d_gdi_mutex(::particle * pparticle)
{

   s_pmutex = ___new ::mutex();

}
