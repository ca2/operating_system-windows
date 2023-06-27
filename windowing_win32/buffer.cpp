// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-02-01 23:29
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "buffer.h"
#include "windowing.h"
#include "display.h"
#include "window.h"
#include "monitor.h"
#include "acme/constant/message.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/task.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/image.h"
#ifdef REDRAW_HINTING
#include <gdiplus.h>
#endif

namespace windowing_win32
{


   //CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::size_i32 & size, i32 * piScan, ::color32_t ** ppdata);


   buffer::layered_window_buffer::layered_window_buffer()
   {

      m_hbitmap = nullptr;

      m_hdc = nullptr;

      m_hbitmapOld = nullptr;

   }


   buffer::layered_window_buffer::~layered_window_buffer()
   {

   }


   void buffer::layered_window_buffer::destroy_buffer()
   {

      if (m_hdc != nullptr)
      {

         if (m_hbitmapOld != nullptr)
         {

            ::SelectObject(m_hdc, m_hbitmapOld);

         }

         ::DeleteDC(m_hdc);

         m_hdc = nullptr;

      }

      m_hbitmapOld = nullptr;

      if (m_hbitmap != nullptr)
      {

         ::DeleteObject(m_hbitmap);

         m_hbitmap = nullptr;

         m_pixmap.clear();

      }

   }


   buffer::buffer()
   {

      m_rectangleLast.Null();

      m_bSingleBufferMode = true;

   }


   buffer::~buffer()
   {

   }


   void buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus = 

      ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      ::graphics::double_buffer::initialize_graphics_graphics(pimpl);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pwindow = pimpl->m_pwindow;

      //return estatus;

   }


   bool buffer::is_single_buffer_mode() const
   {

      return m_bSingleBufferMode;

   }


   bool buffer::create_window_device_context(const ::size_i32 & size, int iStrideParam)
   {

      if (m_hdcScreen != NULL && m_pwindow)
      {

         return true;

      }

      destroy_window_device_context();

      if (!m_pwindow)
      {

         return false;

      }

      m_hdcScreen = ::GetDCEx(get_hwnd(), nullptr, DCX_WINDOW);

      if (m_hdcScreen != nullptr)
      {

         m_bWindowDC = true;

      }
      else
      {

         m_bWindowDC = false;

         // If it has failed to get window owned device context, 
         // try to get a device context from the cache.
         //m_hdcScreen = ::GetDCEx(interaction_impl,nullptr,DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
         m_hdcScreen = ::GetDCEx(get_hwnd(), nullptr, DCX_CACHE | DCX_WINDOW);

         // If no device context could be retrieved,
         // nothing can be drawn at the screen.
         // The function failed.
         if (m_hdcScreen == nullptr)
         {

            return false;


         }

      }

      return true;

   }


   void buffer::destroy_window_device_context()
   {

      if (m_hdcScreen != nullptr)
      {

         ::ReleaseDC(get_hwnd(), m_hdcScreen);

         m_hdcScreen = nullptr;

      }

      m_bWindowDC = false;

   }


   ::graphics::buffer_item * buffer::on_begin_draw()
   {

      auto pitem = get_buffer_item();

      buffer_size_and_position(pitem);

      auto pimageBuffer = pitem->m_pimage2;

      update_buffer(pitem);

      return double_buffer::on_begin_draw();

   }


   bool buffer::update_buffer(::graphics::buffer_item * pitem)
   {

      if (is_single_buffer_mode() && m_ptaskUpdateScreen)
      {

         m_ptaskUpdateScreen->set_finish();

         m_ptaskUpdateScreen.release();

      }
      else if (!is_single_buffer_mode() && !m_ptaskUpdateScreen)
      {

         m_ptaskUpdateScreen = fork([this]()
         {

            update_screen_task();

         });

      }

      if (get_hwnd() == nullptr || ::is_null(m_pimpl))
      {

         return false;

      }

      //auto size = pitem->m_size;

      //auto pitem = get_buffer_item();

      auto & pparticleData = pitem->m_pparticleData;

      if (!pparticleData)
      {

         pparticleData = __create_new < layered_window_buffer >();

      }

      ::pointer < layered_window_buffer > playeredwindowbuffer = pparticleData;

      //pitem->m_point = m_pimpl->m_puserinteraction->const_layout().design().m_point;

      //pitem->m_size = m_pimpl->m_puserinteraction->const_layout().design().m_size;

      //information("windowing_win32::buffer::update_buffer size(%d, %d)", size.cx(), size.cy());

      if (pitem->m_size == playeredwindowbuffer->m_pixmap.size())
      {

         return false;

      }

      ::image32_t * pimage32 = nullptr;

      int iScan = -1;

      auto pwindowing = m_pimpl->m_puserinteraction->windowing();

      auto pdisplay = pwindowing->display();

      auto sizeLargeInternalBitmap = pdisplay->get_monitor_union_size();

      if (pitem->m_size.cx() > sizeLargeInternalBitmap.cx())
      {

         sizeLargeInternalBitmap.cx() = pitem->m_size.cx();

      }

      if (pitem->m_size.cy() > sizeLargeInternalBitmap.cy())
      {

         sizeLargeInternalBitmap.cy() = pitem->m_size.cy();

      }

      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cx() > sizeLargeInternalBitmap.cx())
      {

         sizeLargeInternalBitmap.cx() = playeredwindowbuffer->m_pixmap.m_sizeRaw.cx();

      }

      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cy() > sizeLargeInternalBitmap.cy())
      {

         sizeLargeInternalBitmap.cy() = playeredwindowbuffer->m_pixmap.m_sizeRaw.cy();

      }

      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cx() < sizeLargeInternalBitmap.cx()
         || playeredwindowbuffer->m_pixmap.m_sizeRaw.cy() < sizeLargeInternalBitmap.cy())
      {

         HBITMAP hbitmap = ::windows::create_windows_dib(sizeLargeInternalBitmap, &iScan, &pimage32);

         if (hbitmap == nullptr
            || pimage32 == nullptr
            || iScan == 0)
         {

            if (hbitmap != nullptr)
            {

               ::DeleteObject(hbitmap);

            }

            return false;

         }

         playeredwindowbuffer->m_pixmap.init(sizeLargeInternalBitmap, pimage32, iScan);

         if (playeredwindowbuffer->m_hbitmap != nullptr)
         {

            ::DeleteObject(playeredwindowbuffer->m_hbitmap);

         }

         playeredwindowbuffer->m_hbitmap = hbitmap;

         bool bCreatedCompatibleDC = false;

         if (playeredwindowbuffer->m_hdc == nullptr)
         {

            playeredwindowbuffer->m_hdc = ::CreateCompatibleDC(nullptr);

            bCreatedCompatibleDC = true;

         }

         if (playeredwindowbuffer->m_hdc == nullptr)
         {

            destroy_buffer();

            throw ::exception(error_null_pointer);

         }

         HBITMAP hbitmapPrevious = (HBITMAP) ::SelectObject(playeredwindowbuffer->m_hdc, playeredwindowbuffer->m_hbitmap);

         if (bCreatedCompatibleDC)
         {

            playeredwindowbuffer->m_hbitmapOld = hbitmapPrevious;

         }

      }

      playeredwindowbuffer->m_pixmap.m_size = pitem->m_size;

      if (pitem->m_pimage2->host(playeredwindowbuffer->m_pixmap))
      {

         m_bDibIsHostingBuffer = true;

      }
      else
      {

         try
         {

            pitem->m_pimage2->create(playeredwindowbuffer->m_pixmap.m_sizeRaw);

         }
         catch (...)
         {

            return false;

         }

         m_bDibIsHostingBuffer = false;

      }

      return true;

   }


   void buffer::destroy_buffer()
   {

      auto pitem = get_buffer_item();

      if (pitem)
      {

         ::pointer < layered_window_buffer > playeredwindowbuffer = pitem->m_pparticleData;

         if (playeredwindowbuffer)
         {

            playeredwindowbuffer->destroy_buffer();

            pitem->m_pparticleData.release();

         }

      }

      double_buffer::destroy_buffer();

   }


   bool buffer::update_screen()
   {

      if (m_ptaskUpdateScreen)
      {

         m_ptaskUpdateScreen->post_procedure([this]()
            {

               double_buffer::update_screen();

});

         m_eventUpdateScreen.SetEvent();

         return true;

      }

      return double_buffer::update_screen();

   }


   ::point_i32 g_pointLastBottomRight;


   bool buffer::on_update_screen(::graphics::buffer_item * pitem)
   {

      if (!pitem->m_pimage2.ok())
      {

         return false;

      }

      ::user::interaction * pinteraction = m_pimpl->m_puserinteraction;

      if (::is_null(pinteraction))
      {

         return false;

      }

      HWND hwnd = get_hwnd();

      auto uExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);

      bool bLayered = (uExStyle & WS_EX_LAYERED) != 0;

      bool bAsync = false;

      bool bWasVisible = false;

      index iScreenBuffer = get_screen_index();

      ::pointer < layered_window_buffer > playeredwindowbuffer = pitem->m_pparticleData;

      auto sizeLayeredWindowBuffer = playeredwindowbuffer->m_pixmap.size();

      //information("windowing_win32::buffer::update_screen size(%d, %d)", size.cx(), size.cy());

      auto pixmapRawData = playeredwindowbuffer->m_pixmap.m_pimage32Raw;

      auto pimageRawData = pitem->m_pimage2->m_pimage32Raw;

      if (m_bDibIsHostingBuffer && pimageRawData == pixmapRawData)
      {

      }
      else if (m_bDibIsHostingBuffer && pitem->m_pimage2->on_host_read_pixels(playeredwindowbuffer->m_pixmap))
      {


      }
      else
      {

         if (sizeLayeredWindowBuffer != pitem->m_pimage2->size())
         {

            return false;

         }

         pitem->m_pimage2->map();

         ::copy_image32(playeredwindowbuffer->m_pixmap, sizeLayeredWindowBuffer, pitem->m_pimage2);

      }

      if (!bLayered)
      {

         //HideCaret(get_hwnd());

         ::RedrawWindow(get_hwnd(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

         //ShowCaret(get_hwnd());

         return true;


      }


      try
      {

         //auto & layout = m_pimpl->m_puserinteraction->const_layout();

         //auto point = layout.output().origin();

         //auto size = layout.output().size();

         auto point = pitem->m_point;

         auto size = pitem->m_size;

         auto sizeBuffer = pitem->m_pimage2->size();

         //if (size.cx() < sizeDrawn.cx() && size.cy() < sizeDrawn.cy())
         //if (size != sizeDrawn || sizeDesign != size)
         if (size != sizeBuffer)
         {

            error() <<"Requested size is different of buffer size.";
            error() <<"Requested size: " << size;
            error() <<"Buffer size: " << sizeBuffer;
            //error() <<"Design size: " << sizeDesign;

            //m_pimpl->m_puserinteraction->set_need_redraw();

            m_pimpl->m_puserinteraction->post_redraw();

            return false;

         }
         else if (sizeLayeredWindowBuffer != sizeBuffer)
         {

            error() <<"Os buffer size is different of buffer size.";
            error() <<"Os buffer size: " << sizeLayeredWindowBuffer;
            error() <<"Buffer size: " << sizeBuffer;

            m_pimpl->m_puserinteraction->post_redraw();

            return false;

         }
         //else
         //{

         if (!create_window_device_context(size, playeredwindowbuffer->m_pixmap.m_iScan))
         {

            return false;

         }

         //if (!m_bDibIsHostingBuffer)
         //{
         //   try
         //   {

         //      pimage->map();

         //      ::copy_image32(cx, cy, m_pcolorref, m_iScan, pimage->get_data(), pimage->scan_size());

         //   }
         //   catch (...)
         //   {

         //   }
         //}

         //if (bLayered)
         //   //&& m_pimpl != nullptr
         //   //&& m_pimpl->m_puserinteraction != nullptr
         //   //&& m_pimpl->m_puserinteraction->_is_window_visible())
         {

            //if (!m_pimpl->m_bOkToUpdateScreen)
            //{

            //   output_debug_string("nok yet to update the screen \n");

            //   m_pimpl->m_puserinteraction->set_need_redraw();

            //}
            //else
            //{

            ::point_i32 pointSrc = { 0 };

            BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

            //::SelectClipRgn(m_hdcScreen, nullptr);

#ifdef REDRAW_HINTING

            {
               //HBRUSH h = ::CreateSolidBrush(rgb(255, 240, 155));

               //rectangle r;

               //rectangle.left = 10;
               //rectangle.right = 20;
               //rectangle.top = 0;
               //rectangle.bottom = sz.cy();

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);

               Gdiplus::Graphics g(m_hdcScreen);

               Gdiplus::Rect rectangle;

               rectangle.X = 10;
               rectangle.Width = 10;
               rectangle.Y = 0;
               rectangle.Height = size.cy();

               Gdiplus::SolidBrush b(Gdiplus::Color(argb(255, 155, 240, 255)));

               g.FillRectangle(&b, rectangle);

            }

#endif

            SelectClipRgn(m_hdcScreen, nullptr);

            SelectClipRgn(playeredwindowbuffer->m_hdc, nullptr);

            SetViewportOrgEx(m_hdcScreen, 0, 0, nullptr);

            SetViewportOrgEx(playeredwindowbuffer->m_hdc, 0, 0, nullptr);

#ifdef REDRAW_HINTING

            {

               //HBRUSH h = ::CreateSolidBrush(rgb(180, 200, 255));

               //rectangle r;

               //rectangle.left = 20;
               //rectangle.right = 30;
               //rectangle.top = 0;
               //rectangle.bottom = sz.cy();

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);
               Gdiplus::Graphics g(buffer.m_hdc);

               Gdiplus::Rect rectangle;

               rectangle.X = 0;
               rectangle.Y = 0;
               rectangle.Width = size.cx();
               rectangle.Height = size.cy();

               Gdiplus::SolidBrush b(Gdiplus::Color(argb(127, 255, 210, 170)));

               g.FillRectangle(&b, rectangle);
            }

#endif

#ifdef __DEBUG

            //               {

                              //HBRUSH h = ::CreateSolidBrush(rgb(180, 200, 255));

                              //rectangle r;

                              //rectangle.left = 20;
                              //rectangle.right = 30;
                              //rectangle.top = 0;
                              //rectangle.bottom = sz.cy();

                              //::FillRect(m_hdc, rectangle, h);

                              //::DeleteObject(h);

            //               }


#ifdef SQUARY_HINT
            {

               Gdiplus::Graphics g(m_hdc);

               Gdiplus::Rect rectangle;

               rectangle.X = 0;
               rectangle.Y = 0;

               rectangle.Width = 49;
               rectangle.Height = 49;

               Gdiplus::SolidBrush b(Gdiplus::Color(argb(128, 255, 180, 170)));

               g.FillRectangle(&b, rectangle);

               Gdiplus::Font font(L"Segoe UI", 20);



               wstring wstr;

               int i = m_pimpl->prop("iSquaryHint");
               string str;
               str.format("%d", i);
               //iSquaryHint++;
               wstr = str;
               m_pimpl->prop("iSquaryHint") = i + 1;

               Gdiplus::SolidBrush b2(Gdiplus::Color(argb(255, 155, 120, 50)));

               Gdiplus::PointF origin(0.f, 0.f);

               g.DrawString(wstr, -1, &font, origin, &b2);

            }

#endif


#endif // __DEBUG


            //point.x() = 100;

            //point.y() = 100;

            //size.cx() = 200;

            //size.cy() = 200;

            //::SetWindowPos(get_hwnd(), HWND_TOPMOST, point.x(), point.y(), size.cx(), size.cy(), SWP_NOZORDER);

            string strType = __type_name(m_pimpl->m_puserinteraction);

            if (strType.case_insensitive_contains("font_format"))
            {

               information() << "font_format going to UpdateLayeredWindow";

               bool bVisible = IsWindowVisible(get_hwnd());

               if (bVisible)
               {

                  information() << "font_format is visible!!";

               }
               else
               {

                  information() << "font_format ISN'T visible!!";

               }

               RECT rectangleProbe;

               if (::GetWindowRect(get_hwnd(), &rectangleProbe))
               {

                  information() << "GetWindowRect (%d, %d) - (%d, %d)", rectangleProbe.left, rectangleProbe.top, rectangleProbe.right, rectangleProbe.bottom;

               }

            }

            bool bOk = true;

            bool bSizeOrPositionChanged = false;

            //if (layout.design().is_screen_visible())
            {

               //HWND hwnd = get_hwnd();

               //string str;

               //rectangle_i32 rectangleDrawing(point, size);

               rectangle_i32 rectangleWindowCurrent;

               GetWindowRect(hwnd, (RECT *)&rectangleWindowCurrent);

                  //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
               {


                  //               }
                                 //else
                                 //{

                                 //   information("Update discarded");

                                 //}


                                 //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
                                 //{

                  UINT uFlagsSetWindowPos = SWP_NOZORDER
                     | SWP_ASYNCWINDOWPOS
                     | SWP_FRAMECHANGED
                     | SWP_NOREDRAW
                     | SWP_NOCOPYBITS
                     | SWP_DEFERERASE
                     | SWP_NOACTIVATE
                     | SWP_SHOWWINDOW;


                  ::UpdateLayeredWindow(hwnd, m_hdcScreen, (POINT *)&point, (SIZE *)&size, playeredwindowbuffer->m_hdc, (POINT *)&pointSrc, make_u32(0, 0, 0, 0), &blendPixelFunction, ULW_ALPHA);

                  if (rectangleWindowCurrent.top_left() != point
                     || rectangleWindowCurrent.size() != size)
                  {

                     ::SetWindowPos(hwnd, nullptr, point.x(), point.y(), size.cx(), size.cy(), uFlagsSetWindowPos);

                     bSizeOrPositionChanged = true;

                  }

                  if (m_pimpl->m_puserinteraction->const_layout().window().origin() != point)
                  {

                     m_pimpl->m_puserinteraction->post_message(e_message_reposition, 0, point);

                  }

                  if (m_pimpl->m_puserinteraction->const_layout().window().size() != size)
                  {

                     m_pimpl->m_puserinteraction->post_message(e_message_size, 0, size);

                  }

               }
               //else
               //{
               //   information("Update discarded");

               //}

               ::point_i32 pointBottomRight = point + size;

               //if (g_pointLastBottomRight != pointBottomRight)
               //{

               //   information("UpdateLayeredWindow Changed");

               //   g_pointLastBottomRight = pointBottomRight;

               //}

               //information("UpdateLayeredWindow Bottom Right (%d, %d)", pointBottomRight.x(), pointBottomRight.y());


            }

            //m_pimpl->m_puserinteraction->post_message(message_do_show_window);

            m_pimpl->m_puserinteraction->window_show_change_visibility();

            if (bSizeOrPositionChanged)
            {

               m_pimpl->m_puserinteraction->on_visual_applied();

            }

            //#ifdef WINDOWS_DESKTOP
            //               if ((m_pimpl->m_puserinteraction->GetExStyle() & WS_EX_LAYERED))
            //#endif
            //               {
            //
            //                  u32 uFlags = SWP_NOREDRAW
            //                     | SWP_NOCOPYBITS
            //                     | SWP_NOACTIVATE
            //                     | SWP_NOOWNERZORDER
            //                     | SWP_DEFERERASE
            //                  | SWP_NOZORDER;
            //                  ::SetWindowPos(get_hwnd(), NULL, point.x(), point.y(), size.cx(), size.cy(), 
            //                     uFlags);
            //                  m_pimpl->on_visual_applied();
            //
            //               }

                           //::rectangle_i32 r3;

                           //GetWindowRect(m_oswindow, &r3);

                           //::rectangle_i32 r4;

                           //GetClientRect(m_oswindow, &r4);

                           //::SendMessage(get_hwnd(), WM_PRINT, (wparam)m_hdcScreen, PRF_OWNED | PRF_CHILDREN);

#ifdef __DEBUG

            HBITMAP b1 = (HBITMAP) ::GetCurrentObject(playeredwindowbuffer->m_hdc, OBJ_BITMAP);

            //if (b1 != buffer.m_hbitmap)
            //{

            //   output_debug_string("damn0");

            //}

            //BITMAP bmp1;

            //::GetObject(b1, sizeof(BITMAP), &bmp1);

            //if (bmp1.bmHeight != size.cy())
            //{

            //   output_debug_string("damn1");
            //}

            //{

            //   RECT rClipScreen;

            //   int iResult = ::GetClipBox(m_hdcScreen, &rClipScreen);

            //   if (iResult == ERROR_REGION || iResult == NULLREGION)
            //   {

            //   }
            //   else
            //   {

            //      if (::height(rClipScreen) != size.cy())
            //      {

            //         output_debug_string("damn2");

            //      }

            //   }

            //}

            //{

            //   RECT rClip;

            //   int iResult = ::GetClipBox(buffer.m_hdc, &rClip);

            //   if (iResult == ERROR_REGION || iResult == NULLREGION)
            //   {
            //   }
            //   else
            //   {

            //      if (::height(rClip) != size.cy())
            //      {

            //         output_debug_string("damn3");

            //      }

            //   }

            //}

            if (!bOk)
            {

               output_debug_string("UpdateLayeredWindow failed");

            }

#endif // __DEBUG

         }
         //else
         //{

         //}

         //}

      }
      catch (...)
      {


      }

      if (!m_bWindowDC)
      {

         destroy_window_device_context();

      }

      return true;

   }


   void buffer::update_screen_task()
   {

      while (::task_get_run())
      {

         m_eventUpdateScreen.wait(1_s);

         m_eventUpdateScreen.ResetEvent();

         m_ptaskUpdateScreen->run_posted_procedures();

      }

   }


   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      bool bOk1 = double_buffer::buffer_lock_round_swap_key_buffers();

      if (!m_pimpl || !m_pimpl->m_pprodevian)
      {

         return false;

      }

      bool bOk2 = bitmap_source_buffer::buffer_lock_round_swap_key_buffers();

      return bOk1 && bOk2;

   }


   HWND buffer::get_hwnd() const
   {

      return (HWND)m_pwindow->get_os_data();

   }


} // namespace windows




