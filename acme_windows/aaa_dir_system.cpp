#include "framework.h"
#include "apex/operating_system.h"
#include <Shlobj.h>
#include "dir_system.h"
//#include "_windows.h"
//#include "acme/os/windows_common/cotaskptr.h"

//#include "apex/xml/_.h"




namespace windows
{


   dir_system::dir_system()
   {


   }


   dir_system::~dir_system()
   {

   }



   ::e_status dir_system::initialize(::object * pobject)
   {

      auto estatus = ::dir_system::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_pathInstall = ::dir::install();

      shell_get_special_folder_path(
         nullptr,
         m_strCommonAppData,
         CSIDL_COMMON_APPDATA,
         false);
      //shell_get_special_folder_path(
      // nullptr,
      //m_pathProfile,
      //CSIDL_PROFILE,
      //false);

      m_pathHome = get_known_folder(FOLDERID_Profile);

      m_pathCa2Config = pacmedir->roaming();

      m_strCommonAppData /= "ca2";

      m_strAppData = get_known_folder(FOLDERID_RoamingAppData);

      shell_get_special_folder_path(
         nullptr,
         m_strPrograms,
         CSIDL_PROGRAMS,
         false);
      shell_get_special_folder_path(
         nullptr,
         m_strCommonPrograms,
         CSIDL_COMMON_PROGRAMS,
         false);

      {

         //string strRelative;
         //strRelative = install();
         //index iFind = strRelative.find(':');
         //if (iFind >= 0)
         //{
         //   strsize iFind1 = strRelative.reverse_find("\\", iFind);
         //   strsize iFind2 = strRelative.reverse_find("/", iFind);
         //   strsize iStart = maximum(iFind1 + 1, iFind2 + 1);
         //   strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
         //}



      }

      if (m_strTimeFolder.is_empty())
      {

         m_strTimeFolder = ::dir::appdata() / "time";

      }

      if (m_strNetSeedFolder.is_empty())
      {

         m_strNetSeedFolder = ::dir::install() / "net";

      }

      ::dir::mk(m_strTimeFolder);
      //xxdebug_box("win_dir::initialize (m_strTimeFolder)", "win_dir::initialize", 0);

      if (!::dir::is(m_strTimeFolder))
         return false;

      ::dir::mk(m_strTimeFolder / "time");

      //xxdebug_box("win_dir::initialize", "win_dir::initialize", 0);

      return ::success;

   }


   ::e_status dir_system::init_system()
   {

      auto estatus = ::dir_system::init_system();

      if (!estatus)
      {

         return estatus;

      }


      return ::success;

   }



   string dir_system::dir_root()
   {

      ::std::string path;

      path = get_known_folder(FOLDERID_RoamingAppData);

      if (path.length() > 0 && path[path.length() - 1] != '\\')
      {

         path += "\\";

      }

      path += "ca2";

      return path;

   }


   ::file::path dir_system::get_memory_map_base_folder_path() const
   {

      auto path = get_known_folder(FOLDERID_RoamingAppData);

      path /= "ca2/memory_map";

      return path;

   }

   
   ::file::path dir_system::home()
   {

      return ::get_known_folder(FOLDERID_Profile);

   }





   ::file::path dir::program_data()
   {

      return ::get_known_folder(FOLDERID_ProgramData);

   }


   ::file::path dir::roaming()
   {


      return ::get_known_folder(FOLDERID_RoamingAppData);


   }


   

} // namespace windows



