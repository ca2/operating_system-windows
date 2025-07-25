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
#include "acme/platform/application.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme_windowing_win32/activation_token.h"
#include "acme/user/user/_string.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/system.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/image.h"
//#define REDRAW_HINTING
#ifdef REDRAW_HINTING
#include <gdiplus.h>
#endif

CLASS_DECL_AURA::int_point __get_bottom_right();
CLASS_DECL_AURA void __set_bottom_right(const ::int_point & pointBottomRight);


namespace windowing_win32
{


   //CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::int_size & size, int * piScan, ::color32_t ** ppdata);


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

      //m_bAllocateBiggerBuffer = true;

   }


   buffer::~buffer()
   {

   }


   void buffer::initialize_graphics_graphics(::windowing::window * pimpl)
   {

      //auto estatus = 

      ::graphics::bitmap_source_buffer::initialize_graphics_graphics(pimpl);

      defer_create_synchronization();

      m_bSingleBufferMode = system()->draw2d()->graphics_context_supports_single_buffer_mode();

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

      //m_pwindow = pimpl->m_pwindow;

      //return estatus;

   }


   bool buffer::is_single_buffer_mode() const
   {

      return m_bSingleBufferMode;

   }


   bool buffer::create_window_device_context(const ::int_size & size, int iStrideParam)
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         return true;

      }

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

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         return;

      }

      if (m_hdcScreen != nullptr)
      {

         ::ReleaseDC(get_hwnd(), m_hdcScreen);

         m_hdcScreen = nullptr;

      }

      m_bWindowDC = false;

   }


   bool buffer::_on_begin_draw(::graphics::buffer_item * pbufferitem)
   {

      //auto pbufferitem = get_buffer_item();

      //buffer_size_and_position(pbufferitem);

      //if (pbufferitem->m_size.is_empty())
      //{

      //}

      auto pimageBuffer = pbufferitem->m_pimage2;

      if (pimageBuffer->m_size != pbufferitem->m_sizeBufferItemDraw)
      {

         if (!update_buffer(pbufferitem))
         {

            return false;

         }

      }

      if (!m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (!double_buffer::_on_begin_draw(pbufferitem))
         {

            return false;

         }

      }

      return true;

   }


   void buffer::_defer_update_screen_task()
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

   }


   bool buffer::update_buffer(::graphics::buffer_item * pbufferitem)
   {

      _defer_update_screen_task();

      if (get_hwnd() == nullptr || ::is_null(m_pwindow))
      {

         return false;

      }

      HWND hwnd = get_hwnd();

      auto uExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);

      bool bLayered = (uExStyle & WS_EX_LAYERED) != 0;

      ::pointer < layered_window_buffer > playeredwindowbuffer;

      if (bLayered && ! m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         auto & pparticleData = pbufferitem->m_pparticleData;

         if (!pparticleData)
         {

            pparticleData = __create_new < layered_window_buffer >();

         }

         playeredwindowbuffer = pparticleData;

         if (pbufferitem->m_sizeBufferItemDraw == playeredwindowbuffer->m_pixmap.size())
         {

            return false;

         }

      }

      ::image32_t * pimage32 = nullptr;

      int iScan = -1;

      ::int_size sizeAllocate;

      auto pwindowing = m_pwindow->user_interaction()->windowing();

      auto pdisplay = pwindowing->display();

      auto rectangleUnion = pdisplay->get_monitor_union_rectangle();

      auto sizeLargeInternalBitmap = rectangleUnion.size();

      if (pbufferitem->m_sizeBufferItemDraw.cx() > sizeLargeInternalBitmap.cx())
      {

         sizeLargeInternalBitmap.cx() = pbufferitem->m_sizeBufferItemDraw.cx();

      }

      if (pbufferitem->m_sizeBufferItemDraw.cy() > sizeLargeInternalBitmap.cy())
      {

         sizeLargeInternalBitmap.cy() = pbufferitem->m_sizeBufferItemDraw.cy();

      }

      if (playeredwindowbuffer)
      {

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

            if (hbitmap == nullptr || pimage32 == nullptr || iScan == 0)
            {

               if (hbitmap != nullptr)
               {

                  ::DeleteObject(hbitmap);

               }

               return false;

            }

            playeredwindowbuffer->m_pixmap.initialize(sizeLargeInternalBitmap, pimage32, iScan);

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

         playeredwindowbuffer->m_pixmap.m_size = pbufferitem->m_sizeBufferItemDraw;

         if (pbufferitem->m_pimage2->host(playeredwindowbuffer->m_pixmap, m_pwindow))
         {

            m_bDibIsHostingBuffer = true;

         }
         else
         {

            try
            {

               pbufferitem->m_pimage2->create(playeredwindowbuffer->m_pixmap.m_sizeRaw);

            }
            catch (...)
            {

               return false;

            }

            m_bDibIsHostingBuffer = false;

         }

      }
      else
      {

         if (!pbufferitem->m_pgraphics)
         {

            __øconstruct(pbufferitem->m_pgraphics);

            auto puserinteraction = dynamic_cast < ::user::interaction * >( m_pwindow->m_pacmeuserinteraction.m_p);

            //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
            //{

            //   pbufferitem->m_pgraphics->create_offscreen_graphics_for_swap_chain_blitting(pbufferitem->m_sizeBufferItemDraw);

            //}
            //else
            //{

            pbufferitem->m_pgraphics->create_for_window_draw2d(puserinteraction, pbufferitem->m_sizeBufferItemDraw);

               //pbufferitem->m_pgraphics->create_memory_graphics(pbufferitem->m_sizeBufferItemDraw);

//            }

            //pbufferitem->m_pgraphics->set_hint_window_output();

            //pbufferitem->m_pgraphics->create_window_graphics(m_pwindow);

         }
         else
         {

            pbufferitem->m_pgraphics->defer_set_size(pbufferitem->m_sizeBufferItemDraw);

         }


      }

      return true;

   }


   void buffer::destroy_buffer()
   {

      auto pbufferitem = get_buffer_item();

      if (pbufferitem)
      {

         ::pointer < layered_window_buffer > playeredwindowbuffer = pbufferitem->m_pparticleData;

         if (playeredwindowbuffer)
         {

            playeredwindowbuffer->destroy_buffer();

            pbufferitem->m_pparticleData.release();

         }

      }

      double_buffer::destroy_buffer();

   }


   void buffer::update_screen()
   {

      //if (m_pwindow->m_ptaskUpdateScreen)
      //{

      //   m_pwindow->m_ptaskUpdateScreen->_post([this]()
      //      {

      //         double_buffer::update_screen();

      //      });

      //   m_happeningUpdateScreen.set_happening();

      //   return;
      //}

      if (m_ptaskUpdateScreen)
      {

         m_ptaskUpdateScreen->main_post()
            << [this]()
            {

               double_buffer::update_screen();

            };

         m_happeningUpdateScreen.set_happening();

         //return true;

         return;

      }

      return double_buffer::update_screen();

   }


   void buffer::destroy()
   {

      ::graphics::double_buffer::destroy();

      destroy_buffer();

   }


   ::int_point g_pointLastBottomRight;


   void buffer::on_update_screen(::graphics::buffer_item * pbufferitem)
   {

      ::user::interaction * pinteraction = m_pwindow->user_interaction();

      if (::is_null(pinteraction))
      {

         throw ::exception(error_wrong_state);

      }

      HWND hwnd = get_hwnd();

      auto uExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);

      bool bLayered = (uExStyle & WS_EX_LAYERED) != 0;

      bool bAsync = false;

      bool bWasVisible = false;

      ::collection::index iScreenBuffer = get_screen_index();

      ::pointer < layered_window_buffer > playeredwindowbuffer = pbufferitem->m_pparticleData;
      ::int_size sizeLayeredWindowBuffer;
      if (playeredwindowbuffer)
      {

         if (!pbufferitem->m_pimage2.ok())
         {

            throw ::exception(error_wrong_state);

         }



         sizeLayeredWindowBuffer = playeredwindowbuffer->m_pixmap.size();

         //informationf("windowing_win32::buffer::update_screen size(%d, %d)", size.cx(), size.cy());

         auto pixmapRawData = playeredwindowbuffer->m_pixmap.m_pimage32Raw;

         auto pimageRawData = pbufferitem->m_pimage2->m_pimage32Raw;

         if (m_bDibIsHostingBuffer && pimageRawData == pixmapRawData)
         {

         }
         else if (m_bDibIsHostingBuffer && pbufferitem->m_pimage2->on_host_read_pixels(playeredwindowbuffer->m_pixmap))
         {


         }
         else
         {

            auto sizeBufferImage = pbufferitem->m_pimage2->size();

            if (sizeLayeredWindowBuffer != sizeBufferImage)
            {

               if (m_pwindow->m_timeLastDrawGuard1.elapsed() > 1_s)
               {

                  throw ::exception(error_failed);

               }

               return;

            }

            pbufferitem->m_pimage2->map();

            playeredwindowbuffer->m_pixmap.copy(sizeLayeredWindowBuffer, pbufferitem->m_pimage2);

         }

      }
      ::cast < ::windowing_win32::window  > pwindow = m_pwindow;
      //if (!bLayered && !pwindow->m_hglrcProto)
      if (!bLayered && !m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         //::cast < ::windowing_win32::window  > pwindow = m_pwindow;

         //if (pwindow && m_papplication->m_bUseSwapChainWindow)
         //{

         //   auto pgraphics = pbufferitem->g();

         //   pgraphics->do_on_context([this, pgraphics,
         //      pbufferitem]
         //   {

         //      pgraphics->on_present();

         //   });

         //}
         //else
         {
            //HideCaret(get_hwnd());

            ::RedrawWindow(get_hwnd(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

         }

         //ShowCaret(get_hwnd());

         return;


      }


      try
      {

         //auto & layout = m_pwindow->user_interaction()->const_layout();

         //auto point = layout.output().origin();

         //auto size = layout.output().size();

         auto pointBufferItemWindow = pbufferitem->m_pointBufferItemWindow;

         auto sizeBufferItemWindow = pbufferitem->m_sizeBufferItemWindow;

         if (playeredwindowbuffer)
         {


         auto sizeBuffer = pbufferitem->m_pimage2->size();

         //if (size.cx() < sizeDrawn.cx() && size.cy() < sizeDrawn.cy())
         //if (size != sizeDrawn || sizeDesign != size)
         if (sizeBufferItemWindow != sizeBuffer)
         {

            if (m_pwindow->m_timeLastDrawGuard1.elapsed() > 1_s)
            {

               throw ::exception(error_failed);

            }

            error() << "Requested size is different of buffer size.";
            error() << "Requested size: " << sizeBufferItemWindow;
            error() << "Buffer size: " << sizeBuffer;
            //error() <<"Design size: " << sizeDesign;

            //m_pwindow->user_interaction()->set_need_redraw();

            m_pwindow->user_interaction()->post_redraw();

            return;

         }
         else if (sizeLayeredWindowBuffer != sizeBuffer)
         {

            if (m_pwindow->m_timeLastDrawGuard1.elapsed() > 1_s)
            {

               throw ::exception(error_failed);

            }

            error() << "Os buffer size is different of buffer size.";
            error() << "Os buffer size: " << sizeLayeredWindowBuffer;
            error() << "Buffer size: " << sizeBuffer;

            m_pwindow->user_interaction()->post_redraw();

            return;

         }
         
         //else
         //{


         //pbufferitem->m_pimage2->fill_channel(1, color::e_channel_opacity);
         //pbufferitem->m_pimage2->fill_channel(0, color::e_channel_red);
         //pbufferitem->m_pimage2->fill_channel(0, color::e_channel_green);
         //pbufferitem->m_pimage2->fill_channel(0, color::e_channel_blue);

            if (!create_window_device_context(sizeBufferItemWindow, playeredwindowbuffer->m_pixmap.m_iScan))
            {

               throw ::exception(error_failed);

            }

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
         //   //&& m_pwindow != nullptr
         //   //&& m_pwindow->user_interaction() != nullptr
         //   //&& m_pwindow->user_interaction()->_is_window_visible())
         {

            //if (!m_pwindow->m_bOkToUpdateScreen)
            //{

            //   output_debug_string("nok yet to update the screen \n");

            //   m_pwindow->user_interaction()->set_need_redraw();

            //}
            //else
            //{

            ::cast < ::windowing_win32::window > pwindow = m_pwindow;

            ::int_point pointSrc = { 0 };

            BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, pwindow->m_uOpacity, AC_SRC_ALPHA };

            //::SelectClipRgn(m_hdcScreen, nullptr);

#ifdef REDRAW_HINTING

            {
               //HBRUSH h = ::CreateSolidBrush(rgb(255, 240, 155));

               //rectangle r;

               //rectangle.left() = 10;
               //rectangle.right() = 20;
               //rectangle.top() = 0;
               //rectangle.bottom() = sz.cy();

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);

               Gdiplus::Graphics g(m_hdcScreen);

               Gdiplus::Rect rectangle;

               g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

               rectangle.X = 10;
               rectangle.Width = 10;
               rectangle.Y = 0;
               rectangle.Height = size.cy();

               Gdiplus::SolidBrush b(Gdiplus::Color(255, 155, 240, 255));

               g.FillRectangle(&b, rectangle);

            }

#endif

            //SelectClipRgn(m_hdcScreen, nullptr);

            //SelectClipRgn(playeredwindowbuffer->m_hdc, nullptr);

            //SetViewportOrgEx(m_hdcScreen, 0, 0, nullptr);

            //SetViewportOrgEx(playeredwindowbuffer->m_hdc, 0, 0, nullptr);

#ifdef REDRAW_HINTING

            {

               //HBRUSH h = ::CreateSolidBrush(rgb(180, 200, 255));

               //rectangle r;

               //rectangle.left() = 20;
               //rectangle.right() = 30;
               //rectangle.top() = 0;
               //rectangle.bottom() = sz.cy();

               //::FillRect(m_hdc, rectangle, h);

               //::DeleteObject(h);
               Gdiplus::Graphics g(playeredwindowbuffer->m_hdc);

               Gdiplus::Rect rectangle;

               g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

               rectangle.X = 0;
               rectangle.Y = 0;
               rectangle.Width = size.cx();
               rectangle.Height = size.cy();

               Gdiplus::SolidBrush b(Gdiplus::Color(127, 255, 210, 170));

               g.FillRectangle(&b, rectangle);
            }

#endif

#ifdef _DEBUG

            //               {

                              //HBRUSH h = ::CreateSolidBrush(rgb(180, 200, 255));

                              //rectangle r;

                              //rectangle.left() = 20;
                              //rectangle.right() = 30;
                              //rectangle.top() = 0;
                              //rectangle.bottom() = sz.cy();

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

               int i = m_pwindow->prop("iSquaryHint");
               string str;
               str.formatf("%d", i);
               //iSquaryHint++;
               wstr = str;
               m_pwindow->prop("iSquaryHint") = i + 1;

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

            string strType = ::type(m_pwindow->user_interaction()).name();

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

                  informationf("GetWindowRect (%d, %d) - (%d, %d)", rectangleProbe.left, rectangleProbe.top, rectangleProbe.right, rectangleProbe.bottom);

               }

            }
            else if (strType.case_insensitive_contains("list_box"))
            {

               information() << "list_box going to UpdateLayeredWindow";

               bool bVisible = IsWindowVisible(get_hwnd());

               if (bVisible)
               {

                  information() << "list_box is visible!!";

               }
               else
               {

                  information() << "list_box ISN'T visible!!";

               }

               RECT rectangleProbe;

               if (::GetWindowRect(get_hwnd(), &rectangleProbe))
               {

                  informationf("GetWindowRect (%d, %d) - (%d, %d)", rectangleProbe.left, rectangleProbe.top, rectangleProbe.right, rectangleProbe.bottom);

               }

               auto edisplay = m_pwindow->user_interaction()->const_layout().sketch().display();


               information() << "list_box display is : " << ::as_string(edisplay.m_eenum);

            }


            //::pointer < ::windowing_win32::window > pwindow = m_pwindow->m_pwindow;

            try
            {

               pwindow->set_window_position_unlocked();

            }
            catch (...)
            {

            }


            //bool bOk = true;

            //bool bSizeOrPositionChanged = false;

            //if (layout.design().is_screen_visible())
            {

               //HWND hwnd = get_hwnd();

               //string str;

               //int_rectangle rectangleDrawing(point, size);


                  //if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
               {


                  /*             };

                            p();*/

                            //::SendMessage((HWND) m_pwindow->oswindow(),
             //WM_APP + 12345, 0, (LPARAM) p.m_pbase.m_p);

                            //if (m_pwindow->user_interaction()->get_parent() == nullptr)
                  {

                     auto p = __get_bottom_right();

                     if (p.is_set())
                     {

                        auto r = ::int_rectangle(pointBufferItemWindow, sizeBufferItemWindow);

                        auto Δ = r.bottom_right() - p;

                        if (Δ.cx() != 0 || Δ.cy() != 0)
                        {

                           //information() << "sketch_to_lading top right offset not null " << Δ;

                        }

                     }

                  }


                  //if (rectangleWindowCurrent.top_left() != point
                  //   || rectangleWindowCurrent.size() != size
                  //   || m_pwindow->user_interaction()->const_layout().design().has_activation_request())
                  //{

                  //   m_pwindow->m_pwindow->_set_window_position(
                  //      m_pwindow->user_interaction()->const_layout().design().zorder(),
                  //      point.x(),
                  //      point.y(),
                  //      size.cx(),
                  //      size.cy(),
                  //      m_pwindow->user_interaction()->const_layout().design().activation(),
                  //      true, false, false, true, false, 
                  //      uFlagsSetWindowPos);

                  //   m_pwindow->user_interaction()->reset_pending();

                  //   bSizeOrPositionChanged = true;

                  //}

                  if (!m_pwindow
                     || !m_pwindow->user_interaction())
                  {

                     throw ::exception(error_wrong_state);

                  }

                  //if (m_pwindow->user_interaction()->const_layout().window().origin() != pointBufferItemWindow)
                  //{

                  //   m_pwindow->user_interaction()->post_message(e_message_reposition, 0, pointBufferItemWindow);

                  //}

                  //if (m_pwindow->user_interaction()->const_layout().window().size() != sizeBufferItemWindow)
                  //{

                  //   m_pwindow->user_interaction()->post_message(e_message_size, 0, sizeBufferItemWindow);

                  //}

               }
               //else
               //{
               //   informationf("Update discarded");

               //}

               ::int_point pointBottomRight = pointBufferItemWindow + sizeBufferItemWindow;

               //if (::IsWindowVisible(hwnd) && !::IsIconic(hwnd))
               {

                  //::pointer < ::windowing_win32::window > p2 = m_pwindow;

                  //if (!p2->m_bSizeMoveMode)
                  {

                     ::int_rectangle rectangleWindow;

                     RECT rectWindow;

                     ::GetWindowRect(hwnd, &rectWindow);

                     rectangleWindow = rectWindow;

                     ::int_rectangle rectangleRequest(pointBufferItemWindow, sizeBufferItemWindow);

                     //if (rectangleWindow.size() != size)
                     //{

                     //   return false;

                     //}

                     if (rectangleRequest.is_empty())
                     {

                        return;

                     }

                     bool bDifferent = rectangleWindow != rectangleRequest;

                     auto hwndInsertAfter = pwindow->m_hwndSetWindowPosLastInsertAfter;

                     auto pOwner = pwindow->owner_window();
                     
                     if (pOwner)
                     {
                        
                        auto pwnd = pOwner->get_wnd();

                        if (pwnd)
                        {

                           ::cast <::windowing_win32::window > pwindow2;

                           pwindow2 = pwnd->m_pacmewindowingwindow;

                           if (pwindow2)
                           {
                              
                              hwndInsertAfter = pwindow2->m_hwnd;
                              
                              hwndInsertAfter = HWND_TOPMOST;

                           }

                        }

                     }

                     bool bWindowVisible = ::IsWindowVisible(pwindow->m_hwnd) ? true : false;

                     bool bExTopMost = (::GetWindowLongPtr(pwindow->m_hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;

                     bool bSwpShowWindow = (pwindow->m_uSetWindowPosLastFlags & SWP_SHOWWINDOW) != 0;

                     bool bSwpHideWindow = (pwindow->m_uSetWindowPosLastFlags & SWP_HIDEWINDOW) != 0;

                     auto nFlags = pwindow->m_uSetWindowPosLastFlags;

                     bool bZOrder = !(nFlags & SWP_NOZORDER);

                     bool bActivate = !(nFlags & SWP_NOACTIVATE);

                     if (rectangleWindow != rectangleRequest
                        //|| (hwndInsertAfter == HWND_TOPMOST && !bExTopMost)
                        || bZOrder
                        || bActivate
                        || (bWindowVisible && bSwpHideWindow)
                        || (!bWindowVisible && bSwpShowWindow))
                     {

                        if (!::IsIconic(hwnd) && !::IsZoomed(hwnd))
                        {

                           information() << "windowing_win32::buffer !IsIconic";
                           information() << "windowing_win32::buffer bZOrder = " << bZOrder;
                           information() << "windowing_win32::buffer bActivate = " << bActivate;

                           nFlags &= ~SWP_NOMOVE;
                           nFlags &= ~SWP_NOSIZE;
                           //nFlags |= SWP_NOZORDER;
                           if (strType.case_insensitive_contains("list_box"))
                           {

                              if (nFlags & SWP_SHOWWINDOW)
                              {

                                 print_line("nFlags & SWP_SHOWWINDOW");
                              }

                              if (nFlags & SWP_HIDEWINDOW)
                              {

                                 print_line("nFlags & SWP_HIDEWINDOW");
                              }

                           }

                           auto cx = rectangleRequest.width();
                           
                           pwindow->_main_send([&]()
                              {

                                 //if (!(nFlags & SWP_NOMOVE))
                                 //{

                                 //   pwindow->m_pointDesignRequest = rectangleRequest.top_left();

                                 //}

                                 //if (!(nFlags & SWP_NOSIZE))
                                 //{

                                 //   pwindow->m_sizeDesignRequest = rectangleRequest.size();

                                 //}

                                 if (rectangleRequest.left() > 100)
                                 {

                                    informationf("test");

                                 }

                                 ::SetWindowPos(
                                    hwnd,
                                    hwndInsertAfter,
                                    rectangleRequest.left(),
                                    rectangleRequest.top(),
                                    cx,
                                    rectangleRequest.height(),
                                    nFlags);

                                 if (pwindow->m_activationSetWindowPosLast & ::user::e_activation_set_foreground)
                                 {
                                    
                                    ::cast < ::win32::acme::windowing::activation_token > pactivationtoken = pwindow->m_activationSetWindowPosLast.m_pactivationtoken;

                                    if (pactivationtoken)
                                    {

                                       pactivationtoken->m_ptaskForeground->post([pwindow, hwnd]()
                                          {

                                                ::SetForegroundWindow(hwnd);

                                                pwindow.m_p->m_activationSetWindowPosLast.clear();

});

                                    }
                                    else
                                    {

                                       ::SetForegroundWindow(hwnd);
                                       pwindow->m_activationSetWindowPosLast.clear();

                                    }

                                    pwindow->m_uSetWindowPosLastFlags &= ~SWP_NOACTIVATE;

                                 }

                           });

                        }

                     }

                     //GdiFlush();
                     if (::IsWindowVisible(pwindow->m_hwnd)
                        && !::IsIconic(pwindow->m_hwnd)
                        && pointBufferItemWindow.x() >-16384
                        && pointBufferItemWindow.y() >-16384)
                     {


                        if (m_papplication->m_gpu.m_bUseSwapChainWindow)
                        {

                           //auto pgraphics = pbufferitem->g();

                           //pgraphics->do_on_context([this, pgraphics,
                           //   pbufferitem]
                           //   {

                           //      pgraphics->on_present();

                           //});

                        }
                        else
                        {

                           ::UpdateLayeredWindow(
   hwnd,
   m_hdcScreen,
   (POINT *)&pointBufferItemWindow,
   (SIZE *)&sizeBufferItemWindow,
   playeredwindowbuffer->m_hdc,
   (POINT *)&pointSrc,
   make_unsigned_int(0, 0, 0, 0),
   &blendPixelFunction,
   ULW_ALPHA);


                        }

                        m_pwindow->m_timeLastDrawGuard1.Now();

                     }

                     //GdiFlush();

                     ::GetWindowRect(hwnd, &rectWindow);

                     rectangleWindow = rectWindow;

                     ::int_rectangle rectangleCache(pwindow->m_pointWindow, pwindow->m_sizeWindow);

                     if (rectangleCache != rectangleWindow)
                     {

                        pwindow->m_pointWindow = rectangleWindow.origin();

                        pwindow->m_sizeWindow = rectangleWindow.size();

                     }

                  }

               }


               //if (g_pointLastBottomRight != pointBottomRight)
               //{

               //   informationf("UpdateLayeredWindow Changed");

               //   g_pointLastBottomRight = pointBottomRight;

               //}

               //informationf("UpdateLayeredWindow Bottom Right (%d, %d)", pointBottomRight.x(), pointBottomRight.y());


            }

            //m_pwindow->user_interaction()->post_message(message_do_show_window);

            //m_pwindow->user_interaction()->_window_show_change_visibility_unlocked();

            //if (bSizeOrPositionChanged)
            //{

            //   m_pwindow->user_interaction()->on_visual_applied();

            //}

            //#ifdef WINDOWS_DESKTOP
            //               if ((m_pwindow->user_interaction()->GetExStyle() & WS_EX_LAYERED))
            //#endif
            //               {
            //
            //                  unsigned int uFlags = SWP_NOREDRAW
            //                     | SWP_NOCOPYBITS
            //                     | SWP_NOACTIVATE
            //                     | SWP_NOOWNERZORDER
            //                     | SWP_DEFERERASE
            //                  | SWP_NOZORDER;
            //                  ::SetWindowPos(get_hwnd(), NULL, point.x(), point.y(), size.cx(), size.cy(), 
            //                     uFlags);
            //                  m_pwindow->on_visual_applied();
            //
            //               }

                           //::int_rectangle r3;

                           //GetWindowRect(m_oswindow, &r3);

                           //::int_rectangle r4;

                           //GetClientRect(m_oswindow, &r4);

                           //::SendMessage(get_hwnd(), WM_PRINT, (wparam)m_hdcScreen, PRF_OWNED | PRF_CHILDREN);

#ifdef _DEBUG

            if (playeredwindowbuffer)
            {

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

        /*       if (!bOk)
               {

                  output_debug_string("UpdateLayeredWindow failed");

               }*/

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

      //return true;

   }


   void buffer::update_screen_task()
   {

      while (::task_get_run())
      {

         m_happeningUpdateScreen.wait(1_s);

         m_happeningUpdateScreen.reset_happening();

         m_ptaskUpdateScreen->task_iteration();

      }

   }


   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      bool bOk1 = double_buffer::buffer_lock_round_swap_key_buffers();

      if (!m_pwindow || !m_pwindow->m_pgraphicsthread)
      {

         return false;

      }

      bool bOk2 = bitmap_source_buffer::buffer_lock_round_swap_key_buffers();

      return bOk1 && bOk2;

   }


   HWND buffer::get_hwnd() const
   {

      return (HWND)m_pwindow->oswindow();

   }


} // namespace windows




