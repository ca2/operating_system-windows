#pragma once

namespace production
{

   class CLASS_DECL_CA2_PRODUCTION form_callback :
      virtual public ::user::form_callback
   {
   public:
      form_callback();
      virtual ~form_callback();

      void update(::user::form * pform, ::update & update);
      virtual void on_control_event(::user::control_event * pevent);
   };

} // namespace production