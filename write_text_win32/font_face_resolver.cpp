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

         return _query_substitute_with_charset_suffix(
            hkeyRoot,
            scopedstrFamily,
            strSubstitute);

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


   bool font_face_resolver::_query_substitute_with_charset_suffix(
      HKEY hkeyRoot,
      const ::scoped_string & scopedstrFamily,
      ::string & strSubstitute)
   {

      HKEY hkeyFontSubstitutes = nullptr;

      auto lstatus = ::RegOpenKeyExW(
         hkeyRoot,
         g_pwszFontSubstitutes,
         0,
         KEY_QUERY_VALUE,
         &hkeyFontSubstitutes);

      if (lstatus != ERROR_SUCCESS)
      {

         return false;

      }

      bool bFound = false;

      for (DWORD dwIndex = 0; ; dwIndex++)
      {

         wchar_t wszValueName[1024]{};
         wchar_t wszSubstitute[1024]{};
         DWORD dwValueNameLength = (DWORD)std::size(wszValueName);
         DWORD dwSubstituteSize = sizeof(wszSubstitute);
         DWORD dwType = 0;

         lstatus = ::RegEnumValueW(
            hkeyFontSubstitutes,
            dwIndex,
            wszValueName,
            &dwValueNameLength,
            nullptr,
            &dwType,
            reinterpret_cast<BYTE *>(wszSubstitute),
            &dwSubstituteSize);

         if (lstatus == ERROR_NO_MORE_ITEMS)
         {

            break;

         }

         if (lstatus != ERROR_SUCCESS || dwType != REG_SZ)
         {

            continue;

         }

         ::string strValueName(wszValueName);
         auto iComma = strValueName.find_index(',');

         if (iComma < 0)
         {

            continue;

         }

         strValueName.truncate(iComma);
         strValueName.trim();

         if (!strValueName.case_insensitive_equals(scopedstrFamily))
         {

            continue;

         }

         strSubstitute = wszSubstitute;
         strSubstitute.trim();

         iComma = strSubstitute.find_index(',');

         if (iComma >= 0)
         {

            strSubstitute.truncate(iComma);
            strSubstitute.trim();

         }

         bFound = strSubstitute.has_character();

         break;

      }

      ::RegCloseKey(hkeyFontSubstitutes);

      return bFound;

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


   bool font_face_resolver::_resolve_gdi_font(
      ::comptr<IDWriteFont> & pfont,
      const ::scoped_string & scopedstrFamily,
      const ::write_text::font_face_request & request)
   {

      if (!m_pgdinterop)
      {

         auto hr = m_pdwritefactory->GetGdiInterop(&m_pgdinterop);

         if (FAILED(hr) || !m_pgdinterop)
         {

            return false;

         }

      }

      ::wstring wstrFamily(scopedstrFamily);

      if (wstrFamily.size() >= LF_FACESIZE)
      {

         return false;

      }

      LOGFONTW logfont{};
      logfont.lfWeight = request.m_fontweight.as_i32();
      logfont.lfItalic = request.m_bItalic ? TRUE : FALSE;
      logfont.lfCharSet = DEFAULT_CHARSET;

      wcscpy_s(logfont.lfFaceName, LF_FACESIZE, wstrFamily);

      auto hr = m_pgdinterop->CreateFontFromLOGFONT(&logfont, &pfont);

      return SUCCEEDED(hr) && pfont;

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

      ::comptr<IDWriteFont> pfont;

      if (SUCCEEDED(hr) && bExists)
      {

         ::comptr<IDWriteFontFamily> pfontfamily;

         hr = m_pfontcollection->GetFontFamily(uFamilyIndex, &pfontfamily);

         if (SUCCEEDED(hr) && pfontfamily)
         {

            hr = pfontfamily->GetFirstMatchingFont(
               static_cast<DWRITE_FONT_WEIGHT>(request.m_fontweight.as_i32()),
               DWRITE_FONT_STRETCH_NORMAL,
               request.m_bItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
               &pfont);

         }

      }
      else
      {

         _resolve_gdi_font(
            pfont,
            source.m_strResolvedFamily,
            request);

      }

      if (!pfont)
      {

         _log_failure(
            bExists ? "face_not_found" : "family_not_found",
            request,
            source);

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
