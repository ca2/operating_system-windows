//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/pen.h"
#include "object.h"




      namespace nano_graphics_gdi
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI pen :
            virtual public ::nano::graphics::pen,
            virtual public object
         {
         public:


            //__CreatableFromBase(::nano::graphics::pen, ::nano::graphics::pen);


            pen();
            ~pen() override;


            void update(::nano::graphics::context* pgraphicscontext) override;


         };



      } // namespace nano_graphics_gdi
