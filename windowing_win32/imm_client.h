#pragma once


class CLASS_DECL_WINDOWING_WIN32 imm_client :
   virtual public ::user::text_composition_client,
   virtual public ::channel
{
public:


   //__creatable_from_base(imm_client, ::user::text_composition_client);


   bool                             m_bTextCompositionActive2; // replaced by m_bTextCompositionActive in base class.
   bool                             m_bImeCancelling;
   __pointer(::user::interaction)   m_puserinteraction;


   imm_client();
   virtual ~imm_client();


   virtual void initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction) override;


   DECLARE_MESSAGE_HANDLER(on_message_key_down);
   DECLARE_MESSAGE_HANDLER(_011OnChar);
   DECLARE_MESSAGE_HANDLER(_001OnIme);
   DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
   DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

   virtual int on_text_composition_message(int iMessage);

   virtual void on_text_composition_done() override;

   virtual void on_text_composition(string strMessage);

   virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context) override;

   virtual bool is_text_composition_active() const;

   virtual void set_text_composition_active(bool bActive = true);

   virtual string get_ime_composition() const;

   virtual void clear_ime_composition();


};



//
//
//class CLASS_DECL_WINDOWING_WIN32 imm_client :
//   virtual public ::user::text_composition_client
//{
//public:
//
//
//   //bool   m_bTextCompositionActive; // replaced by m_bTextCompositionActive in base class.
//
//   bool                                         m_bImeCancelling;
//   
//
//
//   imm_client();
//   virtual ~imm_client();
//
//
//   void install_message_routing(::channel * pchannel) override;
//
//
//   DECLARE_MESSAGE_HANDLER(on_message_key_down);
//   DECLARE_MESSAGE_HANDLER(_011OnChar);
//   DECLARE_MESSAGE_HANDLER(_001OnIme);
//   DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
//   DECLARE_MESSAGE_HANDLER(_001OnKillFocus);
//
//   virtual int on_text_composition_message(int iMessage);
//
//   virtual void on_text_composition_done() override;
//
//   virtual void on_text_composition(string strMessage);
//
//   virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;
//
//   virtual bool is_text_composition_active() const;
//
//   virtual string get_ime_composition() const;
//
//   virtual void clear_ime_composition();
//
//
//};
//
//
//
