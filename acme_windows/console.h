#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS console :
      virtual public ::console::console
   {
   public:


      __creatable_from_library(console, ::console::console, "acme_windows");


      int m_iW;
      int m_iH;
      string_stream m_cout;


      console();
      ~console() override;

      ::string_stream& cout() override;


      void redirect_io();
      void SetWindowSize(int height,int width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(int y,int x);
      void SetTextColor(int color);
      void SetScreenColor(enum_dos_color edoscolor, int iLineStart = 0, int iLineCount = -1);
      void write(const ::string & psz);

   };


} // namespace windows




