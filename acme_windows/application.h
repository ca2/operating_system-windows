// Addition of implementation of ::operating_system::application by camilo on
// 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/application.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS application :
      virtual public ::operating_system::application
   {
   public:


      HANDLE            m_handle;
      bool              m_bHandle;


      application();
      ~application() override;


      virtual void open_by_module_path(const ::scoped_string & scopedstr);

      //virtual ::pointer < ::operating_system::main_window > main_window();

      //void post_close() override;


   };


} //    namespace acme_windows




