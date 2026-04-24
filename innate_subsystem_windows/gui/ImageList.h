//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include <commctrl.h>

#include "subsystem/platform/particle.h"
#include "innate_subsystem/gui/ImageList.h"
#include "acme/_operating_system.h"


namespace innate_subsystem_windows
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS ImageList :
   virtual public Implementation<::innate_subsystem::ImageListInterface>
   {
   public:


      HIMAGELIST  m_himagelist;


      ImageList();
      ~ImageList() override;

      void initializeImageList() override;

      void createImageList(const ::int_size & size, int flags, int iInitialSize, int iGrow) override;

      void destroyImageList() override;

      void addIcon(::innate_subsystem::IconInterface * picon) override;

   };


} // namespace innate_subsystem_windows



