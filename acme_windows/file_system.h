// Created by camilo on 2021-08-09 14:19 <3ThomasBS_
#pragma once


#include "acme_windows_common/file_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS file_system :
      virtual public ::acme_windows_common::file_system
   {
   public:


      file_system();
      ~file_system() override;


      //::file::path module() override;


      class ::time modification_time(const ::file::path & path) override;
      void set_modification_time(const ::file::path & path, const class ::time & time) override;


      ::file::path time_put_contents(const ::file::path & pathFolder, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrExtension, const ::string& str) override;


      void _erase(const ::file::path & path) override;


      string get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension) override;
      
      //void write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten) override;

   
   };


} // namespace acme_windows



