#include "framework.h"
#include "acme/operating_system.h"


static HANDLE g_hMainThread = nullptr;
static itask g_iMainThread = -1;

void set_main_hthread(htask htask)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_hMainThread = (HANDLE) htask;

}


void set_main_ithread(itask itask)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_iMainThread = itask;

}


htask get_main_hthread()
{

   return (htask) g_hMainThread;

}


itask get_main_ithread()
{

   return (itask) g_iMainThread;

}


htask current_htask()
{

   return (htask) ::GetCurrentThread();

}


itask current_itask()
{

   return (itask) ::GetCurrentThreadId();

}



bool on_init_timer_thread()
{

   return true;

}



