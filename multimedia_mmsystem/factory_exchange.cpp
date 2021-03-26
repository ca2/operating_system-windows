#include "framework.h"


namespace multimedia
{


   namespace mmsystem
   {


      factory_exchange::factory_exchange(::object * pobject) :
         ::object(pobject)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace mmsystem


} // namespace multimedia


void factory_exchange(::object * pobject)
{

   ::multimedia::mmsystem::factory_exchange factoryexchange(pobject);

}









