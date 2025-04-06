#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP form_callback :
      virtual public ::production::form_callback
   {
   public:
      form_callback();
      virtual ~form_callback();

      void update(::user::form * pform, ::update & update);
      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);
   };


} // namespace backup



