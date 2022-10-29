#include "framework.h"


namespace multimedia
{


   namespace audio_directsound
   {


      factory_exchange::factory_exchange(::particle * pparticle) :
         ::object(pobject),
         ::multimedia::directsound::factory_exchange(pobject)
      {

         create_factory < in, ::wave::in >();
         create_factory < out, ::wave::out >();

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace audio_directsound


} // namespace multimedia


extern "C"
void ca2_factory(::particle * pparticle)
{

   ::multimedia::audio_directsound::factory_exchange factoryexchange(pobject);

}









