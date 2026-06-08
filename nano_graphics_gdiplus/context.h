//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/context.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS context : 
      virtual public ::nano::graphics::context
   {
   public:


      // CreatableFromBase(device, device);

      HDC m_hdc;

      ::auto_pointer<::Gdiplus::Graphics> m_pgraphics;
      ::auto_pointer<::Gdiplus::Bitmap> m_pbitmapMemory;
      ::pointer < ::nano_graphics_gdiplus::brush > m_pbrush;
      ::pointer<::nano_graphics_gdiplus::pen> m_ppen;
      ::pointer<::nano_graphics_gdiplus::font> m_pfont;


      //HDC m_hdc;
      //bool m_bDelete;


      context();

      ~context() override;

      
      void create(const ::i32_size &size);

      
      void set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode);


      void set_text_rendering_hint(::nano::graphics::enum_text_rendering_hint etextrenderinghint);


      void clear(const ::color::color & color);

      void set_brush(::nano::graphics::brush * pbrush) override;
      void set_pen(::nano::graphics::pen * ppen) override;
      void set_font(::nano::graphics::font * pfont) override;

      /// <summary>
      ///  type 0 is HDC
      /// </summary>
      /// <param name="posdata"></param>
      /// <param name="size"></param>
      /// <param name="iType"></param>
      void attach(void *posdata, const ::i32_size &size, ::i32 iType) override;

      //void _draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText, const ::e_align &ealign,
        //              const ::e_draw_text &edrawtext, ::nano::graphics::brush *pnanobrushBack,
          //            ::nano::graphics::brush *pnanobrushText, ::nano::graphics::font *pnanofont) override;
      void _draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText,
                      const ::e_draw_text &edrawtext, const ::e_align
       &ealign) override;
      //::i32_size get_text_extents(const ::scoped_string &scopedstr, ::nano::graphics::font *pnanofont) override;
      ::f64_size get_text_extents(const ::scoped_string &scopedstr) override;
      //void rectangle(const ::f64_rectangle &rectangle, ::nano::graphics::brush *pnanobrush,
        //             ::nano::graphics::pen *pnanopen) override;
       void rectangle(const ::f64_rectangle &rectangle) override;
      //void ellipse(const ::f64_rectangle &rectangle, ::nano::graphics::brush *pnanobrush,
        //             ::nano::graphics::pen *pnanopen) override;
       void ellipse(const ::f64_rectangle &rectangle) override;

      //void line(const ::f64_point &point1, const ::f64_point &point2,
        //           ::nano::graphics::pen *pnanopen) override;
        void line(const ::f64_point &point1, const ::f64_point &point2) override;

      void draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon *picon) override;


      void draw_image(const ::f64_rectangle &rectangle, ::nano::graphics::image *pimage) override;

      void draw_image(const ::f64_point &point, const ::f64_rectangle &rectangle,
                              ::nano::graphics::image *pimage)override;


      void translate(::f64 x, ::f64 y) override;

      //void do_path(::nano::graphics::path *ppath, ::nano::graphics::brush *pbrush,
        //           ::nano::graphics::pen *ppen) override;
       void do_path(::nano::graphics::path *ppath) override;

      //void draw_path(::nano::graphics::path *ppath, ::nano::graphics::pen *ppen) override;


   };


} // namespace nano_graphics_gdiplus
