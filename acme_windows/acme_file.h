// Created by camilo on 2021-08-09 14:19 <3ThomasBS_
#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS acme_file :
      virtual public ::windows_common::acme_file
   {
   public:


      __creatable_from_library(acme_file, ::acme_file, "acme_windows");


      acme_file();
      ~acme_file() override;


      ::file::path module() override;

      ::duration modification_time(const char* psz) override;
      void set_modification_time(const char* psz, const ::duration& duration) override;


      ::file::path time_put_contents(const ::file::path & pathFolder, const ::string & strPrefix, const ::string & strExtension, const ::string& str) override;


   };


} // namespace windows



