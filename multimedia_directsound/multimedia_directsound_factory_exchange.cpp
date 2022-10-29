#include "framework.h"


namespace multimedia
{


   namespace directsound
   {


      factory_exchange::factory_exchange(::particle * pparticle) :
         ::object(pobject)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace directsound


} // namespace multimedia


void ca2_factory(::particle * pparticle)
{

   ::multimedia::directsound::factory_exchange factoryexchange(pobject);

}









