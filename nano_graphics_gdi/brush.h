//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/brush.h"
#include "object.h"



      namespace nano_graphics_gdi
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI brush :
            virtual public ::nano::graphics::brush,
            virtual public object
         {
         public:


            //CreatableFromBase(brush, brush);


            brush();
            ~brush() override;




            //void update(::nano::graphics::context* pgraphicscontext) override;


         };



      } // namespace nano_graphics_gdi

