#include "framework.h"


namespace production
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject)
   {

      m_strAppName         = "production";
      m_strBaseSupportId   = "ca2_production";
      m_bLicense           = false;
      m_pview = nullptr;

   }


   void application::construct()
   {

   }


   application::~application()
   {

   }


   ::estatus application::init_instance()
   {

      create_factory <document >();
      create_factory <frame >();
      create_factory <view >();
      create_factory <pane_view >();


      if(!::aura::application::init_instance())
         return false;

//      User.filemanager()->m_strLevelUp = "levelup";


      m_pdocumenttemplateMain = new ::user::single_document_template(
      this,
      "production/frame",
      __type(document),
      __type(frame),
      __type(pane_view));

      add_document_template(m_pdocumenttemplateMain);

      return true;

   }


   void application::term_instance()
   {

      i32 iExitCode = 0;

      try
      {

         ::aura::application::term_instance();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

   }


   bool application::bergedge_start()
   {

      return true;

   }


   void application::on_request(::create * pcreate)
   {

      string strVersion = pcreate->m_pcommandline->m_varQuery["version"];

      if (strVersion == "basis")
      {

         m_eversion = ::production::production::version_basis;

      }
      else
      {

         m_eversion = ::production::production::version_stage;

      }

      m_pdocumenttemplateMain->do_request(pcreate);

      __pointer(::user::document) pdocument = ::user::__document(pcreate);

      if(pdocument.is_null())
         return;

      //if (pcreate->m_pcommandline->m_varQuery.has_property("start"))
      //{
      // m_pview->make_production();
      //}
      //else if (pcreate->m_pcommandline->m_varQuery.has_property("start_deferred"))
      //{
      // m_pview->production_loop(Application.handler()->m_varTopicQuery["start_deferred"]);
      //}

      m_pview->release_production();


   }


   void application::route_command_message(::user::command * pcommand)

   {
      ::aura::application::route_command_message(pcommand);
   }





   void application::OnFileManagerOpenFile(
   ::filemanager::data * pdata,
   ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         Context.os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
      }

   }


} // namespace production


extern "C"
::aura::library * platform_production_get_new_library(::object * pobject)
{

   return new ::aura::single_application_library < production::application >(pobject, "platform/production");

}


aura_app aura_app_core_hellomultiverse("platform/production", &platform_production_get_new_library);




