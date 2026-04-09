//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include <commctrl.h>

#include "acme/subsystem/particle.h"
#include "apex/innate_subsystem/ImageList.h"
#include "acme/_operating_system.h"


namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 ImageList :
   virtual public ::subsystem::implementation<::innate_subsystem::ImageListInterface>
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


} // namespace innate_subsystem_win32



