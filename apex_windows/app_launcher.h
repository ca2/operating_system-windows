// From apex/platform/app_launcher.h by camilo on 2022-11-07 01:12 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_launcher.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS app_launcher :
      virtual public ::apex::app_launcher
   {
   public:


      string   m_strApp;
      string   m_strPlatform;

      ::pointer<::launcher>m_plauncher;



      app_launcher();

      virtual void initialize_app_launcher(::particle * pparticle, string strPlatform, string strApp);

      virtual string get_executable_extension();

      //virtual string get_executable_path();

      virtual string get_params();

      virtual void run();


   };


} // namespace apex_windows



