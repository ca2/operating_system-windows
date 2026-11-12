#include <windows.h>
#include <dbghelp.h>
#include <cstring>
#include <cstdio>
#ifdef FORCE_XP_FALLBACK
FARPROC WINAPI xp_lookup(HMODULE module, LPCSTR name) {
 if(!strcmp(name,"GetThreadId")||!strcmp(name,"GetCurrentProcessorNumber")||!strcmp(name,"SymRefreshModuleList"))return nullptr;
 return GetProcAddress(module,name);
}
#define GetProcAddress xp_lookup
#endif
#define WINDOWS_XP
#include "acme/operating_system/windows/windows_xp_compat.h"
#ifdef FORCE_XP_FALLBACK
#undef GetProcAddress
#endif
DWORD WINAPI worker(void*) { Sleep(200);return 0; }
int main(){
 if(ca2_xp_get_thread_id(GetCurrentThread())!=GetCurrentThreadId())return 1;
 DWORD id=0;HANDLE thread=CreateThread(nullptr,0,worker,nullptr,0,&id);if(!thread)return 2;
 if(ca2_xp_get_thread_id(thread)!=id)return 3;
 WaitForSingleObject(thread,INFINITE);CloseHandle(thread);
 if(ca2_xp_get_thread_id(nullptr)!=0 || GetLastError()!=ERROR_INVALID_HANDLE)return 4;
#ifdef FORCE_XP_FALLBACK
 if(ca2_xp_current_processor_index()!=-1)return 5;
#else
 if(ca2_xp_current_processor_index()<0)return 5;
#endif
 ca2_xp_is_light_theme();
 HANDLE process=GetCurrentProcess();if(!SymInitialize(process,nullptr,TRUE))return 6;
 if(!ca2_xp_refresh_module_list(process))return 7;
 if(!SymCleanup(process))return 8;
 puts("PASS: XP adapters (thread IDs, invalid handles, processor, theme, DbgHelp refresh)");return 0;
}
