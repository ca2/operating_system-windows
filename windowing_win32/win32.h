// First insertions by camilo on 2022-08-27 19:56 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/operating_system.h"


namespace windows
{


   CLASS_DECL_WINDOWING_WIN32 HMONITOR get_primary_monitor_handle();
   CLASS_DECL_WINDOWING_WIN32 HMONITOR get_window_monitor_handle(HWND hwnd);


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap(pixmap * ppixmap);
   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap_2(pixmap * ppixmap);


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_alpha_bitmap_v5(const ::image * pimage);
   CLASS_DECL_WINDOWING_WIN32 HICON create_alpha_icon(const ::image * pimage, bool bIcon = true, int xHotSpot = 0, int yHotSpot = 0);
   CLASS_DECL_WINDOWING_WIN32 HCURSOR create_alpha_cursor(const ::image * pimage, int xHotSpot, int yHotSpot);
   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::size_i32 & size, i32 * piScan = nullptr, ::color32_t ** ppdata = nullptr);;
   CLASS_DECL_WINDOWING_WIN32 HICON load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy);


   CLASS_DECL_WINDOWING_WIN32 int show_window(enum_display edisplay, enum_activation eactivation);
   CLASS_DECL_WINDOWING_WIN32 enum_display show_window_to_edisplay(int iShowWindow, enum_activation & eactivation);

   CLASS_DECL_WINDOWING_WIN32 HWND get_mouse_capture(itask_t itask);


   using window_map = map < HWND, __pointer(::windowing_win32::window) >;



} // namespace windows



