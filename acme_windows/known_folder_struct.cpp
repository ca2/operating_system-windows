// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "known_folder_struct.h"
#include <KnownFolders.h>


struct sz_known_folder_struct g_knownfolderstructa[] =
{

   {"desktop://",FOLDERID_Desktop},
   {"document://",FOLDERID_Documents},
   {"music://",FOLDERID_Music},
   {"image://",FOLDERID_Pictures},
   {"video://",FOLDERID_Videos},
   {"download://",FOLDERID_Downloads},
   {nullptr, NULL},

};

const char * skip_file_name(const char * psz)
{

   while (character_isalnum(*psz) || *psz == '_' || *psz == '-' || *psz == '.')
   {

      psz++;

   }

   return psz;

}

::string get_known_folder_name_candidate(const ::scoped_string & scopedstrKnownFolderCandidate)
{

   string strKnownFolderCandidate = scopedstrKnownFolderCandidate;

   auto psz = skip_file_name(strKnownFolderCandidate);

   if (strcmp(psz, "") == 0)
   {

      strKnownFolderCandidate += "://";

   }
   else if (strcmp(psz, ":") == 0)
   {

      strKnownFolderCandidate += "//";

   }
   else if (strcmp(psz, ":/") == 0)
   {

      strKnownFolderCandidate += "/";

   }

   return strKnownFolderCandidate;

}

sz_known_folder_struct * get_known_folder_struct(const ::scoped_string & scopedstrKnownFolder)
{

   string strKnownFolderCandidate = get_known_folder_name_candidate(scopedstrKnownFolder);

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_pszKnownFolder)
   {

      if (strKnownFolderCandidate.case_insensitive_order(pknownfolderstruct->m_pszKnownFolder) == 0)
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}


sz_known_folder_struct * case_insensitive_path_begins_eat_known_folder_struct(::string & strPath)
{

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_pszKnownFolder)
   {

      if (strPath.case_insensitive_begins_eat(pknownfolderstruct->m_pszKnownFolder))
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}



