// Created by camilo on 2026-07-30 23:35 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "layered_window_buffer.h"
#include "acme/operating_system/windows/device_independent_bitmap.h"
#include "aura/windowing/display.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "operating_system-windows/acme_windowing_win32/activation_token.h"
#include "operating_system-windows/acme_windowing_win32/window.h"
#include <dwmapi.h>


namespace windowing_win32
{


   // CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::i32_size & size, ::i32 * piScan, ::color32_t **
   // ppdata);


   layered_window_buffer::layered_window_buffer()
   {

      //m_hbitmap = nullptr;

      //m_hdc = nullptr;

      //m_hbitmapOld = nullptr;

      m_hwnd = nullptr;

      m_hdcScreen = nullptr;

      m_hdcDirectDiagnostic = nullptr;
      m_hbitmapDirectDiagnostic = nullptr;
      m_hbitmapDirectDiagnosticOld = nullptr;
      m_pimage32DirectDiagnostic = nullptr;
      m_sizeDirectDiagnostic = {};
      m_dwMainThreadDiagnosticCreateThreadId = 0;
      m_dwProductionDibCreateThreadId = 0;

      m_bWindowDC = false;

      m_uExtraFlagsSetWindowPos = 0;

      m_uSetWindowPosLastFlags = 0;
      m_hwndSetWindowPosLastInsertAfter = nullptr;


   }


   layered_window_buffer::~layered_window_buffer()
   {

      _destroy_direct_diagnostic_dib();

   }


   void layered_window_buffer::initialize_window_buffer(::windowing::window * pwindow)
   {

      ::windowing::window_buffer::initialize_window_buffer(pwindow);

      m_pwindowWin32 = m_pwindow;

      m_hwnd = ::as_HWND(pwindow->operating_system_window());

      if (m_pwindowWin32->_get_ex_style() & WS_EX_LAYERED)
      {

         m_uExtraFlagsSetWindowPos =
            SWP_NOZORDER |
            SWP_ASYNCWINDOWPOS
            //| SWP_FRAMECHANGED
            //| SWP_NOSENDCHANGING
            | SWP_NOREDRAW
            | SWP_NOCOPYBITS
            //| SWP_DEFERERASE
            | SWP_NOACTIVATE;
         //| SWP_SHOWWINDOW;
      }


   }


   HWND layered_window_buffer::get_hwnd() const
   {

      return m_hwnd;

   }


   ::windows::device_independent_bitmap * layered_window_buffer::_device_independent_bitmap()
   {

      ::cast < ::windows::device_independent_bitmap > pbitmap = m_ppixmapWindowBuffer;

      if (!m_ppixmapWindowBuffer)
      {

         throw ::exception(error_wrong_state, "layered_window_buffer::_device_independent_bitmap: m_ppixmapWindowBuffer is null");

         //auto pdeviceindependentbitmap = create_newø<::windows::device_independent_bitmap>();

         //pdeviceindependentbitmap->defer_create_device_independent_bitmap(m_pwindow->m_sizeWindow);

         //m_ppixmapWindowBuffer = pdeviceindependentbitmap;

         //pbitmap = pdeviceindependentbitmap;

      }

      return pbitmap;

   }


   bool layered_window_buffer::_create_direct_diagnostic_dib(const ::i32_size & size)
   {

      if (size.is_empty())
      {

         return false;

      }

      if (m_hdcDirectDiagnostic
         && m_hbitmapDirectDiagnostic
         && m_pimage32DirectDiagnostic
         && m_sizeDirectDiagnostic == size)
      {

         return true;

      }

      _destroy_direct_diagnostic_dib();

      BITMAPINFO info{};
      info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      info.bmiHeader.biWidth = size.cx;
      info.bmiHeader.biHeight = -size.cy;
      info.bmiHeader.biPlanes = 1;
      info.bmiHeader.biBitCount = 32;
      info.bmiHeader.biCompression = BI_RGB;

      auto hdcMemory = ::CreateCompatibleDC(nullptr);

      if (!hdcMemory)
      {

         informationf("DirectDibDiagnostic CreateCompatibleDC failed error=%lu", (unsigned long)::GetLastError());
         return false;

      }

      ::image32_t * pimage32 = nullptr;
      auto hbitmap = ::CreateDIBSection(
         nullptr,
         &info,
         DIB_RGB_COLORS,
         (void **)&pimage32,
         nullptr,
         0);

      if (!hbitmap || !pimage32)
      {

         auto dwLastError = ::GetLastError();
         ::DeleteDC(hdcMemory);
         informationf("DirectDibDiagnostic CreateDIBSection failed error=%lu", (unsigned long)dwLastError);
         return false;

      }

      auto hbitmapOld = (HBITMAP)::SelectObject(hdcMemory, hbitmap);

      if (!hbitmapOld)
      {

         auto dwLastError = ::GetLastError();
         ::DeleteObject(hbitmap);
         ::DeleteDC(hdcMemory);
         informationf("DirectDibDiagnostic SelectObject failed error=%lu", (unsigned long)dwLastError);
         return false;

      }

      m_hdcDirectDiagnostic = hdcMemory;
      m_hbitmapDirectDiagnostic = hbitmap;
      m_hbitmapDirectDiagnosticOld = hbitmapOld;
      m_pimage32DirectDiagnostic = pimage32;
      m_sizeDirectDiagnostic = size;

      return true;

   }


   void layered_window_buffer::_destroy_direct_diagnostic_dib()
   {

      if (m_hdcDirectDiagnostic && m_hbitmapDirectDiagnosticOld)
      {

         ::SelectObject(m_hdcDirectDiagnostic, m_hbitmapDirectDiagnosticOld);

      }

      if (m_hbitmapDirectDiagnostic)
      {

         ::DeleteObject(m_hbitmapDirectDiagnostic);

      }

      if (m_hdcDirectDiagnostic)
      {

         ::DeleteDC(m_hdcDirectDiagnostic);

      }

      m_hdcDirectDiagnostic = nullptr;
      m_hbitmapDirectDiagnostic = nullptr;
      m_hbitmapDirectDiagnosticOld = nullptr;
      m_pimage32DirectDiagnostic = nullptr;
      m_sizeDirectDiagnostic = {};

   }


   void layered_window_buffer::destroy_window_buffer()
   {

      m_pdeviceindependentbitmapMainThreadDiagnostic.release();
      m_dwMainThreadDiagnosticCreateThreadId = 0;

      _destroy_direct_diagnostic_dib();

      ::windowing::window_buffer::destroy_window_buffer();

      //if (m_hdc != nullptr)
      //{

      //   if (m_hbitmapOld != nullptr)
      //   {

      //      ::SelectObject(m_hdc, m_hbitmapOld);
      //   }

      //   ::DeleteDC(m_hdc);

      //   m_hdc = nullptr;
      //}

      //m_hbitmapOld = nullptr;

      //if (m_hbitmap != nullptr)
      //{

      //   ::DeleteObject(m_hbitmap);

      //   m_hbitmap = nullptr;

      //   m_pixmap.clear();
      //}
   }




   bool layered_window_buffer::_create_window_device_context(const ::i32_size & size, ::i32 iStrideParam)
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         return true;

      }

      if (m_hdcScreen != NULL && m_pwindow)
      {

         return true;

      }

      _destroy_window_device_context();

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


   void layered_window_buffer::_destroy_window_device_context()
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



   void layered_window_buffer::present_window_buffer()
   {
      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {
         return;
      }
      _configure_window();
      _update_layered_window();
   }


   void layered_window_buffer::_configure_window()
   {
      if (!m_pwindow)
      {
         return;
      }
      if (!m_pwindow->user_interaction())
      {
         return;
      }

      auto pwindow = m_pwindow;

      //auto pwindow = m_pwindow;

      HWND hwnd = get_hwnd();

      auto pointBufferItemWindow = m_pointBufferItemWindow;

      auto sizeBufferItemWindow = m_sizeBufferItemWindow;

      string strType = ::platform::type(m_pwindow->user_interaction()).name();

      // bool bOk = true;

      // bool bSizeOrPositionChanged = false;

      // if (layout.design().is_screen_visible())
      {

         // HWND hwnd = get_hwnd();

         // string str;

         // i32_rectangle rectangleDrawing(point, size);


         // if (rectangleDrawing.size() == pimage->m_rectangleTag.size())
         {


            /*             };

                      p();*/

                      //::SendMessage((HWND) m_pwindow->oswindow(),
                      // WM_APP + 12345, 0, (LPARAM) p.m_pbase.m_p);

                      // if (m_pwindow->user_interaction()->get_parent() == nullptr)
            //{

            //   //auto p = __get_bottom_right();

            //   if (p.is_set())
            //   {

            //      auto r = ::i32_rectangle(pointBufferItemWindow, sizeBufferItemWindow);

            //      auto Δ = r.bottom_right() - p;

            //      if (Δ.cx != 0 || Δ.cy != 0)
            //      {

            //         // information() << "sketch_to_lading top right offset not null " << Δ;
            //      }
            //   }
            //}


            // if (rectangleWindowCurrent.top_left() != point
            //    || rectangleWindowCurrent.size() != size
            //    || m_pwindow->user_interaction()->const_layout().design().has_activation_request())
            //{

            //   m_pwindow->m_pwindow->_set_window_position(
            //      m_pwindow->user_interaction()->const_layout().design().zorder(),
            //      point.x,
            //      point.y,
            //      size.cx,
            //      size.cy,
            //      m_pwindow->user_interaction()->const_layout().design().activation(),
            //      true, false, false, true, false,
            //      uFlagsSetWindowPos);

            //   m_pwindow->user_interaction()->reset_pending();

            //   bSizeOrPositionChanged = true;

            //}

            if (!m_pwindow || !m_pwindow->user_interaction())
            {

               throw ::exception(error_wrong_state);
            }

            // if (m_pwindow->user_interaction()->const_layout().window().origin() != pointBufferItemWindow)
            //{

            //   m_pwindow->user_interaction()->post_message(::user::e_message_reposition, 0, pointBufferItemWindow);

            //}

            // if (m_pwindow->user_interaction()->const_layout().window().size() != sizeBufferItemWindow)
            //{

            //   m_pwindow->user_interaction()->post_message(::user::e_message_size, 0, sizeBufferItemWindow);

            //}
         }
         // else
         //{
         //    informationf("Update discarded");

         //}

         ::i32_point pointBottomRight = pointBufferItemWindow + sizeBufferItemWindow;

         // if (::IsWindowVisible(hwnd) && !::IsIconic(hwnd))
         {

            //::pointer < ::windowing_win32::window > p2 = m_pwindow;

            // if (!p2->m_bSizeMoveMode)
            {

               ::i32_rectangle rectangleWindow;

               RECT rectWindow;

               ::GetWindowRect(hwnd, &rectWindow);

               {
                  i32_rectangle rWindow2;
                  ::GetWindowRect(hwnd, (LPRECT)&rWindow2);
                  i32_rectangle rClient2;
                  ::GetClientRect(hwnd, (LPRECT)&rClient2);
                  //information("rWindow2 x{} y{} w{} h{}", rWindow2.left, rWindow2.top, rWindow2.width(), rWindow2.height());
                  //information("rClient2 x{} y{} w{} h{}", rClient2.left, rClient2.top, rClient2.width(),
                  //            rClient2.height());
               }


               rectangleWindow = rectWindow;

               ::i32_rectangle rectangleRequest(pointBufferItemWindow, sizeBufferItemWindow);

               // if (rectangleWindow.size() != size)
               //{

               //   return false;

               //}

               if (rectangleRequest.is_empty())
               {

                  return;
               }

               bool bDifferent = rectangleWindow != rectangleRequest;

               auto hwndInsertAfter = m_hwndSetWindowPosLastInsertAfter;

               auto pOwner = pwindow->owner_window();

               if (pOwner)
               {

                  auto pwnd = pOwner->get_wnd();

                  if (pwnd)
                  {

                     auto pwindow2 = pwnd->m_pacmewindowingwindow;

                     if (pwindow2)
                     {

                        hwndInsertAfter = ::as_HWND(pwindow2->operating_system_window());

                        hwndInsertAfter = HWND_TOPMOST;

                     }
                  }
               }

               bool bWindowVisible = ::IsWindowVisible(::as_HWND(pwindow->operating_system_window())) ? true : false;

               bool bExTopMost =
                  (::GetWindowLongPtr(::as_HWND(pwindow->operating_system_window()), GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;

               bool bSwpShowWindow = (m_uSetWindowPosLastFlags & SWP_SHOWWINDOW) != 0;

               bool bSwpHideWindow = (m_uSetWindowPosLastFlags & SWP_HIDEWINDOW) != 0;

               auto nFlags = m_uSetWindowPosLastFlags;

               nFlags &= ~SWP_ASYNCWINDOWPOS;

               if (m_activationSetWindowPosLast.is_activation_request())
               {

                  if (!bSwpHideWindow)
                  {

                     nFlags &= ~SWP_NOACTIVATE;

                     m_uSetWindowPosLastFlags |= SWP_SHOWWINDOW;

                  }

               }

               bool bZOrder = !(nFlags & SWP_NOZORDER);

               bool bActivate = !(nFlags & SWP_NOACTIVATE);

               if (rectangleWindow != rectangleRequest
                   //|| (hwndInsertAfter == HWND_TOPMOST && !bExTopMost)
                   || bZOrder || bActivate || (bWindowVisible && bSwpHideWindow) || (!bWindowVisible && bSwpShowWindow))
               {

                  if (!::IsIconic(hwnd) && !::IsZoomed(hwnd))
                  {

                     //information() << "windowing_win32::graphics !IsIconic";
                     //information() << "windowing_win32::graphics bZOrder = " << bZOrder;
                     //information() << "windowing_win32::graphics bActivate = " << bActivate;

                     nFlags &= ~SWP_NOMOVE;
                     nFlags &= ~SWP_NOSIZE;
                     // nFlags |= SWP_NOZORDER;
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

                     // if (!(nFlags & SWP_NOMOVE))
                                             //{

                                             //   pwindow->m_pointDesignRequest = rectangleRequest.top_left();

                                             //}

                                             // if (!(nFlags & SWP_NOSIZE))
                                             //{

                                             //   pwindow->m_sizeDesignRequest = rectangleRequest.size();

                                             //}

                     if (rectangleRequest.left > 100)
                     {

                        //informationf("test");
                     }
                     ::string str;
                     if (nFlags & SWP_NOSIZE)
                     {

                        str += "SWP_NOSIZE; ";

                     }

                     ::i32 iRequestWidth = rectangleRequest.width();
                     ::i32 iRequestHeight = rectangleRequest.height();
                     str.append_formatf("w=%d; ", iRequestWidth);
                     str.append_formatf("h=%d; ", iRequestHeight);

                     ::SetLastError(ERROR_SUCCESS);

                     auto bSetWindowPosition = ::SetWindowPos(
                        hwnd, hwndInsertAfter, rectangleRequest.left, rectangleRequest.top,
                        iRequestWidth,
                        iRequestHeight,
                        nFlags);

                     auto dwSetWindowPositionError =
                        bSetWindowPosition ? ERROR_SUCCESS : ::GetLastError();

                     auto activationSetWindowPos = m_activationSetWindowPosLast;

                     m_activationSetWindowPosLast.clear();

                     RECT rectWindowAfter{};

                     auto bGotWindowRectAfter = ::GetWindowRect(hwnd, &rectWindowAfter);

                     m_uSetWindowPosLastFlags |= SWP_NOZORDER;

                     informationf(
                        "SetWindowPos result=%d error=%lu before=(%d,%d)-(%d,%d) "
                        "request=(%d,%d)-(%d,%d) afterResult=%d after=(%ld,%ld)-(%ld,%ld) "
                        "flags=0x%08x activation=0x%08x causes[different=%d zorder=%d activate=%d "
                        "hide=%d show=%d] %s",
                        (int)bSetWindowPosition,
                        (unsigned long)dwSetWindowPositionError,
                        rectangleWindow.left,
                        rectangleWindow.top,
                        rectangleWindow.right,
                        rectangleWindow.bottom,
                        rectangleRequest.left,
                        rectangleRequest.top,
                        rectangleRequest.right,
                        rectangleRequest.bottom,
                        (int)bGotWindowRectAfter,
                        rectWindowAfter.left,
                        rectWindowAfter.top,
                        rectWindowAfter.right,
                        rectWindowAfter.bottom,
                        (unsigned int)nFlags,
                        (unsigned int)activationSetWindowPos.m_eactivation,
                        (int)bDifferent,
                        (int)bZOrder,
                        (int)bActivate,
                        (int)(bWindowVisible && bSwpHideWindow),
                        (int)(!bWindowVisible && bSwpShowWindow),
                        str.c_str());

                     if (activationSetWindowPos & ::user::e_activation_set_foreground)
                     {

                        ::cast<::win32::acme::windowing::activation_token> pactivationtoken =
                           activationSetWindowPos.m_pactivationtoken;

                        if (pactivationtoken)
                        {

                           pactivationtoken->m_ptaskForeground->post(
                              [hwnd]()
                              {
                                 ::SetForegroundWindow(hwnd);
                              });
                        }
                        else
                        {

                           ::SetForegroundWindow(hwnd);
                        }

                     }
                     m_uSetWindowPosLastFlags |= SWP_NOACTIVATE;

                  }

               }

            }

         }

      }


   }


   void layered_window_buffer::_update_layered_window_with_main_thread_device_independent_bitmap()
   {

      static constexpr bool s_bUseFullScreenMappedGeometry = true;

      auto sizeWindow = m_pwindowWin32->m_sizeWindow;

      if (sizeWindow.is_empty())
      {

         return;

      }

      auto sizeRaw = sizeWindow;

      ::i32_point pointMap{};

      if (s_bUseFullScreenMappedGeometry)
      {

         sizeRaw = m_pwindow->m_sizeRaw.maximum(sizeWindow);

         pointMap = m_pwindowWin32->m_pointWindow;

      }

      auto pdeviceindependentbitmap = m_pdeviceindependentbitmapMainThreadDiagnostic;

      if (!pdeviceindependentbitmap
         || !pdeviceindependentbitmap->m_hdcMemory
         || !pdeviceindependentbitmap->m_hbitmap
         || !pdeviceindependentbitmap->m_pimage32Raw
         || pdeviceindependentbitmap->m_sizeRaw != sizeRaw)
      {

         pdeviceindependentbitmap = create_newø<::windows::device_independent_bitmap>();
         pdeviceindependentbitmap->defer_create_device_independent_bitmap(sizeRaw);
         m_pdeviceindependentbitmapMainThreadDiagnostic = pdeviceindependentbitmap;
         m_dwMainThreadDiagnosticCreateThreadId = ::GetCurrentThreadId();

      }

      if (pdeviceindependentbitmap->m_point != pointMap
         || pdeviceindependentbitmap->m_size != sizeWindow)
      {

         pdeviceindependentbitmap->pixmap_map({ pointMap, sizeWindow });

      }

      m_pdeviceindependentbitmapMainThreadDiagnostic->fill_byte(128);

      ::GdiFlush();

      POINT pointWindow = { m_pwindowWin32->m_pointWindow.x, m_pwindowWin32->m_pointWindow.y };
      SIZE sizeWindowWin32 = { sizeWindow.cx, sizeWindow.cy };
      POINT pointSrc = { pdeviceindependentbitmap->m_point.x, pdeviceindependentbitmap->m_point.y };
      COLORREF crKey = RGB(0, 0, 0);
      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, m_pwindowWin32->m_uOpacity, AC_SRC_ALPHA };

      auto hbitmapSelected =
         (HBITMAP)::GetCurrentObject(pdeviceindependentbitmap->m_hdcMemory, OBJ_BITMAP);
      auto uSourcePixel = *(::u32 *)pdeviceindependentbitmap->m_pimage32Raw;
      auto dwPresentThreadId = ::GetCurrentThreadId();

      ::SetLastError(ERROR_SUCCESS);

      auto bUpdated = ::UpdateLayeredWindow(
         m_hwnd,
         m_hdcScreen,
         &pointWindow,
         &sizeWindowWin32,
         pdeviceindependentbitmap->m_hdcMemory,
         &pointSrc,
         crKey,
         &blendPixelFunction,
         ULW_ALPHA);

      auto dwLastError = bUpdated ? ERROR_SUCCESS : ::GetLastError();

      DWORD dwDwmCloaked = 0;
      HRESULT hresultDwmCloaked = S_FALSE;
      bool bDwmGetWindowAttributeAvailable = false;

      using PFN_DWM_GET_WINDOW_ATTRIBUTE = HRESULT(WINAPI *)(HWND, DWORD, PVOID, DWORD);
      auto hmoduleDwmApi = ::GetModuleHandleW(L"dwmapi.dll");

      if (hmoduleDwmApi)
      {

         auto pfnDwmGetWindowAttribute = reinterpret_cast<PFN_DWM_GET_WINDOW_ATTRIBUTE>(
            ::GetProcAddress(hmoduleDwmApi, "DwmGetWindowAttribute"));

         if (pfnDwmGetWindowAttribute)
         {

            bDwmGetWindowAttributeAvailable = true;
            hresultDwmCloaked = pfnDwmGetWindowAttribute(
               m_hwnd,
               (DWORD)DWMWA_CLOAKED,
               &dwDwmCloaked,
               sizeof(dwDwmCloaked));

         }

      }

      informationf(
         "MainThreadMappedDibDiagnostic UpdateLayeredWindow result=%d error=%lu hwnd=%p visible=%d iconic=%d "
         "dwmAvailable=%d dwmResult=0x%08lx cloaked=%lu dst=(%ld,%ld) size=(%ld,%ld) src=(%ld,%ld) "
         "raw=(%d,%d) map=(%d,%d)-(%d,%d) scan=%d opacity=%u hdcDst=%p hdcMemory=%p "
         "selectedBitmap=%p expectedBitmap=%p sourcePixel=0x%08x createThread=%lu presentThread=%lu",
         (int)bUpdated,
         (unsigned long)dwLastError,
         m_hwnd,
         (int)::IsWindowVisible(m_hwnd),
         (int)::IsIconic(m_hwnd),
         (int)bDwmGetWindowAttributeAvailable,
         (unsigned long)hresultDwmCloaked,
         (unsigned long)dwDwmCloaked,
         pointWindow.x,
         pointWindow.y,
         sizeWindowWin32.cx,
         sizeWindowWin32.cy,
         pointSrc.x,
         pointSrc.y,
         pdeviceindependentbitmap->m_sizeRaw.cx,
         pdeviceindependentbitmap->m_sizeRaw.cy,
         pdeviceindependentbitmap->m_point.x,
         pdeviceindependentbitmap->m_point.y,
         pdeviceindependentbitmap->m_size.cx,
         pdeviceindependentbitmap->m_size.cy,
         pdeviceindependentbitmap->m_iScan,
         (unsigned int)m_pwindowWin32->m_uOpacity,
         m_hdcScreen,
         pdeviceindependentbitmap->m_hdcMemory,
         hbitmapSelected,
         pdeviceindependentbitmap->m_hbitmap,
         (unsigned int)uSourcePixel,
         (unsigned long)m_dwMainThreadDiagnosticCreateThreadId,
         (unsigned long)dwPresentThreadId);

   }


   void layered_window_buffer::_update_layered_window_with_direct_diagnostic_dib()
   {

      auto size = m_pwindowWin32->m_sizeWindow;

      if (!_create_direct_diagnostic_dib(size))
      {

         return;

      }

      memset(
         m_pimage32DirectDiagnostic,
         128,
         size.cx * sizeof(::image32_t) * size.cy);

      ::GdiFlush();

      POINT pointWindow = { m_pwindowWin32->m_pointWindow.x, m_pwindowWin32->m_pointWindow.y };
      SIZE sizeWindow = { size.cx, size.cy };
      POINT pointSrc = { 0, 0 };
      COLORREF crKey = RGB(0, 0, 0);
      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, m_pwindowWin32->m_uOpacity, AC_SRC_ALPHA };

      auto hbitmapSelected = (HBITMAP)::GetCurrentObject(m_hdcDirectDiagnostic, OBJ_BITMAP);
      auto uSourcePixel = *(::u32 *)m_pimage32DirectDiagnostic;

      ::SetLastError(ERROR_SUCCESS);

      auto bUpdated = ::UpdateLayeredWindow(
         m_hwnd,
         m_hdcScreen,
         &pointWindow,
         &sizeWindow,
         m_hdcDirectDiagnostic,
         &pointSrc,
         crKey,
         &blendPixelFunction,
         ULW_ALPHA);

      auto dwLastError = bUpdated ? ERROR_SUCCESS : ::GetLastError();

      DWORD dwDwmCloaked = 0;
      HRESULT hresultDwmCloaked = S_FALSE;
      bool bDwmGetWindowAttributeAvailable = false;

      using PFN_DWM_GET_WINDOW_ATTRIBUTE = HRESULT(WINAPI *)(HWND, DWORD, PVOID, DWORD);
      auto hmoduleDwmApi = ::GetModuleHandleW(L"dwmapi.dll");

      if (hmoduleDwmApi)
      {

         auto pfnDwmGetWindowAttribute = reinterpret_cast<PFN_DWM_GET_WINDOW_ATTRIBUTE>(
            ::GetProcAddress(hmoduleDwmApi, "DwmGetWindowAttribute"));

         if (pfnDwmGetWindowAttribute)
         {

            bDwmGetWindowAttributeAvailable = true;
            hresultDwmCloaked = pfnDwmGetWindowAttribute(
               m_hwnd,
               (DWORD)DWMWA_CLOAKED,
               &dwDwmCloaked,
               sizeof(dwDwmCloaked));

         }

      }

      informationf(
         "DirectDibDiagnostic UpdateLayeredWindow result=%d error=%lu hwnd=%p visible=%d iconic=%d "
         "dwmAvailable=%d dwmResult=0x%08lx cloaked=%lu dst=(%ld,%ld) size=(%ld,%ld) src=(%ld,%ld) "
         "opacity=%u hdcDst=%p hdcMemory=%p selectedBitmap=%p expectedBitmap=%p sourcePixel=0x%08x",
         (int)bUpdated,
         (unsigned long)dwLastError,
         m_hwnd,
         (int)::IsWindowVisible(m_hwnd),
         (int)::IsIconic(m_hwnd),
         (int)bDwmGetWindowAttributeAvailable,
         (unsigned long)hresultDwmCloaked,
         (unsigned long)dwDwmCloaked,
         pointWindow.x,
         pointWindow.y,
         sizeWindow.cx,
         sizeWindow.cy,
         pointSrc.x,
         pointSrc.y,
         (unsigned int)m_pwindowWin32->m_uOpacity,
         m_hdcScreen,
         m_hdcDirectDiagnostic,
         hbitmapSelected,
         m_hbitmapDirectDiagnostic,
         (unsigned int)uSourcePixel);

   }


   void layered_window_buffer::_update_layered_window()
   {

      static constexpr bool s_bUseMainThreadDeviceIndependentBitmapDiagnostic = false;

      if (s_bUseMainThreadDeviceIndependentBitmapDiagnostic)
      {

         _update_layered_window_with_main_thread_device_independent_bitmap();
         return;

      }

      static constexpr bool s_bUseDirectDibDiagnostic = false;

      if (s_bUseDirectDibDiagnostic)
      {

         _update_layered_window_with_direct_diagnostic_dib();
         return;

      }

      ::cast < ::windows::device_independent_bitmap > pdeviceindependentbitmap = m_ppixmapWindowBuffer;

      auto hdcScreen = m_hdcScreen;

      POINT pointWindow = { m_pwindowWin32->m_pointWindow.x, m_pwindowWin32->m_pointWindow.y };

      SIZE sizeWindow = { m_pwindowWin32->m_sizeWindow.cx, m_pwindowWin32->m_sizeWindow.cy };

      auto hdcMemory = pdeviceindependentbitmap->m_hdcMemory;

      POINT pointSrc = { 0, 0 };

      if (pdeviceindependentbitmap->m_sizeRaw == m_pwindow->m_sizeRaw)
      {

         pointSrc =
         {
            pdeviceindependentbitmap->m_point.x,
            pdeviceindependentbitmap->m_point.y
         };

      }

      COLORREF crKey = RGB(0, 0, 0);

      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, m_pwindowWin32->m_uOpacity, AC_SRC_ALPHA };

      ::GdiFlush();

      auto hbitmapSelected = (HBITMAP) ::GetCurrentObject(hdcMemory, OBJ_BITMAP);

      BITMAP bitmapSource{};
      auto iBitmapSourceObjectSize =
         ::GetObject(hbitmapSelected, sizeof(bitmapSource), &bitmapSource);
      auto colorrefGdiSource = ::GetPixel(hdcMemory, pointSrc.x, pointSrc.y);
      auto iMemoryDcObjectType = ::GetObjectType(hdcMemory);
      auto iBitmapObjectType = ::GetObjectType(hbitmapSelected);
      auto iMapMode = ::GetMapMode(hdcMemory);
      auto dwLayout = ::GetLayout(hdcMemory);
      POINT pointViewportOrigin{};
      POINT pointWindowOrigin{};
      POINT pointDeviceContextOrigin{};
      ::GetViewportOrgEx(hdcMemory, &pointViewportOrigin);
      ::GetWindowOrgEx(hdcMemory, &pointWindowOrigin);
      ::GetDCOrgEx(hdcMemory, &pointDeviceContextOrigin);

      ::u32 uSourcePixel = 0;
      ::u32 uSourceCenterPixel = 0;
      unsigned int uSampledAlphaPixels = 0;
      unsigned int uSampledPixels = 0;

      if (pointSrc.x >= 0
         && pointSrc.y >= 0
         && pointSrc.x < pdeviceindependentbitmap->m_sizeRaw.cx
         && pointSrc.y < pdeviceindependentbitmap->m_sizeRaw.cy)
      {

         auto pbyteSource =
            ((::u8 *)pdeviceindependentbitmap->m_pimage32Raw)
            + pointSrc.y * pdeviceindependentbitmap->m_iScan
            + pointSrc.x * sizeof(::image32_t);

         uSourcePixel = *(::u32 *)pbyteSource;

         if (sizeWindow.cx > 0 && sizeWindow.cy > 0)
         {

            auto xCenter = pointSrc.x + sizeWindow.cx / 2;
            auto yCenter = pointSrc.y + sizeWindow.cy / 2;

            if (xCenter >= 0
               && yCenter >= 0
               && xCenter < pdeviceindependentbitmap->m_sizeRaw.cx
               && yCenter < pdeviceindependentbitmap->m_sizeRaw.cy)
            {

               auto pbyteCenter =
                  ((::u8 *)pdeviceindependentbitmap->m_pimage32Raw)
                  + yCenter * pdeviceindependentbitmap->m_iScan
                  + xCenter * sizeof(::image32_t);

               uSourceCenterPixel = *(::u32 *)pbyteCenter;

            }

            for (int iy = 0; iy < 9; iy++)
            {

               auto y = pointSrc.y + (sizeWindow.cy - 1) * iy / 8;

               for (int ix = 0; ix < 9; ix++)
               {

                  auto x = pointSrc.x + (sizeWindow.cx - 1) * ix / 8;

                  if (x >= 0
                     && y >= 0
                     && x < pdeviceindependentbitmap->m_sizeRaw.cx
                     && y < pdeviceindependentbitmap->m_sizeRaw.cy)
                  {

                     auto pbyteSample =
                        ((::u8 *)pdeviceindependentbitmap->m_pimage32Raw)
                        + y * pdeviceindependentbitmap->m_iScan
                        + x * sizeof(::image32_t);
                     auto uPixel = *(::u32 *)pbyteSample;
                     uSampledAlphaPixels += ((uPixel >> 24) != 0) ? 1U : 0U;
                     uSampledPixels++;

                  }

               }

            }

         }

      }

      ::SetLastError(ERROR_SUCCESS);

      auto bUpdated = ::UpdateLayeredWindow(
         m_hwnd, 
         hdcScreen,
         (POINT *)&pointWindow,
         (SIZE *)&sizeWindow,
         hdcMemory,
         (POINT *)&pointSrc,
         crKey,
         &blendPixelFunction,
         ULW_ALPHA);

      auto dwLastError = bUpdated ? ERROR_SUCCESS : ::GetLastError();

      {

         auto lStyle = ::GetWindowLongPtr(m_hwnd, GWL_STYLE);
         auto lExStyle = ::GetWindowLongPtr(m_hwnd, GWL_EXSTYLE);
         auto hwndParent = ::GetParent(m_hwnd);
         auto hwndOwner = ::GetWindow(m_hwnd, GW_OWNER);
         auto hwndRoot = ::GetAncestor(m_hwnd, GA_ROOT);
         auto hwndRootOwner = ::GetAncestor(m_hwnd, GA_ROOTOWNER);
         auto hwndForeground = ::GetForegroundWindow();
         auto hwndActive = ::GetActiveWindow();
         auto hwndTop = ::GetTopWindow(nullptr);

         RECT rectWindowRegion{};
         auto iWindowRegionType = ::GetWindowRgnBox(m_hwnd, &rectWindowRegion);

         DWORD dwDwmCloaked = 0;
         HRESULT hresultDwmCloaked = S_FALSE;
         bool bDwmGetWindowAttributeAvailable = false;

         using PFN_DWM_GET_WINDOW_ATTRIBUTE = HRESULT(WINAPI *)(HWND, DWORD, PVOID, DWORD);

         auto hmoduleDwmApi = ::GetModuleHandleW(L"dwmapi.dll");

         if (hmoduleDwmApi)
         {

            auto pfnDwmGetWindowAttribute =
               reinterpret_cast<PFN_DWM_GET_WINDOW_ATTRIBUTE>(
                  ::GetProcAddress(hmoduleDwmApi, "DwmGetWindowAttribute"));

            if (pfnDwmGetWindowAttribute)
            {

               bDwmGetWindowAttributeAvailable = true;
               hresultDwmCloaked = pfnDwmGetWindowAttribute(
                  m_hwnd,
                  (DWORD)DWMWA_CLOAKED,
                  &dwDwmCloaked,
                  sizeof(dwDwmCloaked));

            }

         }

         informationf(
            "MappedDibDiagnostic UpdateLayeredWindow result=%d error=%lu hwnd=%p visible=%d iconic=%d "
            "style=0x%Ix exstyle=0x%Ix parent=%p owner=%p root=%p rootOwner=%p "
            "foreground=%p active=%p top=%p regionType=%d region=(%ld,%ld)-(%ld,%ld) "
            "dwmAvailable=%d dwmResult=0x%08lx cloaked=%lu "
            "dst=(%ld,%ld) size=(%ld,%ld) src=(%ld,%ld) raw=(%d,%d) map=(%d,%d)-(%d,%d) "
            "scan=%d opacity=%u hdcScreen=%p hdcMemory=%p selectedBitmap=%p expectedBitmap=%p "
            "sourcePixel=0x%08x centerPixel=0x%08x alphaSamples=%u/%u "
            "object=%p createThread=%lu presentThread=%lu "
            "getObject=%d bitmap=(type=%ld width=%ld height=%ld widthBytes=%ld planes=%u bitsPixel=%u bits=%p) "
            "rawBits=%p gdiPixel=0x%08lx dcType=%lu bitmapType=%lu mapMode=%d layout=0x%08lx "
            "viewportOrigin=(%ld,%ld) windowOrigin=(%ld,%ld) dcOrigin=(%ld,%ld)",
            (int)bUpdated,
            (unsigned long)dwLastError,
            m_hwnd,
            (int)::IsWindowVisible(m_hwnd),
            (int)::IsIconic(m_hwnd),
            (::uptr)lStyle,
            (::uptr)lExStyle,
            hwndParent,
            hwndOwner,
            hwndRoot,
            hwndRootOwner,
            hwndForeground,
            hwndActive,
            hwndTop,
            (int)iWindowRegionType,
            rectWindowRegion.left,
            rectWindowRegion.top,
            rectWindowRegion.right,
            rectWindowRegion.bottom,
            (int)bDwmGetWindowAttributeAvailable,
            (unsigned long)hresultDwmCloaked,
            (unsigned long)dwDwmCloaked,
            pointWindow.x,
            pointWindow.y,
            sizeWindow.cx,
            sizeWindow.cy,
            pointSrc.x,
            pointSrc.y,
            pdeviceindependentbitmap->m_sizeRaw.cx,
            pdeviceindependentbitmap->m_sizeRaw.cy,
            pdeviceindependentbitmap->m_point.x,
            pdeviceindependentbitmap->m_point.y,
            pdeviceindependentbitmap->m_size.cx,
            pdeviceindependentbitmap->m_size.cy,
            pdeviceindependentbitmap->m_iScan,
            (unsigned int)m_pwindowWin32->m_uOpacity,
            hdcScreen,
            hdcMemory,
            hbitmapSelected,
            pdeviceindependentbitmap->m_hbitmap,
            (unsigned int)uSourcePixel,
            (unsigned int)uSourceCenterPixel,
            uSampledAlphaPixels,
            uSampledPixels,
            pdeviceindependentbitmap,
            (unsigned long)m_dwProductionDibCreateThreadId,
            (unsigned long)::GetCurrentThreadId(),
            iBitmapSourceObjectSize,
            bitmapSource.bmType,
            bitmapSource.bmWidth,
            bitmapSource.bmHeight,
            bitmapSource.bmWidthBytes,
            bitmapSource.bmPlanes,
            bitmapSource.bmBitsPixel,
            bitmapSource.bmBits,
            pdeviceindependentbitmap->m_pimage32Raw,
            (unsigned long)colorrefGdiSource,
            (unsigned long)iMemoryDcObjectType,
            (unsigned long)iBitmapObjectType,
            iMapMode,
            (unsigned long)dwLayout,
            pointViewportOrigin.x,
            pointViewportOrigin.y,
            pointWindowOrigin.x,
            pointWindowOrigin.y,
            pointDeviceContextOrigin.x,
            pointDeviceContextOrigin.y);

      }

   }


   void layered_window_buffer::buffer_lock_round_swap_key_buffers()
   {

      //auto pwindowing = m_pwindow->user_interaction()->windowing();

      //auto pdisplay = pwindowing->display();

      //auto rectangleUnion = pdisplay->get_monitor_union_rectangle();

      //m_pwindow->m_sizeScreen = rectangleUnion.size();

      auto pointWindow = m_pwindow->m_pointWindow;
      auto sizeWindow = m_pwindow->m_sizeWindow;
      auto sizeRaw = m_pwindow->m_sizeRaw;
      //auto sizeRaw = m_pwindow->m_sizeScreen.maximum(sizeWindow);

      ::cast < ::windows::device_independent_bitmap > pdeviceindependentbitmap =
         m_ppixmapWindowBuffer;

      auto bNeedsWindowThreadUpdate =
         !pdeviceindependentbitmap
         || !pdeviceindependentbitmap->m_hdcMemory
         || !pdeviceindependentbitmap->m_hbitmap
         || !pdeviceindependentbitmap->m_pimage32Raw
         || !(sizeRaw <= pdeviceindependentbitmap->m_sizeRaw)
         || pdeviceindependentbitmap->m_point != pointWindow
         || pdeviceindependentbitmap->m_size != sizeWindow;

      if (bNeedsWindowThreadUpdate)
      {

         //m_pwindow->main_sendø()
           // << [this, sizeRaw, pointWindow, sizeWindow]()
            //{

               ::cast < ::windows::device_independent_bitmap > pdeviceindependentbitmap =
                  m_ppixmapWindowBuffer;

               if (!pdeviceindependentbitmap)
               {

                  auto pdeviceindependentbitmapNew =
                     create_newø<::windows::device_independent_bitmap>();

                  m_ppixmapWindowBuffer = pdeviceindependentbitmapNew;
                  pdeviceindependentbitmap = pdeviceindependentbitmapNew;
                  m_dwProductionDibCreateThreadId = ::GetCurrentThreadId();

               }

               pdeviceindependentbitmap->defer_create_device_independent_bitmap(sizeRaw);

               if (pdeviceindependentbitmap->m_point != pointWindow
                  || pdeviceindependentbitmap->m_size != sizeWindow)
               {

                  pdeviceindependentbitmap->pixmap_map({ pointWindow, sizeWindow });

               }

            //};

      }

      pdeviceindependentbitmap = _device_independent_bitmap();

      if (!pdeviceindependentbitmap
         || !pdeviceindependentbitmap->m_hdcMemory
         || !pdeviceindependentbitmap->m_hbitmap
         || !pdeviceindependentbitmap->m_pimage32Raw
         || !pdeviceindependentbitmap->m_pimage32
         || !(sizeRaw <= pdeviceindependentbitmap->m_sizeRaw)
         || pdeviceindependentbitmap->m_point != pointWindow
         || pdeviceindependentbitmap->m_size != sizeWindow)
      {

         throw ::exception(error_wrong_state, "layered_window_buffer production DIB is invalid after main-thread defer-create");

      }

   }


} // namespace windowing_win32



