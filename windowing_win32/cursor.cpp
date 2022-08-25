// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-02-02 02:43
#include "framework.h"
#include "cursor.h"


TCHAR * windows_get_system_cursor(enum_cursor ecursor);


namespace windowing_win32
{


   cursor::cursor(HCURSOR hcursor)
   {

      set_hcursor(hcursor);

   }


   cursor::~cursor()
   {

      ::DestroyCursor(get_hcursor());

      set_hcursor(nullptr);

   }


   void cursor::_create_os_cursor()
   {

      if (get_hcursor())
      {

         return;
         

      }

      if (m_pimage)
      {

         //auto estatus = 
         
         _create_from_image(m_pimage, m_szHotspotOffset.cx, m_szHotspotOffset.cy);

         //if(estatus.succeeded())
         //{

         //   return estatus;

         //}

      }

      //auto estatus = 
      
      _load_default_cursor(m_ecursor);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void cursor::_create_from_image(const ::image * pimage, ::i32 xHotspot, ::i32 yHotspot)
   {

      HCURSOR hcursor = (HCURSOR) create_alpha_cursor(pimage, xHotspot, yHotspot);

      if (!hcursor)
      {

         //return ::error_failed;

         throw ::exception(error_null_pointer);

      }

      set_hcursor(hcursor);

      //return ::success;

   }


   void cursor::_load_default_cursor(enum_cursor ecursor)
   {

      auto pcursor = windows_get_system_cursor(ecursor);

      if (pcursor == nullptr)
      {

         //return ::error_not_found;

         throw ::exception(error_null_pointer);

      }

      HCURSOR hcursor = ::LoadCursor(NULL, pcursor);

      if (::is_null(hcursor))
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      set_hcursor(hcursor);

      //return ::success;

   }


   //void cursor::initialize_system_default()
   //{

   //   return load_default_cursor(m_ecursor);

   //}


} // namespace windowing_win32





TCHAR * windows_get_system_cursor(enum_cursor ecursor)
{

   switch (ecursor)
   {
   case e_cursor_arrow:
      return IDC_ARROW;
   case e_cursor_text_select:
      return IDC_IBEAM;
   case e_cursor_hand:
      return IDC_HAND;
   case e_cursor_size_bottom_right:
      return IDC_SIZENWSE;
   case e_cursor_size_top_left:
      return IDC_SIZENWSE;
   case e_cursor_size_bottom_left:
      return IDC_SIZENESW;
   case e_cursor_size_top_right:
      return IDC_SIZENESW;
   case e_cursor_size_left:
      return IDC_SIZEWE;
   case e_cursor_size_right:
      return IDC_SIZEWE;
   case e_cursor_size_top:
      return IDC_SIZENS;
   case e_cursor_size_bottom:
      return IDC_SIZENS;
   default:
      return IDC_ARROW;
   }

}

