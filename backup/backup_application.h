#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP application :
      public production::application
   {
   public:


      ::pointer<::user::single_document_template>m_ptemplate_html;


      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual bool initialize_application();
      virtual void term_instance() override;

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

   };


} // namespace backup




