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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// From apex/innate_subsystem/resource_loader.cpp by
// camilo on 2026-04-11 04:44 <3ThomasBorregaardSørensen!!

#include "framework.h"
#include "resource_loader.h"
#include "drawing/Icon.h"
#include "drawing/Cursor.h"
#include "acme/operating_system/windows/user.h"
//#include "util/UnicodeStringStorage.h"

// #include aaa_<crtdbg.h>

namespace innate_subsystem_windows
{

   //resource_loader::resource_loader(HINSTANCE appInst)
   resource_loader::resource_loader()
      //: m_appInstance(appInst)
   {}

   resource_loader::~resource_loader()
   {}//h

   ::pointer < innate_subsystem::IconInterface > resource_loader::loadStandardIcon(enum_cursor ecursor)
   {

      auto picon = create_newø<::innate_subsystem_windows::Icon>();

      auto lpcwsz = (LPCWSTR)::windows::get_system_cursor(ecursor);
      //return LoadIcon(NULL, iconName);
      // if ((::iptr)iconName < 65536)
      // {
         picon->m_hicon = ::LoadIcon(NULL, lpcwsz);
      //
      // }
      // else
      // {
      //    ::wstring wstrIconName(iconName);
      //    picon->m_hicon = ::LoadIcon(NULL, wstrIconName);
      // }

      //throw ::interface_only();
      return picon;
   }

   ::pointer < innate_subsystem::IconInterface > resource_loader::loadIcon(const char* iconName)
   {
      //return LoadIcon(m_appInstance, iconName);
      auto picon = create_newø<::innate_subsystem_windows::Icon>();
      //return LoadIcon(NULL, iconName);
      if ((::iptr)iconName < 65536)
      {
         picon->m_hicon = ::LoadIcon((HINSTANCE) main_subsystem()->m_hinstanceResource, (LPCWSTR) iconName);

      }
      else
      {
         ::wstring wstrIconName(iconName);
         picon->m_hicon = ::LoadIcon((HINSTANCE) main_subsystem()->m_hinstanceResource,  wstrIconName);
      }

      //throw ::interface_only();
      return picon;
   }

   ::pointer < ::innate_subsystem::IconInterface > resource_loader::loadIconByIntResource(int iId)
   {
      //return LoadIcon(m_appInstance, iconName);
      auto picon = create_newø<::innate_subsystem_windows::Icon>();
      //return LoadIcon(NULL, iconName);
      if ((::iptr)iId < 65536)
      {
         picon->m_hicon = ::LoadIcon((HINSTANCE) main_subsystem()->m_hinstanceResource, (LPCWSTR) iId);

      }
      // else
      // {
      //    ::wstring wstrIconName(iconName);
      //    picon->m_hicon = ::LoadIcon((HINSTANCE) main_subsystem()->m_hinstanceResource,  wstrIconName);
      // }

      //throw ::interface_only();
      return picon;


   }



   // bool resource_loader::loadString(unsigned int id, ::string & str)
   // {
   //    //_ASSERT(string != 0);
   //    str = "(Undef)";
   //
   //    //
   //    // Format of string table:
   //    // Strings are stored in groups of 16 strings.
   //    // Group format is:
   //    // | length  |     string     | length  | string  | ...
   //    // | 2 unsigned chars | len * 2 unsigned chars  | 2 unsigned chars | len * 2 | ...
   //    // Strings stored in the UTF16-encoding.
   //    //
   //
   //
   //    //// Id of string-group, based from 0.
   //    //int resId = (id / 16) + 1;
   //    //HRSRC resHnd = FindResource(m_appInstance,
   //    //   MAKEINTRESOURCE(resId),
   //    //   RT_STRING);
   //    //if (resHnd != 0) {
   //    //   HGLOBAL hGlobal = LoadResource(m_appInstance, resHnd);
   //    //   LPVOID lockRes = LockResource(hGlobal);
   //
   //    //   WCHAR* lpStr = reinterpret_cast<WCHAR*>(lockRes);
   //    //   for (unsigned int i = 0; i < (id % 16); i++) {
   //    //      lpStr += 1 + static_cast<UINT16>(lpStr[0]);
   //    //   }
   //
   //    //   UINT16 strLen = static_cast<UINT16>(lpStr[0]);
   //
   //    //   std::vector<WCHAR> strBuff;
   //    //   strBuff.resize(strLen + 1);
   //    //   memcpy(&strBuff.front(), lpStr + 1, strLen * sizeof(WCHAR));
   //    //   strBuff[strLen] = L'\0';
   //
   //    //   UnlockResource(lockRes);
   //    //   FreeResource(hGlobal);
   //
   //    //   UnicodeStringStorage unicodeString;
   //    //   unicodeString.setString(&strBuff.front());
   //    //   unicodeString.toStringStorage(string);
   //    //}
   //    return true;
   // }
   //
   void * resource_loader::loadAccelerator(unsigned int id)
   {
      return (void *) (HACCEL) ::LoadAcceleratorsW((HINSTANCE) system()->m_hinstanceMain, (LPCWSTR) MAKEINTRESOURCEW(id));

   //      MAKEINTRESOURCE(id));
      //throw ::interface_only();
      //return nullptr;

   }

   //HCURSOR resource_loader::loadStandardCursor(const char* id)
   //{
   //   return LoadCursor(0, id);
   //}

   ::pointer <innate_subsystem::CursorInterface> resource_loader::loadCursor(unsigned int id)
   {
      //return LoadCursor(m_appInstance, iconName);
      auto pcursor = create_newø<::innate_subsystem_windows::Cursor>();
      //return LoadCursor(NULL, iconName);
      //if ((::iptr)id < 65536)
      //{
         pcursor->m_hcursor = ::LoadCursor((HINSTANCE) main_subsystem()->m_hinstanceResource, (LPCWSTR) MAKEINTRESOURCEW(id));

      // }
      // else
      // {
      //    ::wstring wstrCursorName(iconName);
      //    picon->m_hicon = ::LoadCursor((HINSTANCE) main_subsystem()->m_hinstanceResource,  wstrCursorName);
      // }

      //throw ::interface_only();
      return pcursor;
   }


} // namespace innate_subsystem



