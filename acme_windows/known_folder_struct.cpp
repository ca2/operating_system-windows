// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardS�rensen!!
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


sz_known_folder_struct * get_known_folder_struct(const ::string & strKnownFolder)
{

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_pszKnownFolder)
   {

      if (strKnownFolder.compare_ci(pknownfolderstruct->m_pszKnownFolder) == 0)
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}


sz_known_folder_struct * path_begins_eat_known_folder_struct_ci(::string & strPath)
{

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_pszKnownFolder)
   {

      if (strPath.begins_eat_ci(pknownfolderstruct->m_pszKnownFolder))
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}



