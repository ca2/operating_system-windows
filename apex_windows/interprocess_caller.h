// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:33 <3ThomasBorregaardSorensen!!
#pragma once


#include "interprocess_base.h"
#include "apex/interprocess/caller.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS interprocess_caller :
      virtual public interprocess_base,
      virtual public interprocess::caller
   {
   public:


      //__creatable_from_base(interprocess_caller, ::inteprocess::caller);


      interprocess_caller();
      ~interprocess_caller() override;


      void open(const ::scoped_string & scopedstrChannel, ::launcher * plauncher = nullptr) override;
      void close() override;


      void call(const ::scoped_string & scopedstrUri, const class time & timeTimeout) override;
      //void send(int message, void * pdata, int len, const class time & timeTimeout) override;


      bool is_caller_ok() override;


   };


} // namespace apex_windows



