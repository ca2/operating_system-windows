#include "framework.h"


namespace multimedia
{


   namespace directsound
   {


      factory_exchange::factory_exchange(::layered * pobjectContext) :
         ::object(pobject)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace directsound


} // namespace multimedia


void ca2_factory_exchange(::layered * pobjectContext)
{

   ::multimedia::directsound::factory_exchange factoryexchange(pobject);

}









