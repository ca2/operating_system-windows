#include "framework.h"


namespace multimedia
{


   namespace directsound
   {


      factory_exchange::factory_exchange(::object * pobject) :
         ::object(pobject)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace directsound


} // namespace multimedia


void ca2_factory_exchange(::object * pobject)
{

   ::multimedia::directsound::factory_exchange factoryexchange(pobject);

}









