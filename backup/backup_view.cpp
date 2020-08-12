#include "framework.h"


namespace backup
{


   view::view(::object * pobject) :
      ::object(pobject),
      ::production::view(pobject)
   {

   }


   view::~view()
   {

   }


   ::production::production * view::create_production()
   {

      return new ::backup::backup(get_context_application());

   }


} // namespace backup





