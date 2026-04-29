// Addition of implementation of ::operating_system::application by camilo on
// 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "axis/accessibility/application.h"


namespace accessibility_windows
{


   class CLASS_DECL_ACCESSIBILITY_WINDOWS application :
      virtual public ::accessibility::application
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


} //    namespace namespace accessibility_windows





