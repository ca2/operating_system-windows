// Created by camilo on 2021-08-09 14:19 <3ThomasBS_
#pragma once


#include "acme_windows_common/acme_file.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS acme_file :
      virtual public ::acme_windows_common::acme_file
   {
   public:


      acme_file();
      ~acme_file() override;


      ::file::path module() override;


      class ::time modification_time(const ::file::path & path) override;
      void set_modification_time(const ::file::path & path, const class ::time & time) override;


      ::file::path time_put_contents(const ::file::path & pathFolder, const ::string & strPrefix, const ::string & strExtension, const ::string& str) override;


      void _erase(const ::file::path & path) override;


      string get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension) override;
      
      void write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten) override;

   
   };


} // namespace acme_windows



