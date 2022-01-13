// Recreated by camilo on 2021-03-17 13:51 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/launcher.h"
#include "launcher.h"


namespace windows
{


   void launcher::start()
   {

      if (!ensure_executable())
      {

         //return false;

         return;

      }

      string strPath(get_executable_path());

      string strDir(::file_path_folder(strPath));

      string strParams = get_params();

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      pnode->call_async(strPath, strParams, strDir, e_display_none, m_bPrivileged);

//      return true;

   }



}//namespace windows
