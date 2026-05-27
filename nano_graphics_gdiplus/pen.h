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


      void create_pen(const ::color::color & color, ::f64 fWidth) override;

      void set_start_cap(::nano::graphics::enum_line_cap elinecap) override;
      void set_end_cap(::nano::graphics::enum_line_cap elinecap) override;

      //void update(::nano::graphics::context *pnanodevice) override;
   };


} // namespace nano_graphics_gdiplus
