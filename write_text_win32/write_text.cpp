// Created by camilo 2021-02-10 <3TBS_!!
#include "framework.h"
#include "write_text.h"


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

      return ::write_text::write_text::resolve_font_face(source, fallbackRequest);

   }


} // namespace write_text_win32



