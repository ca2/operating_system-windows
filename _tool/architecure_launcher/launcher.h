#pragma once
// Standalone bootstrap: no ca2 runtime or CRT, so it can start on XP/ReactOS.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shellapi.h>

namespace architecture_launcher
{
   const DWORD capacity = 32768;
   wchar_t root[capacity], target[capacity], command[capacity], probe[capacity];
   DWORD used;

   bool append(wchar_t * destination, const wchar_t * value)
   {
      auto length = lstrlenW(destination);
      if (length + lstrlenW(value) >= capacity) return false;
      lstrcatW(destination, value);
      return true;
   }

   bool begins(const wchar_t * value, const wchar_t * prefix)
   {
      while (*prefix) if (*value++ != *prefix++) return false;
      return true;
   }

   bool parent(wchar_t * path)
   {
      auto length = lstrlenW(path);
      while (length && path[length - 1] != L'\\' && path[length - 1] != L'/') --length;
      if (length <= 3) return false;
      path[length - 1] = 0;
      return true;
   }

   bool put(wchar_t value)
   {
      if (used + 1 >= capacity) return false;
      command[used++] = value;
      command[used] = 0;
      return true;
   }

   bool quote(const wchar_t * value)
   {
      if (!put(L'"')) return false;
      DWORD slashes = 0;
      for (; *value; ++value)
      {
         if (*value == L'\\') { ++slashes; continue; }
         auto count = *value == L'"' ? slashes * 2 + 1 : slashes;
         while (count--) if (!put(L'\\')) return false;
         slashes = 0;
         if (!put(*value)) return false;
      }
      slashes *= 2;
      while (slashes--) if (!put(L'\\')) return false;
      return put(L'"');
   }

   const wchar_t * architecture()
   {
      auto kernel = GetModuleHandleW(L"kernel32.dll");
      typedef BOOL (WINAPI * wow64_query)(HANDLE, USHORT *, USHORT *);
      auto query = reinterpret_cast<wow64_query>(GetProcAddress(kernel, "IsWow64Process2"));
      USHORT processMachine = 0, nativeMachine = 0;
      if (query && query(GetCurrentProcess(), &processMachine, &nativeMachine))
      {
         if (nativeMachine == 0xaa64) return L"arm64";
         if (nativeMachine == 0x8664) return L"x64";
         if (nativeMachine == 0x014c) return L"x86";
         return nullptr;
      }
      typedef void (WINAPI * system_query)(LPSYSTEM_INFO);
      auto nativeInfo = reinterpret_cast<system_query>(GetProcAddress(kernel, "GetNativeSystemInfo"));
      static SYSTEM_INFO info;
      if (nativeInfo) nativeInfo(&info); else GetSystemInfo(&info);
      if (info.wProcessorArchitecture == 9) return L"x64";
      if (info.wProcessorArchitecture == 12) return L"arm64";
      if (info.wProcessorArchitecture == 0) return L"x86";
      return nullptr;
   }

   int fail(const wchar_t * message)
   {
      MessageBoxW(nullptr, message, L"Architecture launcher", MB_OK | MB_ICONERROR);
      return 1;
   }

   int run(const wchar_t * fixedFolder = nullptr, const wchar_t * fixedExecutable = nullptr)
   {
      int count = 0;
      auto arguments = CommandLineToArgvW(GetCommandLineW(), &count);
      if (!arguments) return fail(L"Cannot read launcher arguments.");
      const wchar_t * folder = fixedFolder;
      const wchar_t * executable = fixedExecutable;
      int forwarded = fixedFolder ? 1 : count;
      bool valid = true;
      for (int i = 1; !fixedFolder && i < count; ++i)
      {
         if (lstrcmpW(arguments[i], L"--") == 0) { forwarded = i + 1; break; }
         if (begins(arguments[i], L"folder=")) folder = arguments[i] + 7;
         else if (begins(arguments[i], L"executable=")) executable = arguments[i] + 11;
         else valid = false;
      }
      if (!valid || !folder || !*folder || !executable || !*executable)
      {
         LocalFree(arguments);
         return fail(L"Usage: architecture_launcher.exe folder=PATH executable=NAME [-- ARGUMENTS]\nRelative folders resolve from the checkout containing this launcher.");
      }
      auto length = GetModuleFileNameW(nullptr, root, capacity);
      if (!length || length >= capacity || !parent(root)) valid = false;
      // Prefer the specified folder suffix over .git: tool itself is a nested
      // submodule, so its nearest .git is not the enclosing project checkout.
      bool resolvedRoot = false;
      if (valid && folder[0] != L'\\' && !(folder[0] && folder[1] == L':'))
      {
         lstrcpyW(probe, folder);
         for (auto p = probe; *p; ++p) if (*p == L'/') *p = L'\\';
         auto rootLength = lstrlenW(root), folderLength = lstrlenW(probe);
         if (rootLength > folderLength && root[rootLength - folderLength - 1] == L'\\'
            && lstrcmpiW(root + rootLength - folderLength, probe) == 0)
         {
            root[rootLength - folderLength - 1] = 0;
            resolvedRoot = true;
         }
      }
      while (valid && !resolvedRoot)
      {
         lstrcpyW(probe, root);
         if (!append(probe, L"\\.git")) { valid = false; break; }
         if (GetFileAttributesW(probe) != INVALID_FILE_ATTRIBUTES) break;
         if (!parent(root)) { valid = false; break; }
      }
      auto arch = architecture();
      if (valid && arch)
      {
         // Absolute drive/UNC folders are also accepted.
         if (folder[0] == L'\\' || (folder[0] && folder[1] == L':')) lstrcpyW(target, folder);
         else { lstrcpyW(target, root); valid = append(target, L"\\") && append(target, folder); }
         valid = valid && append(target, L"\\") && append(target, arch)
            && append(target, L"\\") && append(target, executable) && quote(target);
         for (int i = forwarded; valid && i < count; ++i) valid = put(L' ') && quote(arguments[i]);
      }
      else valid = false;
      LocalFree(arguments);
      if (!valid) return fail(L"Cannot resolve checkout/architecture or command is too long. Place the launcher inside the checkout and check its arguments.");
      auto attributes = GetFileAttributesW(target);
      if (attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY))
      {
         lstrcpyW(probe, L"Missing architecture executable:\n");
         if (!append(probe, target)) return fail(L"Missing architecture executable (path too long).");
         return fail(probe);
      }
      static STARTUPINFOW startup;
      startup.cb = sizeof(startup);
      static PROCESS_INFORMATION process;
      if (!CreateProcessW(target, command, nullptr, nullptr, FALSE, 0, nullptr, root, &startup, &process))
         return fail(L"Cannot start the selected executable. Check its runtime dependencies and compatibility with this Windows version.");
      CloseHandle(process.hThread);
      DWORD code = 1;
      bool succeeded = WaitForSingleObject(process.hProcess, INFINITE) == WAIT_OBJECT_0
         && GetExitCodeProcess(process.hProcess, &code);
      CloseHandle(process.hProcess);
      return succeeded ? static_cast<int>(code) : 1;
   }
}

