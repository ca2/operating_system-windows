#include "framework.h"
#include "acme/node/windows/registry.h"
#include <shlobj.h>
#include <RestartManager.h>
#include <string.h>
#include "explorer_restart.h"

#pragma comment( lib, "Rstrtmgr" )
#pragma comment( lib, "Shlwapi")


RM_UNIQUE_PROCESS rm_get_application(string strName)
{

   strName.ensure_ends_ci(".exe");

   wstring wstrName(strName);

   RM_UNIQUE_PROCESS  result = { 0 };

   DWORD dwByteCount = 0;

   dword_array dwaPid;

   while (dwByteCount == dwaPid.get_size_in_bytes())
   {

      dwaPid.set_size(dwaPid.get_size() + 1024);

      EnumProcesses((DWORD *)dwaPid.get_data(), (DWORD)(dwaPid.get_size_in_bytes()), &dwByteCount);

   }

   for (auto pid : dwaPid)
   {

      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);

      if (hProcess)
      {

         wstring imageName;

         imageName.allocate(4096);

         if (GetProcessImageFileNameW(hProcess, (LPWSTR)imageName.operator unichar * (), 4096) > 0)
         {

            if (wcscmp(wstrName, PathFindFileNameW(imageName.operator unichar * ())) == 0)
            {

               //this is assmuing the user is not running elevated and won't see explorer processes in other sessions

               FILETIME ftCreate, ftExit, ftKernel, ftUser;

               if (GetProcessTimes(hProcess, &ftCreate, &ftExit, &ftKernel, &ftUser))
               {

                  if (result.dwProcessId == 0)
                  {

                     result.dwProcessId = pid;

                     result.ProcessStartTime = ftCreate;

                  }
                  else if (CompareFileTime(&result.ProcessStartTime, &ftCreate) > 0)
                  {

                     result.dwProcessId = pid;

                     result.ProcessStartTime = ftCreate;

                  }

               }

            }

         }

         CloseHandle(hProcess);

      }

   }

   return result;

}


bool pre_explorer_restart(DWORD & dwSession, bool bForce)
{

   //return true;

   STARTUPINFOW si = {};

   si.cb = sizeof(si);

   si.wShowWindow = SW_HIDE;

   PROCESS_INFORMATION pi = {};

   WCHAR wszSystem[2048];

   GetSystemDirectoryW(wszSystem, sizeof(wszSystem) / sizeof(WCHAR));

   wstring wstrSystem(wszSystem);

   ::file::path path(wstrSystem);

   path /= "taskkill.exe";

   wstring wstrPath(path);

   wstring wstrForce(L"taskkill.exe /F /IM explorer.exe");

   wstring wstrNormal(L"taskkill.exe /IM explorer.exe");

   if (CreateProcessW(wstrPath, bForce ? wstrForce : wstrNormal, nullptr, nullptr, false, 0, nullptr, wstrSystem, &si, &pi))
   {

      output_debug_string("created");

   }
   else
   {

      output_debug_string("not created");

   }

   CloseHandle(pi.hProcess);

   CloseHandle(pi.hThread);

   return true;

}


bool pos_explorer_restart(DWORD dwSession)
{

   STARTUPINFOW si = {};

   si.cb = sizeof(si);

   si.wShowWindow = SW_HIDE;

   PROCESS_INFORMATION pi = {};

   WCHAR wszSystem[2048];

   GetWindowsDirectoryW(wszSystem, sizeof(wszSystem) / sizeof(WCHAR));

   wstring wstrSystem(wszSystem);

   ::file::path path(wstrSystem);

   path /= "explorer.exe";

   wstring wstrPath(path);

   if (CreateProcessW(wstrPath, (LPWSTR)L"explorer.exe", nullptr, nullptr, false, 0, nullptr, wstrSystem, &si, &pi))
   {

      output_debug_string("created");

   }
   else
   {

      output_debug_string("not created");

   }

   CloseHandle(pi.hProcess);

   CloseHandle(pi.hThread);

   return true;

}


bool restart_explorer()
{

   DWORD dwSession = 0;

   pre_explorer_restart2(dwSession);

   pos_explorer_restart2(dwSession);

   return true;

}




bool pre_explorer_restart2(DWORD & dwSession)
{

   WCHAR szSessionKey[CCH_RM_SESSION_KEY + 1] = { 0 };

   DWORD dwError = RmStartSession(&dwSession, 0, szSessionKey);

   if (dwError == ERROR_SUCCESS)
   {

      RM_UNIQUE_PROCESS rgApplications[1] = { rm_get_application("explorer.exe") };

      dwError = RmRegisterResources(dwSession, 0, nullptr, 1, rgApplications, 0, nullptr);

      DWORD dwReason;

      UINT nProcInfoNeeded = 0;

      UINT nProcInfo = 256;

      RM_PROCESS_INFO rgpi[256];

      dwError = RmGetList(dwSession, &nProcInfoNeeded, &nProcInfo, rgpi, &dwReason);

      if (dwReason == RmRebootReasonNone)//now free to restart explorer
      {

         RmShutdown(dwSession, RmForceShutdown, nullptr);//important, if we change the registry before shutting down explorer will override our change
         //using undocumented setting structure, could break any time

         //edge setting is stored at HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\StuckRects2!Settings
         ::count cWait = 45;

         while (cWait > 0)
         {

            bool bOneRunning = false;

            DWORD dwReason;

            UINT nProcInfoNeeded = 0;

            UINT nProcInfo = 256;

            RM_PROCESS_INFO rgpi[256];

            dwError = RmGetList(dwSession, &nProcInfoNeeded, &nProcInfo, rgpi, &dwReason);

            for (index i = 0; i < nProcInfo; i++)
            {

               if (rgpi[i].AppStatus & RmStatusRunning)
               {

                  bOneRunning = true;

                  break;

               }

            }

            if (!bOneRunning)
            {

               break;

            }

            cWait--;

         }

      }

   }

   return true;

}


bool pos_explorer_restart2(DWORD dwSession)
{

   RmRestart(dwSession, 0, nullptr);

   ::count cWait = 45;

   while (cWait > 0)
   {

      ::count cRestarted = 0;

      DWORD dwReason;

      UINT nProcInfoNeeded = 0;

      UINT nProcInfo = 256;

      RM_PROCESS_INFO rgpi[256];

      DWORD dwError = RmGetList(dwSession, &nProcInfoNeeded, &nProcInfo, rgpi, &dwReason);

      for (index i = 0; i < nProcInfo; i++)
      {
         if (rgpi[i].AppStatus & RmStatusRestarted)
         {

            cRestarted++;

         }

      }

      if (cRestarted >= nProcInfo)
      {

         break;

      }

      cWait--;

   }

   RmEndSession(dwSession);

   return true;

}
