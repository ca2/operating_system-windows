#include "framework.h"
#include "aura/user/_user.h"
#include "windowing.h"
#include "top_level_enum.h"


#define ___TEMP_CLASS_NAME_SIZE 4096

//
//CLASS_DECL_WINDOWING_WIN32 int_bool os_init_windowing()
//{
//
//   return true;
//
//}
//
//
//CLASS_DECL_WINDOWING_WIN32 void os_term_windowing()
//{
//
//}


namespace windowing_win32
{

   /// from top to bottom
   CLASS_DECL_WINDOWING_WIN32 __pointer(hwnd_array) get_top_level_windows(bool bDesktop, bool bVisible)
   {

      /// from top to bottom
      top_level_enum toplevelenum(bDesktop, bVisible);

      return toplevelenum.m_phwnda;

   }


   top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
      m_bVisible(bVisible)
   {

      __construct_new(m_phwnda);

      if (bDesktop)
      {

         ::EnumDesktopWindows(nullptr, &top_level_enum::EnumWindowsProc, (lparam)this);

      }
      else
      {

         ::EnumWindows(&top_level_enum::EnumWindowsProc, (lparam)this);

      }

   }


   top_level_enum::~top_level_enum()
   {


   }


   BOOL CALLBACK top_level_enum::EnumWindowsProc(HWND hwnd, LPARAM lParam)
   {

      top_level_enum * ptoplevelenum = (top_level_enum *)lParam;

      if (ptoplevelenum->m_bVisible && !IsWindowVisible(hwnd))
      {

         return true;

      }

      ptoplevelenum->m_phwnda->add(hwnd);

      return true;

   }


   void window_create_caret(HWND hwnd, HBITMAP hbitmap)
   {

      ASSERT(::IsWindow(hwnd));

      ::CreateCaret(hwnd, hbitmap, 0, 0);

   }


   void window_create_solid_caret(HWND hwnd, i32 nWidth, i32 nHeight)
   {

      ASSERT(::IsWindow(hwnd));

      ::CreateCaret(hwnd, (HBITMAP)nullptr, nWidth, nHeight);

   }


   void window_create_gray_caret(HWND hwnd, i32 nWidth, i32 nHeight)
   {

      ASSERT(::IsWindow(hwnd));

      ::CreateCaret(hwnd, (HBITMAP)1, nWidth, nHeight);

   }


   CLASS_DECL_WINDOWING_WIN32 string message_box_result_to_string(int iResult);


   void defer_term_ui()
   {


   }


   CLASS_DECL_WINDOWING_WIN32 int erelative_get_window(enum_relative erelative)
   {

      switch (erelative)
      {
      case e_relative_first_child:
         return GW_CHILD;
      default:
         return -1;

      };

   }


   CLASS_DECL_WINDOWING_WIN32 HWND get_window(HWND hwnd, enum_relative erelative)
   {

      int iGetWindow = erelative_get_window(erelative);

      if (iGetWindow < 0)
      {

         ::output_debug_string("Unknown Get Window (GW_*) for enum_relative");

         return nullptr;

      }

      return ::GetWindow(hwnd, iGetWindow);

   }







#ifdef WINDOWS_DESKTOP

   int windows_desktop1_main(HINSTANCE hInstance, int nCmdShow);

#endif




   color32_t get_default_sys_color(u64 u)
   {

      switch (u)
      {
      case COLOR_3DFACE:
         return argb(127, 192, 192, 184);
      case COLOR_WINDOW:
         return argb(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return argb(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return argb(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return argb(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return argb(127, 90, 90, 80);
      default:
         break;
      }

      return argb(127, 0, 0, 0);

   }



} // namespace windowing_win32



