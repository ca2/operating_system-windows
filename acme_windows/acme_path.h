// Create on 2021-03-22 09:12 <3ThomasBS_
#pragma once


#include "acme_windows_common/acme_path.h"


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


      ::file::path _real_path(const ::file::path & path) override;


      ::file::path _safe_real_path(const ::file::path & path) override;


      ::file::path get_absolute_path(const ::scoped_string& scopedstr) override;


   };


} // namespace acme_windows



