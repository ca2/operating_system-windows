// Created by camilo 2021-02-10 <3TBS_!!
#include "platform.h"
#include "write_text.h"
#if defined(__REACTOS__)
#include "acme/_operating_system.h"
#include "acme/prototype/collection/string_array.h"
#endif


namespace write_text_win32
{

   
   write_text::write_text()
   {


   }


   write_text::~write_text()
   {


   }


   void write_text::destroy()
   {

      {

         critical_section_lock synchronouslock(&m_csFont);

         m_mapFontFaceSource.clear();
         m_pfontfaceresolver.release();

      }

      ::write_text::write_text::destroy();

   }


   void write_text::handle_font_enumeration(::topic * ptopic)
   {

      {

         critical_section_lock synchronouslock(&m_csFont);

         m_mapFontFaceSource.clear();

         if (m_pfontfaceresolver)
         {

            m_pfontfaceresolver->clear();

         }

      }

      ::write_text::write_text::handle_font_enumeration(ptopic);

   }


   bool write_text::resolve_font_face(
      ::write_text::font_face_source & source,
      const ::write_text::font_face_request & request)
   {

      ::string strFamilyKey(request.m_strFamily);
      strFamilyKey.trim();
      strFamilyKey.make_lower();

      ::string strKey;
      strKey.formatf(
         "%s|%d|%d",
         strFamilyKey.c_str(),
         request.m_fontweight.as_i32(),
         request.m_bItalic ? 1 : 0);

      ::string strSubstituteFamily;

      {

         critical_section_lock synchronouslock(&m_csFont);

         auto passociation = m_mapFontFaceSource.find(strKey);

         if (passociation)
         {

            source = passociation->element2();

            return true;

         }

         if (!m_pfontfaceresolver)
         {

            construct_newø(m_pfontfaceresolver);

         }

         if (m_pfontfaceresolver->resolve(source, request))
         {

            m_mapFontFaceSource[strKey] = source;

            return true;

         }

         strSubstituteFamily =
            m_pfontfaceresolver->resolve_substitute_family(request.m_strFamily);

      }

      auto fallbackRequest = request;
      fallbackRequest.m_strFamily = strSubstituteFamily;

      if (::write_text::write_text::resolve_font_face(source, fallbackRequest))
         return true;
#if defined(__REACTOS__)
      // Segoe UI is not necessarily installed on ReactOS. Prefer the host's
      // actual GUI font before trying compatibility font families.
      ::string_array_base candidates;
      LOGFONTW guiFont{};
      if (::GetObjectW(::GetStockObject(DEFAULT_GUI_FONT), sizeof(guiFont), &guiFont))
         candidates.add(::string(guiFont.lfFaceName));
      candidates.add("Tahoma");
      candidates.add("DejaVu Sans");
      candidates.add("Liberation Sans");
      candidates.add("Arial");
      for (const auto &family : candidates)
      {
         auto candidateRequest = request;
         candidateRequest.m_strFamily = family;
         {
            critical_section_lock lock(&m_csFont);
            candidateRequest.m_strFamily = m_pfontfaceresolver->resolve_substitute_family(family);
         }
         if (::write_text::write_text::resolve_font_face(source, candidateRequest))
         {
            critical_section_lock lock(&m_csFont);
            m_mapFontFaceSource[strKey] = source;
            informationf("ReactOS font fallback: requested=%s selected=%s file=%s",
               request.m_strFamily.c_str(), source.m_strResolvedFamily.c_str(), source.m_path.c_str());
            return true;
         }
      }
#endif
      return false;

   }


} // namespace write_text_win32



