#include "framework.h"


namespace backup
{


   impact::impact(::particle * pparticle) :
      ::object(pobject),
      ::production::impact(pobject)
   {

   }


   impact::~impact()
   {

   }


   ::production::production * impact::create_production()
   {

      return ___new ::backup::backup(get_application());

   }


} // namespace backup





