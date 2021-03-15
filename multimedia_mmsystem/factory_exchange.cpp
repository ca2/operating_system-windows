#include "framework.h"


namespace multimedia
{


   namespace mmsystem
   {


      factory_exchange::factory_exchange(::context_object * pcontextobject) :
         ::object(pobject)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace mmsystem


} // namespace multimedia


void factory_exchange(::context_object * pcontextobject)
{

   ::multimedia::mmsystem::factory_exchange factoryexchange(pobject);

}









