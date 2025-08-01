// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:33 <3ThomasBorregaardSorensen!!
#pragma once


#include "interprocess_base.h"
#include "apex/interprocess/target.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS interprocess_target :
      virtual public interprocess_base,
      virtual public interprocess::target
   {
   public:


      //__creatable_from_base(interprocess_handler, ::inteprocess::handler);


      interprocess_target();
      ~interprocess_target() override;


      void create(const ::scoped_string & scopedstrChannel) override;
      void destroy() override;


      //void * on_interprocess_receive(const ::scoped_string & scopedstrMessage) override;
      //void * on_interprocess_receive(int message, void * pdata, memsize len) override;
      //void * on_interprocess_post(long long a, long long b) override;


      virtual bool on_idle() override;


      LRESULT message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam);


      bool is_target_ok();


   };


} // namespace apex_windows



