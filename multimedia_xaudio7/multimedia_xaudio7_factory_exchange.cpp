#include "framework.h"


namespace multimedia
{


   namespace xaudio7
   {


      factory_exchange::factory_exchange(::layered * pobjectContext) :
         object(papp)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace xaudio7


} // namespace multimedia


void ca2_factory_exchange(::layered * pobjectContext)
{

   ::multimedia::xaudio7::factory_exchange factoryexchange(papp);

}









