// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
// From apex/innate_subsystem/resource_loader.h by
// camilo on 2026-04-11 04:43 <3ThomasBorregaardSørensen!!
#pragma once


#include "innate_subsystem/platform/ResourceLoader.h"
//#include "drawing/Icon.h"

//#include "winhdr.h"

//#include "Singleton.h"
namespace innate_subsystem_windows
{
   /**
    * Loader of resources from resource files linked with application.
    *
    * Singleton without support of "lazy" initialization.
    */
   //class ResourceLoader : public Singleton<ResourceLoader>
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS ResourceLoader : virtual public ::innate_subsystem::ResourceLoader
   {
   public:
      /**
       * Initializes resource loader singleton.
       * @param appInst windwos application instance.
       */
      //resource_loader(HINSTANCE appInst);
      ResourceLoader();
      /**
       * Frees resource loader singleton.
       */
      ~ResourceLoader() override;

      /**
       * Loads standart icon from resources.
       * @param iconName icon name.
       * @return icon handle of 0 if cannot load icon.
       */
      ::pointer < ::innate_subsystem::IconInterface >  loadStandardIcon(enum_cursor ecursor) override;

      /**
       * Loads icon from resources.
       * @param iconName icon name.
       * @return icon handle of 0 if cannot load icon.
       */
      ::pointer < ::innate_subsystem::IconInterface > loadIconByIntResource(::i32 iId) override;

      ::pointer < ::innate_subsystem::IconInterface > loadIcon(const ::i8* iconName) override;

      // /**
      //  * Loads string from resources.
      //  * @param [in] id identifier of string in resource file.
      //  * @param [out] string storage for string from resources.
      //  * @return true if string is loaded, false otherwise.
      //  */
      bool loadString(::u32 id, ::string & str) override;
      // virtual ::string loadString(::u32 id);

      /**
       * Loads accelerator from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of accelerator if it's loaded.
       */
      //HACCEL loadAccelerator(::u32 id);
      void * loadAccelerator(::u32 id) override;

      /**
       * Loads standart cursor.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadStandardCursor(const ::i8 *id);
      /**
       * Loads cursor from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadCursor(::u32 id);
      virtual ::pointer < ::innate_subsystem::CursorInterface > loadCursor(::u32 id) override;

   //protected:
      /**
       * Application instance.
       */
     // HINSTANCE m_appInstance;
   };

   //#endif
} // namespace innate_subsystem_windows



