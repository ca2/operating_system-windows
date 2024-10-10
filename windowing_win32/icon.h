// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Soerensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:43
#pragma once


#include "acme/filesystem/filesystem/path.h"
#include "acme/prototype/collection/map.h"
#include "aura/graphics/image/map.h"
#include "aura/windowing/icon.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 icon :
      virtual public ::windowing::icon
   {
   public:
      

      struct icon_item
      {
         HICON m_hicon = nullptr;
         bool m_bCalculated = false;

      };

      map < ::size_i32, icon_item >              m_iconmap;

      ::file::path                           m_pathProcessed;

      map < ::size_i32, ::image::image_pointer >      m_imagemap;

      
      icon();
      ~icon() override;


      virtual void * get_os_data(const ::size_i32 & size) const;
      
      void load_file(const ::string & strPath) override;

      void load_app_tray_icon(const string& strApp) override;

      virtual bool add_icon(HICON hicon);

      void get_sizes(::size_i32_array & a) override;

      ::image::image_pointer get_image(const ::size_i32 & size) override;

      virtual ::image::image_pointer _create_image(const ::size_i32 & size);


      void _erase_all();

      ::pointer < ::innate_ui::icon > innate_ui_icon(const ::size_i32 & size) override;

      
   };



} // namespace windowing



