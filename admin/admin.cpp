#pragma once


#include "platform/app_core/app_core.h"


BEGIN_EXTERN_C

i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, i32 nCmdShow)
{

   if(!defer_core_init())
      return -1;

   int iRet = app_core_main(hinstance,hPrevInstance,nullptr,nCmdShow);

   defer_core_term();

   return iRet;

}

END_EXTERN_C
