// Created by camilo 2021-02-10 <3TBS_!!
#include "framework.h"


namespace write_text_win32
{


   font_department::font_department()
   {


   }


   font_department::~font_department()
   {


   }

   ::e_status font_department::initialize(::object * pobject)
   {

      auto estatus = ::write_text::font_department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace write_text_win32



