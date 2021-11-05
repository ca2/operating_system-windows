#include "framework.h"


namespace backup
{


   impact::impact(::object * pobject) :
      ::object(pobject),
      ::production::impact(pobject)
   {

   }


   impact::~impact()
   {

   }


   ::production::production * impact::create_production()
   {

      return new ::backup::backup(get_application());

   }


} // namespace backup





