// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-02-01 23:29
#include "framework.h"

//#define REDRAW_HINTING
#ifdef REDRAW_HINTING
#include <gdiplus.h>
#endif

namespace windowing_win32
{


   //CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::size_i32 & size, i32 * piScan, ::color32_t ** ppdata);


   buffer::os_buffer::os_buffer()
   {

      m_hbitmap = nullptr;

      m_hdc = nullptr;

      m_hbitmapOld = nullptr;

   }


   buffer::os_buffer::~os_buffer()
   {

   }


   void buffer::os_buffer::destroy_buffer()
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

      defer_create_mutex();

      m_rectangleLast.Null();

   }


   buffer::~buffer()
   {

   }


   void buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus = 
      
      ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

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


   bool buffer::create_os_buffer(const ::size_i32 & size, int iStrideParam)
   {

      if (m_hdcScreen != NULL && m_pwindow)
      {

         return true;

      }

      destroy_os_buffer();

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


   void buffer::destroy_os_buffer()
   {

      if (m_hdcScreen != nullptr)
      {

         ::ReleaseDC(get_hwnd(), m_hdcScreen);

         m_hdcScreen = nullptr;

      }

      m_bWindowDC = false;

   }


   ::draw2d::graphics * buffer::on_begin_draw()
   {

      auto sizeWindow = window_size();

      auto pimageBuffer = get_buffer_image();

      update_buffer(sizeWindow);

      return pimageBuffer->get_graphics();

      //return double_buffer::on_begin_draw();

   }


   bool buffer::update_buffer(const ::size_i32 & sizeParam, int iStrideParam)
   {

      if (get_hwnd() == nullptr || ::is_null(m_pimpl))
      {

         return false;

      }

      os_buffer & buffer = m_osbuffera[m_iCurrentBuffer];

      auto size = sizeParam;

      FORMATTED_INFORMATION("windowing_win32::buffer::update_buffer size(%d, %d)", size.cx, size.cy);

      if (size == buffer.m_pixmap.size())
      {

         return false;

      }

      ::color32_t * pcolorref = nullptr;

      int iScan = -1;

      auto psession = m_pcontext->get_session();

      auto puser = psession->m_paurasession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      auto sizeMonitor = pdisplay->get_monitor_union_size();

      if (size.cx > sizeMonitor.cx)
      {

         sizeMonitor.cx = size.cx;

      }

      if (size.cy > sizeMonitor.cy)
      {

         sizeMonitor.cy = size.cy;

      }

      if (buffer.m_pixmap.m_sizeRaw.cx < sizeMonitor.cx
         || buffer.m_pixmap.m_sizeRaw.cy < sizeMonitor.cy)
      {


         HBITMAP hbitmap = create_windows_dib(sizeMonitor, &iScan, &pcolorref);

         if (hbitmap == nullptr
            || pcolorref == nullptr
            || iScan == 0)
         {

            if (hbitmap != nullptr)
            {

               ::DeleteObject(hbitmap);

            }

            return false;

         }

         buffer.m_pixmap.init(sizeMonitor, pcolorref, iScan);

         if (buffer.m_hbitmap != nullptr)
         {

            ::DeleteObject(buffer.m_hbitmap);

         }

         buffer.m_hbitmap = hbitmap;

         bool bCreatedCompatibleDC = false;

         if (buffer.m_hdc == nullptr)
         {

            buffer.m_hdc = ::CreateCompatibleDC(nullptr);

            bCreatedCompatibleDC = true;

         }

         if (buffer.m_hdc == nullptr)
         {

            destroy_buffer();

            throw ::exception(error_null_pointer);

         }

         HBITMAP hbitmapPrevious = (HBITMAP) ::SelectObject(buffer.m_hdc, buffer.m_hbitmap);

         if (bCreatedCompatibleDC)
         {

            buffer.m_hbitmapOld = hbitmapPrevious;

         }

      }

      buffer.m_pixmap.m_size = size;

      auto pimageBuffer = get_buffer_image();

      if (pimageBuffer->host(buffer.m_pixmap))
      {

         m_bDibIsHostingBuffer = true;

      }
      else
      {

         try
         {

            pimageBuffer->create(size);

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

      m_osbuffera[m_iCurrentBuffer].destroy_buffer();

      double_buffer::destroy_buffer();

   }


   bool buffer::update_screen()
   {

      return double_buffer::update_screen();

   }


   ::point_i32 g_pointLastBottomRight;


   bool buffer::update_screen(::image * pimage)
   {

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

      if (!pimage)
      {

         return false;

      }

      index iScreenBuffer = get_screen_index();

      auto & buffer = m_osbuffera[iScreenBuffer];

      auto size = buffer.m_pixmap.size();

      FORMATTED_INFORMATION("windowing_win32::buffer::update_screen size(%d, %d)", size.cx, size.cy);

      auto pixmapData = buffer.m_pixmap.colorref();

      auto pimageData= pimage->colorref();

      if (m_bDibIsHostingBuffer && pimageData == pixmapData)
      {

      }
      else if (m_bDibIsHostingBuffer && pimage->on_host_read_pixels(buffer.m_pixmap))
      {


      }
      else
      {

         size = minimum(size, pimage->size());

         pimage->map();

         ::copy_colorref(buffer.m_pixmap, size, pimage);

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

         if (!create_os_buffer(size, buffer.m_pixmap.m_iScan))
         {

            return false;

         }

         auto & layout = m_pimpl->m_puserinteraction->layout();

         //auto point = layout.output().origin();

         //auto size = layout.output().size();

         auto point = layout.design().origin();

         auto size = layout.design().size();

         //if (!m_bDibIsHostingBuffer)
         //{
         //   try
         //   {

         //      pimage->map();

         //      ::copy_colorref(cx, cy, m_pcolorref, m_iScan, pimage->get_data(), pimage->scan_size());

         //   }
         //   catch (...)
         //   {

         //   }
         //}

         if (bLayered)
            //&& m_pimpl != nullptr
            //&& m_pimpl->m_puserinteraction != nullptr
            //&& m_pimpl->m_puserinteraction->_is_window_visible())
         {

            //if (!m_pimpl->m_bOkToUpdateScreen)
            //{

            //   output_debug_string("nok yet to update the screen \n");

            //   m_pimpl->m_puserinteraction->set_need_redraw();

            //}
            //else
            //{

            POINT_I32 pointSrc = { 0 };

            BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

            //::SelectClipRgn(m_hdcScreen, nullptr);

#ifdef REDRAW_HINTING

            {
               //HBRUSH h = ::CreateSolidBrush(rgb(255, 240, 155));

               //rectangle r;

               //rectangle.left = 10;
               //rectangle.right = 20;
               //rectangle.top = 0;
               //rectangle.bottom = sz.cy;

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);

               Gdiplus::Graphics g(m_hdcScreen);

               Gdiplus::Rect rectangle;

               rectangle.X = 10;
               rectangle.Width = 10;
               rectangle.Y = 0;
               rectangle.Height = size.cy;

               Gdiplus::SolidBrush b(Gdiplus::Color(argb(255, 155, 240, 255)));

               g.FillRectangle(&b, rectangle);

            }

#endif

            SelectClipRgn(m_hdcScreen, nullptr);

            SelectClipRgn(buffer.m_hdc, nullptr);

            SetViewportOrgEx(m_hdcScreen, 0, 0, nullptr);

            SetViewportOrgEx(buffer.m_hdc, 0, 0, nullptr);

#ifdef REDRAW_HINTING

            {

               //HBRUSH h = ::CreateSolidBrush(rgb(180, 200, 255));

               //rectangle r;

               //rectangle.left = 20;
               //rectangle.right = 30;
               //rectangle.top = 0;
               //rectangle.bottom = sz.cy;

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);
               Gdiplus::Graphics g(buffer.m_hdc);

               Gdiplus::Rect rectangle;

               rectangle.X = 0;
               rectangle.Y = 0;
               rectangle.Width = size.cx;
               rectangle.Height = size.cy;

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
                              //rectangle.bottom = sz.cy;

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


            //point.x = 100;

            //point.y = 100;

            //size.cx = 200;

            //size.cy = 200;

            //::SetWindowPos(get_hwnd(), HWND_TOPMOST, point.x, point.y, size.cx, size.cy, SWP_NOZORDER);

            string strType = __type_name(m_pimpl->m_puserinteraction);

            if (strType.contains_ci("font_format"))
            {

               INFORMATION("font_format going to UpdateLayeredWindow");

               bool bVisible = IsWindowVisible(get_hwnd());

               if (bVisible)
               {

                  INFORMATION("font_format is visible!!");

               }
               else
               {

                  INFORMATION("font_format ISN'T visible!!");

               }

               RECT rectangleProbe;

               if (::GetWindowRect(get_hwnd(), &rectangleProbe))
               {

                  INFORMATION("GetWindowRect (%d, %d) - (%d, %d)", rectangleProbe.left, rectangleProbe.top, rectangleProbe.right, rectangleProbe.bottom);

               }

            }

            bool bOk = true;

            if (layout.design().is_screen_visible())
            {

               HWND hwnd = get_hwnd();

               string str;

               rectangle_i32 rectangleDrawing(point, size);

               rectangle_i32 rectangleWindowCurrent;

               GetWindowRect(hwnd, (RECT *) &rectangleWindowCurrent);

               //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
               {


//               }
               //else
               //{

               //   TRACE("Update discarded");

               //}


               //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
               //{


                  ::UpdateLayeredWindow(hwnd, m_hdcScreen, (POINT*)&point, (SIZE*)&size, buffer.m_hdc, (POINT*)&pointSrc, rgb(0, 0, 0), &blendPixelFunction, ULW_ALPHA);
                  //::SetWindowPos(hwnd, nullptr,
                  //   rectangleDrawing.left,
                  //   rectangleDrawing.top,
                  //   rectangleDrawing.width(),
                  //   rectangleDrawing.height(),
                  //   SWP_NOZORDER
                  //   | SWP_ASYNCWINDOWPOS
                  //   | SWP_FRAMECHANGED
                  //   | SWP_NOREDRAW
                  //   | SWP_NOCOPYBITS
                  //   | SWP_DEFERERASE
                  //   | SWP_NOACTIVATE);

               }
               //else
               //{
               //   TRACE("Update discarded");

               //}

               ::point_i32 pointBottomRight = point + size;

               //if (g_pointLastBottomRight != pointBottomRight)
               //{

               //   TRACE("UpdateLayeredWindow Changed");

               //   g_pointLastBottomRight = pointBottomRight;

               //}

               //TRACE("UpdateLayeredWindow Bottom Right (%d, %d)", pointBottomRight.x, pointBottomRight.y);


            }

            //m_pimpl->m_puserinteraction->post_message(message_do_show_window);

            m_pimpl->m_puserinteraction->window_show_change_visibility();

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
            //                  ::SetWindowPos(get_hwnd(), NULL, point.x, point.y, size.cx, size.cy, 
            //                     uFlags);
            //                  m_pimpl->on_visual_applied();
            //
            //               }

                           //RECTANGLE_I32 r3;

                           //GetWindowRect(m_oswindow, &r3);

                           //RECTANGLE_I32 r4;

                           //GetClientRect(m_oswindow, &r4);

                           //::SendMessage(get_hwnd(), WM_PRINT, (wparam)m_hdcScreen, PRF_OWNED | PRF_CHILDREN);

#ifdef __DEBUG

            HBITMAP b1 = (HBITMAP) ::GetCurrentObject(buffer.m_hdc, OBJ_BITMAP);

            //if (b1 != buffer.m_hbitmap)
            //{

            //   output_debug_string("damn0");

            //}

            //BITMAP bmp1;

            //::GetObject(b1, sizeof(BITMAP), &bmp1);

            //if (bmp1.bmHeight != size.cy)
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

            //      if (::height(rClipScreen) != size.cy)
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

            //      if (::height(rClip) != size.cy)
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
         else
         {

         }

      }
      catch (...)
      {


      }

      if (!m_bWindowDC)
      {

         destroy_os_buffer();

      }

      return true;

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


} // namespace windows




