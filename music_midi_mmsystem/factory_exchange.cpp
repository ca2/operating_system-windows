#include "framework.h"

//
//namespace music
//{
//
//
//   namespace midi
//   {
//
//
//      namespace mmsystem
//      {
//
//
//         factory_exchange::factory_exchange(::layered * pobjectContext) :
//            ::object(pobject),
//            ::multimedia::mmsystem::factory_exchange(pobject)
//         {
//
//            
//
//         }
//
//
//         factory_exchange::~factory_exchange()
//         {
//
//         }
//
//
//      } // namespace mmsystem
//
//
//   } // namespace midi_mmsystem
//
//
//} // namespace music


void music_midi_mmsystem_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::music::midi::mmsystem::midi, ::music::midi::midi                   >();

}



