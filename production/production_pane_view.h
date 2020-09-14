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


      pane_view(::layered * pobjectContext);
      virtual ~pane_view();


      DECL_GEN_SIGNAL(_001OnUserMessage);

      __pointer(::production::document) get_document();

      void on_control_event(::user::control_event * pevent);

      virtual void on_create_impact(::user::impact_data * pcreatordata) override;
      virtual void on_change_cur_sel() override;

      virtual void install_message_routing(::channel * pchannel);

      virtual void update(::update * pupdate) override;
      virtual bool pre_create_window(::user::create_struct& cs);


      void OnFileManagerOpenFile(
      ::filemanager::data * pdata,
      ::file::item_array & itema);

      DECL_GEN_SIGNAL(_001OnMenuMessage);
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      DECL_GEN_SIGNAL(_001OnCreate);
   };


} // namespace production




