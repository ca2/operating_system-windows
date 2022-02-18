// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/graphics/write_text/write_text.h"


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 write_text :
      virtual public ::write_text::write_text
   {
   public:


      //__creatable_from_base(write_text, ::write_text::write_text, "write_text_win32");


      write_text();
      ~write_text() override;


   };


} // namespace write_text_win32



