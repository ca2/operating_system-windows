// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"
#include "innate_ui.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/operating_system/windows/window.h"
#include "acme/operating_system/windows/windowing.h"


namespace innate_ui_win32
{
   


   dialog::dialog()
   {
   }


   dialog::~dialog()
   {

   }
   void dialog::_get_class(WNDCLASSEXW & wndclassex)
   {


      auto hinstanceWndProc = ::windows::get_window_procedure_hinstance();

      wndclassex.hInstance = (HINSTANCE)hinstanceWndProc;
      wndclassex.lpfnWndProc = &::windows::window_procedure;
      wndclassex.style = CS_HREDRAW | CS_VREDRAW;
      //wndclassex.lpfnWndProc = WndProc;
      wndclassex.cbClsExtra = 0;
      wndclassex.cbWndExtra = 0;
      //wndclassex.hInstance = (HINSTANCE) ::platform::get()->m_hinstanceThis;
      //wndclassex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
      wndclassex.hIcon = nullptr;
      wndclassex.hCursor = LoadCursor(nullptr, IDC_ARROW);
      wndclassex.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
      //wndclassex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
      wndclassex.lpszMenuName = nullptr;
      //wndclassex.hIconSm = LoadIcon(wndclassex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
      wndclassex.hIconSm = nullptr;

   }


   void dialog::create()
   {

      return ::innate_ui_win32::window::create();

   }


   void dialog::_create()
   {

      ::CreateWindowW(_get_class_name(), L"", WS_DLGFRAME | WS_CAPTION | WS_POPUPWINDOW,
              CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::windows::get_window_procedure_hinstance(),
              (::windows::window *)this);

      if (m_hwnd)
      {

         system()->innate_ui()->add_top_level_window(this);

      }


   }


   //void dialog::_show()
   //{

   //   ::innate_ui_win32::window::_show();

   //}


} // namespace innate_ui
