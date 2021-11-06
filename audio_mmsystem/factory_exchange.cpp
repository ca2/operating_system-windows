#include "framework.h"


extern "C"
void audio_mmsystem_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::audio_mmsystem::in, ::wave::in >();

   pfactorymap->create_factory < ::audio_mmsystem::out, ::wave::out >();

}









