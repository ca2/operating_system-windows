#include "framework.h"


__FACTORY_EXPORT void audio_mmsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::audio_mmsystem::in, ::wave::in >();

   pfactory->add_factory_item < ::audio_mmsystem::out, ::wave::out >();

}









