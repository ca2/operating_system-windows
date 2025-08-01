#include "framework.h"
#include "file_find.h"
#include "acme/filesystem/filesystem/path.h"

#include "acme/prototype/datetime/earth_time.h"
#include "acme/prototype/string/international.h"


namespace acme_windows
{


   file_find::file_find()
   {

      m_pFoundInfo = nullptr;
      m_pNextInfo = nullptr;
      m_hContext = nullptr;
      m_chDirSeparator = '\\';

   }


   file_find::~file_find()
   {

      close();

   }


   void file_find::close()
   {

      //::acme::del(m_pFoundInfo);

      //::acme::del(m_pNextInfo);

      CloseContext();

      m_hContext = nullptr;

   }


   void file_find::CloseContext()
   {

      if(m_hContext != nullptr && m_hContext != INVALID_HANDLE_VALUE)
      {

         ::FindClose(m_hContext);

         m_hContext = nullptr;

      }

   }


   bool file_find::find_file(const ::scoped_string & scopedstrNameParam /* = nullptr */, unsigned int dwUnused /* = 0 */)
   {

      close();

      if (m_pNextInfo == nullptr)
      {

         m_pNextInfo = &m_dataNext;

      }

      m_bGotLast = false;

      string strName(strNameParam);

      if (strName.is_empty())
      {

         strName = "*.*";

      }

      multibyte_to_unicode(CP_UTF8, m_pNextInfo->cFileName, MAX_PATH, strName);

      wstring wstrName = utf8_to_unicode(strName);

      m_hContext = ::FindFirstFileW(wstrName, m_pNextInfo);

      if (m_hContext == INVALID_HANDLE_VALUE)
      {

         DWORD dwError = ::GetLastError();

         close();

         ::SetLastError(dwError);

         return false;

      }

      wstring wstrRoot;

      unichar * pstrRoot = wstrRoot.get_buffer(_MAX_PATH);

      const unichar * pstr = ::_wfullpath(pstrRoot, wstrName, _MAX_PATH);

      // passed name isn't a valid path but was found by the API

      ASSERT(pstr != nullptr);

      if (pstr == nullptr)
      {

         m_strRoot.empty();

         close();

         ::SetLastError(ERROR_INVALID_NAME);

         return false;
      }
      else
      {

         // find the last forward or backward whack

         unichar * pstrBack  = wcsrchr(pstrRoot, '\\');

         unichar * pstrFront = wcsrchr(pstrRoot, '/');

         if (pstrFront != nullptr || pstrBack != nullptr)
         {

            if (pstrFront == nullptr)
               pstrFront = pstrRoot;

            if (pstrBack == nullptr)
               pstrBack = pstrRoot;

            // from the start to the last whack is the root

            if (pstrFront >= pstrBack)
               *pstrFront = '\0';
            else
               *pstrBack = '\0';

         }

         wstrRoot.release_buffer();

      }

      m_strRoot = unicode_to_utf8(wstrRoot);

      return true;

   }


   bool file_find::GetLastAccessTime(FILETIME* pTimeStamp) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT(pTimeStamp != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = m_pFoundInfo->ftLastAccessTime;
         return true;
      }
      else
         return false;

   }

   bool file_find::GetLastWriteTime(FILETIME* pTimeStamp) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT(pTimeStamp != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = m_pFoundInfo->ftLastWriteTime;
         return true;
      }
      else
         return false;

   }


   bool file_find::GetCreationTime(FILETIME* pTimeStamp) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = m_pFoundInfo->ftCreationTime;
         return true;
      }
      else
         return false;

   }


   bool file_find::GetLastAccessTime(::earth::time& refTime) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
      {

         refTime = ::earth::time(as_file_time(m_pFoundInfo->ftLastAccessTime));

         return true;

      }  

      return false;

   }


   bool file_find::GetLastWriteTime(::earth::time& refTime) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (::is_null(m_pFoundInfo))
      {

         return false;

      }
       
      refTime = ::earth::time(as_file_time(m_pFoundInfo->ftLastWriteTime));

      return true;

   }


   bool file_find::GetCreationTime(::earth::time& refTime) const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (::is_null(m_pFoundInfo))
      {

         return false;

      }
         
      refTime = ::earth::time(as_file_time(m_pFoundInfo->ftCreationTime));
      
      return true;
      
   }


   bool file_find::IsDots() const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      // return true if the file name is "." or ".." and
      // the file is a directory

      bool bResult = false;

      if (m_pFoundInfo != nullptr && IsDirectory())
      {

         LPWIN32_FIND_DATAW pFindData = m_pFoundInfo;

         if (pFindData->cFileName[0] == '.')
         {

            if (pFindData->cFileName[1] == '\0' ||
                  (pFindData->cFileName[1] == '.' &&
                   pFindData->cFileName[2] == '\0'))
            {

               bResult = true;

            }

         }

      }

      return bResult;

   }


   bool file_find::find_next_file()
   {

      //ASSERT(m_hContext != nullptr);

      if (m_hContext == nullptr)
         return false;

      if (m_pFoundInfo == nullptr)
      {

         m_pFoundInfo = &m_dataFound;

      }

      //ASSERT_VALID(this);

      WIN32_FIND_DATAW * pTemp = m_pFoundInfo;

      m_pFoundInfo = m_pNextInfo;

      m_pNextInfo = pTemp;

      return ::FindNextFileW(m_hContext, m_pNextInfo);

   }


   string file_find::GetFileURL() const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strResult(L"file://");

      strResult += GetFilePath();

      return strResult;

   }


   string file_find::GetRoot() const
   {

      ASSERT(m_hContext != nullptr);

      ASSERT_VALID(this);

      return m_strRoot;

   }


   ::file::path file_find::GetFilePath() const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strResult = GetRoot();

      if (strResult[strResult.length()-1] != '\\' &&
            strResult[strResult.length()-1] != '/')
         strResult += m_chDirSeparator;

      strResult += GetFileName();

      return strResult;

   }


   string file_find::GetFileTitle() const
   {

      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strFullName = GetFileName();

      string strResult;

      _splitpath(strFullName, nullptr, nullptr, strResult.get_buffer(_MAX_PATH), nullptr);

      strResult.release_buffer();

      return strResult;

   }

   ::file::path file_find::GetFileName() const
   {

      //ASSERT(m_hContext != nullptr);
      //ASSERT_VALID(this);

      if (m_pFoundInfo == nullptr)
      {

         return ::file::path();

      }

      character_count iLen = wcslen(m_pFoundInfo->cFileName);

      character_count i = iLen - 1;

      while (i >= 0 && m_pFoundInfo->cFileName[i] == '\\')
      {

         i--;

      }

      if (i < 0)
      {

         i = 0;

      }

      auto etype = IsDirectory() ? ::file::e_type_existent_folder : ::file::e_type_existent_file;

      return ::file::path(m_pFoundInfo->cFileName, ::e_path_file, etype, false, get_length());

   }


   //void file_find::dump(dump_context & dumpcontext) const
   //{

   //   matter::dump(dumpcontext);

   //   //dumpcontext << "\nm_hContext = " << m_hContext;

   //}


   //void file_find::assert_ok() const
   //{

   //   // if you trip the ASSERT in the else side, you've called
   //   // a get() function without having done at least one
   //   // FindNext() call

   //   if (m_hContext == nullptr)
   //   {

   //      ASSERT(m_pFoundInfo == nullptr && m_pNextInfo == nullptr);

   //   }
   //   else
   //   {

   //      ASSERT(m_pFoundInfo != nullptr && m_pNextInfo != nullptr);

   //   }

   //}


} // namespace acme_windows




