#include "framework.h"
#include "font_face_resolver.h"
#include "acme/prototype/collection/string_array.h"


namespace write_text_win32
{


   namespace
   {


      constexpr const wchar_t * g_pwszFontSubstitutes =
         L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\FontSubstitutes";


   } // namespace


   font_face_resolver::font_face_resolver()
   {

   }


   font_face_resolver::~font_face_resolver()
   {

   }


   bool font_face_resolver::_query_substitute(
      HKEY hkeyRoot,
      const ::scoped_string & scopedstrFamily,
      ::string & strSubstitute)
   {

      ::wstring wstrFamily(scopedstrFamily);
      wchar_t wszSubstitute[1024]{};
      DWORD dwType = 0;
      DWORD dwSize = sizeof(wszSubstitute);

      auto lstatus = ::RegGetValueW(
         hkeyRoot,
         g_pwszFontSubstitutes,
         wstrFamily,
         RRF_RT_REG_SZ,
         &dwType,
         wszSubstitute,
         &dwSize);

      if (lstatus != ERROR_SUCCESS)
      {

         return false;

      }

      strSubstitute = wszSubstitute;
      strSubstitute.trim();

      auto iComma = strSubstitute.find_index(',');

      if (iComma >= 0)
      {

         strSubstitute.truncate(iComma);
         strSubstitute.trim();

      }

      return strSubstitute.has_character();

   }


   ::string font_face_resolver::resolve_substitute_family(
      const ::scoped_string & scopedstrFamily)
   {

      ::string strFamily(scopedstrFamily);
      strFamily.trim();

      ::string_array straVisited;

      for (int iDepth = 0; iDepth < 16; iDepth++)
      {

         if (straVisited.case_insensitive_contains(strFamily))
         {

            information() << "[write_text_win32.font_face] substitution_cycle family=\""
               << strFamily << "\"";

            return strFamily;

         }

         straVisited.add(strFamily);

         ::string strSubstitute;

         if (!_query_substitute(HKEY_CURRENT_USER, strFamily, strSubstitute)
            && !_query_substitute(HKEY_LOCAL_MACHINE, strFamily, strSubstitute))
         {

            return strFamily;

         }

         if (strSubstitute.case_insensitive_equals(strFamily))
         {

            return strFamily;

         }

         strFamily = strSubstitute;

      }

      information() << "[write_text_win32.font_face] substitution_cycle family=\""
         << strFamily << "\" depth=16";

      return strFamily;

   }


   void font_face_resolver::_log_failure(
      const ::scoped_string & scopedstrCategory,
      const ::write_text::font_face_request & request,
      const ::write_text::font_face_source & source)
   {

      information() << "[write_text_win32.font_face] " << scopedstrCategory
         << " requested_family=\"" << request.m_strFamily
         << "\" weight=" << request.m_fontweight.as_i32()
         << " italic=" << (request.m_bItalic ? 1 : 0)
         << " resolved_family=\"" << source.m_strResolvedFamily
         << "\" path=\"" << source.m_path
         << "\" face_index=" << source.m_iFaceIndex;

   }


   bool font_face_resolver::resolve(
      ::write_text::font_face_source & source,
      const ::write_text::font_face_request & request)
   {

      source = {};
      source.m_strResolvedFamily = resolve_substitute_family(request.m_strFamily);

      if (!m_pdwritefactory)
      {

         auto hr = ::DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown **>(&m_pdwritefactory));

         if (FAILED(hr) || !m_pdwritefactory)
         {

            _log_failure("factory_failed", request, source);

            return false;

         }

      }

      if (!m_pfontcollection)
      {

         auto hr = m_pdwritefactory->GetSystemFontCollection(
            &m_pfontcollection,
            TRUE);

         if (FAILED(hr) || !m_pfontcollection)
         {

            _log_failure("collection_failed", request, source);

            return false;

         }

      }

      ::wstring wstrFamily(source.m_strResolvedFamily);
      ::u32 uFamilyIndex = 0;
      BOOL bExists = FALSE;

      auto hr = m_pfontcollection->FindFamilyName(
         wstrFamily,
         &uFamilyIndex,
         &bExists);

      if (FAILED(hr) || !bExists)
      {

         _log_failure("family_not_found", request, source);

         return false;

      }

      ::comptr<IDWriteFontFamily> pfontfamily;

      hr = m_pfontcollection->GetFontFamily(uFamilyIndex, &pfontfamily);

      if (FAILED(hr) || !pfontfamily)
      {

         _log_failure("family_not_found", request, source);

         return false;

      }

      ::comptr<IDWriteFont> pfont;

      hr = pfontfamily->GetFirstMatchingFont(
         static_cast<DWRITE_FONT_WEIGHT>(request.m_fontweight.as_i32()),
         DWRITE_FONT_STRETCH_NORMAL,
         request.m_bItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
         &pfont);

      if (FAILED(hr) || !pfont)
      {

         _log_failure("face_not_found", request, source);

         return false;

      }

      ::comptr<IDWriteFontFace> pfontface;

      hr = pfont->CreateFontFace(&pfontface);

      if (FAILED(hr) || !pfontface)
      {

         _log_failure("face_not_found", request, source);

         return false;

      }

      source.m_iFaceIndex = static_cast<int>(pfontface->GetIndex());

      ::u32 uFileCount = 0;

      hr = pfontface->GetFiles(&uFileCount, nullptr);

      if (FAILED(hr) || uFileCount != 1)
      {

         _log_failure("multiple_files", request, source);

         return false;

      }

      ::comptr<IDWriteFontFile> pfontfile;

      hr = pfontface->GetFiles(&uFileCount, &pfontfile);

      if (FAILED(hr) || !pfontfile)
      {

         _log_failure("path_failed", request, source);

         return false;

      }

      const void * pReferenceKey = nullptr;
      ::u32 uReferenceKeySize = 0;

      hr = pfontfile->GetReferenceKey(&pReferenceKey, &uReferenceKeySize);

      if (FAILED(hr) || !pReferenceKey || uReferenceKeySize == 0)
      {

         _log_failure("path_failed", request, source);

         return false;

      }

      ::comptr<IDWriteFontFileLoader> pfontfileloader;

      hr = pfontfile->GetLoader(&pfontfileloader);

      if (FAILED(hr) || !pfontfileloader)
      {

         _log_failure("path_failed", request, source);

         return false;

      }

      ::comptr<IDWriteLocalFontFileLoader> plocalfontfileloader;

      hr = pfontfileloader.as(plocalfontfileloader);

      if (FAILED(hr) || !plocalfontfileloader)
      {

         _log_failure("nonlocal_file", request, source);

         return false;

      }

      ::u32 uPathLength = 0;

      hr = plocalfontfileloader->GetFilePathLengthFromKey(
         pReferenceKey,
         uReferenceKeySize,
         &uPathLength);

      if (FAILED(hr) || uPathLength == 0)
      {

         _log_failure("path_failed", request, source);

         return false;

      }

      ::wstring wstrPath;
      auto pwszPath = wstrPath.get_buffer(uPathLength + 1);

      hr = plocalfontfileloader->GetFilePathFromKey(
         pReferenceKey,
         uReferenceKeySize,
         pwszPath,
         uPathLength + 1);

      wstrPath.release_buffer();

      if (FAILED(hr))
      {

         _log_failure("path_failed", request, source);

         return false;

      }

      source.m_path = wstrPath;

      if (::GetFileAttributesW(wstrPath) == INVALID_FILE_ATTRIBUTES)
      {

         _log_failure("path_missing", request, source);

         return false;

      }

      return true;

   }


   void font_face_resolver::clear()
   {

      m_pfontcollection.release();

   }


} // namespace write_text_win32
