#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP pane_impact :
      public ::userex::pane_tab_impact,
      public production::form_callback
   {
   public:
      pane_impact(::particle * pparticle);
      virtual ~pane_impact();
#ifdef DEBUG
      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;
#endif

      void on_create_impact(::user::impact_data * pcreatordata);
      void install_message_routing(::channel * pchannel);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;



      DECLARE_MESSAGE_HANDLER(_001OnCreate);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} // namespace backup



