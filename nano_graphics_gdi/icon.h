//
// Created by camilo on 2024-09-27 02:47 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/icon.h"
#include "object.h"

#include <gdiplus.h>
namespace windows
{

   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI icon :
            virtual public ::nano::graphics::icon
         {
         public:

            //CreatableFromBase(::nano::graphics::font, ::nano::graphics::font);

            Gdiplus::Image * m_pimage;


            icon();
            ~icon() override;


            void load_image_file(const void * p, memsize size) override;



         };



      } // namespace graphics


   } // namespace nano



} // namespace windows



