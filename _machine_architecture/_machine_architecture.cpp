#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

int main(void)
{
   USHORT processMachine = 0;
   USHORT nativeMachine = 0;

   if (!IsWow64Process2(GetCurrentProcess(),
      &processMachine,
      &nativeMachine))
   {
      puts("unknown");
      return 1;
   }

   switch (nativeMachine)
   {
   case IMAGE_FILE_MACHINE_ARM64:
      puts("arm64");
      break;

   case IMAGE_FILE_MACHINE_AMD64:
      puts("x64");
      break;

   case IMAGE_FILE_MACHINE_I386:
      puts("x86");
      break;

   default:
      puts("unknown");
      break;
   }

   return 0;
}
