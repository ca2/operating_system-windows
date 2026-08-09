// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-02-01 23:29
#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "aura/graphics/graphics/double_buffer.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"
#include "acme/graphics/image/pixmap.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 graphics :
      virtual public ::graphics::double_buffer_graphics,
      virtual public ::graphics::bitmap_source_buffer_graphics
   {
   public:


      //__creatable_from_base(buffer, ::graphics::graphics);

      //::pointer < ::draw2d::graphics > m_pdraw2dgraphics;

      //layered_window_buffer         m_layeredwindowbuffera[2];
      HWND                          m_hwndIpc;
      ::i32_rectangle               m_rectangleLast;
      ::task_pointer                m_ptaskUpdateScreen;
      ::manual_reset_happening          m_happeningUpdateScreen;
      //bool                          m_bSingleBufferMode;

      graphics();
      ~graphics() override;


      virtual void initialize_graphics_graphics(::windowing::window * pimpl) override;


      //bool is_single_buffer_mode() const override;


      virtual void _defer_update_screen_task();


      bool update_buffer(::graphics::buffer_item * pitem) override;
      void destroy_buffer() override;
      void update_screen() override;


      void destroy() override;

      void _on_configure_window(::graphics::buffer_item *pbufferitem) override;

      void on_update_screen(::graphics::buffer_item * pitem) override;

      virtual void update_screen_task();

      bool _on_begin(::graphics::buffer_item * pbufferitem) override;



      bool buffer_lock_round_swap_key_buffers() override;

      virtual HWND get_hwnd() const;


   };


} // namespace windows



