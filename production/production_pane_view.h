#pragma once


namespace production
{


   class document;


   class CLASS_DECL_CA2_PRODUCTION pane_view :
      public ::userex::pane_tab_view,
      public ::filemanager::callback,
      public ::production::form_callback
   {
   public:


      __pointer(::user::form_view)      m_pviewOptions;


      pane_view(::object * pobject);
      virtual ~pane_view();


      DECLARE_MESSAGE_HANDLER(_001OnUserMessage);

      __pointer(::production::document) get_document();

      void handle(::subject * psubject, ::context * pcontext);

      virtual void on_create_impact(::user::impact_data * pcreatordata) override;
      void on_change_cur_sel() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem);


      void OnFileManagerOpenFile(
      ::filemanager::data * pdata,
      ::file::item_array & itema);

      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
#ifdef DEBUG
      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;
#endif

      DECLARE_MESSAGE_HANDLER(_001OnCreate);
   };


} // namespace production




