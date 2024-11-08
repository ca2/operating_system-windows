#include "framework.h"
#include "directory_context.h"
#include "directory_system.h"
#include "file_system.h"
#include "acme_windows/file_find.h"
#include "acme_windows/registry.h"
#include "acme/constant/id.h"
#include "acme/parallelization/task_flag.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme_windows/directory_system.h"


#include "acme/_operating_system.h"


#include <Shlobj.h>


namespace acme_windows
{


   directory_context::directory_context()
   {


   }


   directory_context::~directory_context()
   {

   }


   void directory_context::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ::pointer<::platform::system>psystem = system();

      //__refer(
      m_pfilesystem = psystem->m_pfilesystem;

      m_pdirectorysystem = psystem->m_pdirectorysystem;

      //return ::success;



   }


   void directory_context::init_system()
   {

      //auto estatus = 
      
      ::directory_context::init_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto pdocument = create_xml_document();

      //if (pdocument->load(m_papplication->file().as_string(::dir::appdata() / "configuration/directory.xml")))
      //{

      //   //xxdebug_box("win_dir::initialize (configuration)", "win_dir::initialize", 0);

      //   if (pdocument->root()->get_name() == "directory_configuration")
      //   {

      //      ::file::path pathFolderTime = pdocument->root()->get_child_value("time");

      //      if (m_papplication->dir().is(pathFolderTime))
      //      {

      //         m_pdirectorysystem->m_strTimeFolder = pathFolderTime;

      //      }

      //      ::file::path pathFolderNetseed = pdocument->root()->get_child_value("netseed");

      //      if (m_papplication->dir().is(pathFolderNetseed))
      //      {

      //         m_pdirectorysystem->m_strNetSeedFolder = pathFolderNetseed;

      //      }

      //   }

      //}

      //return ::success;

   }


   void directory_context::term_system()
   {

      //auto estatus = 

      ::directory_context::term_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto pdocument = create_xml_document();

      //if (pdocument->load(m_papplication->file().as_string(::dir::appdata() / "configuration/directory.xml")))
      //{

      //   //xxdebug_box("win_dir::initialize (configuration)", "win_dir::initialize", 0);

      //   if (pdocument->root()->get_name() == "directory_configuration")
      //   {

      //      ::file::path pathFolderTime = pdocument->root()->get_child_value("time");

      //      if (m_papplication->dir().is(pathFolderTime))
      //      {

      //         m_pdirectorysystem->m_strTimeFolder = pathFolderTime;

      //      }

      //      ::file::path pathFolderNetseed = pdocument->root()->get_child_value("netseed");

      //      if (m_papplication->dir().is(pathFolderNetseed))
      //      {

      //         m_pdirectorysystem->m_strNetSeedFolder = pathFolderNetseed;

      //      }

      //   }

      //}

      //return ::success;

   }


   void directory_context::destroy()
   {

      m_pfilesystem.release();

      m_pdirectorysystem.release();

      ::directory_context::destroy();

   }


   inline bool myspace(char ch)
   {
      return ch == ' ' ||
         ch == '\t' ||
         ch == '\r' ||
         ch == '\n';
   }



   //string directory_context::path(const ::string & pszFolder, character_count iLenFolder, const ::string & pszRelative, character_count iLenRelative, const ::string & psz2, character_count iLen2, bool bUrl)
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
   //      psz = strPath.get_buffer(iLenFolder + 1 + iLenRelative);

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

   //   psz = strPath.get_buffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);

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

   //string directory_context::relpath(const string & pcszSource,const string & lpcszRelative)

   //{
   //   const scoped_string & strRequest;
   //   if(::url::is_url(pcszSource,&pszRequest))

   //   {
   //      if(::str().begins(pcszRelative,astr.Slash))

   //      {
   //         return path((const ::string &)string(pcszSource,pszRequest - lpcszSource),lpcszRelative);

   //      }
   //      else if(*pszRequest == '\0' || ::str().ends(pcszSource,"/"))

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
   //      if(::str().ends(pcszSource,"\\") || ::str().ends(lpcszSource,"/"))

   //      {
   //         return path(pcszSource,lpcszRelative);

   //      }
   //      else
   //      {
   //         return path((const ::string &)name(pcszSource),lpcszRelative);

   //      }
   //   }
   //}


   //string directory_context::relpath(const string & pcszSource, const string & lpcszRelative, const string & psz2)

   //{
   //   const scoped_string & strRequest;
   //   if(::url::is_url(pcszSource, &pszRequest))

   //   {
   //      if(::str().begins(pcszRelative,astr.Slash))

   //      {
   //         return path((const ::string &) string(pcszSource, pszRequest - lpcszSource), lpcszRelative, psz2);

   //      }
   //      else if(*pszRequest == '\0' || pcszSource.ends("/"))

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
   //      if(pcszSource.ends("\\") || lpcszSource.ends("/"))

   //      {
   //         return path(pcszSource, lpcszRelative, psz2);

   //      }
   //      else
   //      {
   //         return path((const ::string &) name(pcszSource), lpcszRelative, psz2);

   //      }
   //   }
   //}


   ::file::listing & directory_context::root_ones(::file::listing & listing)
   {

      listing.fix_flag();

      unsigned int dwSize = ::GetLogicalDriveStringsW(0, nullptr);

      ::acme::malloc < LPWSTR > pszAlloc;

      pszAlloc.alloc((dwSize + 1) * sizeof(WCHAR));

      LPWSTR psz = pszAlloc;

      dwSize = ::GetLogicalDriveStringsW(dwSize + 1, psz);

      string str;

      while (*psz)
      {

         str.empty();

         while (*psz)
         {

            str += *psz;

            psz++;

         }

         ::file::path path;

         path = str;

         path.set_folder_path();

         listing.defer_add(path);
         
         str.trim(":/\\");

         listing.m_straTitle.add("Drive " + str);

         psz++;

      }

      return listing;


   }


   bool directory_context::enumerate(::file::listing & listing)
   {

      if (::directory_context::enumerate(listing))
      {

         return true;

      }

      return directory_system()->enumerate(listing);

      //   index iStart = listing.get_size();

      //   {

      //      __scoped_restore(listing.m_pathUser);

      //      __scoped_restore(listing.m_pathFinal);

      //      __scoped_restore(listing.m_eextract);

      //      ::file::listing dira;

      //      enumerate(dira, listing.m_pathUser);

      //      for (int i = 0; i < dira.get_count(); i++)
      //      {

      //         ::file::path directory_context = dira[i];

      //         if (directory_context == listing.m_pathUser)
      //         {

      //            continue;

      //         }

      //         listing.m_pathUser = directory_context;

      //         if (listing.m_eextract != e_extract_all)
      //         {

      //            listing.m_eextract = e_extract_none;

      //         }

      //         m_papplication->dir().ls(listing);

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

      //   for (::collection::index i = iStart; i < listing.get_size(); i++)
      //   {

      //      listing[i].m_iRelative = listing.m_pathUser.get_length() + 1;

      //   }

      //}
      //else
      //{

      //   if (listing.m_pathFinal.is_empty())
      //   {

      //      listing.m_pathFinal = m_papplication->defer_process_matter_path(listing.m_pathUser);

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

      //            if (strFile.case_insensitive_begins("resident_"))
      //            {

      //               information() << "resident_*";

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


   //bool directory_context::ls_relative_name(::file::listing & listing)
   //{

   //   if (::directory_context::ls_relative_name(listing))
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

   //         for (int i = 0; i < dira.get_count(); i++)
   //         {

   //            ::file::path directory_context = dira[i];

   //            if (directory_context == listing.m_pathUser)
   //            {

   //               continue;

   //            }

   //            listing.m_pathUser = directory_context;

   //            if (listing.m_eextract != e_extract_all)
   //            {

   //               listing.m_eextract = e_extract_none;

   //            }

   //            m_papplication->dir().ls(listing);

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

   //      for (::collection::index i = iStart; i < listing.get_size(); i++)
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

   //               //if (strFile.case_insensitive_begins("resident_"))
   //               //{

   //               //   informationf("resident_*");
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


   //bool directory_context::is_impl(const ::file::path & pcszPath)
   //{

   //   if (::directory_context::is_impl(pcszPath))

   //   {

   //      return true;

   //   }

   //   unsigned int dwAttrib;

   //   dwAttrib = windows_get_file_attributes(pcszPath);

   //   bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

   //   return bIsDir;

   //}


   bool directory_context::name_is(const ::file::path & str)
   {

      character_count iLast = str.length() - 1;

      while (iLast >= 0)
      {
         if (str.m_begin[iLast] != '\\' && str.m_begin[iLast] != '/' && str.m_begin[iLast] != ':')
            break;
         iLast--;
      }
      while (iLast >= 0)
      {
         if (str.m_begin[iLast] == '\\' || str.m_begin[iLast] == '/' || str.m_begin[iLast] == ':')
            break;
         iLast--;
      }
      if (iLast >= 0)
      {
         while (iLast >= 0)
         {
            if (str.m_begin[iLast] != '\\' && str.m_begin[iLast] != '/' && str.m_begin[iLast] != ':')
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

      if (::task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3 && !case_insensitive_ansi_count_compare( & ((const ::string &)str)[iLast - 3], ".zip", 4))
      {

         //m_isdirmap.set(str.left()(iLast + 1), true, 0);

         return true;

      }

      unsigned int dwAttrib;

      dwAttrib = ::windows::get_file_attributes(str);

      bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      //      m_isdirmap.set(str.left()(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;

   }


   ::file::path directory_context::time()
   {
      
      return m_pdirectorysystem->m_strTimeFolder;

   }


   ::file::path directory_context::stage()
   {
   
      return install() / "stage";

   }

   
   ::file::path directory_context::stageapp()
   {

      return install() / "basis";

   }

   
   ::file::path directory_context::netseed()
   {

      return m_pdirectorysystem->m_strNetSeedFolder;

   }


   ::file::path directory_context::module()
   {

      //::pointer<::apex::system>psystem = system();

      //return psystem->m_pdirectorysystem->m_pathModule;

      auto papplication = application();

      return papplication->get_module_folder();

   }


   //::file::path directory_context::ca2module()
   //{

   //   ::pointer<::apex::system>psystem = system();

   //   return psystem->m_pdirectorysystem->m_pathCa2Module;

   //}


   ::file::path directory_context::time_square(const ::string & strPrefix, const ::string & strSuffix)
   {

      __UNREFERENCED_PARAMETER(strPrefix);
      __UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }


   ::file::path directory_context::time_log()
   {

      return appdata() / "log";

   }


   //void directory_context::create(const ::file::path & path)
   //{

   //   directory_system()->create(path);

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

   //   //::collection::index i = stra.get_upper_bound();

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

   //   //      directory_system()->create_directory(strDir)

   //   //   }
   //   //   catch(...)

   //   //   //if (directory_system()->create_directory(strDir))
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

   //   //            m_papplication->file().del(str);

   //   //         }
   //   //         catch (...)
   //   //         {

   //   //         }

   //   //         str = stra[i];

   //   //         str.trim_right("\\/");

   //   //         try
   //   //         {

   //   //            m_papplication->file().del(str);

   //   //         }
   //   //         catch (...)
   //   //         {

   //   //         }

   //   //         if (directory_system()->create_directory(strDir))
   //   //         {

   //   //            //                  m_isdirmap.set(strDir, true, 0);

   //   //            continue;

   //   //         }

   //   //         //   m_isdirmap.set(strDir, false, 0);

   //   //         dwError = ::GetLastError();

   //   //         WCHAR * pwszError;

   //   //         FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *) &pwszError, 8, nullptr);

   //   //         //informationf("directory_context::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);

   //   //         ::LocalFree(pwszError);

   //   //         //m_isdirmap.set(stra[i], false);

   //   //         return false;

   //   //      }

   //   //   }

   //   //}

   //   //return true;

   //}


   //void directory_context::rm(const ::file::path & path, bool bRecursive)
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


   //::file::path directory_context::name(const ::file::path & path1)
   //{
   //   const scoped_string & str = path1 + strlen(path1) - 1;
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
   //      const scoped_string & strEnd = psz;
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

   ::file::path directory_context::name(const ::file::path & str)
   {

      character_count iLast = str.length() - 1;

      while (iLast >= 0)
      {
         if (str.m_begin[iLast] != '\\' && str.m_begin[iLast] != '/' && str.m_begin[iLast] != ':')
            break;
         iLast--;
      }
      while (iLast >= 0)
      {
         if (str.m_begin[iLast] == '\\' || str.m_begin[iLast] == '/' || str.m_begin[iLast] == ':')
            break;
         iLast--;
      }
      if (iLast >= 0)
      {
         while (iLast >= 0)
         {
            if (str.m_begin[iLast] != '\\' && str.m_begin[iLast] != '/' && str.m_begin[iLast] != ':')
               break;
            iLast--;
         }
         return str.left(iLast + 1);
      }
      else
      {
         return "";
      }
   }



   ::file::path directory_context::trash_that_is_not_trash(const ::file::path & psz)
   {
      if (psz.is_empty())
         return "";

      if (psz[1] == ':')
      {
         string strDir = name(psz);
         string str;
         str = strDir.left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::earth::time time;
         time = ::earth::time::now();
         strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.year(), time.month(), time.day(), time.hour(), time.minute(), time.second());
         str += strFormat;
         if (strDir.m_begin[2] == '\\')
         {
            str += strDir.substr(3);
         }
         else
         {
            str += strDir.substr(2);
         }
         return str;
      }

      return "";
   }

   ::file::path directory_context::appdata()
   {

      return ::directory_context::appdata();

   }


   ::file::path directory_context::commonappdata_root()
   {

      return m_pdirectorysystem->m_strCommonAppData;

   }


   ::file::path directory_context::userquicklaunch()
   {

      return m_pdirectorysystem->m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }


   ::file::path directory_context::userprograms()
   {

      return m_pdirectorysystem->m_strPrograms;

   }


   ::file::path directory_context::commonprograms()
   {

      return m_pdirectorysystem->m_strCommonPrograms;

   }


   bool directory_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }


   bool directory_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return pszDir.case_insensitive_begins(pszPath);

   }


   bool directory_context::has_subdir(const ::file::path & pszDir)
   {

      ::acme_windows::file_find file_find;

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
   //   wstrFileName = utf8_to_unicode(pszFileName);

   //   if(!windows_full_path(wstrFullName,wstrFileName))
   //   {
   //      rStatus.m_strFullName.empty();
   //      return false;
   //   }
   //   unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

   //   WIN32_FIND_DATA findFileData;
   //   HANDLE hFind = FindFirstFile((char *)pszFileName,&findFileData);

   //   if(hFind == INVALID_HANDLE_VALUE)
   //      return false;
   //   VERIFY(FindClose(hFind));

   //   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //   rStatus.m_attribute = (unsigned char)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //   // get just the low unsigned int of the file int_size
   //   ASSERT(findFileData.nFileSizeHigh == 0);
   //   rStatus.m_size = (int)findFileData.nFileSizeLow;

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

   ::file::path directory_context::document()
   {

      ::file::path path;

      directory_system()->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYDOCUMENTS,
         false);

      return path;

   }

   ::file::path directory_context::desktop()
   {

      ::file::path path;

      directory_system()->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_DESKTOP,
         false);

      return path;

   }

   ::file::path directory_context::download()
   {

      ::file::path path;

      path = directory_system()->m_pplatformdir->_get_known_folder(FOLDERID_Downloads);

      return path;

   }

   ::file::path directory_context::music()
   {

      ::file::path path;

      directory_system()->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYMUSIC,
         false);

      return path;

   }


   ::file::path directory_context::video()
   {

      ::file::path path;

      directory_system()->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYVIDEO,
         false);

      return path;

   }


   ::file::path directory_context::image()
   {

      ::file::path path;

      directory_system()->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         path,
         CSIDL_MYPICTURES,
         false);

      return path;

   }


   ::file::path directory_context::onedrive()
   {

      ::acme_windows::registry::key key;

      if (key._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\OneDrive", false))
      {

         string strPath;

         if (key._get("UserFolder", strPath))
         {

            return strPath;

         }

      }

      if (key._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SkyDrive", false))
      {

         string strPath;

         if (key._get("UserFolder", strPath))
         {

            return strPath;

         }

      }

      return "";

   }


   ::file::path directory_context::dropbox_client()
   {

      ::acme_windows::registry::key key;

      if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Dropbox"))
      {

         ::string str;

         if (key._get("InstallPath", str))
         {

            return str;

         }

      }

      if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Dropbox"))
      {

         ::string str;

         if (key._get("InstallPath", str))
         {

            return str;

         }

      }

      return {};

   }


} // namespace apex_windows


