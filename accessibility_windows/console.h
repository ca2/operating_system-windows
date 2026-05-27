#pragma once


#include "acme/filesystem/file/text_stream.h"
#include "acme/operating_system/console.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS console :
      virtual public ::console::console
   {
   public:


      //__creatable_from_base(console, ::console::console);


      ::i32                                       m_iW;
      ::i32                                       m_iH;
      //write_text_stream < ::file::file >     m_cout;
      ::file_pointer                            m_pfileOut;


      console();
      ~console() override;


      //::write_text_stream < ::file::file >& cout() override;


      void redirect_io();
      void SetWindowSize(::i32 height,::i32 width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(::i32 y,::i32 x);
      void SetTextColor(::i32 color);
      void SetScreenColor(enum_dos_color edoscolor, ::i32 iLineStart = 0, ::i32 iLineCount = -1);
      void write(const ::scoped_string & scopedstr);

   };


} // namespace acme_windows




