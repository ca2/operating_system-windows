#include "framework.h"


namespace multimedia
{


   namespace xaudio7
   {


      factory_exchange::factory_exchange(::object * pobject) :
         object(papp)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace xaudio7


} // namespace multimedia


void ca2_factory_exchange(::object * pobject)
{

   ::multimedia::xaudio7::factory_exchange factoryexchange(papp);

}









