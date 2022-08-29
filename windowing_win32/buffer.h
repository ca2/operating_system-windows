// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-02-01 23:29
#pragma once


#include "aura/graphics/graphics/_.h"
#include "aura/graphics/graphics/_graphics.h"
#include "aura/operating_system.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      //__creatable_from_base(buffer, ::graphics::graphics);


      class os_buffer
      {
      public:


         os_buffer();
         ~os_buffer();


         ::pixmap                      m_pixmap;
         HBITMAP                       m_hbitmap;
         HBITMAP                       m_hbitmapOld;
         HDC                           m_hdc;


         void destroy_buffer();


      };


      os_buffer                     m_osbuffera[2];
      HDC                           m_hdcScreen;
      bool                          m_bWindowDC;
      oswindow                      m_hwndIpc;
      ::rectangle_i32               m_rectangleLast;


      buffer();
      ~buffer() override;


      virtual void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;


      virtual bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
      virtual void destroy_buffer() override;
      virtual bool update_screen() override;


      virtual bool update_screen(::image * pimage) override;


      virtual ::draw2d::graphics * on_begin_draw() override;


      bool create_os_buffer(const ::size_i32 & size, int iStride = -1);
      void destroy_os_buffer();


      virtual bool buffer_lock_round_swap_key_buffers() override;

      virtual HWND get_hwnd() const;


   };


} // namespace windows



