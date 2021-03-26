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

      auto estatus = ::font_department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status font_department::finalize()
   {

       auto estatus = ::font_department::finalize();

       return estatus;
      
   }


   void font_department::enum_fonts(::write_text::font_enum_item_array & itema)
   {

      wingdi_font_enum fontenum(itema, true, true, true);

   }


} // namespace write_text_win32



