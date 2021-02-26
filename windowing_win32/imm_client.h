#pragma once


class CLASS_DECL_WINDOWING_WIN32 imm_client :
   virtual public ::user::text_composition_client
{
public:


   //bool   m_bImeCandidateOpened; // replaced by m_bTextCompositionActive in base class.

   bool                                         m_bImeCancelling;
   


   imm_client();
   virtual ~imm_client();


   virtual void install_message_routing(::channel * pchannel) override;


   DECL_GEN_SIGNAL(_001OnKeyDown);
   DECL_GEN_SIGNAL(_011OnChar);
   DECL_GEN_SIGNAL(_001OnIme);
   DECL_GEN_SIGNAL(_001OnSetFocus);
   DECL_GEN_SIGNAL(_001OnKillFocus);

   virtual int on_text_composition_message(int iMessage);

   virtual void on_text_composition_done() override;

   virtual void on_text_composition(string strMessage);

   virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

   virtual bool is_text_composition_active() const;

   virtual string get_ime_composition() const;

   virtual void clear_ime_composition();


};



