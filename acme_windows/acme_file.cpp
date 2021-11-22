// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// 03:09 BRT <3ThomasBorregaardS�rensen
#include "framework.h"
#include "acme/operating_system.h"
#include <stdio.h>


namespace windows
{


   acme_file::acme_file()
   {

   }


   acme_file::~acme_file()
   {


   }


   ::file::path acme_file::module()
   {

      ::file::path path;

      {

         wstring wstrPath(get_buffer, MAX_PATH * 16);

         if (!GetModuleFileNameW(nullptr, wstrPath, (DWORD)wstrPath.get_length()))
         {

            return "";

         }

         path = wstrPath.release_string_buffer();

      }

      return path;

   }

   //string acme_file::extension_dup(const char * path)
   //{

   //   string str = acme_file::name_dup(path);

   //   strsize iPos = str.find('.');

   //   if (iPos >= 0)
   //   {

   //      return str.Mid(iPos + 1);

   //   }
   //   else
   //   {

   //      return "";

   //   }

   //}

   //string acme_file::final_extension_dup(const char * path)
   //{

   //   string str = acme_file::name_dup(path);

   //   strsize iPos = str.rfind('.');

   //   if (iPos >= 0)
   //   {

   //      return str.Mid(iPos + 1);

   //   }
   //   else
   //   {

   //      return "";

   //   }

   //}





   //string url_dir_name_for_relative(const char * pszPath)
   //{
   //   string strDir(pszPath);

   //   if (str::ends(strDir, "/"))
   //      return strDir;

   //   str::ends_eat(strDir, "/");

   //   strsize iFind = strDir.reverse_find("/");

   //   if (iFind < 0)
   //      return "/";

   //   return strDir.substr(0, iFind + 1);

   //}


   //CLASS_DECL_ACME string solve_relative(const ::string & strParam, bool * pbUrl)
   //{

   //   string str(strParam);

   //   bool bUrl;

   //   bool bOnlyNativeFileSep;

   //   strsize iaSlash[512];

   //   int iSlashCount = 512;

   //   solve_relative_inline(str, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

   //   if (pbUrl)
   //   {

   //      *pbUrl = bUrl;

   //   }

   //   return str;

   //}

   //CLASS_DECL_ACME string defer_solve_relative(const char * pszRelative, const char * pszAbsolute)
   //{
   //   string strRelative(pszRelative);
   //   string strAbsolute(pszAbsolute);
   //   if (strRelative.is_empty())
   //      return "";
   //   if (strAbsolute.is_empty())
   //      return solve_relative(strRelative);
   //   if (str::begins_ci(strRelative, "http://"))
   //      return solve_relative(strRelative);
   //   if (str::begins_ci(strRelative, "https://"))
   //      return solve_relative(strRelative);
   //   if (str::begins_ci(strRelative, "ftp://"))
   //      return solve_relative(strRelative);
   //   if (str::begins_ci(strRelative, "ext://"))
   //      return solve_relative(strRelative);
   //   if (str::begins(strRelative, "/"))
   //      return solve_relative(strRelative);
   //   if (str::begins(strRelative, "\\\\"))
   //      return solve_relative(strRelative);

   //   index iFind = strRelative.find(":\\");

   //   if (iFind >= 0)
   //   {
   //      index i = 0;
   //      for (; i < iFind; i++)
   //      {
   //         if (!ansi_char_is_alphabetic(strRelative[i]) && !ansi_char_is_digit(strRelative[i]))
   //            break;
   //      }

   //      if (i == iFind)
   //         return solve_relative(strRelative);

   //   }

   //   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   //   if (!str::ends(strAbsolute, "/"))
   //      strAbsolute += "/";
   //   strRelative = strAbsolute + strRelative;


   //   return solve_relative(strRelative);

   //}




   ////CLASS_DECL_ACME bool read_resource_as_file(const char * pszFile,HINSTANCE hinst,::u32 nID,LPCTSTR pcszType);




   //string get_temp_acme_file::name_dup(const char * lpszName, const char * pszExtension)
   //{

   //#ifdef WINDOWS

   //   WCHAR pPathBuffer[MAX_PATH * 16];

   //   ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

   //   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
   //   {

   //      debug_print("GetTempPath failed (%d)\n", ::GetLastError());

   //      return "";

   //   }

   //#else

   //   char pPathBuffer[MAX_PATH * 16];

   //   strcpy(pPathBuffer, "/tmp/");

   //#endif

   //   ::file::path pathFolder(pPathBuffer);

   //   for (int i = 0; i < 1000; i++)
   //   {

   //      ::file::path path;

   //      path = pathFolder;

   //      path /= lpszName;

   //      path /= __string(i);

   //      path /= (string(lpszName) + "." + string(pszExtension));

   //      if (acme_file::exists(path))
   //      {

   //         if (::acme_file::delete(path))
   //         {

   //            return ::move(path);

   //         }

   //      }
   //      else
   //      {

   //         return ::move(path);

   //      }

   //   }

   //   return "";

   //}




   //bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)

   //{

   //#if OSBIT > 32

   //   memsize pos = 0;

   //   ::u32 dw = 0;

   //   ::u32 dwWrite;

   //   memsize uiWrittenTotal = 0;

   //   while (pos < nCount)
   //   {

   //      dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);

   //      dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));


   //      if (dw != dwWrite)
   //      {

   //         uiWrittenTotal += dw;

   //         if (puiWritten != nullptr)
   //         {

   //            *puiWritten = uiWrittenTotal;

   //         }

   //         return false;

   //      }

   //      uiWrittenTotal += dw;

   //      if (dw != dwWrite)
   //         break;

   //      pos += dw;

   //   }

   //   if (puiWritten != nullptr)
   //   {

   //      *puiWritten = uiWrittenTotal;

   //   }

   //   return uiWrittenTotal == nCount;

   //#else

   //   ::u32 dw = 0;

   //   dw = ::fwrite(pdata, 1, (size_t)nCount, file);


   //   int_bool bOk = dw == nCount;

   //   if (puiWritten != nullptr)
   //   {

   //      *puiWritten = dw;

   //   }

   //   return bOk;

   //#endif

   //}


   //CLASS_DECL_ACME bool acme_file::append_wait(const ::string & strFile, const block & block, const ::duration & duration)
   //{

   //            auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->create(::file_path_folder(strFile));

   //   if (!         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->is(::file_path_folder(strFile)))
   //   {

   //      return false;

   //   }

   //   wstring wstr(strFile);

   //   FILE * pfile = nullptr;

   //   auto millisStart = ::duration::now();

   //   while (true)
   //   {

   //#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
   //      pfile = fopen(strFile, "ab");
   //#else
   //      pfile = _wfopen(wstr, L"ab");
   //#endif

   //      if (pfile != nullptr)
   //      {

   //         break;

   //      }

   //      if (millisStart.elapsed() > duration)
   //      {

   //         return false;

   //      }

   //      sleep(500_ms);

   //   }

   //   fwrite(block.get_data(), block.get_size(), 1, pfile);

   //   fclose(pfile);

   //   return true;

   //}


   ////bool acme_file::append_wait(const ::string & strFile, const ::string & str, ::u32 tickTimeout)
   ////{
   ////
   ////   return acme_file::append_wait(strFile, str, str.get_length(), tickTimeout);
   ////
   ////}


   //CLASS_DECL_ACME bool acme_file::append(const ::string & strFile, const block & block)
   //{

   //   return acme_file::append_wait(strFile, block, 0);

   //}


 





   //void replace_char(char * sz, char ch1, char ch2)
   //{

   //   while (*sz)
   //   {

   //      if (*sz == ch1)
   //      {

   //         *sz = ch2;

   //      }

   //      sz++;

   //   }

   //}


   //::file::path acme_file::full_file_path(const char * path)
   //{

   //   WCHAR wszPath[8192];

   //   ::u32 dw = GetFullPathNameW(L"\\\\?\\" + wstring(path), sizeof(wszPath) / sizeof(WCHAR), wszPath, nullptr);

   //   return wszPath;

   //}




} // namespace windows



