// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/string/string.h"
#include "acme/_operating_system.h"


struct sz_known_folder_struct
{

   const char *         m_pszKnownFolder;
   KNOWNFOLDERID        m_knownfolderid;

};


CLASS_DECL_ACME_WINDOWS sz_known_folder_struct * get_known_folder_struct(const ::string & strKnownFolder);

CLASS_DECL_ACME_WINDOWS sz_known_folder_struct * case_insensitive_path_begins_eat_known_folder_struct(::string & strPath);

//comptr < IKnownFolder > get_IKnownFolder(const ::string & strPath);


