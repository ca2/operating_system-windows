#pragma once


#include "acme/_.h"
#include "acme/operating_system.h"


#if defined(_ACME_WINDOWS_LIBRARY)
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWS  CLASS_DECL_IMPORT
#endif


//::e_status gdiplus_draw_text(::draw2d::graphics * pgraphics, ::draw2d::path * ppath, const string & str, rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfont, double dFontWidth, ::draw2d::brush * pbrush = nullptr, bool bMeasure = false);


//inline auto gdiplus_color(const ::color::color& color)
//{
//   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
//}
//
//
//
//#define __graphics(pgraphics) ((::draw2d_gdiplus::graphics *) pgraphics->m_pthis)
//#define __pen(ppen) ((::draw2d_gdiplus::pen *) ppen->m_pthis)
//#define __brush(pbrush) ((::draw2d_gdiplus::brush *) pbrush->m_pthis)
//#define __font(pfont) ((::draw2d_gdiplus::font *) pfont->m_pthis)
//#define __graphics_path(ppath) ((::draw2d_gdiplus::path *) ppath->m_pthis)
//
//
//
//
//class g_keep
//{
//
//public:
//
//   Gdiplus::Graphics* point_i32;
//   Gdiplus::GraphicsState s;
//
//   g_keep(Gdiplus::Graphics* point1)
//   {
//
//      point = point1;
//
//      s = point_i32->Save();
//
//   }
//
//   ~g_keep()
//   {
//
//      point_i32->Restore(s);
//
//   }
//
//};


//#include "tts_speaker.h"



//#include "apex.h"



//namespace windows
//{
//
//
//   class thread;
//
//   class windows
//   {
//      i32 function();
//   };
//
//   CLASS_DECL_ACME_WINDOWS HINSTANCE   load_library(const char* psz);
//
//   CLASS_DECL_ACME_WINDOWS bool        shell_get_special_folder_path(HWND hwnd, ::file::path& str, i32 csidl, bool fCreate);
//   CLASS_DECL_ACME_WINDOWS::file::path  shell_get_special_folder_path(i32 csidl, bool fCreate = true, ::windowing::window* pwindow = nullptr);
//   CLASS_DECL_ACME_WINDOWS::u32       get_file_attributes(const char* pFileName);
//
//   CLASS_DECL_ACME_WINDOWS::u32       get_current_directory(string& str);
//   CLASS_DECL_ACME_WINDOWS::u32       get_temp_path(string& str);
//   CLASS_DECL_ACME_WINDOWS::i32        reg_query_value(HKEY hkey, const char* pszSubKey, string& str);
//
//   CLASS_DECL_ACME_WINDOWS HICON       extract_icon(HINSTANCE hInst, const char* pszExeFileName, ::u32 nIconIndex);
//
//   CLASS_DECL_ACME_WINDOWS bool        delete_file(const char* pFileName);
//
//   CLASS_DECL_ACME_WINDOWS i32     get_menu_string(HMENU hMenu, ::u32 uDItem, string& str, ::u32 flags);
//   CLASS_DECL_ACME_WINDOWS void        time_to_filetime(::matter* pobject, const ::datetime::time& time, LPFILETIME pFileTime);
//
//   CLASS_DECL_ACME_WINDOWS ::file::path get_known_folder(REFKNOWNFOLDERID kfid);
//
//} // namespace windows
//
//
//
//

