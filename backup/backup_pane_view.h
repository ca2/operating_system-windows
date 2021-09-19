#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP pane_view :
      public ::userex::pane_tab_view,
      public production::form_callback
   {
   public:
      pane_view(::object * pobject);
      virtual ~pane_view();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      void on_create_impact(::user::impact_data * pcreatordata);
      void install_message_routing(::channel * pchannel);

      virtual void handle(::subject * psubject, ::context * pcontext) override;



      DECLARE_MESSAGE_HANDLER(_001OnCreate);

      virtual void handle(::subject * psubject, ::context * pcontext) override;


   };


} // namespace backup



