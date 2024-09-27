//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/pen.h"
#include "object.h"


namespace windows
{


   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI pen :
            virtual public ::nano::graphics::pen,
            virtual public object
         {
         public:


            //__CreatableFromBase(::nano::graphics::pen, ::nano::graphics::pen);


            pen();
            ~pen() override;


            void update(::nano::graphics::device* pnanodevice) override;


         };



      } // namespace graphics


   } // namespace nano

} // namespace windows



