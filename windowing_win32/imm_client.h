#pragma once


#include "apex/message/channel.h"
#include "aura/user/user/text_composition_client.h"


class CLASS_DECL_WINDOWING_WIN32 imm_client :
   virtual public ::user::text_composition_client,
   virtual public ::channel
{
public:


   //__creatable_from_base(imm_client, ::user::text_composition_client);


   bool                             m_bTextCompositionActive2; // replaced by m_bTextCompositionActive in base class.
   bool                             m_bImeCancelling;
   ::pointer<::user::interaction>  m_puserinteraction;


   imm_client();
   virtual ~imm_client();


   virtual void initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction) override;


   DECLARE_MESSAGE_HANDLER(on_message_key_down);
   DECLARE_MESSAGE_HANDLER(_011OnChar);
   DECLARE_MESSAGE_HANDLER(_001OnIme);
   DECLARE_MESSAGE_HANDLER(on_message_set_focus);
   DECLARE_MESSAGE_HANDLER(on_message_kill_focus);

   virtual int on_text_composition_message(int iMessage);

   virtual void on_text_composition_done() override;

   virtual void on_text_composition(const ::scoped_string & scopedstrMessage);

   virtual void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context& actioncontext) override;

   virtual bool is_text_composition_active() const;

   void set_text_composition_active(bool bActive = true) override;

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
//   DECLARE_MESSAGE_HANDLER(on_message_set_focus);
//   DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
//
//   virtual int on_text_composition_message(int iMessage);
//
//   virtual void on_text_composition_done() override;
//
//   virtual void on_text_composition(const ::scoped_string & scopedstrMessage);
//
//   virtual void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) override;
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
