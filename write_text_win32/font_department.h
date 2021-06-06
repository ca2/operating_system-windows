// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 font_department :
      virtual public ::write_text::font_department
   {
   public:



      font_department();
      ~font_department() override;


      ::e_status initialize(::object * pobject) override;



   };


} // namespace write_text_win32



