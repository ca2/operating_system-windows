// Create on 2021-03-22 09:12 <3ThomasBS_
#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS acme_path :
      virtual public ::acme_path
   {
   public:


      acme_path();
      virtual ~acme_path();


      virtual ::file::path app_module() override;


   };


} // namespace windows



