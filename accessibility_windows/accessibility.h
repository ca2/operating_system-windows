// Created by camilo on 2026-04-27 19:14 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "axis/accessibility/accessibility.h"


namespace accessibility_windows
{


   class CLASS_DECL_ACCESSIBILITY_WINDOWS accessibility :
      virtual public ::accessibility::accessibility
   {
   public:



      accessibility();
      ~accessibility()() override;


      //::pointer < ::accessibility::application > process_identifier_application(::process_identifier processidentifier) override;

      ::pointer < ::accessibility::application > module_path_application(const ::scoped_string & scopestr) override;

      //::pointer < ::operating_system::application > process_identifier_application(::process_identifier processidentifier) override;

      //::pointer < ::operating_system::application > application_predicate(const ::function < bool(::operating_system::application * papplication) > & function) override;



   };


} //    namespace namespace accessibility_windows





