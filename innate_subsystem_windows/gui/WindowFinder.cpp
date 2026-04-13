// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "../framework.h"
#include "../WindowFinder.h"

namespace innate_subsystem_windows
{
   struct WindowsParam
   {
      ::comparable_array_base<HWND> *hwndVector;
      const ::string_array_base *classNames;
   };

   BOOL CALLBACK WindowFinder::findWindowsByClassFunc(HWND hwnd, LPARAM lparam)
   {
      if (IsWindowVisible(hwnd) != 0) {
         WindowsParam *windowsParam = (WindowsParam *)lparam;
         //::sStringVector::iterator classNameIter;

         const size_t maxTcharCount = 256;
         TCHAR winName[maxTcharCount];
         if (GetClassName(hwnd, winName, maxTcharCount) != 0) {
            ::string nextWinName(winName);

            if (nextWinName.has_character() && hwnd != 0)
               {
               for (auto & str : *windowsParam->classNames)
               {
                  if (str == nextWinName)
                  {
                     windowsParam->hwndVector->add(hwnd);
                  }
               }

            }

            // Recursion
            EnumChildWindows(hwnd, findWindowsByClassFunc, (::lparam) windowsParam);
         }
      }
      return TRUE;
   }

   ::comparable_array_base<HWND> WindowFinder::findWindowsByClass(const ::string_array_base & straClassNames)
   {
      ::comparable_array_base<HWND> hwnda;
      if (straClassNames.empty()) {
         return hwnda;
      }
      WindowsParam windowsParam;
      windowsParam.classNames = &straClassNames;
      windowsParam.hwndVector = &hwnda;
      EnumWindows(findWindowsByClassFunc, (LPARAM)&windowsParam);
      return hwnda;
   }

   BOOL CALLBACK WindowFinder::findWindowsByNameFunc(HWND hwnd, LPARAM lparam)
   {
      if (IsWindowVisible(hwnd) != 0) {
         const size_t maxTcharCount = 256;
         TCHAR nameChars[maxTcharCount];
         if (GetWindowText(hwnd, nameChars, maxTcharCount) != 0) {
            ::string winName(nameChars);
            winName.make_lower();

            if (winName.has_character() && hwnd != 0) {
               WindowsParam *winParams = (WindowsParam *)lparam;
               auto substr = winParams->classNames->first();
               if (winName.contains( substr)) {
                  winParams->hwndVector->add(hwnd);
                  return FALSE;
               }
            }
         }
      }
      return TRUE;
   }

   HWND WindowFinder::findFirstWindowByName(const ::scoped_string & scopedstrWindowNamePart)
   {
      ::comparable_array_base<HWND> hwnda;
      ::string_array_base winNameVector;
      winNameVector.add(scopedstrWindowNamePart);
      winNameVector[0].make_lower();
      WindowsParam winParams = { &hwnda, &winNameVector };

      EnumWindows(findWindowsByNameFunc, (::lparam)&winParams);
      if (hwnda.has_element()) {
         return hwnda.first();
      } else {
         return 0;
      }
   }
} // namespace innate_subsystem_windows

