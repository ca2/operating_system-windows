#pragma once


#include "aura_windows/_aura_windows.h"
#include "aura/user/_user.h"


namespace windowing_win32
{


   CLASS_DECL_WINDOWING_WIN32 void wingdi_enum_fonts(::write_text::font_enumeration_item_array& itema, bool bRaster, bool bTrueType, bool bOther);
   CLASS_DECL_WINDOWING_WIN32::enum_character_set wingdi_get_cs(int iCharSet);

   
   CLASS_DECL_WINDOWING_WIN32 HMONITOR get_primary_monitor_handle();
   CLASS_DECL_WINDOWING_WIN32 HMONITOR get_window_monitor_handle(HWND hwnd);


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap(pixmap* ppixmap);
   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap_2(pixmap* ppixmap);


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_alpha_bitmap_v5(const ::image* pimage);
   CLASS_DECL_WINDOWING_WIN32 HICON create_alpha_icon(const ::image* pimage, bool bIcon = true, int xHotSpot = 0, int yHotSpot = 0);
   CLASS_DECL_WINDOWING_WIN32 HCURSOR create_alpha_cursor(const ::image* pimage, int xHotSpot, int yHotSpot);
   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::size_i32& size, i32* piScan = nullptr, color32_t** ppdata = nullptr);;
   CLASS_DECL_WINDOWING_WIN32 HICON load_icon(::object* pobject, string_array& straMatter, string strIcon, int cx, int cy);


} // namespace windowing_win32


CLASS_DECL_WINDOWING_WIN32 int windows_show_window(enum_display edisplay, enum_activation eactivation);
CLASS_DECL_WINDOWING_WIN32 enum_display windows_show_window_to_edisplay(int iShowWindow, enum_activation& eactivation);


#include "window_util.h"
#include "win32.h"


#include "buffer.h"
#include "display.h"
#include "cursor.h"
#include "icon.h"
#include "imm_client.h"
#include "imm_context.h"
#include "monitor.h"
#include "keyboard.h"


#include "notification_area.h"
#include "notify_icon.h"


#include "copydesk.h"


#include "shell.h"


#include "system_interaction.h"


#include "window.h"


#include "windowing.h"


#include "top_level_enum.h"


#include "_impl.h"



