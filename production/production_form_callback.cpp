#include "framework.h"

namespace production
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   
   void form_callback::update(::user::form * pform, ::update & update)
   {

      __UNREFERENCED_PARAMETER(pform);
      __UNREFERENCED_PARAMETER(ptopic);

   }


   void form_callback::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


} // namespace production
