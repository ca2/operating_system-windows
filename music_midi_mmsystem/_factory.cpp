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
//         factory_exchange::factory_exchange(::object * pobject) :
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


__FACTORY_EXPORT void music_midi_mmsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::music::midi::mmsystem::midi, ::music::midi::midi                   >();

}



