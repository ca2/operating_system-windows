// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "font_face_resolver.h"
#include "aura/graphics/write_text/write_text.h"


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 write_text :
      virtual public ::write_text::write_text
   {
   public:


      ::pointer < font_face_resolver >                    m_pfontfaceresolver;
      string_map_base < ::write_text::font_face_source > m_mapFontFaceSource;

      //__creatable_from_base(write_text, ::write_text::write_text, "write_text_win32");


      write_text();
      ~write_text() override;

      void destroy() override;

      void handle_font_enumeration(::topic * ptopic) override;

      bool resolve_font_face(
         ::write_text::font_face_source & source,
         const ::write_text::font_face_request & request) override;


   };


} // namespace write_text_win32



