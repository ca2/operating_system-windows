// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-02-02 02:43
#include "framework.h"
#include "cursor.h"
#include "win32.h"
#include "acme/exception/exception.h"


namespace windows
{

   CLASS_DECL_ACME const wchar_t *get_system_cursor(enum_cursor ecursor);

} // namespace windows


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


   void cursor::_create_from_image(::image::image * pimage, int xHotspot, int yHotspot)
   {

      HCURSOR hcursor = (HCURSOR)::windows::create_alpha_cursor(pimage, xHotspot, yHotspot);

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

      auto pcursor = ::windows::get_system_cursor(ecursor);

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






