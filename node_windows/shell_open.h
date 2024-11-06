#pragma once

#include "acme/operating_system.h"
#include <ddeml.h>


namespace windows
{


   class CLASS_DECL_AURA shell_open :
      virtual public ::shell_open
   {
   public:


      HSZ               m_hszAppName;
      HSZ               m_hszSystemTopic;
      DWORD             m_dwDde;

      shell_open();
      virtual ~shell_open();


      virtual void initialize(::particle * pparticle) override;

      static HDDEDATA CALLBACK DdeCallback(
         unsigned int uType,
         unsigned int uFmt,
         HCONV hconv,
         HDDEDATA hsz1,
         HDDEDATA hsz2,
         HDDEDATA hdata,
         HDDEDATA dwData1,
         HDDEDATA dwData2
      );


      virtual void initialize_shell_open() override;

   };

} // namespace windows



