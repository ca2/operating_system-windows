// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "known_folder_struct.h"
#include <KnownFolders.h>


struct known_folder_struct g_knownfolderstructa[] =
{

   {"desktop://",FOLDERID_Desktop},
   {"document://",FOLDERID_Documents},
   {"music://",FOLDERID_Music},
   {"image://",FOLDERID_Pictures},
   {"video://",FOLDERID_Videos},
   {"download://",FOLDERID_Downloads},
   {"", NULL},

};


known_folder_struct * get_known_folder_struct(const ::string & strKnownFolder)
{

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_strKnownFolder.has_char())
   {

      if (strKnownFolder.compare_ci(pknownfolderstruct->m_strKnownFolder) == 0)
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}


known_folder_struct * path_known_folder_struct_ci(::string & strPath)
{

   auto pknownfolderstruct = g_knownfolderstructa;

   while (pknownfolderstruct->m_strKnownFolder.has_char())
   {

      if (strPath.begins_eat_ci(pknownfolderstruct->m_strKnownFolder))
      {

         return pknownfolderstruct;

      }

      pknownfolderstruct++;

   }

   return nullptr;

}



