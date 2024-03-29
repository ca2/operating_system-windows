#pragma once


namespace production
{


   class impact;


   class CLASS_DECL_CA2_PRODUCTION application :
      virtual public ::sphere::application
   {
   public:


      impact * m_pimpact;
      
      
      ::pointer<::user::single_document_template>m_pimpactsystemMain;


      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual void construct();

      virtual void init_instance() override;
      virtual void term_instance() override;

      virtual bool bergedge_start();

      virtual void on_request(::request * prequest) override;

	   virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);
   		

      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::file::item_array & itema);

      production::e_version m_eversion;

   };


} // namespace production


