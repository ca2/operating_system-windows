#include "framework.h"
#include "apex/operating_system.h"
#include "acme/id.h"
#include <Shlobj.h>
//#include "dir_system.h"
//#include "dir_context.h"
//#include "acme/node/windows/file_find.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme_windows/acme_directory.h"


namespace windows
{


   dir_context::dir_context()
   {


   }


   dir_context::~dir_context()
   {

   }


   void dir_context::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      __pointer(::apex::system) psystem = get_system();

      __refer(m_pfilesystem, psystem->m_pfilesystem);

      __refer(m_pdirsystem, psystem->m_pdirsystem);

      //return ::success;



   }


   void dir_context::init_system()
   {

      //auto estatus = 
      
      ::dir_context::init_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto pdocument = create_xml_document();

      //if (pdocument->load(m_pcontext->m_papexcontext->file().as_string(::dir::appdata() / "configuration/directory.xml")))
      //{

      //   //xxdebug_box("win_dir::initialize (configuration)", "win_dir::initialize", 0);

      //   if (pdocument->root()->get_name() == "directory_configuration")
      //   {

      //      ::file::path pathFolderTime = pdocument->root()->get_child_value("time");

      //      if (m_pcontext->m_papexcontext->dir().is(pathFolderTime))
      //      {

      //         m_pdirsystem->m_strTimeFolder = pathFolderTime;

      //      }

      //      ::file::path pathFolderNetseed = pdocument->root()->get_child_value("netseed");

      //      if (m_pcontext->m_papexcontext->dir().is(pathFolderNetseed))
      //      {

      //         m_pdirsystem->m_strNetSeedFolder = pathFolderNetseed;

      //      }

      //   }

      //}

      //return ::success;

   }


   inline bool myspace(char ch)
   {
      return ch == ' ' ||
         ch == '\t' ||
         ch == '\r' ||
         ch == '\n';
   }



   //string dir_context::path(const ::string & pszFolder, strsize iLenFolder, const ::string & pszRelative, strsize iLenRelative, const ::string & psz2, strsize iLen2, bool bUrl)
   //{

   //   bool bEmptyRelative = iLenRelative == 0 || pszRelative == nullptr || *pszRelative == '\0';
   //   bool bEmpty2 = iLen2 == 0 || psz2 == nullptr || *psz2 == '\0';

   //   if(bEmptyRelative && bEmpty2)
   //      return pszFolder;

   //   string strPath;
   //   char * psz;


   //   if(bEmptyRelative)
   //   {
   //      pszRelative = psz2;
   //      iLenRelative = iLen2;
   //   }

   //   while((pszFolder[iLenFolder - 1] == '\\' || pszFolder[iLenFolder - 1] == '/') && iLenFolder > 0)
   //   {
   //      if(bUrl)
   //      {
   //         if((iLenFolder - 2) >= 0 && (pszFolder[iLenFolder - 2] == '\\' || pszFolder[iLenFolder - 2] == '/' || pszFolder[iLenFolder - 2] == ':'))
   //         {
   //            if(pszFolder[iLenFolder - 2] == ':')
   //            {
   //               break;
   //            }
   //            else
   //            {
   //               if((iLenFolder - 3) >= 0 && (pszFolder[iLenFolder - 3] == ':'))
   //               {
   //                  iLenFolder--;
   //                  break;
   //               }
   //            }
   //         }
   //         else
   //         {
   //            iLenFolder--;
   //         }
   //      }
   //      else
   //      {
   //         iLenFolder--;
   //      }
   //   }

   //   while(*pszRelative != '\0' && (*pszRelative == '\\' || *pszRelative == '/') && iLenRelative > 0)
   //   {
   //      pszRelative++;
   //      iLenRelative--;
   //   }

   //   if(bEmptyRelative || bEmpty2)
   //   {
   //      psz = strPath.get_string_buffer(iLenFolder + 1 + iLenRelative);

   //      ansi_count_copy(psz, pszFolder, iLenFolder);

   //      if(ansi_count_compare_ci(&psz[iLenFolder - 5], ".zip:", 5) == 0)

   //      {
   //         iLenFolder--;
   //      }
   //      else
   //      {
   //         psz[iLenFolder] = '/';

   //      }
   //      ansi_count_copy(&psz[iLenFolder + 1], pszRelative, iLenRelative);

   //      psz[iLenFolder + 1 + iLenRelative] = '\0';

   //      {
   //         if(bUrl)
   //         {
   //            while(*psz++ != '\0')

   //               if(*psz == '\\') *psz = '/';

   //         }
   //         else
   //         {
   //            while(*psz++ != '\0')

   //               if(*psz == '/') *psz = '\\';

   //         }
   //      }
   //      strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative);
   //      return strPath;
   //   }

   //   while((pszRelative[iLenRelative - 1] == '\\' || pszRelative[iLenRelative - 1] == '/') && iLenRelative > 0)
   //   {
   //      iLenRelative--;
   //   }

   //   while(*psz2 != '\0' && (*psz2 == '\\' || *psz2 == '/') && iLen2 > 0)
   //   {
   //      psz2++;
   //      iLen2--;
   //   }

   //   psz = strPath.get_string_buffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);

   //   ansi_count_copy(psz, pszFolder, iLenFolder);

   //   psz[iLenFolder] = '/';

   //   ansi_count_copy(&psz[iLenFolder + 1], pszRelative, iLenRelative);

   //   psz[iLenFolder + 1 + iLenRelative] = '/';

   //   ansi_count_copy(&psz[iLenFolder + 1 + iLenRelative + 1], psz2, iLen2);

   //   psz[iLenFolder + 1 + iLenRelative + 1 + iLen2] = '\0';

   //   {
   //      if(bUrl)
   //      {
   //         while(*psz++ != '\0')

   //            if(*psz == '\\') *psz = '/';

   //      }
   //      else
   //      {
   //         while(*psz++ != '\0')

   //            if(*psz == '/') *psz = '\\';

   //      }
   //   }
   //   strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);
   //   return strPath;
   //}

   //string dir_context::relpath(const string & pcszSource,const string & lpcszRelative)

   //{
   //   const char * pszRequest;
   //   if(::url::is_url(pcszSource,&pszRequest))

   //   {
   //      if(::str::begins(pcszRelative,astr.Slash))

   //      {
   //         return path((const ::string &)string(pcszSource,pszRequest - lpcszSource),lpcszRelative);

   //      }
   //      else if(*pszRequest == '\0' || ::str::ends(pcszSource,"/"))

   //      {
   //         return path(pcszSource,lpcszRelative);

   //      }
   //      else
   //      {
   //         return path((const ::string &)name(pcszSource),lpcszRelative);

   //      }
   //   }
   //   else
   //   {
   //      if(::str::ends(pcszSource,"\\") || ::str::ends(lpcszSource,"/"))

   //      {
   //         return path(pcszSource,lpcszRelative);

   //      }
   //      else
   //      {
   //         return path((const ::string &)name(pcszSource),lpcszRelative);

   //      }
   //   }
   //}


   //string dir_context::relpath(const string & pcszSource, const string & lpcszRelative, const string & psz2)

   //{
   //   const char * pszRequest;
   //   if(::url::is_url(pcszSource, &pszRequest))

   //   {
   //      if(::str::begins(pcszRelative,astr.Slash))

   //      {
   //         return path((const ::string &) string(pcszSource, pszRequest - lpcszSource), lpcszRelative, psz2);

   //      }
   //      else if(*pszRequest == '\0' || ::str::ends(pcszSource, "/"))

   //      {
   //         return path(pcszSource, lpcszRelative, psz2);

   //      }
   //      else
   //      {
   //         return path((const ::string &) name(pcszSource), lpcszRelative, psz2);

   //      }
   //   }
   //   else
   //   {
   //      if(::str::ends(pcszSource, "\\") || ::str::ends(lpcszSource, "/"))

   //      {
   //         return path(pcszSource, lpcszRelative, psz2);

   //      }
   //      else
   //      {
   //         return path((const ::string &) name(pcszSource), lpcszRelative, psz2);

   //      }
   //   }
   //}


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.fix_flag();

      ::u32 dwSize = ::GetLogicalDriveStringsW(0, nullptr);

      ::acme::malloc < LPWSTR > pszAlloc;

      pszAlloc.alloc((dwSize + 1) * sizeof(WCHAR));

      LPWSTR psz = pszAlloc;

      dwSize = ::GetLogicalDriveStringsW(dwSize + 1, psz);

      string str;

      while (*psz)
      {

         str.Empty();

         while (*psz)
         {

            str += *psz;

            psz++;

         }

         ::file::path path;

         path = str;

         path.m_iDir = 1;

         listing.defer_add(path);
         
         str.trim(":/\\");

         listing.m_straTitle.add("Drive " + str);

         psz++;

      }

      return listing;


   }


   bool dir_context::enumerate(::file::listing & listing)
   {

      if (::dir_context::enumerate(listing))
      {

         return true;

      }

      return m_psystem->m_pacmedirectory->enumerate(listing);

      //   index iStart = listing.get_size();

      //   {

      //      __scoped_restore(listing.m_pathUser);

      //      __scoped_restore(listing.m_pathFinal);

      //      __scoped_restore(listing.m_eextract);

      //      ::file::listing dira;

      //      enumerate(dira, listing.m_pathUser);

      //      for (i32 i = 0; i < dira.get_count(); i++)
      //      {

      //         ::file::path dir_context = dira[i];

      //         if (dir_context == listing.m_pathUser)
      //         {

      //            continue;

      //         }

      //         listing.m_pathUser = dir_context;

      //         if (listing.m_eextract != extract_all)
      //         {

      //            listing.m_eextract = extract_none;

      //         }

      //         m_pcontext->m_papexcontext->dir().ls(listing);

      //      }

      //   }

      //   file_find file_find;

      //   bool bWorking = file_find.find_file(listing.m_pathUser / "*") != false;

      //   if (bWorking)
      //   {

      //      while (bWorking)
      //      {

      //         bWorking = file_find.find_next_file() != false;

      //         if (!file_find.IsDots() && file_find.GetFilePath() != listing.m_pathUser)
      //         {

      //            if ((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
      //            {

      //               if (matches_wildcard_criteria_ci(listing.m_straPattern, file_find.GetFileName()))
      //               {

      //                  listing.add(file_find.GetFilePath());

      //                  listing.last().m_iSize = file_find.get_length();

      //                  listing.last().m_iDir = file_find.IsDirectory() != false;

      //               }

      //            }

      //         }

      //      }

      //   }
      //   else
      //   {

      //      throw ::exception(error_failed);

      //   }

      //   for (index i = iStart; i < listing.get_size(); i++)
      //   {

      //      listing[i].m_iRelative = listing.m_pathUser.get_length() + 1;

      //   }

      //}
      //else
      //{

      //   if (listing.m_pathFinal.is_empty())
      //   {

      //      listing.m_pathFinal = m_pcontext->m_papexcontext->defer_process_path(listing.m_pathUser);

      //   }

      //   ::file::path path = listing.m_pathFinal;

      //   file_find file_find;

      //   bool bWorking;

      //   bWorking = file_find.find_file(path / "*");

      //   if (!bWorking)
      //   {

      //      return listing;

      //   }

      //   while (bWorking)
      //   {

      //      bWorking = file_find.find_next_file();

      //      if (!file_find.IsDots())
      //      {

      //         if ((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
      //         {

      //            string strFile = file_find.GetFileName();

      //            if (strFile.begins_ci("resident_"))
      //            {

      //               INFORMATION("resident_*");

      //            }

      //            if (matches_wildcard_criteria_ci(listing.m_straPattern, strFile))
      //            {

      //               listing.add(file_find.GetFilePath());

      //               listing.last().m_iSize = file_find.get_length();

      //               listing.last().m_iDir = file_find.IsDirectory() ? 1 : 0;

      //            }

      //         }

      //      }

      //   }

      //}

      //return true;

   }


   //bool dir_context::ls_relative_name(::file::listing & listing)
   //{

   //   if (::dir_context::ls_relative_name(listing))
   //   {

   //      return true;

   //   }

   //   if (listing.m_bRecursive)
   //   {

   //      // to finish;

   //      index iStart = listing.get_size();

   //      {

   //         __scoped_restore(listing.m_pathUser);

   //         __scoped_restore(listing.m_pathFinal);

   //         __scoped_restore(listing.m_eextract);


   //         ::file::listing dira;

   //         ls_dir(dira, listing.m_pathUser);

   //         for (i32 i = 0; i < dira.get_count(); i++)
   //         {

   //            ::file::path dir_context = dira[i];

   //            if (dir_context == listing.m_pathUser)
   //            {

   //               continue;

   //            }

   //            listing.m_pathUser = dir_context;

   //            if (listing.m_eextract != extract_all)
   //            {

   //               listing.m_eextract = extract_none;

   //            }

   //            m_pcontext->m_papexcontext->dir().ls(listing);

   //         }

   //      }

   //      file_find file_find;

   //      bool bWorking = file_find.find_file(listing.m_pathFinal / "*") != false;

   //      if (bWorking)
   //      {

   //         while (bWorking)
   //         {

   //            bWorking = file_find.find_next_file() != false;

   //            if (!file_find.IsDots() && file_find.GetFilePath() != listing.m_pathFinal)
   //            {

   //               if ((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
   //               {

   //                  if (matches_wildcard_criteria_ci(listing.m_straPattern, file_find.GetFileName()))
   //                  {

   //                     listing.add(file_find.GetFilePath());

   //                     listing.last().m_iSize = file_find.get_length();

   //                     listing.last().m_iDir = file_find.IsDirectory() != false;

   //                  }

   //               }

   //            }

   //         }

   //      }
   //      else
   //      {

   //         //listing.m_statusresult = ::error_failed;

   //      }

   //      for (index i = iStart; i < listing.get_size(); i++)
   //      {

   //         listing[i].m_iRelative = listing.m_pathUser.get_length() + 1;

   //      }

   //   }
   //   else
   //   {

   //      file_find file_find;

   //      bool bWorking;

   //      bWorking = file_find.find_file(listing.m_pathFinal / "*");

   //      if (!bWorking)
   //      {

   //         return listing;

   //      }

   //      while (bWorking)
   //      {

   //         bWorking = file_find.find_next_file();

   //         if (!file_find.IsDots())
   //         {

   //            if ((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
   //            {

   //               ::file::path pathName = file_find.GetFileName();

   //               //if (strFile.begins_ci("resident_"))
   //               //{

   //               //   TRACE("resident_*");
   //               //}

   //               if (matches_wildcard_criteria_ci(listing.m_straPattern, pathName))
   //               {

   //                  listing.add(pathName);

   //                  //listing.last().m_iSize = file_find.get_length();

   //                  //listing.last().m_iDir = file_find.IsDirectory() != false;

   //               }

   //            }

   //         }

   //      }

   //   }

   //   return true;

   //}


   bool dir_context::is_impl(const ::file::path & pcszPath)
   {

      if (::dir_context::is_impl(pcszPath))

      {

         return true;

      }

      ::u32 dwAttrib;

      dwAttrib = windows_get_file_attributes(pcszPath);

      bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      return bIsDir;

   }


   bool dir_context::name_is(const ::file::path & str)
   {

      strsize iLast = str.get_length() - 1;

      while (iLast >= 0)
      {
         if (str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
            break;
         iLast--;
      }
      while (iLast >= 0)
      {
         if (str.m_pdata[iLast] == '\\' || str.m_pdata[iLast] == '/' || str.m_pdata[iLast] == ':')
            break;
         iLast--;
      }
      if (iLast >= 0)
      {
         while (iLast >= 0)
         {
            if (str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
            {
               iLast++;
               break;
            }
            iLast--;
         }
      }
      else
      {
         return true; // assume empty string is root_ones directory
      }

      bool bIsDir;

      if (::task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const ::string &)str)[iLast - 3], ".zip", 4))
      {

         //m_isdirmap.set(str.Left(iLast + 1), true, 0);

         return true;

      }

      ::u32 dwAttrib;

      dwAttrib = windows_get_file_attributes(str);

      bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      //      m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;

   }


   ::file::path dir_context::time()
   {
      
      return m_pdirsystem->m_strTimeFolder;

   }


   ::file::path dir_context::stage()
   {
   
      return install() / "stage";

   }

   
   ::file::path dir_context::stageapp()
   {

      return install() / "basis";

   }

   
   ::file::path dir_context::netseed()
   {

      return m_pdirsystem->m_strNetSeedFolder;

   }


   ::file::path dir_context::module()
   {

      __pointer(::apex::system) psystem = get_system();

      return psystem->m_pdirsystem->m_pathModule;

   }


   //::file::path dir_context::ca2module()
   //{

   //   __pointer(::apex::system) psystem = get_system();

   //   return psystem->m_pdirsystem->m_pathCa2Module;

   //}


   ::file::path dir_context::time_square(const ::string & strPrefix, const ::string & strSuffix)
   {

      __UNREFERENCED_PARAMETER(strPrefix);
      __UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }


   ::file::path dir_context::time_log()
   {

      return appdata() / "log";

   }


   //void dir_context::create(const ::file::path & path)
   //{

   //   m_psystem->m_pacmedirectory->create(path);

   //   //}
   //   //catch (...)
   //   //{



   //   //}

   //   //if (is(path))
   //   //{

   //   //   return true;

   //   //}

   //   //::file::path_array stra;

   //   //path.ascendants_path(stra);

   //   //index i = stra.get_upper_bound();

   //   //for (; i >= 0; i--)
   //   //{

   //   //   string strDir = stra[i];

   //   //   if (is(strDir))
   //   //   {

   //   //      break;

   //   //   }

   //   //}

   //   //if (i < 0)
   //   //{

   //   //   return true;

   //   //}

   //   //for (; i < stra.get_count(); i++)
   //   //{

   //   //   string strDir = stra[i];

   //   //   try
   //   //   {

   //   //      m_psystem->m_pacmedirectory->create_directory(strDir)

   //   //   }
   //   //   catch(...)

   //   //   //if (m_psystem->m_pacmedirectory->create_directory(strDir))
   //   //   {

   //   //      //            m_isdirmap.set(strDir, true, 0);

  
   //   //      DWORD dwError = ::GetLastError();

   //   //      if (dwError == ERROR_ALREADY_EXISTS)
   //   //      {

   //   //         string str;

   //   //         str = "\\\\?\\" + strDir;

   //   //         str.trim_right("\\/");

   //   //         try
   //   //         {

   //   //            m_pcontext->m_papexcontext->file().del(str);

   //   //         }
   //   //         catch (...)
   //   //         {

   //   //         }

   //   //         str = stra[i];

   //   //         str.trim_right("\\/");

   //   //         try
   //   //         {

   //   //            m_pcontext->m_papexcontext->file().del(str);

   //   //         }
   //   //         catch (...)
   //   //         {

   //   //         }

   //   //         if (m_psystem->m_pacmedirectory->create_directory(strDir))
   //   //         {

   //   //            //                  m_isdirmap.set(strDir, true, 0);

   //   //            continue;

   //   //         }

   //   //         //   m_isdirmap.set(strDir, false, 0);

   //   //         dwError = ::GetLastError();

   //   //         WCHAR * pwszError;

   //   //         FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *) &pwszError, 8, nullptr);

   //   //         //TRACE("dir_context::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);

   //   //         ::LocalFree(pwszError);

   //   //         //m_isdirmap.set(stra[i], false);

   //   //         return false;

   //   //      }

   //   //   }

   //   //}

   //   //return true;

   //}


   //void dir_context::rm(const ::file::path & path, bool bRecursive)
   //{

   //   if (bRecursive)
   //   {
   //      
   //      ::file::listing patha;

   //      ls(patha, path);

   //      for (auto & pathItem : patha)
   //      {

   //         if (is(pathItem))
   //         {

   //            rm(pathItem, true);

   //         }
   //         else
   //         {

   //            ::DeleteFileW(wstring(pathItem));

   //         }

   //      }

   //   }

   //   return RemoveDirectoryW(wstring(path)) != false;

   //}


   //::file::path dir_context::name(const ::file::path & path1)
   //{
   //   const char * psz = path1 + strlen(path1) - 1;
   //   while(psz >= path1)
   //   {
   //      if(*psz != '\\' && *psz != '/' && *psz != ':')
   //         break;
   //      psz--;
   //   }
   //   while(psz >= path1)
   //   {
   //      if(*psz == '\\' || *psz == '/' || *psz == ':')
   //         break;
   //      psz--;
   //   }
   //   if(psz >= path1) // strChar == "\\" || strChar == "/"
   //   {
   //      const char * pszEnd = psz;
   //      /*while(psz >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }*/
   //      return string(path1, pszEnd - path1 + 1);
   //   }
   //   else
   //   {
   //      return "";
   //   }
   //}

   ::file::path dir_context::name(const ::file::path & str)
   {

      strsize iLast = str.get_length() - 1;

      while (iLast >= 0)
      {
         if (str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
            break;
         iLast--;
      }
      while (iLast >= 0)
      {
         if (str.m_pdata[iLast] == '\\' || str.m_pdata[iLast] == '/' || str.m_pdata[iLast] == ':')
            break;
         iLast--;
      }
      if (iLast >= 0)
      {
         while (iLast >= 0)
         {
            if (str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
               break;
            iLast--;
         }
         return str.Left(iLast + 1);
      }
      else
      {
         return "";
      }
   }



   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
   {
      if (psz.is_empty())
         return "";

      if (psz[1] == ':')
      {
         string strDir = name(psz);
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::earth::time time;
         time = ::earth::time::now();
         strFormat.format("%04d-%02d-%02d %02d-%02d-%02d\\", time.year(), time.month(), time.day(), time.hour(), time.minute(), time.second());
         str += strFormat;
         if (strDir.m_pdata[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";
   }

   ::file::path dir_context::appdata()
   {

      return ::dir_context::appdata();

   }


   ::file::path dir_context::commonappdata_root()
   {

      return m_pdirsystem->m_strCommonAppData;

   }


   ::file::path dir_context::userquicklaunch()
   {

      return m_pdirsystem->m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path dir_context::userprograms()
   {

      return m_pdirsystem->m_strPrograms;

   }


   ::file::path dir_context::commonprograms()
   {

      return m_pdirsystem->m_strCommonPrograms;

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return ::str::begins_ci(pszDir, pszPath);

   }


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {

      file_find file_find;

      bool bWorking;

      bWorking = file_find.find_file(pszDir / "*.*");

      while (bWorking)
      {

         bWorking = file_find.find_next_file();

         if (file_find.IsDirectory() && !file_find.IsDots())
         {

            return true;

         }

      }

      return false;

   }

   //bool file::GetStatus(const ::string & pszFileName,::file::file_status& rStatus)

   //{
   //   // attempt to fully qualify path first
   //   wstring wstrFullName;
   //   wstring wstrFileName;
   //   wstrFileName = ::str::international::utf8_to_unicode(pszFileName);

   //   if(!windows_full_path(wstrFullName,wstrFileName))
   //   {
   //      rStatus.m_strFullName.Empty();
   //      return false;
   //   }
   //   ::str::international::unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

   //   WIN32_FIND_DATA findFileData;
   //   HANDLE hFind = FindFirstFile((char *)pszFileName,&findFileData);

   //   if(hFind == INVALID_HANDLE_VALUE)
   //      return false;
   //   VERIFY(FindClose(hFind));

   //   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //   rStatus.m_attribute = (byte)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //   // get just the low ::u32 of the file size_i32
   //   ASSERT(findFileData.nFileSizeHigh == 0);
   //   rStatus.m_size = (::i32)findFileData.nFileSizeLow;

   //   // convert times as appropriate
   //   rStatus.m_ctime = ::earth::time(findFileData.ftCreationTime);
   //   rStatus.m_atime = ::earth::time(findFileData.ftLastAccessTime);
   //   rStatus.m_mtime = ::earth::time(findFileData.ftLastWriteTime);

   //   if(rStatus.m_ctime.get_time() == 0)
   //      rStatus.m_ctime = rStatus.m_mtime;

   //   if(rStatus.m_atime.get_time() == 0)
   //      rStatus.m_atime = rStatus.m_mtime;

   //   return true;
   //}

   ::file::path dir_context::document()
   {

      ::file::path path;

      m_psystem->m_pacmedirectory->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYDOCUMENTS,
         false);

      return path;

   }

   ::file::path dir_context::desktop()
   {

      ::file::path path;

      m_psystem->m_pacmedirectory->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_DESKTOP,
         false);

      return path;

   }

   ::file::path dir_context::download()
   {

      ::file::path path;

      path = m_psystem->m_pacmedirectory->m_pplatformdir->_get_known_folder(FOLDERID_Downloads);

      return path;

   }

   ::file::path dir_context::music()
   {

      ::file::path path;

      m_psystem->m_pacmedirectory->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYMUSIC,
         false);

      return path;

   }


   ::file::path dir_context::video()
   {

      ::file::path path;

      m_psystem->m_pacmedirectory->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYVIDEO,
         false);

      return path;

   }


   ::file::path dir_context::image()
   {

      ::file::path path;

      m_psystem->m_pacmedirectory->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYPICTURES,
         false);

      return path;

   }


   ::file::path dir_context::onedrive()
   {

      registry::key key;

      if (key._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Onedrive", false))
      {


      }

      if (key._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Window\\CurrentVersion\\SkyDrive", false))
      {

         string strPath;

         if (key._get("UserFolder", strPath))
         {

            return strPath;

         }

      }

      return "";

   }




} // namespace windows







