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

   ::e_status font_department::initialize(::layered * pobjectContext)
   {

      auto estatus = ::font_department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void font_department::finalize()
   {

         ::font_department::finalize();

      
   }



   void font_department::enum_fonts(::write_text::font_enum_item_array & itema)
   {

      wingdi_font_enum fontenum(itema, true, true, true);

   }


} // namespace write_text_win32



