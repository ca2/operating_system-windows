// Create on 2021-03-22 09:12 <3ThomasBS_
#pragma once


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS acme_path :
      virtual public ::acme_windows_common::acme_path
   {
   public:


      //__creatable_from_base(acme_path, ::acme_path);


      acme_path();
      ~acme_path() override;




      //virtual bool __win_find_is_dots(WIN32_FIND_DATAW & data);


      ::file::path _final(const char * path) override;


   };


} // namespace acme_windows



