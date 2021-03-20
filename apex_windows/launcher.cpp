// Recreated by camilo on 2021-03-17 13:51 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/launcher.h"
#include "launcher.h"


namespace windows
{


   ::e_status launcher::start()
   {

      if (!ensure_executable())
      {

         return false;

      }

      string strPath(get_executable_path());

      string strDir(dir::name(strPath));

      string strParams = get_params();

      call_async(strPath, strParams, strDir, e_display_none, m_bPrivileged);

      return true;

   }



}//namespace windows