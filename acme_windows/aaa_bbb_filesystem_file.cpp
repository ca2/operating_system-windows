#include "framework.h"
#include "acme/operating_system.h"
#include <stdio.h>


string file_extension_dup(const char * path)
{

   string str = file_path_name(path);

   character_count iPos = str.find('.');

   if (iPos >= 0)
   {

      return str.substr(iPos + 1);

   }
   else
   {

      return "";

   }

}

string file_final_extension_dup(const char * path)
{

   string str = file_path_name(path);

   character_count iPos = str.rear_find('.');

   if (iPos >= 0)
   {

      return str.substr(iPos + 1);

   }
   else
   {

      return "";

   }

}


string url_dir_name_for_relative(const scoped_string & strPath)
{

   string strDir(pszPath);

   if (strDir.ends("/"))
      return strDir;

   strDir.ends_eat("/");

   character_count iFind = strDir.rear_find("/");

   if (iFind < 0)
      return "/";

   return strDir.substr(0, iFind + 1);

}


CLASS_DECL_ACME string solve_relative(const ::string & strParam, bool * pbUrl)
{

   string str(strParam);

   bool bUrl;

   bool bOnlyNativeFileSep;

   character_count iaSlash[512];

   int iSlashCount = 512;

   solve_relative_inline(str, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

   if (pbUrl)
   {

      *pbUrl = bUrl;

   }

   return str;

}

#ifdef WINDOWS

#define CHECK_NATIVE_FILE_SEP(ch) \
\
if (bOnlyNativeFileSep && psz[iPos] == '/') \
{ \
\
   bOnlyNativeFileSep = false; \
\
}

#else

#define CHECK_NATIVE_FILE_SEP(ch) \
\
if (bOnlyNativeFileSep && psz[iPos] == '/') \
{ \
\
   bOnlyNativeFileSep = false; \
\
}

#endif


CLASS_DECL_ACME bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, character_count * iaSlash, int * piSlashCount)
{

   bOnlyNativeFileSep = true;

   bool bCertainlySyntathicallyDir = false;

   bUrl = false;

   bool bDup = false;

   character_count iLen = str.length();

   char * psz = str.get_buffer(iLen);

   //string strAbsolute(strParam);

   character_count iNewPos;

   bool bDynIa = false;

   //character_count * iaSlash = *iaSlash;

   int & iSlashCount = *piSlashCount;

   iSlashCount = 0;

   iaSlash[0] = 0;

   character_count iPos = 0;

   if (iLen >= 2)
   {

      if (psz[0] == '\\' && psz[1] == '\\')
      {

#ifndef WINDOWS

         bOnlyNativeFileSep = false;

#endif

         iaSlash[0] = 1;

         iPos = 2;

         iSlashCount = 1;

      }

   }

   while (psz[iPos])
   {

      if (psz[iPos] == '/' || psz[iPos] == '\\')
      {

         CHECK_NATIVE_FILE_SEP(psz[iPos]);

         iaSlash[iSlashCount] = iPos;

         iSlashCount++;

         iPos++;

         if (iPos >= iLen)
         {

            // the end of string has been reached

            if (iPos > 2)
            {

               iSlashCount--;

               iPos--; // erase trailing slash

            }

            bCertainlySyntathicallyDir = true;

            goto ret;

         }
         else if (psz[iPos] == '.')
         {

            iPos++;

            if (iPos >= iLen)
            {

               // the end of string has been reached

               if (iSlashCount >= 2)
               {

                  iPos -= 2; // erase the dot and and trailing slash

               }
               else
               {

                  iPos--;// erase the dot

               }

               bCertainlySyntathicallyDir = true;

               goto ret;

            }
            else if (psz[iPos] == '.')
            {

               iPos++;

               if (iPos >= iLen)
               {

                  // the end of string has been reached

                  iPos = iaSlash[maximum(0, iSlashCount - 2)]; // go back to position of previous slash

                  iSlashCount -= 2;

                  if (iSlashCount <= 0)
                  {

                     iSlashCount = 1;

                  }

                  if (iPos > 2)
                  {

                     iPos--;

                  }

                  bCertainlySyntathicallyDir = true;

                  goto ret;

               }
               else if (psz[iPos] == '/' || psz[iPos] == '\\')
               {

                  CHECK_NATIVE_FILE_SEP(psz[iPos]);

                  if (!bDup)
                  {

                     psz = str.get_buffer();

                     bDup = true;

                  }

                  iSlashCount -= 2;

                  if (iSlashCount <= 0)
                  {

                     iNewPos = iaSlash[0];

                     iSlashCount = 1;

                  }
                  else
                  {

                     iNewPos = iaSlash[iSlashCount];

                  }

                  strcpy(&psz[iNewPos], &psz[iPos]);

                  iLen -= iPos - iNewPos;

                  iPos = iNewPos;

               }
               else
               {

                  iPos += ch_unicode_len(psz[iPos]);

                  if (iPos >= iLen)
                  {

                     iPos = iLen - 1;

                     goto ret;

                  }

               }

            }
            else if (psz[iPos] == '/' || psz[iPos] == '\\')
            {

               CHECK_NATIVE_FILE_SEP(psz[iPos]);

               if (!bDup)
               {

                  psz = str.get_buffer();

                  bDup = true;

               }

               iSlashCount--;

               if (iSlashCount <= 0)
               {

                  iNewPos = iaSlash[0];

                  iSlashCount = 1;

               }
               else
               {

                  iNewPos = iaSlash[iSlashCount];

               }

               strcpy(&psz[iNewPos], &psz[iPos]);

               iLen -= iPos - iNewPos;

               iPos = iNewPos;

            }
            else
            {

               iPos += ch_unicode_len(psz[iPos]);

               if (iPos >= iLen)
               {

                  goto ret;

               }

            }

         }
         else if (psz[iPos] == '/' || psz[iPos] == '\\')
         {

            CHECK_NATIVE_FILE_SEP(psz[iPos]);

            iaSlash[iSlashCount] = iPos;

            iSlashCount++;

            iPos++;

            if (iPos > 3 && psz[iPos - 3] == ':')
            {

               bUrl = true;

            }

            if (iPos >= iLen)
            {

               // the end of string has been reached


               bCertainlySyntathicallyDir = true;

               goto ret;

            }

         }
         else
         {

            iPos += ch_unicode_len(psz[iPos]);

            if (iPos >= iLen)
            {

               goto ret;

            }

         }

      }
      else
      {

         iPos += ch_unicode_len(psz[iPos]);

         if (iPos >= iLen)
         {

            goto ret;

         }

      }

   }

ret:

   if (bDup)
   {

      str.release_buffer(iPos);

   }
   else if (iPos < iLen)
   {

      str.truncate(iPos);

   }

   return bCertainlySyntathicallyDir;

}


CLASS_DECL_ACME string defer_solve_relative(const scoped_string & strRelative, const scoped_string & strAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if (strRelative.is_empty())
      return "";
   if (strAbsolute.is_empty())
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("http://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("https://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("ftp://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("ext://"))
      return solve_relative(strRelative);
   if (strRelative.begins("/"))
      return solve_relative(strRelative);
   if (strRelative.begins("\\\\"))
      return solve_relative(strRelative);

   ::collection::index iFind = strRelative.find(":\\");

   if (iFind >= 0)
   {
      ::collection::index i = 0;
      for (; i < iFind; i++)
      {
         if (!ansi_char_isalpha(strRelative[i]) && !ansi_char_isdigit(strRelative[i]))
            break;
      }

      if (i == iFind)
         return solve_relative(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if (!strAbsolute.ends("/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return solve_relative(strRelative);

}




//CLASS_DECL_ACME bool read_resource_as_file(const scoped_string & strFile,HINSTANCE hinst,unsigned int nID,LPCTSTR pcszType);









void replace_char(char * sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}
