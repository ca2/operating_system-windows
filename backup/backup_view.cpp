#include "framework.h"


namespace backup
{


   view::view(::context_object * pcontextobject) :
      ::object(pobject),
      ::production::view(pobject)
   {

   }


   view::~view()
   {

   }


   ::production::production * view::create_production()
   {

      return new ::backup::backup(get_application());

   }


} // namespace backup





