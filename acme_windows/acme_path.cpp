// Create on 2021-03-22 09:12 <3ThomasBS_
#include "framework.h"


namespace windows
{

   
   acme_path::acme_path()
   {

      m_pplatformpath = this;

   }


   acme_path::~acme_path()
   {


   }


   ::file::path acme_path::app_module()
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



} // namespace windows



