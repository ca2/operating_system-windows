// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/graphics/write_text/fonts.h"


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 fonts :
      virtual public ::write_text::fonts
   {
   public:


      //__creatable_from_base(fonts, ::write_text::fonts);


      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;


   };


} // namespace write_text_win32



