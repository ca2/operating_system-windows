// Created by camilo on 2026-07-30 23:32 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "aura/windowing/window_buffer.h"


namespace windowing_win32
{


   class CLASS_DECL_AURA_WINDOWS layered_window_buffer : virtual public ::windowing::window_buffer
   {
   public:



      //HBITMAP m_hbitmap;
      //HBITMAP m_hbitmapOld;
      //HDC m_hdc;
      HWND                                               m_hwnd;
      ::pointer < ::win32::acme::windowing::window >     m_pwindowWin32;
      HDC                                                m_hdcScreen;
      HDC                                                m_hdcDirectDiagnostic;
      HBITMAP                                            m_hbitmapDirectDiagnostic;
      HBITMAP                                            m_hbitmapDirectDiagnosticOld;
      ::image32_t *                                      m_pimage32DirectDiagnostic;
      ::i32_size                                         m_sizeDirectDiagnostic;
      ::pointer < ::windows::device_independent_bitmap > m_pdeviceindependentbitmapMainThreadDiagnostic;
      DWORD                                              m_dwMainThreadDiagnosticCreateThreadId;
      DWORD                                              m_dwProductionDibCreateThreadId;
      bool                                               m_bWindowDC;

      ::u32                                              m_uExtraFlagsSetWindowPos;
      ::u32                                              m_uSetWindowPosLastFlags;
      HWND                                               m_hwndSetWindowPosLastInsertAfter;
      ::user::activation                                 m_activationSetWindowPosLast;
      ::i32_point                                        m_pointBufferItemWindow;
      ::i32_size                                         m_sizeBufferItemWindow;


      layered_window_buffer();
      ~layered_window_buffer();


      void initialize_window_buffer(::windowing::window * pwindow) override;


      virtual void update_window_pixmap_buffer(::graphics::buffer_item * pbufferitem);

      HWND get_hwnd() const;


      bool _create_window_device_context(const ::i32_size & size, ::i32 iStride = -1) override;
      void _destroy_window_device_context() override;



      ::windows::device_independent_bitmap * _device_independent_bitmap();

      void destroy_window_buffer() override;

      void present_window_buffer() override;


      void _configure_window();

      void _update_layered_window();
      bool _create_direct_diagnostic_dib(const ::i32_size & size);
      void _destroy_direct_diagnostic_dib();
      void _update_layered_window_with_main_thread_device_independent_bitmap();
      void _update_layered_window_with_direct_diagnostic_dib();


      void buffer_lock_round_swap_key_buffers() override;


   };


} // namespace windowing
