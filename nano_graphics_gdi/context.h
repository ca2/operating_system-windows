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

            ::pointer<::nano_graphics_gdi::pen> m_ppen;
            ::pointer<::nano_graphics_gdi::brush> m_pbrush;
            ::pointer<::nano_graphics_gdi::font> m_pfont;


            context();
            
            ~context() override;


            void attach(void * posdata, const ::i32_size & size, int iType) override;

            //void _draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle& rectangleText, const ::e_align& ealign, const ::e_draw_text& edrawtext, ::nano::graphics::brush* pnanobrushBack, ::nano::graphics::brush* pnanobrushText, ::nano::graphics::font* pnanofont) override;
            void _draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText, 
                            const ::e_draw_text &edrawtext, const ::e_align &ealign) override;
            //::f64_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font* pnanofont) override;
            ::f64_size get_text_extents(const ::scoped_string &scopedstr) override;
            //void rectangle(const ::f64_rectangle& rectangle, ::nano::graphics::brush* pnanobrush, ::nano::graphics::pen* pnanopen) override;
            void rectangle(const ::f64_rectangle &rectangle) override;


            void draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon *picon) override;


            void translate(::f64 x, ::f64 y) override;


         };




      } // namespace nano_graphics_gdi

