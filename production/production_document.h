#pragma once


namespace production
{


   class CLASS_DECL_CA2_PRODUCTION document :
      public ::user::document
   {
   public:


      document(::object * pobject);

      DECLARE_MESSAGE_HANDLER(data_on_after_change);

	   virtual bool on_new_document();

   public:
	   virtual ~document();
   #ifdef DEBUG
	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;
   #endif

      bool on_open_document(const var & payloadFile) override;


   };


} // namespace production



