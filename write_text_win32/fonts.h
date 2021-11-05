// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 fonts :
      virtual public ::write_text::fonts
   {
   public:



      fonts();
      ~fonts() override;


      ::e_status initialize(::object * pobject) override;


   };


} // namespace write_text_win32



