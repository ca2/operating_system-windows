// Created by camilo on 2026-01-06 21:34 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/typeface/typeface.h"


namespace typeface_gdiplus
{


   class CLASS_DECL_TYPEFACE_GDIPLUS typeface : virtual public ::typeface::typeface
   {
   public:


      typeface();
      ~typeface() override;


      ::file::path _get_font_file_path_by_font_name(const ::scoped_string &scopedstr) override;
   };


} // namespace typeface_gdiplus




