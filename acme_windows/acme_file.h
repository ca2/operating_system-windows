// Created by camilo on 2021-08-09 14:19 <3ThomasBS_
#pragma once


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS acme_file :
      virtual public ::acme_windows_common::acme_file
   {
   public:


      acme_file();
      ~acme_file() override;


      ::file::path module() override;


      ::earth::time modification_time(const char* psz) override;
      void set_modification_time(const char* psz, const ::earth::time & time) override;


      ::file::path time_put_contents(const ::file::path & pathFolder, const ::string & strPrefix, const ::string & strExtension, const ::string& str) override;


      void _erase(const char * path) override;


   };


} // namespace acme_windows



