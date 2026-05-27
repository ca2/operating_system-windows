//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/context.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS context : 
      virtual public ::nano::graphics::context
   {
   public:


      // CreatableFromBase(device, device);


      HDC m_hdc;
      bool m_bDelete;


      context();

      ~context() override;


      
      void set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode);


      void set_text_rendering_hint(::nano::graphics::enum_text_rendering_hint etextrenderinghint);


      void clear(const ::color::color & color);

      /// <summary>
      ///  type 0 is HDC
      /// </summary>
      /// <param name="posdata"></param>
      /// <param name="size"></param>
      /// <param name="iType"></param>
      void attach(void *posdata, const ::i32_size &size, ::i32 iType) override;

      void _draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText, const ::e_align &ealign,
                      const ::e_draw_text &edrawtext, ::nano::graphics::brush *pnanobrushBack,
                      ::nano::graphics::brush *pnanobrushText, ::nano::graphics::font *pnanofont) override;
      ::i32_size get_text_extents(const ::scoped_string &scopedstr, ::nano::graphics::font *pnanofont) override;
      void rectangle(const ::f64_rectangle &rectangle, ::nano::graphics::brush *pnanobrush,
                     ::nano::graphics::pen *pnanopen) override;


      void draw(::nano::graphics::icon *picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy) override;


      void translate(::f64 x, ::f64 y) override;

      void fill_path(::nano::graphics::path *ppath, ::nano::graphics::brush *pbrush) override;

      void draw_path(::nano::graphics::path *ppath, ::nano::graphics::pen *ppen) override;


   };


} // namespace nano_graphics_gdiplus
