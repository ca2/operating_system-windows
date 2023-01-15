// by camilo on 2022-11-02 14:29 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/operating_system/process.h"
#include "acme/_operating_system.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS process :
      virtual public ::operating_system::process
   {
   public:


      //__creatable_from_base(process, ::operating_system::process);


      PROCESS_INFORMATION        m_pi;
      STARTUPINFOW               m_si;


      process();
      ~process() override;


      virtual bool create_child_process(const ::string & pszCmdLine, bool bPiped, const ::string & pszDir = nullptr, ::enum_priority epriority = ::e_priority_none) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const ::string & pszCmdLine,int iShow,const class time & timeTimeOut,bool * pbTimeOut) override;

      virtual bool kill() override;

   };


} // namespace apex_windows




