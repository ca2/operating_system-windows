#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../source/app/acme/memory/diagnostics.h"

static const char *log_path;
static void check(unsigned long long bytes, unsigned long long count)
{
   ca2_memory_diagnostics_snapshot();
   FILE *f=fopen(log_path,"rb");
   if (!f) abort();
   char line[4096], last[4096]={}, expected[128];
   while (fgets(line,sizeof(line),f)) if (!strncmp(line,"tick=",5)) strcpy(last,line);
   fclose(f);
   sprintf(expected,"live_bytes=%llu live_count=%llu ",bytes,count);
   if (!strstr(last,expected)) { fprintf(stderr,"Expected %s, got %s",expected,last); abort(); }
}
static DWORD WINAPI worker(void *)
{
   for (unsigned i=0;i<2000;++i) {
      void *p=HeapAlloc(GetProcessHeap(),0,128);
      ca2_memory_diagnostics_allocate(p,128,"test worker");
      ca2_memory_diagnostics_free(p);
      HeapFree(GetProcessHeap(),0,p);
   }
   return 0;
}
int main(int argc,char **argv)
{
   if (argc!=2) return 2;
   log_path=argv[1];
   SetEnvironmentVariableA("CA2_MEMORY_DIAGNOSTICS_LOG",log_path);
   void *p=(void *)0x1000;
   SetLastError(1234);
   ca2_memory_diagnostics_allocate(p,100,"test allocation");
   if (GetLastError()!=1234) abort();
   check(100,1);
   ca2_memory_diagnostics_reallocate(p,nullptr,200); // Failed realloc retains the old record.
   check(100,1);
   ca2_memory_diagnostics_reallocate(p,p,200);
   check(200,1);
   ca2_memory_diagnostics_reallocate(p,(void *)0x2000,300);
   check(300,1);
   ca2_memory_diagnostics_free((void *)0x2000);
   check(0,0);
   // Force a hash collision chain, remove its middle, and reuse the tombstone.
   ca2_memory_diagnostics_allocate((void *)0x10000,10);
   ca2_memory_diagnostics_allocate((void *)0x210000,20);
   ca2_memory_diagnostics_allocate((void *)0x410000,30);
   ca2_memory_diagnostics_free((void *)0x210000);
   ca2_memory_diagnostics_allocate((void *)0x610000,40);
   ca2_memory_diagnostics_free((void *)0x410000);
   check(50,2);
   ca2_memory_diagnostics_free((void *)0x10000);
   ca2_memory_diagnostics_free((void *)0x610000);
   check(0,0);
   HANDLE threads[4];
   for(unsigned i=0;i<4;++i) threads[i]=CreateThread(nullptr,0,worker,nullptr,0,nullptr);
   if(WaitForMultipleObjects(4,threads,TRUE,30000)!=WAIT_OBJECT_0) abort();
   for(auto thread:threads) CloseHandle(thread);
   check(0,0);
   puts("PASS: allocation/free, failed/in-place/moved realloc, collisions, error preservation, concurrency");
   return 0;
}
