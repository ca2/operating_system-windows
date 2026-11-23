#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <string.h>
static int attempt(const wchar_t *path, DWORD flags, const char *label)
{
   HMODULE module;
   DWORD error;
   SetLastError(0);
   module = LoadLibraryExW(path, NULL, flags);
   error = module ? 0 : GetLastError();
   printf("%s: %s (error=%lu)\n", label, module ? "SUCCESS" : "FAILED", (unsigned long)error);
   fflush(stdout);
   if (module) FreeLibrary(module);
   return module != NULL;
}
int main(int argc, char **argv)
{
   wchar_t input[MAX_PATH], full[MAX_PATH], extended[MAX_PATH+4];
   DWORD length;
   const char *name = argc > 1 ? argv[1] : "windowing_win32.dll";
   if (!MultiByteToWideChar(CP_ACP, 0, name, -1, input, MAX_PATH)) return 2;
   length = GetFullPathNameW(input, MAX_PATH, full, NULL);
   if (!length || length >= MAX_PATH) return 2;
   printf("DLL-load probe: %s\n", name);
   puts("Separate process: this probe does not initialize the ca2 application system.");
   puts("The normal-load tests execute the DLL's initialization code.");
   fflush(stdout);
   attempt(full, DONT_RESOLVE_DLL_REFERENCES, "Normal path, mapping only");
   attempt(full, 0, "Normal path, full initialization");
   if (full[0] && full[1] == L':') {
      wcscpy(extended, L"\\\\?\\");
      wcscat(extended, full);
      attempt(extended, DONT_RESOLVE_DLL_REFERENCES, "Extended path, mapping only");
      attempt(extended, 0, "Extended path, full initialization");
   }
   puts("Probe finished.");
   return 0;
}
