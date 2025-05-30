#include "framework.h"


namespace production
{


   application::application(::particle * pparticle) :
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
      m_pimpact = nullptr;

   }


   void application::construct()
   {

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      add_factory_item <document >();
      add_factory_item <frame >();
      add_factory_item <impact >();
      add_factory_item <pane_impact >();


      if(!::aura::application::init_instance())
         return false;

//      puser->filemanager()->m_strLevelUp = "levelup";


      m_pimpactsystemMain = ___new ::user::single_document_template(
      this,
      "production/frame",
      __type(document),
      __type(frame),
      __type(pane_impact));

      add_document_template(m_pimpactsystemMain);

      return true;

   }


   void application::term_instance()
   {

      int iExitCode = 0;

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


   void application::on_request(::request * prequest)
   {

      string strVersion = pcreate->payload("version");

      if (strVersion == "basis")
      {

         m_eversion = ::production::production::version_basis;

      }
      else
      {

         m_eversion = ::production::production::version_stage;

      }

      m_pimpactsystemMain->do_request(pcreate);

      ::pointer<::user::document>pdocument = ::user::__document(pcreate);

      if(pdocument.is_null())
         return;

      //if (pcreate->has_property("start"))
      //{
      // m_pimpact->make_production();
      //}
      //else if (pcreate->has_property("start_deferred"))
      //{
      // m_pimpact->production_loop(papplication->handler()->m_varTopicQuery["start_deferred"]);
      //}

      m_pimpact->release_production();


   }


   void application::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)

   {
      ::aura::application::route_command(pcommand);
   }





   void application::OnFileManagerOpenFile(
   ::filemanager::data * pdata,
   ::file::item_array & itema)
   {
      __UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         pcontext->os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
      }

   }


} // namespace production


extern "C"
::apex::library * platform_production_get_new_library(::particle * pparticle)
{

   return ___new ::apex::single_application_library < production::application >(pobject, "platform/production");

}


aura_app aura_app_core_hellomultiverse("platform/production", &platform_production_get_new_library);




