//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include <commctrl.h>

#include "acme/subsystem/particle.h"
#include "apex/innate_subsystem_win32/ImageList.h"
#include "acme/_operating_system.h"

namespace windows
{


namespace innate_subsystem_win32
{


   class CLASS_DECL_APEX ImageList :
   virtual public ::subsystem::composite<::innate_subsystem_win32::ImageListInterface>
   {
   public:

         HIMAGELIST  m_himagelist;


      ImageList();
      ~ImageList() override;

      void initializeImageList() override;

      void createImageList(int cx, int cy, int flags, int iInitialSize, int iGrow) override;

      void destroyImageList() override;

      void addIcon(innate_ui::icon* pinnateuiicon) override;

   };


} // namespace innate_subsystem_win32


} // namespace windows