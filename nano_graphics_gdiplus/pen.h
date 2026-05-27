//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/pen.h"
#include "object.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS pen : virtual public ::nano::graphics::pen, virtual public object
   {
   public:


      //__CreatableFromBase(::nano::graphics::pen, ::nano::graphics::pen);

      ::auto_pointer<::Gdiplus::Pen> m_ppen;


      pen();
      ~pen() override;


      void create_pen(::particle *pparticle, ::i32 iWidth, color32_t color) override;

      //void update(::nano::graphics::context *pnanodevice) override;
   };


} // namespace nano_graphics_gdiplus
