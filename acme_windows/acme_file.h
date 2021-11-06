// Created by camilo on 2021-08-09 14:19 <3ThomasBS_
#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS acme_file :
      virtual public ::windows_common::acme_file
   {
   public:


      acme_file();
      ~acme_file() override;


      ::file::path executable() override;


   };


} // namespace windows



