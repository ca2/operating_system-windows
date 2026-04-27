// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "OperatingSystem.h"
#include "CtrlAltDelSimulator.h"
#include "subsystem_windows/platform/subsystem.h"
#include <shlobj.h>
#include <VersionHelpers.h>
// #include aaa_<crtdbg.h>
//#include "remoting/win_system/AutoImpersonator.h"
//#include "remoting/win_system/WTS.h"
//#include "remoting/win_system/ProcessHandle.h"
#include "AutoImpersonator.h"
#include "WTS.h"
#include "ProcessHandle.h"
#include "Shell.h"
#include "DynamicLibrary.h"
//// #include aaa_<vector>
// #include aaa_<algorithm>
#pragma warning(suppress : 4996)
// OSVERSIONINFO OperatingSystem::m_osVerInfo = { 0 };
typedef VOID (WINAPI *SendSas)(BOOL asUser);
typedef HRESULT (WINAPI *DwmIsCompositionEnabled)(BOOL *pfEnabled);
namespace subsystem_windows
{


   OperatingSystem::OperatingSystem() {}

   OperatingSystem::~OperatingSystem() {}

   ::string OperatingSystem::getErrStr()
   {
      ::string out;
      DWORD errCode = GetLastError();

      LPWSTR pBuffer = NULL;

      // 1. Use FORMAT_MESSAGE_ALLOCATE_BUFFER for a dynamic buffer.
      // 2. Use FORMAT_MESSAGE_MAX_WIDTH_MASK to ignore hard-coded line breaks.
      DWORD length = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                      FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                                   NULL, errCode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                                   (LPTSTR)&pBuffer, // Cast the address of your pointer
                                   0, NULL);

      if (length == 0 || pBuffer == NULL)
      {
         out.format("<<Cannot get text error describing>> ({})", errCode);
      }
      else
      {
         // Remove trailing newlines or whitespace manually if still present
         while (length > 0 &&
                (pBuffer[length - 1] == _T('\n') || pBuffer[length - 1] == _T('\r') || pBuffer[length - 1] == _T(' ')))
         {
            pBuffer[--length] = _T('\0');
         }

         ::string strMessage;

         strMessage = pBuffer;

         out.format("{} ({})", strMessage, errCode);

         // Crucial: You must free the system-allocated buffer
         LocalFree(pBuffer);
      }

      return out;
   }

   ::string OperatingSystem::getErrStr(const ::scoped_string &scopedstrSpecification)
   {
      ::string out;
      ::string sysErrText = getErrStr();
      //getErrStr(&sysErrText);
      out.format("{} ({})", scopedstrSpecification, sysErrText);
      return out;
   }

   ::string OperatingSystem::getSpecialFolderPath(int specialFolderId)
   {
      ::string out;
      //_ASSERT(out != NULL);

      int csidl = 0;

      switch (specialFolderId)
      {
         case APPLICATION_DATA_SPECIAL_FOLDER:
            csidl = CSIDL_APPDATA;
            break;
         case COMMON_APPLICATION_DATA_SPECIAL_FOLDER:
            csidl = CSIDL_COMMON_APPDATA;
            break;
         default:
            _ASSERT(FALSE);
            return false;
      } // switch

      bool returnVal = false;

      WCHAR path[MAX_PATH + 1];
      if (SHGetSpecialFolderPathW(NULL, path, csidl, TRUE) == TRUE)
      {
         out = path;
         returnVal = true;
      }

      return returnVal;
   }

   ::string OperatingSystem::getCurrentModulePath()
   {
      ::wstring buffer;
      DWORD size = MAX_PATH;

      while (true)
      {
         // Allocate buffer
         auto p = buffer.get_buffer(size);
         // Try to get file name
         DWORD ret = GetModuleFileName(NULL, p, size);
         buffer.release_buffer();

         if (ret == 0)
         {
            throw ::exception(error_failed);
         }
         else if (ret == size || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
         {
            size += 128;
         }
         else
         {
            break;
         }
      } // while

      //out -= &buffer[0];

      return buffer;
   } // void

   bool OperatingSystem::isItTheSamePathAsCurrent(unsigned int pId)
   {
      ::string currModulePath, testedModulePath;
      ProcessHandle pHandle;

      pHandle.openProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pId);
      testedModulePath = pHandle.getProcessModulePath();
      currModulePath = getCurrentModulePath();

      return currModulePath == testedModulePath;
   }

   ::string OperatingSystem::getCurrentModuleFolderPath()
   {
      ::string out;

      out = getCurrentModuleFolderPath();

      /*if (!getCurrentModulePath(out))
      {
         return false;
      }*/

      auto strFolder = file_path_folder(out);
      //memsize lastPos = out->findLast(_T('\\'));

      //if (lastPos != (memsize)-1)
      //{
      //   out->getSubstring(out, 0, ::maximum(lastPos - 1, (memsize)0));
      //}

      return strFolder;
   }

   //bool OperatingSystem::getCurrentUserName(::string &out, ::subsystem::LogWriter *log)
   bool OperatingSystem::getCurrentUserName(::string & strUsername, ::subsystem::LogWriter * plogwriter)
   {

      ::string out;
      out = WindowsSubsystem().WTS().getCurrentUserName(system()->m_papplication);
      //return !out->is_empty();
      return out;
   }

   ::string OperatingSystem::getComputerName()
   {
      ::string out;
      WCHAR compName[MAX_COMPUTERNAME_LENGTH + 1];
      DWORD length = MAX_COMPUTERNAME_LENGTH + 1;
      if (GetComputerNameW(compName, &length) == 0)
      {
         return {};
      }
      out = compName;
      out.make_lower();
      //return true;
      return out;
   }


   //void OperatingSystem::init()
   //{
   //   if (m_osVerInfo.dwOSVersionInfoSize == 0)
   //   {
   //      m_osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   //      if (!GetVersionEx(&m_osVerInfo))
   //      {
   //         m_osVerInfo.dwOSVersionInfoSize = 0;
   //      }
   //   }
   //}

   //bool OperatingSystem::isWinNTFamily()
   //{
   //   init();
   //   return m_osVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT;
   //}

   //bool OperatingSystem::isWin2000()
   //{
   //   init();
   //   return m_osVerInfo.dwMajorVersion == 5 && m_osVerInfo.dwMinorVersion == 0;
   //}

   //bool OperatingSystem::isWinXP()
   //{
   //   init();
   //   return ((m_osVerInfo.dwMajorVersion == 5) && (m_osVerInfo.dwMinorVersion == 1) && isWinNTFamily());
   //}

   //bool OperatingSystem::isWin2003Server()
   //{
   //   init();
   //   return ((m_osVerInfo.dwMajorVersion == 5) && (m_osVerInfo.dwMinorVersion == 2) && isWinNTFamily());
   //}

   //bool OperatingSystem::isVistaOrLater()
   //{
   //   init();
   //   return m_osVerInfo.dwMajorVersion >= 6;
   //}

   //bool OperatingSystem::isWin7()
   //{
   //   init();
   //   return ((m_osVerInfo.dwMajorVersion == 6) && (m_osVerInfo.dwMinorVersion == 1) && isWinNTFamily());
   //}

   bool OperatingSystem::isWinNTFamily()
   {
      // All modern Windows versions (XP and later) are part of the NT family.
      // VersionHelpers only support XP and later, so this is effectively always true.
      return IsWindowsXPOrGreater();
   }

   bool OperatingSystem::isWin2000()
   {
      // Windows 2000 is Version 5.0.
      // VersionHelpers don't have a named function for 2000, so use the generic helper.
      return IsWindowsVersionOrGreater(5, 0, 0) && !IsWindowsXPOrGreater();
   }

   bool OperatingSystem::isWinXP()
   {
      // Windows XP is Version 5.1.
      return IsWindowsVersionOrGreater(5, 1, 0) && !IsWindowsVersionOrGreater(5, 2, 0);
   }

   bool OperatingSystem::isWin2003Server()
   {
      // Windows Server 2003 is Version 5.2 and is a Server OS.
      return IsWindowsVersionOrGreater(5, 2, 0) && IsWindowsServer();
   }

   bool OperatingSystem::isVistaOrLater()
   {
      // Direct replacement using the named helper function.
      return IsWindowsVistaOrGreater();
   }

   bool OperatingSystem::isWin7()
   {
      // Windows 7 is Version 6.1.
      return IsWindows7OrGreater() && !IsWindows8OrGreater();
   }
   void OperatingSystem::simulateCtrlAltDel(::subsystem::LogWriter *log)
   {
      // FIXME: Do not use log here.
      log->information("Requested Ctrl+Alt+Del simulation");

      // Are we running on Windows NT OS family?
      if (!isVistaOrLater() && isWinNTFamily())
      {
         CtrlAltDelSimulator cadSim;
         cadSim.wait();
      }
   }

   void OperatingSystem::simulateCtrlAltDelUnderVista(::subsystem::LogWriter *log)
   {
      // FIXME: Do not use log here.
      log->information("Requested Ctrl+Alt+Del simulation under Vista or later");

      try
      {
         DynamicLibrary sasLib;
         
         sasLib.initialize_dynamic_library("sas.dll");
         SendSas sendSas = (SendSas)sasLib.getProcAddress("SendSAS");
         if (sendSas == 0)
         {
            throw ::subsystem::Exception("The SendSAS function has not been found");
         }
         sendSas(FALSE); // Try only under service
      }
      catch (::exception &e)
      {
         log->error("The simulateCtrlAltDelUnderVista() function failed: {}", e.get_message());
      }
   }

   bool OperatingSystem::isAeroOn(::subsystem::LogWriter *log)
   {
      try
      {
         DynamicLibrary dwmLib;
         
         dwmLib.initialize_dynamic_library("Dwmapi.dll");
         DwmIsCompositionEnabled dwmIsEnabled =
            (DwmIsCompositionEnabled)dwmLib.getProcAddress("DwmIsCompositionEnabled");
         if (dwmIsEnabled == 0)
         {
            throw ::subsystem::Exception("The DwmIsCompositionEnabled() has not been found in the Dwmapi.dll");
         }
         BOOL result = FALSE;
         HRESULT dwmIsEnabledResult = dwmIsEnabled(&result);
         if (dwmIsEnabledResult != S_OK)
         {
            ::string errMess;
            errMess.formatf("The DwmIsCompositionEnabled() error code is {}", (int)dwmIsEnabledResult);
            throw ::subsystem::Exception("");
         }
         return result != FALSE;
      }
      catch (::exception &e)
      {
         log->error("The DwmIsCompositionEnabled() function failed: {}", e.get_message());
         throw;
      }
   }


   bool OperatingSystem::isUserAnAdmin()
   {

      auto bIsUserAndAdmin = ::IsUserAnAdmin();

      return bIsUserAndAdmin != FALSE;

   }


} // namespace subsystem_windows




