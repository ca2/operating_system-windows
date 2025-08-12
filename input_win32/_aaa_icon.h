// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Soerensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:43
#pragma once


#include "acme/filesystem/filesystem/path.h"
#include "acme/prototype/collection/map_base.h"
#include "aura/graphics/image/map_base.h"
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

      map_base < ::int_size, icon_item >              m_iconmap;

      ::file::path                           m_pathProcessed;

      map_base < ::int_size, ::image::image_pointer >      m_imagemap;

      
      icon();
      ~icon() override;


      virtual void * get_os_data(const ::int_size & size) const;
      
      void load_file(const ::scoped_string & scopedstrPath) override;

      void load_app_tray_icon(const ::scoped_string & scopedstrApp) override;

      virtual bool add_icon(HICON hicon);

      void get_sizes(::int_size_array & a) override;

      ::image::image_pointer get_image(const ::int_size & size) override;

      virtual ::image::image_pointer _create_image(const ::int_size & size);


      void _erase_all();

      
   };



} // namespace windowing



