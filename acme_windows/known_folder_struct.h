// Created by camilo on 2021-08-08 04:50 BRT <3ThomasBorregaardS�rensen!!
#pragma once


struct known_folder_struct
{

   string               m_strKnownFolder;
   KNOWNFOLDERID        m_atomKnownFolder;

};


CLASS_DECL_ACME_WINDOWS known_folder_struct * get_known_folder_struct(const ::string & strKnownFolder);

CLASS_DECL_ACME_WINDOWS known_folder_struct * path_known_folder_struct_ci(::string & strPath);

//comptr < IKnownFolder > get_IKnownFolder(const ::string & strPath);


