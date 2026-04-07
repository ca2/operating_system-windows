#include "framework.h"
#include "acme/operating_system.h"


CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);

//CLASS_DECL_ACME HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, const ::scoped_string & scopedstrDesc, ::file::path pathIcon = nullptr, int iIcon = 0);

//const_char_pointer get_cube_app_id();


CLASS_DECL_ACME int ca2_main();


void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);


void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{

   __UNREFERENCED_PARAMETER(uiCode);
   __UNREFERENCED_PARAMETER(ppointers);

}



#undef ___new


CLASS_DECL_ACME bool os_init_application()
{

   return true;

}


//CLASS_DECL_ACME void os_term_application()
//{
//
//
//}


string ca2_command_line(hinstance hinstance)
{

#ifdef CUBE

   string strAppId = get_cube_app_id();

#else

   string strAppId = read_resource_as_string(hinstance, 1, "APPID");

#endif

   if (strAppId.is_empty())
   {

      return "";

   }

   return "app.exe : app=" + strAppId;

}


//
//
//namespace acme
//{
//
//
//   bool application::os_on_start_application()
//   {
//
//      if (!::is_debugger_attached())
//      {
//
//         ::file::path pathObj;
//
//         ::file::path pathLnk;
//
//         pathObj = m_papplication->file().module();
//
//         string strLinkTitle;
//
//         strLinkTitle = m_strAppName;
//
//         strLinkTitle.replace("/", "_");
//         strLinkTitle.replace("\\", "_");
//         strLinkTitle.replace("-", "_");
//
//         pathLnk =          auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";
//
//                  auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->create(pathLnk.folder());
//
//         os_create_link(pathObj, pathLnk, "app=" + m_strAppName);
//
//      }
//
//      return true;
//
//   }
//
//
//} // namespace acme
//


void os_post_quit()
{


}


//
//
//CLASS_DECL_ACME void main_async_runnable(::matter * pobjectTaskParam)
//{
//
//   ::pointer<::matter>pobjectTask = pobjectTaskParam;
//   
//   system()->post_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}

//
//CLASS_DECL_ACME void main_sync_runnable(::matter * pobjectTaskParam, ::time timeTimeout)
//{
//   
//   ::pointer<::matter>pobjectTask = pobjectTaskParam;
//   
//   system()->send_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}




