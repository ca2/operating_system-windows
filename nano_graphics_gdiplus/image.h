//
// Created by camilo on 2026-06-08.
//
#pragma once


#include "acme/nano/graphics/image.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/geometry2d/size.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS image :
      virtual public ::nano::graphics::image
   {
   public:


      ::i32_size m_size;
      ::i32 m_iStride;
      ::memory m_memory;
      ::auto_pointer < ::Gdiplus::Bitmap > m_pbitmap;


      image();
      ~image() override;


      ::i32_size size() const override;

      void create_image(const ::i32_size & size) override;
      void * get_buffer() override;

      void load_image_file(const void * p, memsize size) override;


   };


} // namespace nano_graphics_gdiplus
