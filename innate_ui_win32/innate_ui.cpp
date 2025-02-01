// Created by camilo on 2024-09-12 02:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/platform/platform.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/windowing/windowing.h"


namespace innate_ui_win32
{


   innate_ui::innate_ui()
   {
      //m_hwnd = nullptr;

      m_bRunning = false;

      m_hthread = nullptr;

      m_dwThread = 0;

      id() = 0;

   }

   
   innate_ui::~innate_ui()
   {
      if (m_dwThread)
      {

         PostThreadMessageW(m_dwThread, WM_APP + 124, 0, 0);

      }
   }



   void innate_ui::on_initialize_particle()
   {

      ::innate_ui::innate_ui::on_initialize_particle();

      //_defer_run_innate_ui_win32_user_loop();

   }

   
   void innate_ui::_main_post(const ::procedure & procedure)
   {

      system()->acme_windowing()->_main_post(procedure);

//      auto psubparticle = (::subparticle *)procedure.m_pbase;
//
//#if REFERENCING_DEBUGGING
//
//      psubparticle->m_prefererTransfer2 = __refdbg_add_referer;
//
//#endif
//
//      psubparticle->increment_reference_count();
//
//      PostThreadMessage(m_dwThread, WM_APP + 123, 0, (LPARAM)psubparticle);

   }


   //LRESULT innate_ui::_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   //{

   //   auto pwindow = m_windowmap[hwnd];

   //   if (pwindow)
   //   {

   //      return pwindow->_window_procedure(message, wparam, lparam);

   //   }

   //   return DefWindowProc(hwnd, message, wparam, lparam);


   //}


   void innate_ui::_defer_run_innate_ui_win32_user_loop()
   {

      //if (m_bRunning)
      //{
      //   return;


      //}
      //manual_reset_happening happening;

      //happening.reset_happening();

      //system()->application()->fork([this, &happening]()
      //   {
      //         try
      //         {
      //            
      //            __check_refdbg

      //            MSG msg;
      //            // Main message loop:
      //            ::PeekMessage(&msg, nullptr, 0, 0, 0);


      //            __check_refdbg

      //            m_hthread = ::GetCurrentThread();

      //            __check_refdbg

      //            m_dwThread = ::GetCurrentThreadId();

      //            __check_refdbg

      //            happening.set_happening();

      //            __check_refdbg

      //            while (::task_get_run())
      //            {

      //               __check_refdbg

      //               DWORD timeout = 100; // 100 ::times;

      //               __check_refdbg

      //               while (MsgWaitForMultipleObjects(0, NULL, FALSE, timeout, QS_ALLINPUT) != WAIT_OBJECT_0)
      //               {

      //                  __check_refdbg

      //                  if (PeekMessage(&msg, nullptr, 0, 0, false))
      //                  {

      //                     break;

      //                  }

      //                  __check_refdbg

      //                  if (!task_get_run())
      //                  {

      //                     return;

      //                  }

      //               }

      //               __check_refdbg

      //               if (GetMessage(&msg, nullptr, 0, 0))
      //               {

      //                  __check_refdbg

      //                  if (msg.message == WM_APP + 123)
      //                  {

      //                     __check_refdbg

      //                     ::pointer < ::subparticle > psubparticle = { transfer_t{}, (::subparticle *)msg.lParam };

      //                     psubparticle->run();

      //                     continue;

      //                  }
      //                  //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      //                  {
      //                     TranslateMessage(&msg);
      //                     DispatchMessage(&msg);
      //                  }

      //               }
      //            }

      //         }
      //         catch (...)
      //         {


      //         }


      //         m_bRunning = false;

      //});

      //happening._wait();

   }



   //LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   //{

   //   ::pointer <::innate_ui_win32::innate_ui> pinnateui = system()->innate_ui();

   //   return pinnateui->_window_procedure(hWnd, message, wParam, lParam);

   //}

   

} // namespace innate_ui_win32



