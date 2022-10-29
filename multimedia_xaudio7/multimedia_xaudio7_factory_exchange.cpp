#include "framework.h"


namespace multimedia
{


   namespace xaudio7
   {


      factory_exchange::factory_exchange(::particle * pparticle) :
         object(papp)
      {

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace xaudio7


} // namespace multimedia


void ca2_factory(::particle * pparticle)
{

   ::multimedia::xaudio7::factory_exchange factoryexchange(papp);

}









