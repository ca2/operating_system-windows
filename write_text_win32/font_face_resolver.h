#pragma once


#include "aura/graphics/write_text/font_face.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include <dwrite.h>


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 font_face_resolver :
      virtual public ::particle
   {
   public:


      ::comptr<IDWriteFactory>          m_pdwritefactory;
      ::comptr<IDWriteFontCollection>   m_pfontcollection;


      font_face_resolver();
      ~font_face_resolver() override;


      ::string resolve_substitute_family(const ::scoped_string & scopedstrFamily);

      bool resolve(
         ::write_text::font_face_source & source,
         const ::write_text::font_face_request & request);

      void clear();


   protected:


      bool _query_substitute(
         HKEY hkeyRoot,
         const ::scoped_string & scopedstrFamily,
         ::string & strSubstitute);

      bool _query_substitute_with_charset_suffix(
         HKEY hkeyRoot,
         const ::scoped_string & scopedstrFamily,
         ::string & strSubstitute);

      void _log_failure(
         const ::scoped_string & scopedstrCategory,
         const ::write_text::font_face_request & request,
         const ::write_text::font_face_source & source);


   };


} // namespace write_text_win32
