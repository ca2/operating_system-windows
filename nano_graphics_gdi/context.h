//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/context.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"



      namespace nano_graphics_gdi
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI context :
            virtual public ::nano::graphics::context
         {
         public:


            //CreatableFromBase(device, device);


            HDC         m_hdc;
            bool        m_bDelete;


            context();
            
            ~context() override;


            void attach(void * posdata, const ::i32_size & size, int iType) override;

            void _draw_text(const ::scoped_string & scopedstr, const ::i32_rectangle& rectangleText, const ::e_align& ealign, const ::e_draw_text& edrawtext, ::nano::graphics::brush* pnanobrushBack, ::nano::graphics::brush* pnanobrushText, ::nano::graphics::font* pnanofont) override;
            ::i32_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font* pnanofont) override;
            void rectangle(const ::i32_rectangle& rectangle, ::nano::graphics::brush* pnanobrush, ::nano::graphics::pen* pnanopen) override;


            void draw(::nano::graphics::icon * picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy) override;


            void translate(::i32 x, ::i32 y) override;


         };




      } // namespace nano_graphics_gdi

