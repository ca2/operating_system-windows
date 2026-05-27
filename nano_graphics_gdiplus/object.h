//
// Created by camilo on 31/01/2022 16:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/_win32_gdi.h"
#include "acme/nano/graphics/object.h"


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS object : virtual public ::nano::graphics::object
   {
   public:


      HGDIOBJ m_hgdiobj;


      object();
      ~object();


      //void *operating_system_data() override;


      void destroy() override;
   };


} // namespace nano_graphics_gdiplus
