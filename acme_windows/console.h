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


      int                                       m_iW;
      int                                       m_iH;
      //write_text_stream < ::file::file >     m_cout;
      ::file_pointer                            m_pfileOut;


      console();
      ~console() override;


      //::write_text_stream < ::file::file >& cout() override;


      void redirect_io();
      void SetWindowSize(int height,int width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(int y,int x);
      void SetTextColor(int color);
      void SetScreenColor(enum_dos_color edoscolor, int iLineStart = 0, int iLineCount = -1);
      void write(const ::scoped_string & scopedstr);

   };


} // namespace acme_windows




