#include "framework.h"


namespace draw2d_gdi
{


   path::path(::object * pobject):
      ::draw2d::path(pobject)
   {

   }

   path::~path()
   {

   }



   void path::get_bounding_rect(LPRECT lprect,::draw2d::path::string_path & p)
   {

      HDC hdc = ::CreateCompatibleDC(nullptr);

      ::SelectObject(hdc, p.m_pfont->get_os_data());

      wstring wstr(p.m_strText);

      ::size_i32 size;

      if(::GetTextExtentPoint32W(hdc,wstr,(int)wstr.get_length(),&size))
      {
         lprect->left   = (LONG)minimum(p.m_x,lprect->left);

         lprect->top    = (LONG)minimum(p.m_y,lprect->top);

         lprect->right  = (LONG)maximum(p.m_x + size.cx,lprect->right);

         lprect->bottom = (LONG)maximum(p.m_y + size.cy,lprect->bottom);
      }


      ::ReleaseDC(nullptr,hdc);

   }


} // namespace draw2d






