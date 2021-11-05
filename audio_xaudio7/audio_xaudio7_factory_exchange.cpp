#include "framework.h"


namespace multimedia
{


   namespace audio_xaudio7
   {


      factory_exchange::factory_exchange(::object * pobject) :
         object(papp),
         ::multimedia::xaudio7::factory_exchange(papp)
      {

         create_factory < in, ::wave::in >();
         create_factory < out, ::wave::out >();

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace audio_xaudio7


} // namespace multimedia


extern "C"
void ca2_factory_exchange(::object * pobject)
{

   ::multimedia::audio_xaudio7::factory_exchange factoryexchange(papp);

}









