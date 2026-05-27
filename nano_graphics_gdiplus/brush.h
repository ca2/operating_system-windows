//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/brush.h"
#include "object.h"
#include <gdiplus.h>



      namespace nano_graphics_gdiplus
      {


         class CLASS_DECL_NANO_GRAPHICS_GDIPLUS brush :
            virtual public ::nano::graphics::brush,
            virtual public object
         {
         public:


            //CreatableFromBase(brush, brush);

            ::auto_pointer<::Gdiplus::Brush> m_pbrush;


            brush();
            ~brush() override;


            void create_solid_brush(const ::color::color &color) override;
            //void update(::nano::graphics::context* pgraphicscontext) override;


         };



      } // namespace nano_graphics_gdiplus

