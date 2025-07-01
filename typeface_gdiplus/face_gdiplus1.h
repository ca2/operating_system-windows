// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"
#include <gdiplus.h>


namespace typeface_gdiplus
{


   class face :
      virtual public ::typeface::face
   {
   public:

      //bool m_bFace;
      
      Gdiplus::FontFamily *m_pfamily;
      Gdiplus::Font *m_pfont;



      face();
      ~face() override;

      
      void create_character(::typeface::character& ch,const ::scoped_string& scopedstr);

      
   };


} // namespace typeface_gdiplus

