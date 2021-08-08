// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardSørensen!!
#pragma once


struct known_folder_struct
{

   string               m_strKnownFolder;
   KNOWNFOLDERID        m_idKnownFolder;

};


CLASS_DECL_ACME_WINDOWS known_folder_struct * get_known_folder_struct(const ::string & strKnownFolder);

CLASS_DECL_ACME_WINDOWS known_folder_struct * path_known_folder_struct_ci(::string & strPath);

//comptr < IKnownFolder > get_IKnownFolder(const ::string & strPath);


