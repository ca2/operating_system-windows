// Created by camilo 2021-02-10 <3TBS_!!
#include "framework.h"


namespace write_text_win32
{


   fonts::fonts()
   {


   }


   fonts::~fonts()
   {


   }

   ::e_status fonts::initialize(::object * pobject)
   {

      auto estatus = ::write_text::fonts::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace write_text_win32



