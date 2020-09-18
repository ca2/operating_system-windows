#include "framework.h"


namespace multimedia
{


   namespace mmsystem
   {


      factory_exchange::factory_exchange(::layered * pobjectContext) :
         ::object(pobjectContext)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace mmsystem


} // namespace multimedia


void factory_exchange(::layered * pobjectContext)
{

   ::multimedia::mmsystem::factory_exchange factoryexchange(pobjectContext);

}









