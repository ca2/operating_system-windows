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
#include "subsystem_windows/_common_header.h"
#include "DynamicLibrary.h"


namespace subsystem_windows
{


   DynamicLibrary::DynamicLibrary()
   : m_hmodule(nullptr)
   {
   }


   DynamicLibrary::~DynamicLibrary()
   {
      
      if (m_hmodule) 
      {

         ::FreeLibrary(m_hmodule);

      }

   }


   void DynamicLibrary::initialize_dynamic_library(const ::scoped_string & scopedstrFilename)
   {

      openLibrary(scopedstrFilename);

   }


   void DynamicLibrary::openLibrary(const ::scoped_string & scopedstrFilename)
   {

      ::wstring wstrLibraryName(scopedstrFilename);

      auto pszLibraryName = wstrLibraryName.c_str();

      m_hmodule = LoadLibraryW(pszLibraryName);

      if (!m_hmodule)
      {

         ::string strMessage;

         strMessage.format("{} library not found", scopedstrFilename);

         throw ::subsystem::Exception(strMessage);

      }

   }


   void * DynamicLibrary::getProcAddress(const char *procName)
   {

      if (!m_hmodule)
      {

         throw ::exception(error_wrong_state);

      }

      auto pProcedureAddress = ::GetProcAddress(m_hmodule, procName);

      if (!pProcedureAddress)
      {

         throw ::exception(error_not_found);

      }

      return pProcedureAddress;

   }



}  // namespace subsystem_windows

