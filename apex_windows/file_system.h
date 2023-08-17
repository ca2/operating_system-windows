#pragma once


#include "acme/filesystem/filesystem/file_system.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS file_system:
      virtual public ::file_system
   {
   public:


      //__creatable_from_base(file_system, ::file_system);


      file_system();
      ~file_system() override;


      virtual void init_system() override;


      //virtual void update_module_path() override;


   };


} // namespace apex_windows



