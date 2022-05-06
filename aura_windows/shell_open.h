#pragma once

#include "aura/operating_system.h"
#include <ddeml.h>


namespace aura_windows
{


   class CLASS_DECL_AURA_WINDOWS shell_open :
      virtual public ::shell_open
   {
   public:


      //__creatable_from_base(shell_open, ::shell_open);


      HSZ               m_hszAppName;
      HSZ               m_hszSystemTopic;
      DWORD             m_dwDde;

      shell_open();
      virtual ~shell_open();


      virtual void initialize(::object * pobject) override;

      static HDDEDATA CALLBACK DdeCallback(
         u32 uType,
         u32 uFmt,
         HCONV hconv,
         HDDEDATA hsz1,
         HDDEDATA hsz2,
         HDDEDATA hdata,
         HDDEDATA dwData1,
         HDDEDATA dwData2
      );


      virtual void initialize_shell_open() override;

   };


} // namespace aura_windows



